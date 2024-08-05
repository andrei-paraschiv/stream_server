// #include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#include "defines.h"

struct thread_request_t {
    uint32_t request;
    struct sockaddr_in cliaddr;
};

struct thread_request_queue_t {
    struct thread_request_t requests[REQUEST_QUEUE_SIZE];
    uint8_t head, tail;
    pthread_mutex_t mutex;
};

struct server_thread_t {
    pthread_t thread;
    struct thread_request_queue_t queue;
};

int init();
void *thread_run(void * ptr);

struct server_thread_t threads[MAX_THREADS];
in_addr_t cliaddrs[MAX_CLIENTS];
in_port_t cliports[MAX_CLIENTS];

int sockfd;

int main (int argc, char *argv[]) { 
    if (init()) return 1;

    struct sockaddr_in cliaddr;
    uint8_t request[REQUEST_SIZE];
    time_t curr_time, prev_time;
    while(1) {
        time(&curr_time);
        if (curr_time - prev_time > TIMEOUT) { // do rollover check in Y2038 lol
            // TODO: do timeout checking
            prev_time = curr_time;
        }
        
        int num_bytes_recv = recvfrom(sockfd, request, REQUEST_SIZE, 0, &cliaddr, sizeof(struct sockaddr_in));
        // TODO: do work
    }
       
    return 0;
}

int init() {
    // Setup and start threads
    for (int i = 0; i < MAX_THREADS; i++) {
        threads[i].queue.mutex ;
        if(pthread_create(&threads[i].thread, NULL, &thread_run, (void*) &threads[i])) return 1;
    }

    // Setup socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (sockfd == -1) {
        printf("ERROR: Failed to create socket with error: %d", errno);
        return 1;
    }

    struct sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, &servaddr, sizeof(servaddr)) == -1) {
        printf("ERROR: Failed to bind socket with error: %d", errno);
        return 1;
    }
}

void *thread_run(void * ptr) {
    struct server_thread_t* self = ptr;
    struct sockaddr_in cliaddrs[MAX_WORK_PER_THREAD] = {0};
    uint32_t media_id[MAX_WORK_PER_THREAD] = {0};
    FILE* fptr[MAX_WORK_PER_THREAD];
    uint8_t buffers[MAX_WORK_PER_THREAD][MTU];
    while (1) {
        // TODO: check request queue
        // do work
        for (int i = 0; i < MAX_WORK_PER_THREAD; i++) {
            if (media_id != 0) {
                if (fptr[i] == NULL) {
                    char path[strlen(MEDIA_PATH) + REQUEST_SIZE*2];
                    sprintf(path, "%s%0*x", REQUEST_SIZE*2, MEDIA_PATH, media_id[i]);
                    fptr[i] = fopen(path, "r");
                }
                if (feof(fptr[i])) {
                    // TODO: Handle finished doing work
                    // probably do nothing and explicitly wait for stop signal from client to stop
                } else {
                    fgets(buffers[i], MTU, fptr[i]);
                    sendto(sockfd, buffers[i], strlen(buffers[i]), 0, &cliaddrs[i], sizeof(struct sockaddr_in));
                }
            }
        }
    }
}

// TODO: create producer and consumer functions for request queues
