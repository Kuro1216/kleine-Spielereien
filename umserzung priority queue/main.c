#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <unistd.h>

typedef struct event_t {
    int type;
    double time;
    long serial;
} event_t;

typedef struct node {
    struct event_t *event;
    struct node *next;
} node;

typedef struct packet_t {
    char *name;
    struct queue_t *queue;
} packet_t;

typedef struct queue_t {
    char *name;
    int size;
    int entries;
    double time;
    struct packet_t **packets;
    int read;
    int write;
    long lost;
} queue_t;

struct node *list;
int length;

node *create_node() {
    node *new_node = (node *) malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Out of memory!!! (create_node)\n");
        exit(1);
    }
    new_node->event = NULL;
    new_node->next = NULL;
//    printf("Creating new node... \n");
    return new_node;
}

event_t *create_event(int type, double time, long ID) {
    event_t *new_event = (event_t *) malloc(sizeof(event_t));
    if (new_event == NULL) {
        printf("Out of memory!!! (create_node)\n");
        exit(1);
    }
    new_event->serial = ID;
    new_event->time = time;
    new_event->type = type;
    return new_event;
}

int store_node(struct event_t *input, struct node *parent) {
    if (parent->event == NULL) {
        parent->event = input;
        parent->next = create_node();
//        printf("Input into Parent cause NULL \n");
        return 1;
    }
    if (parent->event->time > input->time) {
        node *tmp = create_node();
        tmp->next = parent->next;
        tmp->event = parent->event;
        parent->event = input;
        parent->next = tmp;
//        printf("Input into Parent cause smaller \n");
    } else if (parent->event->time <= input->time) {
//        printf("Next \n");
        store_node(input, parent->next);
    } else {
//        printf("Fuck\n");
        return 0;
    }
    return 1;
}

void event_initialize() {
    list = create_node();
    length = 0;
}

long event_store(int type, double time) {
    static long currentID = 0;
    if (store_node(create_event(type, time, currentID), list)) {
//        printf("Success! \n\n");
        currentID++;
        return currentID - 1;
    }
    length++;
    return 0;
}

long event_retrieve(int *type, double time) {
    node *index;
    index = list;
//    while (index->event->time <= time) {
//        if (index->next->event == NULL || index == NULL) {
//            return 0;
//        }
//        index = index->next;
//    }
    long id = index->event->serial;
    index = index->next;
    if (index == NULL) {
        return 0;
    }
    list->event = index->event;
    list->next = index->next;
//    printf("Next Event at: %lf\n", index->event->time);
    long res = index->event->serial;
    return res;
}

queue_t *create_queue(char *name, int size) {

    queue_t *q = (queue_t *) malloc(sizeof(queue_t));

    q->name = name;
    q->size = size;
    q->entries = 0;
    q->time = 0.0;
    q->packets = (packet_t **) malloc(sizeof(packet_t) * q->size);
    q->read = 0;
    q->write = 0;
    q->lost = 0;

//    printf("Created queue with memory address: %ld and name %s\n", (long)q, q->name);

    return q;
}

packet_t *create_packet(char *name) {
    packet_t *p = (packet_t *) malloc(sizeof(packet_t));

    p->name = name;

//    printf("Packet with address: %ld created \n", (long)p);

    return p;
}

long total = 0;

int packet_destroy(packet_t *packet) {

    if (packet == NULL) {
        printf("Could not delete Packet! Is empty!\n");
        return 0;
    }

//    printf("Removing %s... ", packet->name);

    free(packet);

//    printf("Success!\n");

    return 1;
}

long queue_store(queue_t *queue, packet_t *packet) {

    if (queue->entries >= queue->size) {
        //printf("Warteschlange %s ist voll! Packet wird entfernt! \n", queue->name);
        packet_destroy(packet);
        queue->lost++;
        return 0;
    }

    queue->entries++;

    queue->packets[queue->write] = packet;

    if (queue->write + 1 == queue->size) {
        queue->write = 0;
    } else {
        queue->write++;
    }

    packet->queue = queue;
    total++;

//    printf("Stored Packet: %s in Queue: %s \n", packet->name, queue->name);

    return total;
}

packet_t *queue_retrieve(queue_t *queue) {

    packet_t *p = queue->packets[queue->read];

    if (p == NULL) {
        printf("Queue is empty!\n");
        return p;
    }

//    printf("Removing %s from queue %s...", p->name, queue->name);

    queue->packets[queue->read] = NULL;

    if (queue->read + 1 == queue->size) {
        queue->read = 0;
    } else {
        queue->read++;
    }
    queue->entries--;

//    printf("Removed\n");

    return p;
}

int queue_destroy(queue_t *queue) {

    if (queue == NULL) {
        printf("Queue doesn't exist!");
        return 0;
    }

    for (int i = 0; i < queue->entries; i++) {
        queue_retrieve(queue);
    }

//    printf("Removing queue %s... ", queue->name);

    free(queue);

//    printf("Success!\n");

    return 1;
}

int main() {
    event_initialize();
    FILE *fp = fopen("data.txt", "w");

    /**
     * Setting parameters
     */
    int queue_size = 20;
    char *name = "packet";
    int *event_type = 0;
    int ankunftCount = 0, verlassenCount = 0, messungCount = 0;
    srand(time(NULL));
    double nextStamp = 0;

    /**
     * Time handling
     */
    double timer = 0.0;
    clock_t begin = clock();
    clock_t end = clock() - begin;

    queue_t *q = create_queue("Kasse 1", queue_size);

    for (int i = 0; i < 10; i ++) {
        event_store(0, 1.0 * ((double)i / 1.1));
        event_store(1, 0.9 * ((double)i / 1.1));
    }
    event_store(2, 0.5);


    packet_t *new, *new2;

    timer = 0.0;

    do {
        if (list->next == NULL) {
            break;
        }
        double next = list->next->event->time;

        if(timer >= list->next->event->time) {
            int currentType = list->next->event->type;
            switch(currentType) {
                case 0:
                    new = create_packet(name);
                    queue_store(q, new);
                    event_retrieve(event_type, timer);
                    nextStamp = timer + 1;
                    event_store(0, nextStamp);
                    printf("Neuer Kunde in Kassen-Schlange eingereiht. \n");

                    ankunftCount++;
                    break;
                case 1:
                    if (q->entries == 0) {
                        event_retrieve(event_type, timer);
                        nextStamp = timer + ((double)(rand() % (12 + 1 - 6) + 6) / 10.0);
                        event_store(1, nextStamp);
                        break;
                    }

                    new2 = queue_retrieve(q);
                    packet_destroy(new2);
                    event_retrieve(event_type, timer);
                    nextStamp = timer + ((double)(rand() % (12 + 1 - 6) + 6) / 10.0);
                    event_store(1, nextStamp);
                    printf("Kunde wurde abgefertigt. \n");

                    verlassenCount++;

                    break;
                case 2:
                    event_retrieve(event_type, timer);
                    event_store(2, timer + 20.0/1000.0);
                    //printf("Queue: %d entries\n", q->entries);
                    messungCount++;
                    fprintf(fp, "%d \n", q->entries);

                    break;
            }
        }

        end = clock();
        timer = (double)(end - begin) / CLOCKS_PER_SEC;

    } while (timer <= 20);

    fclose(fp);

    return 0;
}
