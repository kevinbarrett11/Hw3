#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

char **split_strings(char * input){
    char **arr = malloc(8 * sizeof(char *));
    char *tempword;
    int i = 0;

    tempword = strtok(input, " \n");
    while (tempword != NULL) {
        arr[i] = tempword;
        i++;
        tempword = strtok(NULL, " \n");
    }
    arr[i] = NULL;
    return arr;
}

void sigint_handler(){
    printf("caught sigint");
}

int main() {
    char *input = malloc(20);
    char **args;
    int status = 0;

    while(1){

        printf("CS361 >");
        fgets(input, 500, stdin);
        args = split_strings(input);

        signal(SIGINT, sigint_handler);

        if(args[0] == NULL){
            continue;
        }
        if(!strcmp(args[0],"exit")){
            exit(0);
        }

        pid_t forkid = fork();
        if(forkid == 0){
            execvp(args[0], args);
            printf("Error\n");
            exit(1);

        } else {
            wait(NULL);
        }

        if(WIFEXITED(status))
        {
            int stats = WEXITSTATUS(status);
            printf("pid:%d status:%d\n", forkid, stats);
        }

    }
    return 0;
}
