#include "unpthread.h"
#include "pthread08.h"

void* thread_main(void*);

void thread_make(int i)
{	
	Pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *) i);
	return;
}

void* thread_main(void* arg)
{
	int connfd;
	int i = (int) arg;
	void web_child(int);
	
	printf("thread %d starting\n", i);
	while(1)
	{
		Pthread_mutex_lock(&clifd_mutex);
		while(iget == iput)
		{
			pthread_cond_wait(&clifd_cond, &clifd_mutex);
		}
		connfd = clifd[iget];
		if(++iget == MAXNCLI)
		{
			iget = 0;
		}
		Pthread_mutex_unlock(&clifd_mutex);
		tptr[i].thread_count++;
		web_child(connfd);
		Close(connfd);
	}
}