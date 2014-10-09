#include "unp.h"

void str_echo(int sockfd)
{
/*
	long arg1, arg2;
	ssize_t n;
	char line[MAXLINE];
	
	while(1)
	{
			if((n = Readline(sockfd, line, MAXLINE)) == 0)
			{
				return;
			}
			
			if(sscanf(line, "%ld%ld", &arg1, &arg2) == 2)
			{
				snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
			}
			else
			{
				snprintf(line, sizeof(line), "input error\n");
			}
			
			n = strlen(line);
			Writen(sockfd, line, n);
	}
*/

	ssize_t n;
	char buf[MAXLINE];
	
again:
	while((n = read(sockfd, buf, MAXLINE)) > 0)
	{
		Writen(sockfd, buf, n);
	}
	
	if(n < 0 && errno == EINTR)
	{
		goto again;
	}
	else if(n < 0)
	{
		err_sys("str_echo: read error");
	}

}