#pragma once
#include <string.h>
#include <stdlib.h>

static char* tut_concat_path(const char* path1, const char* path2) 
{
    int dest_size = strlen(path1) + strlen(path2) + 1;
    char* dest = (char*)malloc(dest_size);
    dest[0] = '\0';
    strcat_s(dest, dest_size, path1);
    strcat_s(dest, dest_size, path2);
    return dest;
}