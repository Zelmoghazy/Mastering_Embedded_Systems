#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include "Platform_Types.h"

/* Overriden by user */
extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

/** environ_
 *    A pointer to a list of environment variables and their values.
 *    For a minimal environment, this empty list is adequate
 */
char *__env[1] = { 0 };
char **environ = __env;

/**
 *  Initialize semihosting features
 *  to use printf
 */
void initialise_monitor_handles()
{
}

/** Process-ID;
 * Minimal implementation, for a system without processes
 */
int _getpid(void)
{
	return 1;
}

/** Send a signal. 
 *  Minimal implementation
 */
int _kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

/** Exit a program without cleaning up files.
 *  If your system doesn’t provide this, it is best to avoid linking with subroutines that require it 
 */
void _exit (int status)
{
	_kill(status, -1);
	while (1) {}		/* Make sure we hang here */
}


/** Close a file.
 *  Minimal implementation:
  */
int _close(int file)
{
	return -1;
}

/** Status of an open file.
 *  For consistency with other minimal implementations, all files are regarded as character special devices. 
 *  The sys/stat.h header file required is distributed in the include subdirectory for this C library.
 */
int _fstat(int file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

/** Query whether output stream is a terminal.
 *   For consistency with the other minimal implementations, which only support output to stdout
 */
int _isatty(int file)
{
	return 1;
}

/** Set position in a file.
 *  Minimal implementation 
 */
int _lseek(int file, int ptr, int dir)
{
	return 0;
}

/** Open a file.
 *  Minimal implementation:
 */
int _open(char *path, int flags, ...)
{
	/* Pretend like we always fail */
	return -1;
}


/** Wait for a child process.
 *  Minimal implementation:  
 */
int _wait(int *status)
{
	errno = ECHILD;
	return -1;
}

/** Remove a file’s directory entry.
 *  Minimal implementation: 
 */
int _unlink(char *name)
{
	errno = ENOENT;
	return -1;
}

/** Timing information for current process. 
 *  Minimal implementation
 */
int _times(struct tms *buf)
{
	return -1;
}

/** Status of a file (by name).
 *  Minimal implementation: 
 */
int _stat(char *file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

/** Establish a new name for an existing file.
 *   Minimal implementation:
 */
int _link(char *old, char *new)
{
	errno = EMLINK;
	return -1;
}

/** Create a new process.
 *  Minimal implementation (for a system without processes) */
int _fork(void)
{
	errno = EAGAIN;
	return -1;
}

/** Transfer control to a new process.
 *  Minimal implementation (for a system without processes) */
int _execve(char *name, char **argv, char **env)
{
	errno = ENOMEM;
	return -1;
}

/**
 * Increase program data space. 
 * As malloc and related functions depend on this, it is useful to have a working implementation.
 * The following suffices for a standalone system; it exploits the symbol _end automatically defined by the GNU linker. 
 */


void *_sbrk(int incr)
{
	extern byte _end;          		/* Defined by the linker */
	extern byte _estack;       		/* Defined by the linker */
	extern uint32 _Min_Stack_Size;  /* Defined by the linker */

	const uint32 stack_limit = (uint32)&_estack - (uint32)&_Min_Stack_Size;
	static byte *heap_end;
	byte *prev_heap_end;

	/* First Initialization  */
	if (heap_end == 0)
	{
		heap_end = &_end;
	}

	prev_heap_end = heap_end;

	/* Protect Stack */
	if (heap_end + incr > stack_limit)
	{
		errno = ENOMEM;
		return (void *)-1;
	}
	heap_end += incr;
	return (void *)prev_heap_end;
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		*ptr++ = __io_getchar();
	}
	return len;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		__io_putchar(*ptr++);
	}
	return len;
}
