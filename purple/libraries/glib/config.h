/* config.h.win32.in Merged from two versions generated by configure for gcc and MSVC.  */
/* config.h.  Generated by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */

/* define if asm blocks can use numeric local labels */
/* #undef ASM_NUMERIC_LABELS */

/* poll doesn't work on devices */
#define BROKEN_POLL 1

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Whether to disable memory pools */
/* #undef DISABLE_MEM_POOLS */

/* Whether to enable GC friendliness by default */
/* #undef ENABLE_GC_FRIENDLY_DEFAULT */

/* always defined to indicate that i18n is enabled */
/* #undef ENABLE_NLS */

/* Define the gettext package to be used */
#define GETTEXT_PACKAGE "glib20"

/* Define to the GLIB binary age */
#define GLIB_BINARY_AGE 1601

/* Byte contents of gmutex */
#ifdef XP_MACOSX
#define GLIB_BYTE_CONTENTS_GMUTEX -89,-85,-86,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
#else
/* #undef GLIB_BYTE_CONTENTS_GMUTEX */
#endif

/* Define to the GLIB interface age */
#define GLIB_INTERFACE_AGE 1

/* Define the location where the catalogs will be installed */
#define GLIB_LOCALE_DIR "NONE/share/locale"

/* Define to the GLIB major version */
#define GLIB_MAJOR_VERSION 2

/* Define to the GLIB micro version */
#define GLIB_MICRO_VERSION 1

/* Define to the GLIB minor version */
#define GLIB_MINOR_VERSION 16

/* The size of gmutex, as computed by sizeof. */
#ifdef XP_MACOSX
#define GLIB_SIZEOF_GMUTEX 44
#else
/* #undef GLIB_SIZEOF_GMUTEX */
#endif

/* The size of system_thread, as computed by sizeof. */
#define GLIB_SIZEOF_SYSTEM_THREAD 4

/* alpha atomic implementation */
/* #undef G_ATOMIC_ALPHA */

/* arm atomic implementation */
/* #undef G_ATOMIC_ARM */

/* i486 atomic implementation */
#ifdef XP_MACOSX
/* #undef G_ATOMIC_I486 */
#else
#ifndef _MSC_VER
#define G_ATOMIC_I486 1
#endif /* _MSC_VER */
#endif

/* ia64 atomic implementation */
/* #undef G_ATOMIC_IA64 */

/* powerpc atomic implementation */
/* #undef G_ATOMIC_POWERPC */

/* s390 atomic implementation */
/* #undef G_ATOMIC_S390 */

/* sparcv9 atomic implementation */
/* #undef G_ATOMIC_SPARCV9 */

/* x86_64 atomic implementation */
/* #undef G_ATOMIC_X86_64 */

/* Have inline keyword */
#ifndef _MSC_VER
#define G_HAVE_INLINE 1
#else /* _MSC_VER */
/* #undef G_HAVE_INLINE */
#endif /* _MSC_VER */

/* Have __inline keyword */
#define G_HAVE___INLINE 1

/* Have __inline__ keyword */
#if !defined(_MSC_VER) && !defined(__DMC__)
#define G_HAVE___INLINE__ 1
#else /* _MSC_VER or __DMC__ */
/* #undef G_HAVE___INLINE__ */
#endif /* _MSC_VER or __DMC__ */

/* Source file containing theread implementation */
#ifdef XP_WIN
#define G_THREAD_SOURCE "gthread-win32.c"
#else
#define G_THREAD_SOURCE "gthread-posix.c"
#endif

/* A 'va_copy' style function */
#ifndef _MSC_VER
#define G_VA_COPY va_copy
#else /* _MSC_VER */
/* #undef G_VA_COPY */
#endif /* _MSC_VER */

/* 'va_lists' cannot be copies as values */
/* #undef G_VA_COPY_AS_ARRAY */

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#ifdef XP_MACOSX
#define HAVE_ALLOCA_H 1
#else
/* #undef HAVE_ALLOCA_H */
#endif

/* Define to 1 if you have the `atexit' function. */
#define HAVE_ATEXIT 1

/* Define to 1 if you have the <attr/xattr.h> header file. */
/* #undef HAVE_ATTR_XATTR_H */

/* Define to 1 if you have the `bind_textdomain_codeset' function. */
/* #undef HAVE_BIND_TEXTDOMAIN_CODESET */

