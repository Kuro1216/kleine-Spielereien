#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wiringPi.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>

sem_t *s1, *s2, *s3, *s4, *s5;

void* thread_1(void *empty) {
    while(1) {
        if(digitalRead(23) == 1) {
            sem_post(s2);
            sem_wait(s1);
            sem_wait(s5);
        }
    }
}

void* thread_2(void *pDistance) {
    while(1) {
        sem_wait(s2);

        struct timeval start, end;
        long sec, usec;

        digitalWrite(22,1);
        delay(10);
        digitalWrite(22,0);
        if(gettimeofday(&start, (struct timezone*)0)) {
            printf("error\n");
            exit(1);
        }

        while(digitalRead(21) == 0) {
            if(gettimeofday(&start, (struct timezone*)0)) {
                printf("error\n");
                exit(1);
            }
        }

        while(digitalRead(21) == 1) {
            if(gettimeofday(&end, (struct timezone*)0)) {
                printf("error\n");
                exit(1);
            }
        }
        sec = end.tv_sec - start.tv_sec;
        usec = end.tv_usec - start.tv_usec;

        double diff = ((double)usec - (double)sec) / 1000000;
        *(double*)pDistance = (diff * 34300)/2;

        sem_post(s3);
        sem_post(s4);
    }
}

void* thread_3(void *pDistance) {
    while(1) {
        double distance = *(double*)pDistance;
        sem_wait(s3);
        
        digitalWrite(0, 0);
        digitalWrite(2, 0);
        digitalWrite(3, 0);

        if(distance < 10) {
            digitalWrite(0, 1);
        } else if(distance >= 10 && distance <= 20) {
            digitalWrite(3, 1);
        } else if(distance > 20) {
            digitalWrite(2, 1);
        }

        sem_post(s1);
    }
}

void* thread_4(void *pDistance) {
    while(1) {
        double distance = *(double*)pDistance;
        sem_wait(s4);
        if(distance < 10) {
            softToneWrite(25, 100);
            delay(300);
            softToneWrite(25, 0);
        }
        sem_post(s5);
    }
}

int main(void) {
    int init = 0;
    unsigned int init_2 = 0;
    s1 = (sem_t*)malloc(sizeof(sem_t));
    s2 = (sem_t*)malloc(sizeof(sem_t));
    s3 = (sem_t*)malloc(sizeof(sem_t));
    s4 = (sem_t*)malloc(sizeof(sem_t));
    s5 = (sem_t*)malloc(sizeof(sem_t));

    sem_init(s1, 0, 0);
    sem_init(s2, 0, 0);
    sem_init(s3, 0, 0);
    sem_init(s4, 0, 0);
    sem_init(s5, 0, 0);
    printf("Initialisiert\n");

    int i;

    pthread_t t1, t2, t3, t4;

    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    pinMode(22, OUTPUT); // Trigger US Sensor
	pinMode(25, OUTPUT); // Buzzer

    pinMode(21, INPUT); // US Sensor
    pinMode(23, INPUT); // Echo US Sensor

    pullUpDnControl(22, PUD_OFF); // Trigger
    pullUpDnControl(21, PUD_OFF);
    pullUpDnControl(23, PUD_OFF);

    softToneCreate(25);

    double distance = 500.0; // Entfernung = 5 Meter

    pthread_create(&t1, NULL,thread_1 , NULL);
    pthread_create(&t2, NULL,thread_2 , (void*)&distance);
    pthread_create(&t3, NULL,thread_3 , (void*)&distance);
    pthread_create(&t4, NULL,thread_4 , (void*)&distance);


    printf("Now sleeping\n");
    sleep(15);
    printf("Stopped sleeping\n");

    pthread_cancel(t1);
    pthread_cancel(t2);
    pthread_cancel(t3);
    pthread_cancel(t4);

    digitalWrite(0, 0);
    digitalWrite(2, 0);
    digitalWrite(3, 0);

    digitalWrite(21, 0);
    digitalWrite(22, 0);
    digitalWrite(23, 0);

    softToneWrite(25, 0);

    sem_destroy(s1);
	sem_destroy(s2);
	sem_destroy(s3);
	sem_destroy(s4);
	sem_destroy(s5);

    return 0;
}