
#ifndef XMALLOC_H
#define XMALLOC_H

#define malloc(size) xmalloc(size, __FILE__, __FUNCTION__, __LINE__) //?

void *xmalloc(size_t xsize, char *file, const char *function, unsigned int line);

#endif
