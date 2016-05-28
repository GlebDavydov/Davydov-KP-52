#ifndef FS_MODULE_H_INCLUDED
#define FS_MODULE_H_INCLUDED

int dir_exists(const char * dirname);

int dir_printFiles(const char * dirname);

int file_exists(const char * filename);

long long file_getSize(const char * filename);

time_t file_getCreateTime(const char * filename);

int file_create(const char * filename);

int file_remove(const char * filename);

#endif // FS_MODULE_H_INCLUDED
