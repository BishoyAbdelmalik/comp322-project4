
/*** fileaccess.c ***/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

/* fileaccess file ...		*/
/* print info on access modes	*/
/*				*/

main(int argc, char *argv[]) 
{
  int errors, k, perm;
  struct stat buf;
  char *p;
  errors = 0;
  for (k = 1; k < argc; k++) {
    /* fetch inode information */
    if (stat(argv[k], &buf) == (-1)) {
      fprintf(stderr, "%s: cannot access %s\n",
                       argv[0], argv[k]);
      errors++;
      continue;
    }
    /* print file permissions */
   
    if (buf.st_mode & 0400)
    printf("read\n");
  else 
    printf("no read\n");   

  }
  if (errors)
    return(1);
  else
    return(0);
}


