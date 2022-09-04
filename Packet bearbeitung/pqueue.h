//
// Created by Kuro on 05.04.2019.
//

#ifndef PRAKTIKUM_6_PQUEUE_H
#define PRAKTIKUM_6_PQUEUE_H

typedef struct priorityqueue_t priorityqueue_t;
typedef struct pqentry pqentry_t;

priorityqueue_t *queue_create();

void pqueue_instet(priorityqueue_t *pq , char *value , float p);

void pqueue_remove(priorityqueue_t *pq , char *value);

char *pq_extractMin(priorityqueue_t *pq);

void pq_decreaskey(priorityqueue_t *pq, char *value , float p);

void pq_destroy(priorityqueue_t *pq);


#endif //PRAKTIKUM_6_PQUEUE_H
