#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#define MAXSIZE 3

semaphore mutex_sem(1);
semaphore men_waiting_sem(0);


int men_waiting = 0;
int men_using = 0;


void man_wants_to_enter()
{
    mutex_sem.wait();

    if((men_using == MAXSIZE) || women_waiting > 0 || women_using > 0)
    {
            men_waiting++;
        printf("A man has entered the queue to use the bathroom.");
            printf("The number of men waiting to use the bathroom are: ", men_waiting);
            mutex_sem.signal();

            men_waiting_sem.wait();
    }
    else
    {
            men_using++;
        printf("A man has entered the bathroom.");
        printf("The number of men using the bathroom are: ", men_using);    
        mutex_sem.signal();
    }

}

void man_leaves()
{
    mutex_sem.wait();

    men_using--;
    printf("A man has exited the bathroom.");
    printf("The number of men using the bathroom is: ", men_using);

    if((women_waiting > 0) && (men_using == 0))
    {
            while((women_waiting > 0) && (women_using != MAXSIZE))
            {
                women_waiting--;
            printf("A woman has exited the queue to use the bathroom.");
            printf("The number of women waiting to use the bathroom are: ", women_waiting);
                women_using++;
            printf("A woman has entered the bathroom.");
            printf("The number of women using the bathroom are: ", women_using);
                women_waiting_sem.signal();
            }
    }
    else if((men_waiting > 0) && (women_waiting == 0))
    {
            men_waiting--;
        printf("A man has exited the queue to use the bathroom.");
        printf("The number of men waiting to use the bathroom are: ", men_waiting);
            men_using++;
        printf("A man has entered the bathroom.");
        printf("The number of men using the bathroom is: ", men_using);
            men_waiting_sem.signal();
    }
    else
    {
            cout << "None shall pass." << endl;
    }

    mutex_sem.signal();
}



void main()
{
    int i;


    printf("Please enter the number of cycles you want the program to continue: ", i);
        scanf("%d",&i);

    for(i = 0; i <= 20; i++)
    { 
        srand(time(NULL));
        int enterleave = (rand()%2)+1;

        switch(enterleave)
        {
            case 1:
                srand(time(NULL));
                int man = (rand()%2)+1;

                switch(man)
                {
                    case 1:
                        printf("A man wants to enter the bathroom.");
                        man_wants_to_enter();
                        break;
                   
                    default;
                }
                    break;

            case 2: 
                switch(man)
                {
                    case 1:
                        printf("A man has left the bathroom.");
                        man_leaves();
                        break;
                  
                    default;
                }
                    break;

            default:printf("There is no one using the bathroom!");
        }
    }
}
