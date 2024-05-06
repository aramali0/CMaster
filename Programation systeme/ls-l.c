#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main()
{
    char *anme = "simo";
    DIR *dir = opendir(name);
    struct dirent *dirent;
    struct stat db;

    if(dir == NULL)
    {
        perror("Error while opening the directory");
        return 1;
    }

    while((dirent = readdir(dir)) != NULL)
    {
        if(stat(dirent->d_name,&sb) == 0)
        {
            struct passwd *pw = getpwuid(sb.st_uid);
            struct group *gr = getgrgid(sb.st_gid);

            char date[20];
            strftime(date,20,"%Y-%m-%d %H-%M-%S",localtime(&sb.st_ctime));
            printf("Name : %-20 | Type : %s | Size: %ld bytes | Owner: %s | Group: %s | Last Modified: %s | Inode: %ld\n",
            dirent->d_name,
            (S_ISDIR(sb.st_mode)) ? "Directory" : "File",
            sb.st_size,
            pw->pw_name,
            gr-> gr_name,
            date,
            sb.st_ino
            );


        }
    }

    closedir(dir);
    return 0; 
}