/* Define if you have a version of the snprintf function with semantics as
   specified by the ISO C99 standard. */
#ifdef XP_MACOX
#define HAVE_C99_SNPRINTF 1
#else
/* #undef HAVE_C99_SNPRINTF */
#endif

/* Define if you have a version of the vsnprintf function with semantics as
   specified by the ISO C99 standard. */
#ifdef XP_MACOSX
#define HAVE_C99_VSNPRINTF 1
#else
/* #undef HAVE_C99_VSNPRINTF */
#endif

/* define to 1 if Carbon is available */
#ifdef XP_MACOSX
#define HAVE_CARBON 1
#else
/* #undef HAVE_CARBON */
#endif

/* Define to 1 if you have the `chown' function. */
#ifdef XP_MACOSX
#define HAVE_CHOWN 1
#else
/* #undef HAVE_CHOWN */
#endif

/* Define to 1 if you have the `clock_gettime' function. */
/* #undef HAVE_CLOCK_GETTIME */

/* Have nl_langinfo (CODESET) */
#ifdef XP_MACOSX
#define HAVE_CODESET 1
#else
/* #undef HAVE_CODESET */
#endif

/* Define to 1 if you have the <crt_externs.h> header file. */
#ifdef XP_MACOSX
#define HAVE_CRT_EXTERNS_H 1
#else
/* #undef HAVE_CRT_EXTERNS_H */
#endif

/* Define to 1 if you have the `dcgettext' function. */
/* #undef HAVE_DCGETTEXT */

/* Define to 1 if you have the <dirent.h> header file. */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#ifdef XP_MACOSX
#define HAVE_DLFCN_H 1
#else
/* #undef HAVE_DLFCN_H */
#endif

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* define for working do while(0) macros */
#ifndef XP_MACOSX
#define HAVE_DOWHILE_MACROS 1
#else
/* #undef HAVE_DOWHILE_MACROS */
#endif

/* Define to 1 if you have the `endmntent' function. */
/* #undef HAVE_ENDMNTENT */

/* Define if we have FAM */
/* #undef HAVE_FAM */

/* Define to 1 if you have the <fam.h> header file. */
/* #undef HAVE_FAM_H */

/* Define if we have FAMNoExists in fam */
/* #undef HAVE_FAM_NO_EXISTS */

/* Define to 1 if you have the `fchmod' function. */
#ifdef XP_MACOSX
#define HAVE_FCHMOD 1
#else
/* #undef HAVE_FCHMOD */
#endif

/* Define to 1 if you have the `fchown' function. */
#ifdef XP_MACOSX
#define HAVE_FCHOWN 1
#else
/* #undef HAVE_FCHOWN */
#endif

/* Define to 1 if you have the `fdwalk' function. */
/* #undef HAVE_FDWALK */

/* Define to 1 if you have the <float.h> header file. */
#define HAVE_FLOAT_H 1

/* Define to 1 if you have the <fstab.h> header file. */
#ifdef XP_MACOSX
#define HAVE_FSTAB_H 1
#else
/* #undef HAVE_FSTAB_H */
#endif

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if you have the `getc_unlocked' function. */
#ifdef XP_MACOSX
#define HAVE_GETC_UNLOCKED 1
#else
/* #undef HAVE_GETC_UNLOCKED */
#endif

/* Define to 1 if you have the `getgrgid' function. */
#ifdef XP_MACOSX
#define HAVE_GETGRGID 1
#else
/* #undef HAVE_GETGRGID */
#endif

/* Define to 1 if you have the `getmntent_r' function. */
/* #undef HAVE_GETMNTENT_R */

/* Define to 1 if you have the `getmntinfo' function. */
#ifdef XP_MACOSX
#define HAVE_GETMNTINFO 1
#else
/* #undef HAVE_GETMNTINFO */
#endif

/* Define to 1 if you have the `getpagesize' function. */
#if !defined(_MSC_VER) && !defined(__DMC__)
#define HAVE_GETPAGESIZE 1
#else
/* #undef HAVE_GETPAGESIZE */
#endif

/* Define to 1 if you have the `getpwuid' function. */
#ifdef XP_MACOSX
#define HAVE_GETPWUID 1
#else
/* #undef HAVE_GETPWUID */
#endif

/* Define if the GNU gettext() function is already present or preinstalled. */
/* #undef HAVE_GETTEXT */

