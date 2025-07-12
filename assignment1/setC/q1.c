#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void count(char *option, char *filename) {
    int charcount = 0, wordcount = 0, linecount = 0;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\nError in opening file %s\n", filename);
        return;
    }

    int ch;
    int in_word = 0;
    while ((ch = fgetc(fp)) != EOF) {
        charcount++;
        if (ch == '\n') {
            linecount++;
        }
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            wordcount++;
        }
    }
    fclose(fp);

    if (strcmp(option, "c") == 0)
        printf("\nTotal number of characters: %d\n", charcount);
    else if (strcmp(option, "w") == 0)
        printf("\nTotal number of words: %d\n", wordcount);
    else if (strcmp(option, "l") == 0)
        printf("\nTotal number of lines: %d\n", linecount);
    else
        printf("Invalid option for count command\n");
}

int main() {
    char buff[80], t1[80], t2[80], t3[80];
    pid_t pid;

    while (1) {
        printf("\nMyShell$ ");
        if (fgets(buff, sizeof(buff), stdin) == NULL) {
            printf("Error reading input\n");
            continue;
        }

        
        buff[strcspn(buff, "\n")] = 0;

        
        int args = sscanf(buff, "%s %s %s", t1, t2, t3);

        if (args < 1) {
            continue; 
        }

        if (strcmp(t1, "pause") == 0) {
            printf("Exiting shell...\n");
            exit(0);
        }

        if (strcmp(t1, "count") == 0) {
            if (args != 3) {
                printf("Usage: count [c|w|l] filename\n");
                continue;
            }
            count(t2, t3);
        } else {
            pid = fork();
            if (pid < 0) {
                perror("Fork failed");
            } else if (pid == 0) {
                
                execlp(t1, t1, t2, t3, (char *)NULL);
                
                printf("Command not found: %s\n", t1);
                exit(1);
            } else {
                
                wait(NULL);
            }
        }
    }
    return 0;
}


