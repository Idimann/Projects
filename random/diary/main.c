#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void createEntry() {
    time_t t_Time = time(NULL);
    struct tm *tm = localtime(&t_Time);

    char timeArr[64];

    size_t ret = strftime(timeArr, sizeof(timeArr), "%c", tm);

    char time[12];
    char clock[9];

    memcpy(time, timeArr + 4, sizeof(char) * 10);
    memcpy(time + sizeof(char) * 6, timeArr + sizeof(char) * 19, sizeof(char) * 5);

    memcpy(clock, timeArr + sizeof(char) * 11, sizeof(char) * 8);

    time[11] = '\0';
    clock[8] = '\0';

    for(char* c = time; *c != '\0'; c++) {
        if(*c == ' ')
            *c = '_';
    }

    FILE* file;

    if(!access(time, F_OK))
        file = fopen(time, "a");
    else
        file = fopen(time, "w+");

    if(file == NULL) {
        printf("Error opening file!\n");
        free(file);
    }

    char input[1024];

    printf("Close the entry by typing EXIT in all caps\n");

    fprintf(file, "\n%s\n\n", clock);

    do {
        scanf(" %1023[^\n]", input);

        if(!strcmp(input, "EXIT"))
            break;

        fprintf(file, "\t");
        fprintf(file, "%s\n", input);

    } while(1);

    fclose(file);
}

void findEntry() {
    printf("Please input the date in this format <Month>_<Day>_<Year>\nThe month has to be displayed in three letters e.g (July = Jul or January = Jan)\n\n");

    char date[11];
    scanf(" %s", date);

    FILE* file = fopen(date, "r");

    if(file == NULL) {
        printf("Error opening file!\n");
        free(file);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while((read = getline(&line, &len, file)) != -1)
        printf("%s", line);

    if(line)
        free(line);

    fclose(file);
}

void scroll() {
    printf("Enter any character for the next file and e to exit\n");

    DIR* d;
    struct dirent* dir;

    d = opendir(".");

    char input;
    FILE* current;

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    
    if(d) {
         while((dir = readdir(d)) != NULL) {
            if(dir->d_type == DT_REG && strcmp(dir->d_name, "release")) {
                current = fopen(dir->d_name, "r");

                if(current == NULL) {
                    printf("Error opening file!\n");
                    continue;
                }

                while((read = getline(&line, &len, current)) != -1)
                    printf("%s", line);

                getchar();
                scanf(" %c", &input);

                int shouldBreak = 0;

                switch(input) {
                    case 'e':
                        shouldBreak = 1;
                        break;
                }

                if(shouldBreak)
                    break;
            }
        }

        closedir(d);
    }

    if(line)
        free(line);

    if(current)
        fclose(current);
}

int main(int argc, char* argv[]) {
    int input;

    while(1) {
        printf("\nOptions:\n[1]\tCreate Entry\n[2]\tGo to Entry\n[3]\tScroll\n[4]\tExit\n\n");
        scanf(" %i", &input);

        switch(input) {
            case 1:
                createEntry();
                break;
            case 2:
                findEntry();
                break;
            case 3:
                scroll();
                break;
            case 4:
                return 0;
        }
    }

    return 0;
}
