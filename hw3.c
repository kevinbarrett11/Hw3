#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

//splits the arguments up into a array of strings
char **split_strings(char * input){
    char **arr = malloc(8 * sizeof(char *));  //allocates space for the strings
    char *tempword;  //makes a temp variable to store a word argument
    int i = 0;  //incrimenter

    tempword = strtok(input, " \n"); //gets first word from input passed up from main
    while (tempword != NULL) {  //runs until no more arguments
        arr[i] = tempword; //adds word to array index
        i++;  //inciments
        tempword = strtok(NULL, " \n");  //gets next value until end of input
    }
    arr[i] = NULL; //sets last index to null so it can terminate without error
    return arr;  //returns array of arguments
}

void sigint_handler(){
    printf("caught sigint");
}
void sigtstp_handler(){
    printf("caught sigstp");
}

int main() {
    char *input = malloc(20);  //initializes where we store input
    char **args;  //array of strings for arguments
    int status = 0;  //initializing status

    while(1){  //runs until exited

        printf("CS361 >");  //prints basic prompt
        fgets(input, 500, stdin);  //gets input from terminal
        args = split_strings(input);  //sends it up to function to split commands up

        signal(SIGINT, sigint_handler);  //handles control + C
        signal(SIGTSTP , sigtstp_handler);  //handles control + Z

        if(args[0] == NULL){  //if first argument empty then it restarts while loop asking for input
            continue;
        }
        if(!strcmp(args[0],"exit")){  //if user inputs exit then it exits the program
            exit(0);
        }

        pid_t forkid = fork();  //forks a proccess


        if (forkid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }


        if(forkid == 0){
            execvp(args[0], args); //runs first command and then arguments of the rest
            printf("Error\n");  //if this is reached returns an error
            exit(1);  //exits with one

        } else {
            wait(NULL);  //if in parent process then it waits until child is done
        }

        if(WIFEXITED(status))
        {
            int stats = WEXITSTATUS(status);
            printf("pid:%d status:%d\n", forkid, stats);  //returns proccess id and status
        }

    }
    return 0;
}
