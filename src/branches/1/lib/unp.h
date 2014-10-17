#ifndef __unp_h
#define __unp_h

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */
#include 	<pthread.h>

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define	LISTENQ		1024	/* 2nd argument to listen() */

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

/* Define some port number that can be used for our examples */
#define	SERV_PORT		 9877			/* TCP and UDP */

#define UNIXSTR_PATH	"/tmp/unixbind"

typedef void Sigfunc(int);

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

/* Following shortens all the typecasts of pointer arguments: */
#define	SA	struct sockaddr

void err_dump(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_ret(const char *, ...);
void err_sys(const char *, ...);

int		tcp_listen(const char *, const char *, socklen_t *);
int 	tcp_listen(const char *, const char *, socklen_t *);

/* prototypes for our Unix wrapper functions: see {Sec errors} */
void Close(int);
ssize_t	 Read(int, void *, size_t);


/* prototypes for our stdio wrapper functions: see {Sec errors} */
void Fclose(FILE *);
FILE *Fdopen(int, const char *);
char *Fgets(char *, int, FILE *);
FILE *Fopen(const char *, const char *);
void Fputs(const char *, FILE *);
pid_t Fork(void);

/* prototypes for our socket wrapper functions: see {Sec errors} */
int	Socket(int, int, int);
void Bind(int, const struct sockaddr*, socklen_t);
void Listen(int, int);
int	 Accept(int, struct sockaddr*, socklen_t *);
void Connect(int fd, const struct sockaddr*, socklen_t);
void Shutdown(int, int);
void Getsockname(int, struct sockaddr*, socklen_t*);
void Setsockopt(int, int, int, const void *, socklen_t);


int	Tcp_connect(const char *, const char *);
int Tcp_listen(const char *, const char *, socklen_t *);
void	*Malloc(size_t);
void *Calloc(size_t n, size_t size);



/**
 * 在“所有地址”上绑定一个临时的端口号
 * @param socdfd socket标识
 * @param family 协议族
 * @return 返回临时端口号
 */
int sock_bind_wild(int sockfd, int family);
/**
 * 为套接字地址结构设置端口号
 * @param sa 套接字地址结构指针
 * @param port 端口号
 * @return 返回临时端口号
 */
void sock_set_port(struct sockaddr* sa, unsigned short int port);
/**
 * 获取给定套接字地址所绑定的端口号
 * @param sa 套接字地址结构指针
 * @return 端口号
 */
int sock_get_port(const struct sockaddr* sa);
/**
 * 通过点分十进制字符串设置套接字地址值
 * @param sa 套接字地址结构指针
 * @param addr in_addr或in6_addr结构指针
 * @return void
 */
void sock_set_addr(struct sockaddr* sa, const void* addr);
/**
 * 从套接字缓冲区中读取n个字节
 * @param fd 套接字描述符标识
 * @param ptr 保存数据的地址
 * @param nbytes 读取的字节数
 * @return void
 */
ssize_t	 Readn(int fd, void *ptr, size_t nbytes);
ssize_t Readline(int fd, void *ptr, size_t maxlen);
/**
 * 向套接字缓冲区中写入n个字节
 * @param fd 套接字描述符标识
 * @param ptr 要写入的数据地址
 * @param nbytes 写入的字节数
 * @return void
 */
void Writen(int fd, const void* ptr, size_t nbytes);

int	Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);

void Inet_pton(int, const char *, void *);
void str_echo(int);
void str_cli(FILE *, int);

Sigfunc* Signal(int signo, Sigfunc* func);
void sig_chld(int signo);

#endif	/* __unp_h */