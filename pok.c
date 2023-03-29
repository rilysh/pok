#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pok.h"

static void pok_cmd_init(void)
{
	args[0] = SHELL_PATH;
	args[1] = "-c";
	args[2] = pkgs;
	args[3] = NULL;

	memset(pkgs, '\0', sizeof(pkgs));
}

static void pok_install_pkg(char *pkg)
{
	strcat(pkgs, POK_INSTALL);
	strcat(pkgs, pkg);

	execv(SHELL_PATH, args);
}

static void pok_uninstall_pkg(char *pkg)
{
	strcat(pkgs, POK_UNINSTALL);
	strcat(pkgs, pkg);

	execv(SHELL_PATH, args);
}

static void pok_remove_cache(void)
{
	strcat(pkgs, POK_CACHE);
#ifdef __NetBSD__
	strcat(pkgs, POK_ORPHANS);
#endif

	execv(SHELL_PATH, args);
}

static void pok_list_pkg(void)
{
	strcat(pkgs, POK_LIST);

	execv(SHELL_PATH, args);
}

static char *clear_args(int len, char **arg)
{
    char *buf = malloc(ARG_SIZE);
    int i;

    memset(buf, '\0', sizeof(&buf));

    for (i = 2; i < len; i++) {
        if (i != 2 && strcmp(arg[i], " ") != 0)
            strcat(buf, " ");
        strcat(buf, arg[i]);
    }

    return buf;
}

static void help(void)
{
	fprintf(stdout,
			"pok - A wrapper for package managers for BSD\n\n"
			"Usage\n"
			"	install [PKGS]     -- Install a or more packages\n"
			"	remove [PKGS]      -- Remove a or more packages\n"
			"	nocache            -- Clean package cache\n"
			"	list               -- List all packages (not filtered)\n"
		);	
}

static void check_args(int args, char *cmd)
{
	if (args < 3) {
		fprintf(stderr, "Error: Command \"%s\" requires an argument\n", cmd);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		help();
		exit(EXIT_SUCCESS);
	}

	char *buf = clear_args(argc, argv);

	pok_cmd_init();

	if (strcmp(argv[1], CMD_INSTALL) == 0) {
		check_args(argc, CMD_INSTALL);
		pok_install_pkg(buf);
	} else if (strcmp(argv[1], CMD_REMOVE) == 0) {
		check_args(argc, CMD_REMOVE);
		pok_uninstall_pkg(buf);
	} else if (strcmp(argv[1], CMD_NOCACHE) == 0) {
		pok_remove_cache();
	} else if (strcmp(argv[1], CMD_LIST) == 0) {
		pok_list_pkg();
	} else if (strcmp(argv[1], CMD_HELP) == 0) {
		help();
	} else {
		goto unknown;
	}

	free(buf);
	exit(EXIT_SUCCESS);

unknown:
	fprintf(stderr, "Error: Invalid command %s\n", argv[1]);
	free(buf);
	exit(EXIT_FAILURE);
}
