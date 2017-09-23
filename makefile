ash: main.c ashLoop.c ashRead.c ashGetArgs.c convertCWD.c builtin.c ashLaunch.c ash_ls.c ash_pinfo.c ash_redirection.c
	gcc -o ash main.c ashLoop.c ashRead.c ashGetArgs.c convertCWD.c builtin.c ashLaunch.c ash_ls.c ash_pinfo.c ash_redirection.c -I .
