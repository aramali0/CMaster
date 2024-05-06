#include<stdio.h>
#include<stdlib.h>
#include<sys/stat>
int main()
{
    struct stat sb;
    char*path;
    printf("enter the path of th derictory :\n");
    scanf("%s",path);


    if(stat(path,&sb) == -1)
    {
        if(mkdir(path,0700) == -1)
        {
            printf("error while creating derictory");
            return -1;
        }
        printf("derictory created succdully !");
    } 
    else{
        printf("directory already existe");
    }

    return 0; 
}