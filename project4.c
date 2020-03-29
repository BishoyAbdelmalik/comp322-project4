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
    printf("%d\n",statoutput);// return negative on error
     printf("Information for %s\n",argv[1]);
    printf("---------------------------\n");
    printf("File Size: \t\t%ld bytes\n",fileStat.st_size);
    int fileUID=fileStat.st_uid;
    int fileGID=fileStat.st_gid;
    printf("File uid: \t\t%d\n",fileUID);
    printf("File gid: \t\t%d\n",fileGID);
    struct passwd  *filepasswd=getpwuid(geteuid());
    char *currentUser=filepasswd->pw_name;
    printf("%s\n",currentUser);
    int currentUID=filepasswd->pw_uid;
    int currentGID=filepasswd->pw_gid;

    

    printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    //printf("\n\n%d\n",fileStat.st_mode);
    //printf("\n\n%d\n",S_IRUSR);
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");
 
    printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
    return 0;
}