#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数代码来之 skynet-src/malloc_hook.c 中 
char *
skynet_strdup(const char *str) {
	size_t sz = strlen(str);
	char * ret = malloc(sz+1); // 修改 skynet_malloc 为 malloc
	memcpy(ret, str, sz+1);
	return ret;
}
