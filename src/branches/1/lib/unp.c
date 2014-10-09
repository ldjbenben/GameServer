#include "unp.h"


int sock_bind_wild(int sockfd, int family)
{
	socklen_t len;
	
	if(family == AF_INET) /* IPv4 */
	{
		struct sockaddr_in sin;
		
		bzero(&sin, sizeof(len));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = htonl(INADDR_ANY);
		sin.sin_port = htons(0); /* bind ephemeral port */
		
		len = sizeof(sin);
		
		if(bind(sockfd, (struct sockaddr*)&sin, len) < 0)
		{
			return (-1);
		}
		
		if(getsockname(sockfd, (struct sockaddr*)&sin, &len) < 0)
		{
			return (-1);
		}
		
		return (sin.sin_port);
	}
#ifdef	IPV6
	else if(family == AF_INET6)
	{
		struct sockaddr_in6 sin6;
		
		bzero(&sin6, sizeof(sin6));
		sin6.sin_family = AF_INET6;
		sin6.sin6_addr = in6addr_any;
		sin6.sin6_port = htons(0);
		
		len = sizeof(sin6);
		
		if(bind(sockfd, (struct sockaddr*)&sin6, len) < 0)
		{
			return (-1);
		}
		
		if(getsockname(sockfd, (struct sockaddr*)&sin6, &len) < 0)
		{
			return (-1);
		}
		
		return (sin6.sin6_port);
	}
#endif
	return (-1);
}

void sock_set_port(struct sockaddr* sa, unsigned short int port)
{
	if(sa->sa_family == AF_INET)
	{
		((struct sockaddr_in*)sa)->sin_port = port;
	}
	#ifdef	IPV6
	else if(sa->sa_family == AF_INET6)
	{
		((struct sockaddr_in6*)sa)->sin6_port = port;
	}
	#endif
}

int sock_get_port(const struct sockaddr* sa)
{
	if(sa->sa_family == AF_INET)
	{
		return (((struct sockaddr_in*)sa)->sin_port);
	}
	#ifdef	IPV6
	else if(sa->sa_family == AF_INET6)
	{
		return (((struct sockaddr_in6*)sa)->sin6_port);
	}
	#endif
	
	return (-1);
}

void sock_set_addr(struct sockaddr* sa, const void* addr)
{
	if(sa->sa_family == AF_INET)
	{
		struct sockaddr_in *sin = (struct sockaddr_in*)sa;
		memcpy(&(sin->sin_addr), addr, sizeof(struct in_addr));
	}
	#ifdef	IPV6
	else if(sa->sa_family == AF_INET6)
	{
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6*)sa;
		memcpy(&(sin6->sin6_addr), addr, sizeof(struct in6_addr));
	}
	#endif
	
	return;
}

ssize_t	readn(int fd, void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = vptr;
	nleft = n;
	
	while (nleft > 0) 
	{
		if ( (nread = read(fd, ptr, nleft)) < 0) 
		{
			if (errno == EINTR)
			{
				nread = 0;		/* and call read() again */
			}
			else
			{
				return(-1);
			}
		} 
		else if (nread == 0)
		{
			break;				/* EOF */
		}

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft);		/* return >= 0 */
}

ssize_t Readn(int fd, void *ptr, size_t nbytes)
{
	ssize_t	n;

	if ( (n = readn(fd, ptr, nbytes)) < 0)
	{
		err_sys("readn error");
	}
	
	return(n);
}

ssize_t writen(int fd, const void* vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char* ptr;
	
	ptr = vptr;
	nleft = n;
	
	while(nleft > 0)
	{
		if((nwritten = write(fd, ptr, nleft)) <=0)
		{
			if(nwritten < 0 && errno == EINTR)
			{
				nwritten = 0;	// and call write() again
			}
			else
			{
				return (-1);	// error
			}
		}
		
		nleft -= nwritten;
		ptr += nwritten;
	}
	
	return (n);
}

void Writen(int fd, const void* ptr, size_t nbytes)
{
	if(writen(fd, ptr, nbytes) != nbytes)
	{
		err_sys("writen error");
	}
}