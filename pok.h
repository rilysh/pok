#ifndef POK_H
#define POK_H

#ifndef ARG_SIZE
	#define ARG_SIZE    512
#endif

#define CMD_INSTALL		"install"
#define CMD_REMOVE		"remove"
#define CMD_NOCACHE		"nocache"
#define CMD_LIST		"list"
#define CMD_HELP		"help"

#if defined(__FreeBSD__) || defined(__DragonFly__)
	#define SHELL_PATH      "/bin/tcsh"
	#define POK_INSTALL	    "pkg install "
	#define POK_UNINSTALL   "pkg delete "
	#define POK_CACHE       "pkg autoremove"
	#define POK_LIST        "pkg info"
#elif defined(__OpenBSD__)
	#define SHELL_PATH      "/bin/ksh"
	#define POK_INSTALL     "pkg_add "
	#define POK_UNINSTALL   "pkg_delete "
	#define POK_CACHE       "pkg_delete -a "
	#define POK_LIST        "pkg_info"
#elif defined(__NetBSD__)
/* Assuming pkgin is already installed */
	#define SHELL_PATH      "/bin/sh"
	#define POK_INSTALL     "pkgin install "
	#define POK_UNINSTALL   "pkgin remove "
	#define POK_CACHE       "pkgin clean"
	#define POK_ORPHANS     "pkgin autoremove"
	#define POK_LIST        "pkgin list"
#else
	#error Unsupported OS
#endif

static char pkgs[ARG_SIZE];
static char *args[4];

#endif
