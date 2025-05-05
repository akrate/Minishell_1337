#include <dirent.h>
#include <stdio.h>
int main(void)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if(dir == NULL)
    {
        perror("opendir");
        return 1;
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(entry->d_type == DT_REG) // check if it's a regular file
        {
            printf("%s\n", entry->d_name); // print the file name
        }
    }
    closedir(dir); // close the directory stream
}