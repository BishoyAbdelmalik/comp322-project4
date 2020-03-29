#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int returnvalue=0;
    if (argc <=1)
    {
        printf("file name is required\n");
        returnvalue=128;//Invalid argument to exit	
    }else{
        int i;
        for (i = 1; i < argc; i++)
        {
            struct stat fileStat;
            struct passwd  *passwd=getpwuid(geteuid());//geteuid() gets effective UID

            int statoutput;
            int fileNameSize=0;
            int j;
            for (j = 0;argv[i][j] != '\0'; j++,fileNameSize++);
            
            if (argv[i][0]!='/'&&argv[i][0]!='~'){
                char *home = passwd->pw_dir;
                //printf("%s\n%ld\n", home, sizeof(home)+1+ sizeof(argv[i]));
                char *file= NULL;
                //file=(char *)calloc(sizeof(home)*1* sizeof(argv[i]),sizeof(char));
                file=(char *)malloc(strlen(home)+1+ strlen(argv[i]));
                //char *file;
                //printf("\nsize of file %ld\n",sizeof(home)+1+ sizeof(argv[i]));
               
                //printf("\nsize of file %zu\n",strlen(file));
                if (file == NULL) {
                    printf("failed to allocate memory\n");
                    // unless there is some other option available, 
                    // exit the program
                }

                strcat(file, home);
                strcat(file, "/");
                strcat(file, argv[i]);
                //printf("\nsize of file %zu\n",strlen(file));

               
                statoutput=stat(file,&fileStat);
                printf("file %s\n", file);

                // return negative on error
                if(statoutput<0){
                    printf("file %s not found\n", file);
                    returnvalue=1;
                    free(file);
                    continue;
                }
                free(file);
            }else{
                statoutput=stat(argv[i],&fileStat);
                printf("file %s\n", argv[i]);

                // return negative on error
                if(statoutput<0){
                    printf("file %s not found\n", argv[i]);
                    returnvalue=1;
                    continue;
                }
                
            }
            
            
            int fileUID=fileStat.st_uid;//uid of file owner
            int fileGID=fileStat.st_gid;//gid of file owner
            
            int currentUID=passwd->pw_uid;//current user id
            int currentGID=passwd->pw_gid;//current user group id

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
        }
    }
    
    return 0;
}