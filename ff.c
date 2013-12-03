/*************************************************************************
  > File Name:     ff.c
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  2013/10/31 19:36:18
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef void (*CALL_BACK_FUNC)(char *path,WIN32_FIND_DATA *findData);
int findFiles(char *path, char *extension, CALL_BACK_FUNC func, int);


//sample
void displayFile(char *path, WIN32_FIND_DATA* findData);


int main(int argc, char *argv[]) {
	if(argc < 3) {
		printf("%s [-r] <path> <file extension>", argv[0]);
	} else {
		if(argc > 3)
				printf("\nfound %d files\n", findFiles(argv[2], argv[3], displayFile, 1));
				else
				printf("\nfound %d files\n", findFiles(argv[1], argv[2], displayFile, 0));
	}
	return 0;
}

/**
 * @param path must be in good format like c:\windows\system32\*
 * @param exten must be in good format link .exe
 */
int findFiles(char *path, char *extension,
		CALL_BACK_FUNC func, int isRecuesive) {
	WIN32_FIND_DATA findData;
	HANDLE searchHandle;
	int count = 0;
	int pathLen = strlen(path);
	int extLen = strlen(extension);


	searchHandle = FindFirstFile(path, &findData);
	path[pathLen - 1] = 0;	

	if(searchHandle == INVALID_HANDLE_VALUE) {
		path[pathLen - 1] = '*';	
		return -1;
	}

	do {
		char *fn = findData.cFileName;
		if(strcmp(fn, ".") == 0 || strcmp(fn, "..") == 0)
			continue;
		if((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
			if(isRecuesive) {
				char *subPath = (char*)malloc(sizeof(char) * 
						(pathLen +  strlen(fn) + 2));
				int c;
				strcpy(subPath, path);
				strcat(subPath, fn);
				strcat(subPath, "\\*");
				//printf("subDir:%s\n", subPath);
				c = findFiles(subPath, extension, func, isRecuesive);
				if(c != -1) count += c;
				free(subPath);
			}
		} else if(strcmp(&fn[strlen(fn) - extLen], extension) == 0) {
			count++;
			func(path, &findData);
		}
	} while(FindNextFile(searchHandle, &findData));

	FindClose(searchHandle);
	path[pathLen - 1] = '*';	
	return count;
}

//sample
void displayFile(char *path,WIN32_FIND_DATA *findData) {
	printf("%s%s\n", path, findData->cFileName);
}