/* Define to 1 if you have the `gmtime_r' function. */
#ifdef XP_MACOSX
#define HAVE_GMTIME_R 1
#endif

/* define to use system printf */
#ifdef XP_MACOSX
#define HAVE_GOOD_PRINTF 1
#else
/* #undef HAVE_GOOD_PRINTF */
#endif

/* Define to 1 if you have the <grp.h> header file. */
#ifdef XP_MACOSX
#define HAVE_GRP_H 1
#else
/* #undef HAVE_GRP_H */
#endif

/* Define to 1 if you have the `hasmntopt' function. */
/* #undef HAVE_HASMNTOPT */

/* define to support printing 64-bit integers with format I64 */
#ifndef XP_MACOSX
#define HAVE_INT64_AND_I64 1
#else
/* #undef HAVE_INT64_AND_I64 */
#endif

/* Define if you have the 'intmax_t' type in <stdint.h> or <inttypes.h>. */
#ifndef _MSC_VER
#define HAVE_INTMAX_T 1
#else /* _MSC_VER */
/* #undef HAVE_INTMAX_T */
#endif /* _MSC_VER */

/* Define to 1 if you have the <inttypes.h> header file. */
#ifndef _MSC_VER
#define HAVE_INTTYPES_H 1
#else /* _MSC_VER */
/* #undef HAVE_INTTYPES_H */
#endif /* _MSC_VER */

/* Define if <inttypes.h> exists, doesn't clash with <sys/types.h>, and
   declares uintmax_t. */
#ifndef _MSC_VER
#define HAVE_INTTYPES_H_WITH_UINTMAX 1
#else /* _MSC_VER */
/* #undef HAVE_INTTYPES_H_WITH_UINTMAX */
#endif /* _MSC_VER */

/* Define if you have <langinfo.h> and nl_langinfo(CODESET). */
#ifdef XP_MACOSX
#define HAVE_LANGINFO_CODESET 1
#else
/* #undef HAVE_LANGINFO_CODESET */
#endif

/* Define to 1 if you have the <langinfo.h> header file. */
#ifdef XP_MACOSX
#define HAVE_LANGINFO_H 1
#else
/* #undef HAVE_LANGINFO_H */
#endif

/* Define to 1 if you have the `lchown' function. */
#ifdef XP_MACOSX
#define HAVE_LCHOWN 1
#else
/* #undef HAVE_LCHOWN */
#endif

/* Define if your <locale.h> file defines LC_MESSAGES. */
#ifdef XP_MACOSX
#define HAVE_LC_MESSAGES 1
#else
/* #undef HAVE_LC_MESSAGES */
#endif

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the `link' function. */
#ifdef XP_MACOSX
#define HAVE_LINK 1
#else
/* #undef HAVE_LINK */

/* Define to 1 if you have the <linux/inotify.h> header file. */
/* #undef HAVE_LINUX_INOTIFY_H */
#endif

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the `localtime_r' function. */
#ifdef XP_MACOSX
#define HAVE_LOCALTIME_R 1
#else
/* #undef HAVE_LOCALTIME_R */
#endif

/* Define if you have the 'long double' type. */
#define HAVE_LONG_DOUBLE 1

/* Define if you have the 'long long' type. */
#ifndef _MSC_VER
#define HAVE_LONG_LONG 1
#else /* _MSC_VER */
/* #undef HAVE_LONG_LONG */
#endif /* _MSC_VER */

/* define if system printf can print long long */
#define HAVE_LONG_LONG_FORMAT 1

/* Define to 1 if you have the `lstat' function. */
#ifdef XP_MACOSX
#define HAVE_LSTAT 1
#else
/* #undef HAVE_LSTAT */
#endif

/* Define to 1 if you have the <malloc.h> header file. */
#ifndef XP_MACOSX
#define HAVE_MALLOC_H 1
#else
/* #undef HAVE_MALLOC_H */
#endif

/* Define to 1 if you have the `memalign' function. */
/* #undef HAVE_MEMALIGN */

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have a working `mmap' system call. */
#ifdef XP_MACOSX
#define HAVE_MMAP 1
#else
/* #undef HAVE_MMAP */
#endif

/* Define to 1 if you have the <mntent.h> header file. */
/* #undef HAVE_MNTENT_H */

/* Have a monotonic clock */
/* #undef HAVE_MONOTONIC_CLOCK */

/* Define to 1 if you have the `nanosleep' function. */
#ifdef XP_MACOSX
#define HAVE_NANOSLEEP 1
#else
/* #undef HAVE_NANOSLEEP */
#endif

