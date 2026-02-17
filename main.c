#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define START_LOCATION 274
#define END_LOCATION 310

int vgmCorrect(char *file) {
        FILE *src;
        FILE *out;
        unsigned char c;
        int count = 0;


        // Make new file name w/ output directory
        char *subDirOut = "out/";
        size_t srcSize = strlen(file);
        size_t outSize = strlen(subDirOut);
        size_t finalSize = srcSize + outSize;
        char dest[finalSize + 1];
        dest[0] = '\0';
        strcat(dest, subDirOut);
        strcat(dest, file);

        // Append original file name w/ source directory
        char *subDirSrc = "src/";
        srcSize = strlen(file);
        outSize = strlen(subDirSrc);
        finalSize = srcSize + outSize;
        char origin[finalSize + 1];
        origin[0] = '\0';
        strcat(origin, subDirSrc);
        strcat(origin, file);
        
        // Correct VGM File by removing Furnace Headers
        src = fopen(origin, "rb");
        out = fopen(dest, "wb"); // Automatically sets file length to 0 if it exists

        if (src == NULL || out == NULL) {
            printf("Error Opening File.\n");
            if (src != NULL) {
                fclose(src);
            }
            if (out != NULL) {
                fclose(out);
            }
            return 1;
        }
        while(fread(&c, sizeof(char), 1, src) > 0) {
            count++;
            if (count < START_LOCATION || count >= END_LOCATION) {
                fwrite(&c, sizeof(char), 1, out);
            }
        }
        printf("Removed headers for %s\nOutput located at %s\n", file, dest);
        fclose(src);
        fclose(out);
        return 0;
}


int main(void)
{
    DIR *currentDir; 
    struct dirent *entry;
    const char *srcFolder = "src";
    const char *outFolder = "out";

    // Create src and out directories if they dont exist.
    mode_t mode = 0777;

    if (mkdir(srcFolder, mode) == -1 && errno != EEXIST) {
        printf("Error creating directory /src/\n");
        return 1;
    }
    if (mkdir(outFolder, mode) == -1 && errno != EEXIST) {
        printf("Error creating directory /out.\n");
        return 1;
    }
    
    // Check src folder for .vg and run corrections
    const char *targetExt = ".vgm";
    if ((currentDir = opendir("src")) == NULL) {
        printf("Error opening directory.\n");
        return 1;
    }

    while ((entry = readdir(currentDir)) != NULL) {
        const char *extPos = strrchr(entry->d_name, '.');
        if (extPos != NULL) {
            if (strcmp(extPos, targetExt) == 0) {
                if (vgmCorrect(entry->d_name) == 1) {
                    printf("Error handling %s.\n", entry->d_name);
                    continue;
                }
            }
        }
    }

    if (closedir(currentDir) == -1) {
        printf("Error closing directory.\n");
        return 1;
    }
    return 0;
}