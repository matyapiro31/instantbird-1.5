# Copyright (c) 2012 Mozilla Foundation. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import collections
import gyp
import gyp.common
import sys
import os
import re
import shlex

generator_wants_sorted_dependencies = True

generator_default_variables = {
}
for dirname in ['INTERMEDIATE_DIR', 'SHARED_INTERMEDIATE_DIR', 'PRODUCT_DIR',
                'LIB_DIR', 'SHARED_LIB_DIR']:
  # Some gyp steps fail if these are empty(!).
  generator_default_variables[dirname] = 'dir'
for unused in ['RULE_INPUT_PATH', 'RULE_INPUT_ROOT', 'RULE_INPUT_NAME',
               'RULE_INPUT_DIRNAME', 'RULE_INPUT_EXT',
               'EXECUTABLE_PREFIX', 'EXECUTABLE_SUFFIX',
               'STATIC_LIB_PREFIX', 'STATIC_LIB_SUFFIX',
               'SHARED_LIB_PREFIX', 'SHARED_LIB_SUFFIX',
               'LINKER_SUPPORTS_ICF']:
  generator_default_variables[unused] = ''

COMMON_HEADER = """# This makefile was automatically generated from %(buildfile)s. Please do not edit it directly.
DEPTH		= %(depth)s
topsrcdir	= %(topsrcdir)s
srcdir          = %(srcdir)s
VPATH           = %(srcdir)s

EXTERNALLY_MANAGED_MAKE_FILE := 1

"""

COMMON_FOOTER = """
# Skip rules that deal with regenerating Makefiles from Makefile.in files.
NO_MAKEFILE_RULE = 1
NO_SUBMAKEFILES_RULE = 1

include $(topsrcdir)/config/rules.mk
include $(topsrcdir)/ipc/chromium/chromium-config.mk
include %(common_mk_path)s
"""

COMMON_MK = """# This file was generated by mozmake.py. Do not edit it directly.
ifndef COMMON_MK_INCLUDED
COMMON_MK_INCLUDED := 1

ifdef MOZ_DEBUG
CFLAGS += $(CPPFLAGS_Debug) $(CFLAGS_Debug)
CXXFLAGS += $(CPPFLAGS_Debug) $(CXXFLAGS_Debug)
DEFINES += $(DEFINES_Debug)
LOCAL_INCLUDES += $(INCLUDES_Debug)
ASFLAGS += $(ASFLAGS_Debug)
else # non-MOZ_DEBUG
CFLAGS += $(CPPFLAGS_Release) $(CFLAGS_Release)
CXXFLAGS += $(CPPFLAGS_Release) $(CXXFLAGS_Release)
DEFINES += $(DEFINES_Release)
LOCAL_INCLUDES += $(INCLUDES_Release)
ASFLAGS += $(ASFLAGS_Release)
endif

ifeq (WINNT,$(OS_TARGET))
# These get set via VC project file settings for normal GYP builds.
DEFINES += -DUNICODE -D_UNICODE
LOCAL_INCLUDES += -I"$(MOZ_DIRECTX_SDK_PATH)/include"
endif

# Don't use STL wrappers when compiling Google code.
STL_FLAGS =

# Skip Mozilla-specific include locations.
# Specific GYP files can add them back by adding
# $(DIST)/include to their includes.
INCLUDES = -I. $(LOCAL_INCLUDES)

# Ensure that subdirs for sources get created before compiling
ifdef OBJS
SUB_SRCDIRS := $(addsuffix .dirstamp,$(addprefix $(CURDIR)/,$(sort $(dir $(OBJS)))))
$(OBJS): $(SUB_SRCDIRS)
$(SUB_SRCDIRS):
	$(MKDIR) -p $(dir $@)
	touch $@
endif

# COPY_SRCS get copied to the current directory to be compiled

define COPY_SRC
$(notdir $(1)): $(1)
	$$(INSTALL) $$(IFLAGS1) "$$<" .

endef # COPY_SRC
ifdef COPY_SRCS
GARBAGE += $(notdir $(COPY_SRCS))
$(foreach s,$(COPY_SRCS), $(eval $(call COPY_SRC,$(s))))
endif

# Rules for regenerating Makefiles from GYP files.
Makefile: %(input_gypfiles)s %(generator)s
	$(PYTHON) %(commandline)s

endif
"""

