#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h> 
#include <sys/stat.h> 

int main() {
    char *object = "file.txt"; 

    struct stat sb; 

    if (stat(object, &sb) == 0) { 
        if (S_ISREG(sb.st_mode)) {
            if (unlink(object) == 0) { 
                printf("File removed successfully: %s\n", object);
            } else {
                perror("error: unlink file");
            }
        } else if (S_ISDIR(sb.st_mode)) { 
            if (rmdir(object) == 0) { 
                printf("Directory removed successfully: %s\n", object);
            } else {
                perror("error: rmdir file");
            }
        } else {
            printf("Unknown object\n");
        }
    } else {
        perror("error: stat");
    }

    return 0;
}
