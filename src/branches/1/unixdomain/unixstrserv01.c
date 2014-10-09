#include "unp.h"

void sig_chld(int signo);

int main(int argc, char** argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_un cliaddr, servaddr;
	void sig_chld(int);
	listenfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
	
	unlink(UNIXSTR_PATH);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);
	
	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);
	Signal(SIGCHLD, sig_chld);
	
	while(1)
	{
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd, (SA*)&cliaddr, &clilen)) < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				err_sys("accept error");
			}
			
			if((childpid = Fork()) == 0)	// child process
			{
				Close(listenfd); // close listening socket
				str_echo(connfd); // process request
				Close(connfd);
				exit(0);
			}
			
			Close(connfd); // parent closed connected socket
		}
	}
}

void sig_chld(int signo)
{
	pid_t	pid;
	int		stat;
	
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		printf("child %d terminated\n", pid);
	}
	return;
}