/* Define to 1 if you have the `nl_langinfo' function. */
#ifdef XP_MACOSX
#define HAVE_NL_LANGINFO 1
#else
/* #undef HAVE_NL_LANGINFO */
#endif

/* Have non-POSIX function getgrgid_r */
/* #undef HAVE_NONPOSIX_GETGRGID_R */

/* Have non-POSIX function getpwuid_r */
/* #undef HAVE_NONPOSIX_GETPWUID_R */

/* Define to 1 if you have the `nsleep' function. */
/* #undef HAVE_NSLEEP */

/* Define to 1 if you have the `on_exit' function. */
/* #undef HAVE_ON_EXIT */

/* Define to 1 if you have the `poll' function. */
#ifdef XP_MACOSX
#define HAVE_POLL 1
#else
/* #undef HAVE_POLL */
#endif

/* Have POSIX function getgrgid_r */
#ifdef XP_MACOSX
#define HAVE_POSIX_GETGRGID_R 1
#else
/* #undef HAVE_POSIX_GETGRGID_R */
#endif

/* Have POSIX function getpwuid_r */
#ifdef XP_MACOSX
#define HAVE_POSIX_GETPWUID_R 1
#else
/* #undef HAVE_POSIX_GETPWUID_R */
#endif

/* Define to 1 if you have the `posix_memalign' function. */
/* #undef HAVE_POSIX_MEMALIGN */

/* Have function pthread_attr_setstacksize */
#ifdef XP_MACOSX
#define HAVE_PTHREAD_ATTR_SETSTACKSIZE 1
#else
/* #undef HAVE_PTHREAD_ATTR_SETSTACKSIZE */
#endif

/* Define to 1 if the system has the type `ptrdiff_t'. */
#define HAVE_PTRDIFF_T 1

/* Define to 1 if you have the <pwd.h> header file. */
#ifdef XP_MACOSX
#define HAVE_PWD_H 1
#else
/* #undef HAVE_PWD_H */
#endif

/* Define to 1 if you have the `readlink' function. */
#ifdef XP_MACOSX
#define HAVE_READLINK 1
#else
/* #undef HAVE_READLINK */
#endif

/* Define to 1 if you have the <sched.h> header file. */
#ifdef XP_MACOSX
#define HAVE_SCHED_H 1
#else
/* #undef HAVE_SCHED_H */
#endif

/* Define to 1 if libselinux is available */
/* #undef HAVE_SELINUX */

/* Define to 1 if you have the <selinux/selinux.h> header file. */
/* #undef HAVE_SELINUX_SELINUX_H */

/* Define to 1 if you have the `setenv' function. */
#ifdef XP_MACOSX
#define HAVE_SETENV 1
#else
/* #undef HAVE_SETENV */
#endif

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the `setmntent' function. */
/* #undef HAVE_SETMNTENT */

/* Define to 1 if you have the `snprintf' function. */
#ifndef _MSC_VER
#define HAVE_SNPRINTF 1
#ifdef __DMC__
#define snprintf _snprintf
#endif
#else /* _MSC_VER */
/* #undef HAVE_SNPRINTF */
#endif /* _MSC_VER */

/* Define to 1 if you have the `statfs' function. */
#ifdef XP_MACOSX
#define HAVE_STATFS 1
#else
/* #undef HAVE_STATFS */
#endif

/* Define to 1 if you have the `statvfs' function. */
#ifdef XP_MACOSX
#define HAVE_STATVFS 1
#else
/* #undef HAVE_STATVFS */
#endif

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#ifndef _MSC_VER
#define HAVE_STDINT_H 1
#else /* _MSC_VER */
/* #undef HAVE_STDINT_H */
#endif /* _MSC_VER */

/* Define if <stdint.h> exists, doesn't clash with <sys/types.h>, and 
   declares uintmax_t. */
