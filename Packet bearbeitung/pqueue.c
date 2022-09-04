//
// Created by Kuro on 05.04.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

struct pqentry {
    char *value;
    float p;
    pqentry_t *next;
    pqentry_t *last;
};

struct priorityqueue_t {
    pqentry_t *beginn;
    unsigned int entries;
};


priorityqueue_t *pqueue_create() {
    priorityqueue_t *q;
    q = (priorityqueue_t *) malloc(sizeof(priorityqueue_t));
    if (q == NULL) {
        printf("LISTE HATTE KB");
        exit(99);
    }
    q->beginn = NULL;
    q->entries = 0;
    return q;
}

static void sort(priorityqueue_t *pq, pqentry_t *pqe) {

    pqentry_t *current = pq->beginn;
    if (pqe->p < current->p) {
        pqe->next = current;
        current->last =pqe;
        pq->beginn = pqe;
        return;
    }
    while (current->next) {
        if (pqe->p <= current->next->p) {
            pqe->next = current->next;
            current->next = pqe;
            current->next -> last = pqe;
            pqe->last = current;

            return;
        }
        current = current->next;
    }
    current->next = pqe;
}

void pqueue_insert(priorityqueue_t *pq, char *value, float p) {
    if (pq == NULL) {
        printf("Liste wurde nicht übergeben oder nicht erzeugt");
        exit(80);
    }
    pqentry_t *pqentry = malloc(sizeof(pqentry_t));
    if (pqentry == NULL) {
        printf("Eintrag konnte nicht erstellt werden");
        exit(98);
    }
    pqentry->value = *value;
    pqentry->p = p;
    pqentry->next = NULL;
    pqentry->last = NULL;

    if (pq->beginn == NULL) {
        pq->beginn = pqentry;
        pq->entries++;
    } else {
        sort(pq, pqentry);
        pq->entries++;
    }
}

void pqueue_remove(priorityqueue_t *pq , char *value) {

    pqentry_t *pqentry = pq->beginn;
    while (pqentry->next != NULL) {
        int cut = 1;
        for (int i = 0; value[i] != '/0' && pqentry->value[i] != '\0'; i++) {
            if (value[i] != pqentry->value[i]) {
                cut = 0;
                pqentry = pqentry->next;
                break;
            }
            if (cut) { break; }
        }
        for (int i = 0; value[i] != '/0' && pqentry->value[i] != '\0'; i++) {
            if (value[i] != pqentry->value[i]) {
                printf("value konnte nicht in der Liste gefunden werden");
                break;
            }
        }
        if (pqentry->last = NULL) {
            pq->beginn = pqentry->next;
            pqentry->next->last = NULL ;

        } else {
            pqentry->last->next = pqentry->next;
            pqentry->next->last = pqentry->last;
            free(pqentry);
        }
    }
}



void pq_decreasekey(priorityqueue_t *pq, char *value, float p){
    pqueue_remove(pq, value);
    pqueue_insert(pq, value, p);
}




char *pq_extractMin(priorityqueue_t *pq) {
        if (pq->beginn == NULL) {
            printf("Liste ist leer");
            exit(91);
        }
      char *value;
        value = (char*)malloc(sizeof(pq->beginn->value) + 1);
        for(int i = 0; pq->beginn->value[i] != '\0'; i++)
            value[i] = pq->beginn->value[i];
        pqueue_remove( pq, value);
        return value;
    }









