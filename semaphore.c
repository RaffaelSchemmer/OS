#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

int numThreads = 4; // NÚMERO DE OPERÁRIOS
pthread_t tid[4]; // PONTEIROS DAS THREADS

int count; // VARIÁVEL COMPARTILHADA

sem_t scount; // SEMAFORO PARA SEÇÃO CRÍTICA

void* Trabalho(void *arg)
{

   unsigned long i = 0;
   
   sem_wait(&scount); // SEMAFORO QUE SINCRONIZA A ORDEM DE CHAMDA
 
   count = count + 1;
 
   printf("\n Job %d COMEÇOU\n", count);

   for(i=0; i< 1024;i++);
   
   printf("\n Job %d TERMINOU\n", count);

   sem_post(&scount);
   
   return NULL;

}

int main(void)
{
    
    int i;

    sem_init(&scount,0,1); // INICIALIZA O SEMAFORO

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
    
    return 0;
}