#ifndef _MSC_VER
#define HAVE_STDINT_H_WITH_UINTMAX 1
#else /* _MSC_VER */
/* #undef HAVE_STDINT_H_WITH_UINTMAX */
#endif /* _MSC_VER */

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `stpcpy' function. */
#ifdef XP_MACOSX
#define HAVE_STPCPY 1
#else
/* #undef HAVE_STPCPY */
#endif

/* Define to 1 if you have the `strcasecmp' function. */
#if !defined(_MSC_VER) && !defined(__DMC__)
#define HAVE_STRCASECMP 1
#else /* _MSC_VER or __DMC__ */
/* #undef HAVE_STRCASECMP */
#endif /* _MSC_VER or __DMC__ */

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#if !defined(_MSC_VER) && !defined(__DMC__)
#define HAVE_STRINGS_H 1
#else /* _MSC_VER or __DMC__ */
/* #undef HAVE_STRINGS_H */
#endif /* _MSC_VER or __DMC__ */

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Have functions strlcpy and strlcat */
#ifdef XP_MACOSX
#define HAVE_STRLCPY 1
#else
/* #undef HAVE_STRLCPY */
#endif

/* Define to 1 if you have the `strncasecmp' function. */
#if !defined(_MSC_VER) && !defined(__DMC__)
#define HAVE_STRNCASECMP 1
#else /* _MSC_VER or __DMC__ */
/* #undef HAVE_STRNCASECMP */
#endif /* _MSC_VER or __DMC__ */

/* Define to 1 if you have the `strsignal' function. */
#ifdef XP_MACOSX
#define HAVE_STRSIGNAL 1
#else
/* #undef HAVE_STRSIGNAL */
#endif

/* Define to 1 if `f_fstypename' is member of `struct statfs'. */
/* #undef HAVE_STRUCT_STATFS_F_FSTYPENAME */

/* Define to 1 if `st_atimensec' is member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_ATIMENSEC */

/* Define to 1 if `st_atim.tv_nsec' is member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_ATIM_TV_NSEC */

/* Define to 1 if `st_blksize' is member of `struct stat'. */
#ifdef XP_MACOSX
#define HAVE_STRUCT_STAT_ST_BLKSIZE 1
#else
/* #undef HAVE_STRUCT_STAT_ST_BLKSIZE */
#endif

/* Define to 1 if `st_blocks' is member of `struct stat'. */
#ifdef XP_MACOSX
#define HAVE_STRUCT_STAT_ST_BLOCKS 1
#else
/* #undef HAVE_STRUCT_STAT_ST_BLOCKS */
#endif

/* Define to 1 if `st_ctimensec' is member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_CTIMENSEC */

/* Define to 1 if `st_ctim.tv_nsec' is member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_CTIM_TV_NSEC */

/* Define to 1 if `st_mtimensec' is member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_MTIMENSEC */

/* Define to 1 if `st_mtim.tv_nsec' is member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC */

/* Define to 1 if you have the `symlink' function. */
#ifdef XP_MACOSX
#define HAVE_SYMLINK 1
#else
/* #undef HAVE_SYMLINK */
#endif

/* Define to 1 if you have the <sys/inotify.h> header file. */
/* #undef HAVE_SYS_INOTIFY_H */

/* Define to 1 if you have the <sys/mntctl.h> header file. */
/* #undef HAVE_SYS_MNTCTL_H */

/* Define to 1 if you have the <sys/mnttab.h> header file. */
/* #undef HAVE_SYS_MNTTAB_H */

/* Define to 1 if you have the <sys/mount.h> header file. */
#ifdef XP_MACOSX
#define HAVE_SYS_MOUNT_H 1
#else
/* #undef HAVE_SYS_MOUNT_H */
#endif

/* Define to 1 if you have the <sys/param.h> header file. */
#if !defined(_MSC_VER) && !defined(__DMC__)
#define HAVE_SYS_PARAM_H 1
#else /* _MSC_VER or __DMC__ */
/* #undef HAVE_SYS_PARAM_H */
#endif /* _MSC_VER or __DMC__ */

/* Define to 1 if you have the <sys/poll.h> header file. */
#ifdef XP_MACOSX
#define HAVE_SYS_POLL_H 1
#else
/* #undef HAVE_SYS_POLL_H */
#endif

/* Define to 1 if you have the <sys/resource.h> header file. */
#ifdef XP_MACOSX
#define HAVE_SYS_RESOURCE_H 1
#else
/* #undef HAVE_SYS_RESOURCE_H */
#endif

