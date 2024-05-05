#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 

int main() {
    DIR *dir = opendir("."); 
    struct dirent *dirent;

    if (dir == NULL) {
        printf("There was a problem while opening the directory\n");
        return 1; 
    }

    while ((dirent = readdir(dir)) != NULL) { 
        if (dirent->d_type == DT_REG) { 
            printf("File name: %s\n", dirent->d_name); 
        } else if (dirent->d_type == DT_DIR) { 
            printf("Directory name: %s\n", dirent->d_name); 
        } else {
            printf("Unknown type for: %s\n", dirent->d_name);
        }
    }

    closedir(dir); 
    return 0;
}

