#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    struct stat fileStat;
    int statoutput=stat(argv[1],&fileStat);
    //take this out later
    printf("response of stat %d\n",statoutput);// return negative on error
    int fileUID=fileStat.st_uid;//uid of file owner
    int fileGID=fileStat.st_gid;//gid of file owner
    
    struct passwd  *filepasswd=getpwuid(geteuid());//geteuid() gets effective UID
    int currentUID=filepasswd->pw_uid;//current user id
    int currentGID=filepasswd->pw_gid;//current user group id

    printf("File Permissions: \n");
    //check if current user is file owner
    if(currentUID==fileUID){
        printf("Current user is owner: \t");
        printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    }else if (currentGID==fileGID){//check if current user in the same group as 
        printf("Current user is in the same group as file owner: \t");
        printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    }else{//other
        printf("Current user is other: \t");
        printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    }    
    printf( "\n");

    return 0;
}