/* found fd_set in sys/select.h */
#ifdef XP_MACOSX
#define HAVE_SYS_SELECT_H 1
#else
/* #undef HAVE_SYS_SELECT_H */
#endif

/* Define to 1 if you have the <sys/statfs.h> header file. */
/* #undef HAVE_SYS_STATFS_H */

/* Define to 1 if you have the <sys/statvfs.h> header file. */
#ifdef XP_MACOSX
#define HAVE_SYS_STATVFS_H 1
#else
/* #undef HAVE_SYS_STATVFS_H */
#endif

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/sysctl.h> header file. */
#ifdef XP_MACOSX
#define HAVE_SYS_SYSCTL_H 1
#else
/* #undef HAVE_SYS_SYSCTL_H */
#endif

/* Define to 1 if you have the <sys/times.h> header file. */
#ifdef XP_MACOSX
#define HAVE_SYS_TIMES_H 1
#else
/* #undef HAVE_SYS_TIMES_H */
#endif

/* Define to 1 if you have the <sys/time.h> header file. */
#ifndef _MSC_VER
#define HAVE_SYS_TIME_H 1
#else /* _MSC_VER */
/* #undef HAVE_SYS_TIME_H */
#endif /* _MSC_VER */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/vfstab.h> header file. */
/* #undef HAVE_SYS_VFSTAB_H */

/* Define to 1 if you have the <sys/vfs.h> header file. */
/* #undef HAVE_SYS_VFS_H */

/* Define to 1 if you have the <sys/vmount.h> header file. */
/* #undef HAVE_SYS_VMOUNT_H */

/* Define to 1 if you have the <sys/wait.h> header file. */
#ifdef XP_MACOSX
#define HAVE_SYS_WAIT_H 1
#else
/* #undef HAVE_SYS_WAIT_H */
#endif

/* Define to 1 if you have the <sys/xattr.h> header file. */
#ifdef XP_MACOSX
#define HAVE_SYS_XATTR_H 1
#else
/* #undef HAVE_SYS_XATTR_H */
#endif

/* Define to 1 if you have the `timegm' function. */
#ifdef XP_MACOSX
#define HAVE_TIMEGM 1
#else
/* #undef HAVE_TIMEGM */
#endif

/* Define to 1 if you have the <unistd.h> header file. */
#ifndef _MSC_VER
#define HAVE_UNISTD_H 1
#else /* _MSC_VER */
/* #undef HAVE_UNISTD_H */
#endif /* _MSC_VER */

/* Define if your printf function family supports positional parameters as
   specified by Unix98. */
#ifdef XP_MACOSX
#define HAVE_UNIX98_PRINTF 1
#else
/* #undef HAVE_UNIX98_PRINTF */
#endif

/* Define to 1 if you have the `unsetenv' function. */
#ifdef XP_MACOSX
#define HAVE_UNSETENV 1
#else
/* #undef HAVE_UNSETENV */
#endif

/* Define to 1 if you have the `utimes' function. */
#ifdef XP_MACOSX
#define HAVE_UTIMES 1
#else
/* #undef HAVE_UTIMES */
#endif

/* Define to 1 if you have the `valloc' function. */
#ifdef XP_MACOSX
#define HAVE_VALLOC 1
#else
/* #undef HAVE_VALLOC */
#endif

/* Define to 1 if you have the <values.h> header file. */
#if !defined(_MSC_VER) && !defined(__DMC__)
#define HAVE_VALUES_H 1
#else /* _MSC_VER or __DMC__ */
/* #undef HAVE_VALUES_H */
#endif /* _MSC_VER or __DMC__ */

/* Define to 1 if you have the `vasprintf' function. */
#define HAVE_VASPRINTF 1

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Define to 1 if you have the `vsnprintf' function. */
#ifndef _MSC_VER
#define HAVE_VSNPRINTF 1
#ifdef __DMC__
#define vsnprintf _vsnprintf
#endif
#else /* _MSC_VER */
/* #undef HAVE_VSNPRINTF */
#endif /* _MSC_VER */

/* Define if you have the 'wchar_t' type. */
#define HAVE_WCHAR_T 1

/* Define to 1 if you have the `wcslen' function. */
#define HAVE_WCSLEN 1

/* Define if you have the 'wint_t' type. */
#define HAVE_WINT_T 1

/* Have a working bcopy */
/* #undef HAVE_WORKING_BCOPY */