def ensure_directory_exists(path):
  dir = os.path.dirname(path)
  if dir and not os.path.exists(dir):
    os.makedirs(dir)

def GetFlavor(params):
  """Returns |params.flavor| if it's set, the system's default flavor else."""
  flavors = {
    'win32': 'win',
    'darwin': 'mac',
    'sunos5': 'solaris',
    'freebsd7': 'freebsd',
    'freebsd8': 'freebsd',
  }
  flavor = flavors.get(sys.platform, 'linux')
  return params.get('flavor', flavor)


def CalculateVariables(default_variables, params):
  generator_flags = params.get('generator_flags', {})
  default_variables['OS'] = generator_flags.get('os', GetFlavor(params))


def CalculateGeneratorInputInfo(params):
  """Calculate the generator specific info that gets fed to input (called by
  gyp)."""
  generator_flags = params.get('generator_flags', {})
  if generator_flags.get('adjust_static_libraries', False):
    global generator_wants_static_library_dependencies_adjusted
    generator_wants_static_library_dependencies_adjusted = True

def WriteMakefile(filename, data, build_file, depth, topsrcdir, srcdir, relative_path, common_mk_path, extra_data=None):
  if not os.path.isabs(topsrcdir):
    topsrcdir = depth + "/" + topsrcdir
  if not os.path.isabs(srcdir):
    srcdir = depth + "/" + srcdir
  #TODO: should compare with the existing file and not overwrite it if the
  # contents are the same!
  ensure_directory_exists(filename)
  with open(filename, "w") as f:
    f.write(COMMON_HEADER % {'buildfile': build_file,
                             'depth': depth,
                             'topsrcdir': topsrcdir,
                             'srcdir': srcdir})
    for k, v in data.iteritems():
      f.write("%s = %s\n" % (k, " \\\n  ".join([''] + v) if isinstance(v, list) else v))
    f.write(COMMON_FOOTER % {'common_mk_path': common_mk_path})
    if extra_data:
      f.write(extra_data)

def WriteCommonMk(path, build_files, scriptname, commandline):
  with open(path, "w") as f:
    f.write(COMMON_MK % {'input_gypfiles': ' '.join(build_files),
                         'generator': scriptname,
                         'commandline': ' '.join(commandline)})

def striplib(name):
  "Strip lib prefixes from library names."
  if name[:3] == 'lib':
    return name[3:]
  return name

AS_EXTENSIONS = set([
  '.s',
  '.S'
])
CPLUSPLUS_EXTENSIONS = set([
  '.cc',
  '.cpp',
  '.cxx'
])
COMPILABLE_EXTENSIONS = set([
  '.c',
  '.s',
  '.S',
  '.m',
  '.mm'
])
COMPILABLE_EXTENSIONS.update(CPLUSPLUS_EXTENSIONS)

def swapslashes(p):
  "Swap backslashes for forward slashes in a path."
  return p.replace('\\', '/')

def getdepth(s):
  """Given a relative path, return a relative path consisting
  of .. segments that would lead to the parent directory."""
  return "/".join(".." for x in swapslashes(s).split("/") if x)

def Compilable(filename):
  return os.path.splitext(filename)[1] in COMPILABLE_EXTENSIONS

