#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pwd.h>
#include<srp.h>


int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <UID>\n",argv[0]);
        return 1;
    }

    int uid = atoi(argv[1]);

    struct passwd *pw;
    struct group *gr;

    if((pw = getpwuid(uid)) != NULL)
    {
        gr = getgrgid(pw->pw_gid);
        printf("name : %s\t group name: %s\n",pw->pw_name,gr->gr_name);
    }
    else{
        printf("User with UID doesnt exist. \n");
    }
}