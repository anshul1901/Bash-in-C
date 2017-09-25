
void ashLoop();
char *ashRead();
char **ashGetArgs(char *input, char *delim);
void convertCWD(char cwd[]);
int ash_cd(char **args);
int ash_pwd();
int ash_echo(char **args);
int ash_ls(char **args);
void ash_pinfo(char **args);
int ashLaunch(char **args, int bgflag);
int ashExecute(char **args, int bgflag);
void handler2(int sig);
void piping(char **args);

char HOME[100];
int bgcount;
char cwd[200], user[200], hostname[200], displayCWD[100];
