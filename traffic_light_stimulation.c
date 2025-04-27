#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define RED_TIME 5
#define GREEN_TIME 5
#define YELLOW_TIME 2

#define NUM_LANES 4

typedef enum {
    RED,
    GREEN,
    YELLOW
} TrafficLightState;

typedef struct {
    int lane_id;
    TrafficLightState state;
} TrafficLane;

TrafficLane lanes[NUM_LANES];
pthread_mutex_t lock;

// Convert state to string
const char* state_to_string(TrafficLightState state) {
    switch (state) {
        case RED: return "RED   ";
        case GREEN: return "GREEN ";
        case YELLOW: return "YELLOW";
        default: return "UNKNOWN";
    }
}

// Function to display traffic lights status
void display_lanes() {
    system("clear"); // Clear terminal screen

    printf("\n====== Traffic Light Simulation ======\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < NUM_LANES; i++) {
        printf("Lane %d: %s\n", lanes[i].lane_id, state_to_string(lanes[i].state));
    }

    printf("----------------------------------------\n");
}

// Each lane runs here
void* lane_controller(void* arg) {
    TrafficLane* lane = (TrafficLane*)arg;

    while (1) {
        pthread_mutex_lock(&lock);
        lane->state = RED;
        display_lanes();
        pthread_mutex_unlock(&lock);
        sleep(RED_TIME);

        pthread_mutex_lock(&lock);
        lane->state = GREEN;
        display_lanes();
        pthread_mutex_unlock(&lock);
        sleep(GREEN_TIME);

        pthread_mutex_lock(&lock);
        lane->state = YELLOW;
        display_lanes();
        pthread_mutex_unlock(&lock);
        sleep(YELLOW_TIME);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_LANES];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_LANES; i++) {
        lanes[i].lane_id = i + 1;
        lanes[i].state = RED;
        pthread_create(&threads[i], NULL, lane_controller, (void*)&lanes[i]);
    }

    for (int i = 0; i < NUM_LANES; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
