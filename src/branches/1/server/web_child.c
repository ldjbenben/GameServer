#include "unp.h"

#define MAXN 16384	// max bytes client can request

void web_child(int sockfd)
{
	int ntowrite;
	ssize_t nread;
	char line[MAXLINE], result[MAXN];
	
	while(1)
	{
		if((nread = Readline(sockfd, line, MAXLINE)) == 0)
		{
			return;	/* connection closed by other end */
		}

		ntowrite = atol(line);
		
		if(ntowrite <=0 || (ntowrite > MAXN))
		{
			err_quit("client request for %d bytes", ntowrite);
		}
		Writen(sockfd, line, ntowrite);
	}
}