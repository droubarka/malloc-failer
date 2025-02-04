
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef SPECIFICLINES
#define SPECIFICLINES
#endif

#ifndef LOGFILE
#define LOGFILE "xmalloc.log"
#endif

static int logfile = -1;

static ssize_t get_index(unsigned int *array, size_t size, unsigned int target)
{
	size_t idx;

	for (idx = 0; idx < size; idx++)
	{
		if (target == array[idx])
		{
			return idx;
		}
	}
	return -1;
}

static void xmalloc_atexit(void)
{
	char *format = "\nxmalloc: note: Log has been successfully saved to %s\n";

	dprintf(2, format, LOGFILE);
	close(logfile);
}

void *xmalloc(size_t xsize, char *file, const char *function, unsigned int line)
{
	unsigned int specific_lines[] = {SPECIFICLINES};
	size_t size = sizeof(specific_lines) / sizeof(unsigned int);

	if (logfile == -1)
	{
		logfile = open(LOGFILE, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (logfile != -1)
			atexit(&xmalloc_atexit);
	}

	char *format = "xmalloc: %s:%s:%u: unable to allocate %zu Bytes\n";

	if (get_index(specific_lines, size, line) != -1)
	{
		dprintf(2, format, file, function, line, xsize);
		if (logfile != -1)
			dprintf(logfile, format, file, function, line, xsize);
		return NULL;
	}
	return malloc(xsize);
}
