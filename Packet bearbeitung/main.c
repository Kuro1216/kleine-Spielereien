#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pqueue.h"


struct event_t
{
    int type;
    double time;
    long serial;
    struct event_t *next;
};

struct list_t
{
    struct event_t *begin;
    unsigned int entries;
    double time;
    long serial;
} *list = NULL;


void event_initialize();
void del_list();
double randDouble();
long event_store(int,double);
void sort(struct event_t*);
long event_retrieve(int*,double*);
void debug();




void event_initialize()
{
    del_list();

    list = (malloc(sizeof(struct list_t)));
    if(list == NULL)
    {
        printf("LISTE KONNTE NICHT ERSTELLT WERDEN!");
        return;
    }

    list->begin = NULL;
    list->entries = 0;
    list->serial = 1;
    list->time = 0.0;
}

long event_store(int type, double time)
{
    if(list == NULL)
    {
        printf("ES WURDE KEINE LISTE INITIALISIERT");
        return 0;
    }

    struct event_t *event =  malloc(sizeof(struct event_t));
    if(event == 0)
    {
        printf("EVENT KONNTE NICHT ERSTELLT WERDEN!");
        return 0;
    }

    event->type = type;
    event->time = list->time + time;
    event->next = NULL;

    if(list->begin == NULL)
    {
        event->serial = list->serial;
        list->begin = event;
        list->entries++;
        list->serial++;
    }
    else
    {
        event->serial = list->serial;
        sort(event);
        list->entries++;
        list->serial++;
    }

}

long event_retrieve(int *type, double *time)
{
    if(list == 0 || list->begin == 0)
    {
        *type = 0;
        *time = 0;
        return 0;
    }

    long serial;
    struct event_t *event = list->begin;

    list->time = event->time;
    serial = event->serial;

    *type = event->type;
    *time = event->time;

    list->begin = event->next;
    list->entries--;

    free(event);
    return serial;
}

void del_list()
{
    if (list == 0) return;

    struct event_t *current;
    struct event_t *next;

    current = list->begin;

    while (current != 0)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
    list = NULL;
}

void sort(struct event_t *event)
{
    struct event_t *current = list->begin;


    if(event->time < current->time)
    {
        event->next = current;
        list->begin = event;
        return;
    }

    while (current->next)
    {

        if(event->time <= current->next->time)
        {
            event->next = current->next;
            current->next = event;
            return;
        }
        current = current-> next;
    }

    current->next = event;
}


double randDouble()
{
    return (double) rand() / ((double) RAND_MAX + 1.0);
}


void debug()
{
    int a = 0;
    double b = 0.0;

    event_initialize();


    printf("%s\n",event_store(1,1.3) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");
    printf("%s\n",event_store(2,0.1) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");
    printf("%s\n",event_store(3,0.6) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");
    printf("%s\n",event_store(4,0.4) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");
    printf("%s\n",event_store(5,1.2) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");
    printf("%s\n",event_store(6,2.4) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");
    printf("%s\n",event_store(7,0.2) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");
    printf("%s\n",event_store(8,0.7) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");
    printf("%s\n",event_store(9,0.6) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");


    while(list->begin != NULL)
    {
        long c = event_retrieve(&a, &b);
        printf("Das zurückgegebene Packet hat folgende Werte: type: %d  time: %lf serial: %d \n",a,b,c);
    }

    printf("\n%s\n",event_store(10,0.2) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");
    printf("%s\n",event_store(11,0.8) != 0 ? "Event hinzugefügt":"Event nicht hinzugefügt");

    while(list->begin != NULL)
    {
        long c = event_retrieve(&a, &b);
        printf("Das zurückgegebene Packet hat folgende Werte: type: %d  time: %lf serial: %d \n",a,b,c);
    }
}

long speed()
{
    event_initialize();


    int a = 0;
    double b = 0.0;
    unsigned long counter = 0;
    long d =0;
    int i =1;

    time_t start = time(0) + 1;
    while (start > time(0))
    {
        counter++;
        d = event_store(i,randDouble());
        i++;
        long c = event_retrieve(&a, &b);
        counter++;
    }
    return counter;
}



int main()
{
    debug();

    printf("\n Es können %d Events pro Sekunde gespeichert und gelesen werden", speed());


    return 0;
}