class MakefileGenerator(object):
  def __init__(self, target_dicts, data, options, depth, topsrcdir, relative_topsrcdir, relative_srcdir, output_dir, flavor, common_mk_path):
    self.target_dicts = target_dicts
    self.data = data
    self.options = options
    self.depth = depth
    self.relative_srcdir = swapslashes(relative_srcdir)
    self.topsrcdir = swapslashes(topsrcdir)
    self.relative_topsrcdir = swapslashes(relative_topsrcdir)
    self.srcdir = swapslashes(os.path.join(topsrcdir, relative_srcdir))
    self.output_dir = output_dir
    self.flavor = flavor
    self.common_mk_path = common_mk_path
    # Directories to be built in order.
    self.dirs = []
    # Directories that can be built in any order, but before |dirs|.
    self.parallel_dirs = []
    # Targets that have been processed.
    self.visited = set()
    # Link dependencies.
    self.target_link_deps = {}

  def CalculateMakefilePath(self, build_file, target_name):
    """Determine where to write a Makefile for a given gyp file."""
    rel_path = gyp.common.RelativePath(os.path.dirname(build_file),
                                       self.srcdir)
    # Add a subdir using the build_file name and the target_name.
    rel_path = os.path.join(rel_path,
                             os.path.splitext(os.path.basename(build_file))[0]
                             + "_" + target_name)
    output_file = os.path.join(self.output_dir, rel_path, "Makefile")
    return swapslashes(rel_path), swapslashes(output_file)

  def ProcessTargets(self, needed_targets):
    """
    Put all targets in proper order so that dependencies get built before
    the targets that need them. Targets that have no dependencies
    can get built in parallel_dirs. Targets with dependencies must be in
    dirs, and must also be listed after any of their dependencies.
    """
    for qualified_target in needed_targets:
      if qualified_target in self.visited:
        continue
      self.ProcessTarget(qualified_target)

  def ProcessTarget(self, qualified_target):
    """
    Write a Makefile.in for |qualified_target| and add it to |dirs| or
    |parallel_dirs| as appropriate, after processing all of its
    dependencies.
    """
    spec = self.target_dicts[qualified_target]
    if 'dependencies' in spec and spec['dependencies']:
      for dep in spec['dependencies']:
        if dep not in self.visited:
          self.ProcessTarget(dep)
      dirs = self.dirs
    else:
      # no dependencies
      dirs = self.parallel_dirs
    # Now write a Makefile for this target
    build_file, target, toolset = gyp.common.ParseQualifiedTarget(
      qualified_target)
    build_file = os.path.abspath(build_file)
    rel_path, output_file = self.CalculateMakefilePath(build_file, target)
    subdepth = self.depth + "/" + getdepth(rel_path)
    if self.WriteTargetMakefile(output_file, rel_path, qualified_target, spec, build_file, subdepth):
        # If WriteTargetMakefile returns True, then this is a useful target
      dirs.append(rel_path)
    self.visited.add(qualified_target)

  def WriteTargetMakefile(self, output_file, rel_path, qualified_target, spec, build_file, depth):
    configs = spec['configurations']
    # Update global list of link dependencies.
    if spec['type'] in ('static_library', 'shared_library'):
      self.target_link_deps[qualified_target] = "$(call EXPAND_LIBNAME_PATH,%s,$(DEPTH)/%s/%s)" % (striplib(spec['target_name']), self.relative_srcdir, rel_path)

    data = {}
    #TODO: handle actions/rules/copies
    if 'actions' in spec:
      pass
    if 'rules' in spec:
      pass
    if 'copies' in spec:
      pass
    libs = []
    if 'dependencies' in spec:
      for dep in spec['dependencies']:
        if dep in self.target_link_deps:
          libs.append(self.target_link_deps[dep])
    if libs:
      data['EXTRA_LIBS'] = libs

    # Get DEFINES/INCLUDES
    for configname in sorted(configs.keys()):
      config = configs[configname]
      #XXX: this sucks
      defines = config.get('defines')
      if defines:
        data['DEFINES_%s' % configname] = ["-D%s" % d for d in defines]
      includes = []
      for i in config.get('include_dirs', []):
        # Make regular paths into srcdir-relative paths, leave
        # variable-specified paths alone.
        if i.startswith("$(") or os.path.isabs(i):
          if ' ' in i:
            includes.append('"%s"' % i)
          else:
            includes.append(i)
        else:
          includes.append("$(srcdir)/" + i)
      if includes:
        data['INCLUDES_%s' % configname] = ["-I%s" %i for i in includes]
      #XXX: handle mac stuff?
