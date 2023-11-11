#include "traffic_light.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Definitions for the duration of each traffic light state
#define RED_DURATION 10
#define GREEN_DURATION 10
#define YELLOW_DURATION 3

// Number of intersections to manage
#define INTERSECTION_COUNT 5

// Array of traffic lights for each intersection
TrafficLight traffic_lights[INTERSECTION_COUNT];

// Initialize a single traffic light
void initialize_traffic_light(TrafficLight *light, int intersection_id) {
    light->intersection_id = intersection_id;
    light->state = RED;  // Start all lights on RED
    light->last_change_time = time(NULL);
    light->red_duration = RED_DURATION;
    light->green_duration = GREEN_DURATION;
    light->yellow_duration = YELLOW_DURATION;
    light->emergency_mode = false;
    light->pedestrian_request = false;
}

// Initialize all traffic lights
void initialize_traffic_lights() {
    for (int i = 0; i < INTERSECTION_COUNT; i++) {
        initialize_traffic_light(&traffic_lights[i], i + 1);
    }
}

// Update the state of a single traffic light
void update_traffic_light_state(TrafficLight *light) {
    // Logic to update traffic light based on sensor data
    // Placeholder for simulation purposes
}

// Update the state of all traffic lights
void update_all_traffic_lights() {
    for (int i = 0; i < INTERSECTION_COUNT; i++) {
        update_traffic_light_state(&traffic_lights[i]);
    }
}

// Print the state of all traffic lights
void print_all_traffic_light_states() {
    for (int i = 0; i < INTERSECTION_COUNT; i++) {
        TrafficLight *light = &traffic_lights[i];
        const char* state_str = (light->state == RED) ? "RED" : (light->state == GREEN) ? "GREEN" : "YELLOW";
        printf("Intersection %d: Traffic Light is %s\n", light->intersection_id, state_str);
    }
}

// Write the state of all traffic lights to a file
void write_traffic_states_to_file() {
    FILE *file = fopen("traffic_states.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE); // Exit if we can't open the file
    }

    for (int i = 0; i < INTERSECTION_COUNT; i++) {
        TrafficLight *light = &traffic_lights[i];
        const char* state_str = (light->state == RED) ? "RED" : (light->state == GREEN) ? "GREEN" : "YELLOW";
        fprintf(file, "Intersection %d: %s\n", light->intersection_id, state_str);
    }

    fflush(file); // Flush the file buffer to make sure data is written
    fclose(file);
}

// Main function to simulate the traffic light control system
void simulate_traffic_light_control_system() {
    initialize_traffic_lights();

    while (1) {
        update_all_traffic_lights();
        print_all_traffic_light_states();
        write_traffic_states_to_file(); // Add this line to write states to file
        sleep(1); // Sleep for 1 second
    }
}