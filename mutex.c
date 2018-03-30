#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int numThreads = 4; // NÚMERO DE OPERÁRIOS
pthread_t tid[4]; // PONTEIROS DAS THREADS

int count; // VARIÁVEL COMPARTILHADA

pthread_mutex_t mcount; // MUTEX PARA SEÇÃO CRÍTICA

void* Trabalho(void *arg)
{

   unsigned long i = 0;
    
   pthread_mutex_lock(&mcount); // MUTEX QUE SINCRONIZA A ORDEM DE CHAMADA

   count = count + 1;
 
   printf("\n Job %d COMEÇOU\n", count);

   for(i=0; i< 1024;i++);
   
   printf("\n Job %d TERMINOU\n", count);

   pthread_mutex_unlock(&mcount);
   
   return NULL;

}

int main(void)
{
    
	int i;

    // INICIALIZA O MUTEX
    pthread_mutex_init(&mcount,NULL);
	
	// CRIA AS THREADS TRABALHADORAS
    i=0;
    while(i < numThreads)
    {
        pthread_create(&(tid[i]), NULL, &Trabalho, NULL);
        i++;
    }

	// SINCRONIZA AS THREADS TRABALHADORAS
	i=0;
	while(i < numThreads)
    {
        pthread_join(tid[i], NULL);
		i++;
    }
    
	// DESTROI O MUTEX
	pthread_mutex_destroy(&mcount);
	
    return 0;
}