# we want to use our compiler options in general
#      cflags = config.get('cflags')
#      if cflags:
#        data['CPPFLAGS_%s' % configname] = cflags
#      cflags_c = config.get('cflags_c')
#      if cflags_c:
#        data['CFLAGS_%s' % configname] = cflags_c
#      cflags_cc = config.get('cflags_cc')
#      if cflags_cc:
#        data['CXXFLAGS_%s' % configname] = cflags_cc
# we need to keep pkg-config flags however
      cflags_mozilla = config.get('cflags_mozilla')
      if cflags_mozilla:
        data['CPPFLAGS_%s' % configname] = cflags_mozilla
      asflags_mozilla = config.get('asflags_mozilla')
      if asflags_mozilla:
        data['ASFLAGS_%s' % configname] = asflags_mozilla
    sources = {
      'CPPSRCS': {'exts': CPLUSPLUS_EXTENSIONS, 'files': []},
      'CSRCS': {'exts': ['.c'], 'files': []},
      'CMSRCS': {'exts': ['.m'], 'files': []},
      'CMMSRCS': {'exts': ['.mm'], 'files': []},
      'SSRCS': {'exts': AS_EXTENSIONS, 'files': []},
      }
    copy_srcs = []
    for s in spec.get('sources', []):
      if not Compilable(s):
        continue

      # Special-case absolute paths, they'll get copied into the objdir
      # for compiling.
      if os.path.isabs(s):
        # GNU Make falls down pretty badly with spaces in filenames.
        # Conveniently, using a single-character ? as a wildcard
        # works fairly well.
        copy_srcs.append(s.replace(' ', '?'))
        s = os.path.basename(s)

      ext = os.path.splitext(s)[1]
      for source_type, d in sources.iteritems():
        if ext in d['exts']:
          d['files'].append(s)
          break
      
    for source_type, d in sources.iteritems():
      if d['files']:
        data[source_type] = d['files']

    if copy_srcs:
      data['COPY_SRCS'] = copy_srcs

    if spec['type'] == 'executable':
      data['PROGRAM'] = spec['target_name']
    elif spec['type'] == 'static_library':
      data['LIBRARY_NAME'] = striplib(spec['target_name'])
      data['FORCE_STATIC_LIB'] = 1
    elif spec['type'] in ('loadable_module', 'shared_library'):
      data['LIBRARY_NAME'] = striplib(spec['target_name'])
      data['FORCE_SHARED_LIB'] = 1
    else:
      # Maybe nothing?
      return False
    if self.flavor == 'win':
      top = self.relative_topsrcdir
    else:
      top = self.topsrcdir
    WriteMakefile(output_file, data, build_file, depth, top,
                  # we set srcdir up one directory, since the subdir
                  # doesn't actually exist in the source directory
                  swapslashes(os.path.normpath(os.path.join(top, self.relative_srcdir, os.path.split(rel_path)[0]))),
                  self.relative_srcdir,
                  self.common_mk_path)
    return True

def GenerateOutput(target_list, target_dicts, data, params):
  options = params['options']
  flavor = GetFlavor(params)
  generator_flags = params.get('generator_flags', {})

  # Get a few directories into Mozilla-common naming conventions
  # The root of the source repository.
  topsrcdir = os.path.abspath(options.toplevel_dir)
  # The object directory (root of the build).
  objdir = os.path.abspath(generator_flags['OBJDIR'] if 'OBJDIR' in generator_flags else '.')
  # A relative path from the objdir to the topsrcdir
  relative_topsrcdir = gyp.common.RelativePath(topsrcdir, objdir)
  # The directory containing the gyp file on which gyp was invoked.
  gyp_file_dir = os.path.abspath(os.path.dirname(params['build_files'][0]) or '.')
  # The relative path from topsrcdir to gyp_file_dir
  relative_srcdir = gyp.common.RelativePath(gyp_file_dir, topsrcdir)
  # The relative path from objdir to gyp_file_dir
  srcdir = gyp.common.RelativePath(gyp_file_dir, objdir)
  # The absolute path to the source dir
  abs_srcdir = topsrcdir + "/" + relative_srcdir
  # The path to get up to the root of the objdir from the output dir.
  depth = getdepth(relative_srcdir)
  # The output directory.
  output_dir = os.path.abspath(options.generator_output or '.')
  # The path to the root Makefile
  makefile_path = os.path.join(output_dir, "Makefile")

  def topsrcdir_path(path):
    return "$(topsrcdir)/" + swapslashes(gyp.common.RelativePath(path, topsrcdir))
  def objdir_path(path):
    return "$(DEPTH)/" + swapslashes(gyp.common.RelativePath(path, objdir))

  # Find the list of targets that derive from the gyp file(s) being built.
  needed_targets = set()
  build_files = set()
  for build_file in params['build_files']:
    build_file = os.path.normpath(build_file)
    for target in gyp.common.AllTargets(target_list, target_dicts, build_file):
      needed_targets.add(target)
      build_file_, _, _ = gyp.common.ParseQualifiedTarget(target)
      build_files.add(topsrcdir_path(build_file_))

  common_mk_path = objdir_path(os.path.join(output_dir, "common.mk"))

  generator = MakefileGenerator(target_dicts, data, options, depth, topsrcdir, relative_topsrcdir, relative_srcdir, output_dir, flavor, common_mk_path)
  generator.ProcessTargets(needed_targets)

  # Write the top-level makefile, which simply calls the other makefiles
  topdata = {'DIRS': generator.dirs}
  if generator.parallel_dirs:
    topdata['PARALLEL_DIRS'] = generator.parallel_dirs
  if flavor == 'win':
    top = relative_topsrcdir
    src = srcdir
  else:
    top = topsrcdir
    src = abs_srcdir
  WriteMakefile(makefile_path, topdata, params['build_files'][0],
                depth,
                swapslashes(top),
                swapslashes(src),
                swapslashes(relative_srcdir),
                common_mk_path)
  scriptname = "$(topsrcdir)/media/webrtc/trunk/tools/gyp/pylib/gyp/generator/mozmake.py"
  # Reassemble a commandline from parts so that all the paths are correct
  # NOTE: this MUST match the commandline generated in configure.in!
  # since we don't see --include statements, duplicate them in FORCE_INCLUDE_FILE lines
  # Being in a define, they also get used by the common.mk invocation of gyp so they
  # they don't disappear in the second round of tail-swallowing
  forced_includes = ""
  for option in options.defines:
    if option[:20] == "FORCED_INCLUDE_FILE=":
      forced_includes += "--include=%s" % option[20:]

  commandline = [topsrcdir_path(sys.argv[0]),
                 "--format=mozmake",
                 forced_includes,
                 "--depth=%s" % topsrcdir_path(options.depth),
                 "--generator-output=%s" % objdir_path(options.generator_output),
                 "--toplevel-dir=$(topsrcdir)",
                 "-G OBJDIR=$(DEPTH)"] + \
                 ['-G %s' % g for g in options.generator_flags if not g.startswith('OBJDIR=')] + \
                 ['-D%s' % d for d in options.defines] + \
                 [topsrcdir_path(b) for b in params['build_files']]

  WriteCommonMk(os.path.join(output_dir, "common.mk"),
                build_files,
                scriptname,
                commandline)
