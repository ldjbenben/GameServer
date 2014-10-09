#include "unp.h"

void *Calloc(size_t n, size_t size)
{
	void	*ptr;

	if ( (ptr = calloc(n, size)) == NULL)
		err_sys("calloc error");
	return(ptr);
}

void *Malloc(size_t size)
{
	void	*ptr;

	if ( (ptr = malloc(size)) == NULL)
		err_sys("malloc error");
	return(ptr);
}

void Close(int fd)
{
	if (close(fd) == -1)
	{
		err_sys("close error");
	}
}

pid_t Fork(void)
{
	pid_t	pid;

	if ( (pid = fork()) == -1)
	{
		err_sys("fork error");
	}
	return(pid);
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t		n;

	if ( (n = read(fd, ptr, nbytes)) == -1)
	{
		err_sys("read error");
	}
	return(n);
}