/* Define to 1 if xattr is available */
#ifdef XP_MACOSX
#define HAVE_XATTR 1
#else
/* #undef HAVE_XATTR */
#endif

#ifdef XP_MACOSX
/* Define to 1 if xattr API uses XATTR_NOFOLLOW */
#define HAVE_XATTR_NOFOLLOW 1
#endif

/* Define to 1 if you have the `_NSGetEnviron' function. */
#ifdef XP_MACOSX
#define HAVE__NSGETENVIRON 1
#else
/* #undef HAVE__NSGETENVIRON */
#endif

/* Do we cache iconv descriptors */
#define NEED_ICONV_CACHE 1

/* didn't find fd_set */
#ifndef XP_MACOSX
#define NO_FD_SET 1
#else
/* #undef NO_FD_SET */
#endif

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* global 'sys_errlist' not found */
#ifndef XP_MACOSX
#define NO_SYS_ERRLIST 1
#else
/* #undef NO_SYS_ERRLIST */
#endif

/* global 'sys_siglist' not found */
#ifndef XP_MACOSX
#define NO_SYS_SIGLIST 1
#else
/* #undef NO_SYS_SIGLIST */
#endif

/* global 'sys_siglist' not declared */
#ifndef XP_MACOSX
#define NO_SYS_SIGLIST_DECL 1
#else
/* #undef NO_SYS_SIGLIST_DECL */
#endif

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "http://bugzilla.gnome.org/enter_bug.cgi?product=glib"

/* Define to the full name of this package. */
#define PACKAGE_NAME "glib"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "glib 2.16.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "glib"

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.16.1"

/* Maximum POSIX RT priority */
#ifdef XP_MACOSX
#define POSIX_MAX_PRIORITY sched_get_priority_max(SCHED_OTHER)
#else
/* #undef POSIX_MAX_PRIORITY */
#endif

/* define if posix_memalign() can allocate any size */
/* #undef POSIX_MEMALIGN_WITH_COMPLIANT_ALLOCS */

/* Minimum POSIX RT priority */
#ifdef XP_MACOSX
#define POSIX_MIN_PRIORITY sched_get_priority_min(SCHED_OTHER)
#else
/* #undef POSIX_MIN_PRIORITY */
#endif

/* The POSIX RT yield function */
#ifdef XP_MACOSX
#define POSIX_YIELD_FUNC sched_yield()
#else
/* #undef POSIX_YIELD_FUNC */
#endif

/* whether realloc (NULL,) works */
#define REALLOC_0_WORKS 1

/* Define if you have correct malloc prototypes */
#ifndef _MSC_VER
#define SANE_MALLOC_PROTOS 1
#else /* _MSC_VER */
/* #undef SANE_MALLOC_PROTOS */
#endif /* _MSC_VER */

/* The size of `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 4

/* The size of `long long', as computed by sizeof. */
#ifndef _MSC_VER
#define SIZEOF_LONG_LONG 8
#else /* _MSC_VER */
#define SIZEOF_LONG_LONG 0
#endif /* _MSC_VER */

/* The size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* The size of `size_t', as computed by sizeof. */
#define SIZEOF_SIZE_T 4

/* The size of `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 4

/* The size of `__int64', as computed by sizeof. */
#ifdef XP_MACOSX
#define SIZEOF___INT64 0
#else
#define SIZEOF___INT64 8
#endif

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Number of arguments to statfs() */
#ifdef XP_MACOSX
#define STATFS_ARGS 2
#else
/* #undef STATFS_ARGS */
#endif

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Using GNU libiconv */
#ifdef XP_MACOSX
#define USE_LIBICONV_GNU 1
#else
/* #undef USE_LIBICONV_GNU */
#endif

/* Using a native implementation of iconv in a separate library */
#ifndef XP_MACOSX
#define USE_LIBICONV_NATIVE 1
#else
/* #undef USE_LIBICONV_NATIVE */
#endif

/* using the system-supplied PCRE library */
/* #undef USE_SYSTEM_PCRE */

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
/* #undef WORDS_BIGENDIAN */

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to long or long long if <inttypes.h> and <stdint.h> don't define. */
#ifndef _MSC_VER
/* #undef intmax_t */
#else /* _MSC_VER */
#define intmax_t __int64
#endif /* _MSC_VER */

/* Define to empty if the C compiler doesn't support this keyword. */
/* #undef signed */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */