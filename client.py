#!/usr/bin/python
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.


DEFAULT_INSTANTBIRD_REV = "default"
DEFAULT_INSTANTBIRD_L10N_REPO_BASE = 'https://hg.instantbird.org/l10n/'

# URL of the default hg repository to clone for Mozilla.
DEFAULT_MOZILLA_REPO = 'http://hg.mozilla.org/releases/mozilla-release/'
DEFAULT_MOZILLA_L10N_REPO_BASE = 'http://hg.mozilla.org/releases/l10n/mozilla-release/'
DEFAULT_MOZILLA_REV = "FIREFOX_25_0_RELEASE"

# URL of the default hg repository to clone for inspector.
DEFAULT_INSPECTOR_REPO = 'http://hg.mozilla.org/dom-inspector/'
DEFAULT_INSPECTOR_REV = "5e221dff8f93"

import os
import sys
import datetime
from optparse import OptionParser
from shutil import copytree, rmtree

topsrcdir = os.path.dirname(__file__)
if topsrcdir == '':
    topsrcdir = '.'

try:
    from subprocess import call
    from subprocess import check_call
except ImportError:
    import subprocess
    def check_call(*popenargs, **kwargs):
        retcode = subprocess.call(*popenargs, **kwargs)
        if retcode:
            cmd = kwargs.get("args")
            if cmd is None:
                cmd = popenargs[0]
                raise Exception("Command '%s' returned non-zero exit status %i" % (cmd, retcode))

def check_call_noisy(cmd, *args, **kwargs):
    print "Executing command:", cmd
    check_call(cmd, *args, **kwargs)

def do_hg_pull(dir, repository, hg, rev):
    fulldir = os.path.join(topsrcdir, dir)
    # clone if the dir doesn't exist, pull if it does
    if not os.path.exists(fulldir):
        fulldir = os.path.join(topsrcdir, dir)
        check_call_noisy([hg, 'clone', repository, fulldir])
    else:
        if options.verbose:
            cmd = [hg, 'pull', '-v', '-R', fulldir]
        else:
            cmd = [hg, 'pull', '-R', fulldir]
        if repository is not None:
            cmd.append(repository)
        check_call_noisy(cmd)
    # update to specific revision
    if options.clean:
        cmd = [hg, 'update', '-C', '-v', '-r', rev, '-R', fulldir]
    else:
        cmd = [hg, 'update', '-v', '-r', rev, '-R', fulldir]
    check_call_noisy(cmd)
    check_call([hg, 'parent', '-R', fulldir,
                '--template=Updated to revision {node}.\n'])

o = OptionParser(usage="client.py [options] checkout")
o.add_option("-m", "--instantbird-repo", dest="instantbird_repo",
             default=None,
             help="URL of Instantbird hg repository to pull from (default: use hg default in .hg/hgrc)")

o.add_option("-z", "--mozilla-repo", dest="mozilla_repo",
             default=None,
             help="URL of Mozilla repository to pull from (default: use \"" + DEFAULT_MOZILLA_REPO + "\".)")
o.add_option("--skip-instantbird", dest="skip_instantbird",
             action="store_true", default=False,
             help="Skip pulling the Instantbird repository.")
o.add_option("--instantbird-rev", dest="ib_rev",
             default=DEFAULT_INSTANTBIRD_REV,
             help="Revision of Instantbird repository to update to. Default: \"" + DEFAULT_INSTANTBIRD_REV + "\"")

o.add_option("--skip-mozilla", dest="skip_mozilla",
             action="store_true", default=False,
             help="Skip pulling the Mozilla repository.")
o.add_option("--mozilla-rev", dest="mozilla_rev",
             default=DEFAULT_MOZILLA_REV,
             help="Revision of Mozilla repository to update to. Default: \"" + DEFAULT_MOZILLA_REV + "\"")

o.add_option("--inspector-repo", dest="inspector_repo",
             default=None,
             help="URL of DOM inspector repository to pull from (default: use \"" + DEFAULT_INSPECTOR_REPO + "\".)")
o.add_option("--skip-inspector", dest="skip_inspector",
             action="store_true", default=False,
             help="Skip pulling the DOM inspector repository.")
o.add_option("--inspector-rev", dest="inspector_rev",
             default=DEFAULT_INSPECTOR_REV,
             help="Revision of DOM inspector repository to update to. Default: \"" + DEFAULT_INSPECTOR_REV + "\"")

o.add_option("--hg", dest="hg", default=os.environ.get('HG', 'hg'),
             help="The location of the hg binary")
o.add_option("-v", "--verbose", dest="verbose",
             action="store_true", default=False,
             help="Enable verbose output on hg updates")
o.add_option("-C", "--clean", dest="clean",
             action="store_true", default=False,
             help="Override local modifications when upgrading")

o.add_option("--l10n-base-dir", dest="l10n_base_dir",
             default=None,
             help="L10NBASEDIR path (for checkout-l10n)")
o.add_option("--locale", dest="ab_cd",
             default=None,
             help="locale to checkout (for checkout-l10n)")

def fixup_repo_options(options):
    """ Check options.instantbird_repo and options.mozilla_repo values;
    populate mozilla_repo if needed.

    options.instantbird_repo and options.mozilla_repo are normally None.
    This is fine-- our "hg pull" commands will omit the repo URL.
    The exception is the initial checkout, which does an "hg clone"
    for Mozilla.  That command requires a repository URL.
    """

    if (options.instantbird_repo is None
        and not options.skip_instantbird
        and not os.path.exists(os.path.join(topsrcdir, '.hg'))):
        o.print_help()
        print
        print "*** The -m option is required for the initial checkout."
        sys.exit(2)

    # Handle special case: initial checkout of Mozilla.
    if (options.mozilla_repo is None):
        options.mozilla_repo = DEFAULT_MOZILLA_REPO

    # Handle special case: initial checkout of inspector.
    if (options.inspector_repo is None):
        options.inspector_repo = DEFAULT_INSPECTOR_REPO

try:
    (options, (action,)) = o.parse_args()
except ValueError:
    o.print_help()
    sys.exit(2)

fixup_repo_options(options)

if action in ('checkout', 'co'):
    if not options.skip_instantbird:
        do_hg_pull('.', options.instantbird_repo, options.hg, options.ib_rev)
        # Reexecute client.py with --skip-instantbird & exit
        args = sys.argv
        args.insert(1, '--skip-instantbird')
        args.insert(0, sys.executable)
        check_call_noisy(args)
        sys.exit(0)

    if not options.skip_mozilla:
        do_hg_pull('mozilla', options.mozilla_repo, options.hg, options.mozilla_rev)
        check_call_noisy("bash tools/patches/apply-patches.sh", shell=True)

    # Check whether destination directory exists for these extensions.
    if not options.skip_inspector and \
       not os.path.exists(os.path.join(topsrcdir, 'mozilla', 'extensions')):
        # Don't create the directory: Mozilla repository should provide it...
        print >>sys.stderr, "Warning: mozilla/extensions directory does not exist; DOM Inspector could not be checked out."
        # Abort checking out dependent extensions.
        options.skip_inspector = \
            True

    if not options.skip_inspector:
        do_hg_pull(os.path.join('mozilla', 'extensions', 'inspector'), options.inspector_repo, options.hg, options.inspector_rev)
elif action == 'checkout-l10n':
    if options.l10n_base_dir is None or options.ab_cd is None:
        sys.exit("Error: --l10-base-dir and --locale are required")
    l10n_dir = os.path.join(topsrcdir, options.l10n_base_dir)
    ib_l10n_dir = os.path.join(l10n_dir, options.ab_cd)
    do_hg_pull(ib_l10n_dir, DEFAULT_INSTANTBIRD_L10N_REPO_BASE + options.ab_cd,
               options.hg, 'default')
    moz_l10n_dir = os.path.join(l10n_dir, 'moz-' + options.ab_cd)
    do_hg_pull(moz_l10n_dir, DEFAULT_MOZILLA_L10N_REPO_BASE + options.ab_cd,
               options.hg, DEFAULT_MOZILLA_REV)
    for root_dir in ['dom', 'extensions', 'netwerk', 'security', 'toolkit']:
        ib_dir = os.path.join(ib_l10n_dir, root_dir)
        rmtree(ib_dir, True)
        try:
            copytree(os.path.join(moz_l10n_dir, root_dir), ib_dir)
        except OSError:
            if root_dir == 'toolkit':
                raise
            else:
                print "Warning: Error while copying (missing?) directory:", root_dir
else:
    o.print_help()
    sys.exit(2)
