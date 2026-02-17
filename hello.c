#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#define START_LOCATION 274
#define END_LOCATION 310

void vgmCorrect(char *file) {
        FILE *src;
        FILE *newFile;
        unsigned char c;
        int count = 0;
        size_t size = END_LOCATION - START_LOCATION;

        // Make new file name w/ output directory
        char *subdir = "out/";
        size_t srcSize = strlen(file);
        size_t outSize = strlen(subdir);
        size_t finalSize = srcSize + outSize;
        char *newFileName = // allocate memory and add strings together with strcat

        src = fopen(file, "rb");
        newFile = fopen(file, "wb");

        while(fread(&c, sizeof(char), 1, src) > 0) {
            count++;
            if (count < START_LOCATION || count >= END_LOCATION) {
                fwrite(&c, sizeof(char), 1, newFile);
            }
        }
        fclose(src);
        fclose(newFile);
}


int main(void)
{
    DIR *currentDir; 
    struct dirent *entry;
    const char *srcFolder = "src";
    const char *outFolder = "out";
    bool srcExists = false;
    bool outExists = false;

    // Open current directory and check if src and out exist - if not create them
    currentDir = opendir("."); // works similarly to fopen
    if (currentDir == NULL) {
        printf("Error opening directory.\n");
        return 1;
    }

    while ((entry = readdir(currentDir)) != NULL) { // Works simiarly to fread - returns NULL when there are no more entries in the directory
        if (entry->d_type == DT_DIR) {
            if (entry->d_name == srcFolder) {
                srcExists = true;
            }
            if (entry->d_name == outFolder) {
                outExists = true;
            }
        }
    }

    mode_t mode = 0777;

    if (srcExists == false) {
        mkdir(srcFolder, mode);
    } 

    if (outExists == false) {
        mkdir(outFolder, mode);
    } 

    if (closedir(currentDir) == -1) {
        printf("Error closing directory.\n");
        return 1;
    }
    
    // Check src folder for .vgm
    const char *targetExt = ".vgm";
    currentDir = opendir("src");

    while ((entry = readdir(currentDir)) != NULL) {
        const char *extPos = strrchr(entry->d_name, '.');
        if (extPos != NULL) {
            if (strcmp(extPos, targetExt) == 0) {
                vgmCorrect(entry->d_name);
            }
        }
    }

    if (closedir(currentDir) == -1) {
        printf("Error closing directory.\n");
        return 1;
    }
}