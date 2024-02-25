#include "headers/shell.h"

int is_exit_cmd(char *cmd) {
    
    return (my_strcmp(cmd, "exit") == 0);
}

void handle_setenv_cmd(char *variable, char *value) {
    if (setenv(variable, value, 1) == -1) {
        perror("setenv");
    }
}

void handle_unsetenv_cmd(char *variable) {
    if (unsetenv(variable) == -1) {
        perror("unsetenv");
    }
}


void handle_builtin_cmd(char *cmd, char *arguments[]) {
    char exit_status[10];
    if (is_exit_cmd(cmd)) {
        exit(0);
    } else if (is_cd_cmd(cmd)) {
        handle_cd_cmd(arguments[1]);
    } else if (my_strcmp(cmd, "setenv") == 0) {
        handle_setenv_cmd(arguments[1], arguments[2]);
    } else if (my_strcmp(cmd, "unsetenv") == 0) {
        handle_unsetenv_cmd(arguments[1]);
    } else {
        int i;
        for (i = 0; arguments[i] != NULL; i++) {
            if (my_strcmp(arguments[i], "$?") == 0) {
                
                sprintf(exit_status, "%d", WEXITSTATUS(0));
                arguments[i] = strdup(exit_status);
            } else if (my_strcmp(arguments[i], "$$") == 0) {
                char process_id[10];
                sprintf(process_id, "%d", getpid());
                arguments[i] = strdup(process_id);
            }
        }
        execute_external_cmd(cmd, arguments);
    }
}