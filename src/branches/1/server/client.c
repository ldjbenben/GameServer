#include "unp.h"

#define MAXN 16348

int main(int argc, char** argv)
{
	int i, j, fd, nchildren, nloops, nbytes;
	pid_t pid;
	ssize_t n;
	char request[MAXLINE], reply[MAXN];
	
	if(argc !=6 )
	{
		err_quit("usage: client <hostname or IPaddr> <port> <#children> <#loops/child> <#bytes/request>");
	}
	
	nchildren = atoi(argv[3]);
	nloops = atoi(argv[4]);
	nbytes = atoi(argv[5]);
	snprintf(request, sizeof(request), "%d\n", nbytes); // newline at end
	
	for(i = 0; i < nchildren; i++)
	{
		if((pid = Fork()) == 0) // child process
		{
			for(j = 0; j < nloops; j++)
			{
				fd = Tcp_connect(argv[1], argv[2]);
				Writen(fd, request, strlen(request));
				if((n = Readn(fd, reply, nbytes)) != nbytes)
				{
					err_quit("server returned %d bytes", n);
				}
				Close(fd);	// TIME_WAIT on client, not server
			}
			printf("child %d done\n", i);
			exit(0);
		}
	}
	
	while(wait(NULL) > 0) // now parent waits for all children
	{}
	
	if(errno != ECHILD)
	{
		err_sys("wait error");
	}
	
	exit(0);
}