#include "traffic_light.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Definitions for the duration of each traffic light state
int RED_DURATION = 10;
int GREEN_DURATION = 10;
int YELLOW_DURATION = 3;

// Number of intersections to manage
#define INTERSECTION_COUNT 5

// Array of traffic lights for each intersection
TrafficLight traffic_lights[INTERSECTION_COUNT];

// Initialize a single traffic light
void initialize_traffic_light(TrafficLight *light, int intersection_id) {
    light->intersection_id = intersection_id - 1;
    light->state = RED;  // Start all lights on RED
    light->last_change_time = time(NULL);
    light->red_duration = RED_DURATION;
    light->green_duration = GREEN_DURATION;
    light->yellow_duration = YELLOW_DURATION;
    light->emergency_mode = false;
    light->pedestrian_request = false;
    light->remaining_time = 0;
}

// Initialize all traffic lights
void initialize_traffic_lights() {
    for (int i = 0; i < INTERSECTION_COUNT; i++) {
        initialize_traffic_light(&traffic_lights[i], i + 1);
    }
}

// This function adjusts the duration for which traffic lights stay green (GREEN_DURATION) based on traffic predictions

// STEPS
// 1. Read Prediction
// 2. Calculate Scale Factor
// 3. Adjust Green Light Duration

void read_and_adjust_traffic_light_timings() {
    FILE *file = fopen("../webserver/traffic_prediction.txt", "r");
    if (file != NULL) {
        float traffic_prediction;
        fscanf(file, "%f", &traffic_prediction);
        fclose(file);

        const int min_green_duration = 5;
        const int max_green_duration = 20;
        const float max_prediction_value = 100.0;

        // Calculate the scale factor based on the traffic prediction
        float scale_factor = traffic_prediction / max_prediction_value;

        // Calculate the green light duration based on the scale factor
        // It scales linearly between min_green_duration and max_green_duration

        // When the traffic prediction is low, scale_factor will be closer to 0, making the GREEN_DURATION closer to min_green_duration
        // When the traffic prediction is high, scale_factor will be closer to 1, making the GREEN_DURATION closer to max_green_duration
        GREEN_DURATION = (int)(min_green_duration + (max_green_duration - min_green_duration) * scale_factor);

        // Ensure the green light duration does not fall below the minimum duration
        if (GREEN_DURATION < min_green_duration) {
            GREEN_DURATION = min_green_duration;
        }

        // Ensure the green light duration does not go above the maximum duration
        if (GREEN_DURATION > max_green_duration) {
            GREEN_DURATION = max_green_duration;
        }

        // Print the new GREEN_DURATION for debugging
        printf("New GREEN_DURATION based on prediction: %d\n", GREEN_DURATION);
    } else {
        perror("Error opening traffic prediction file");
    }
}

// Once read_and_adjust_traffic_light_timings has updated GREEN_DURATION, this new duration is supposed to be used by update_traffic_light_state

// This function manages the state of a single traffic light (RED, GREEN, or YELLOW) based on elapsed time and set durations for each state
// i.e. it manages how long a traffic light remains in a state

// STEPS
// 1. Calculate Elapsed Time (calculates how much time has passed since the traffic light last changed state)
// 2. Check State and Duration (checks the current state of the traffic light and decides whether it's time to switch to the next state based on the elapsed time and the duration set for the current state)
// 3. Update Remaining Time (calculates and updates the remaining time the light will stay in that state before the next transition)

void update_traffic_light_state(TrafficLight *light) {
    time_t current_time = time(NULL);
    double elapsed = difftime(current_time, light->last_change_time);
    int remaining_time = 0;

    if (light->state == RED) {
        remaining_time = light->red_duration - (int)elapsed;
        if (remaining_time <= 0) {
            light->state = GREEN;
            light->last_change_time = current_time;
            light->green_duration = GREEN_DURATION; // Use updated GREEN_DURATION from read_and_adjust_traffic_light_timings
            remaining_time = light->green_duration;
        }
    } else if (light->state == GREEN) {
        remaining_time = light->green_duration - (int)elapsed;
        if (remaining_time <= 0) {
            light->state = YELLOW;
            light->last_change_time = current_time;
            remaining_time = light->yellow_duration;
        }
    } else if (light->state == YELLOW) {
        remaining_time = light->yellow_duration - (int)elapsed;
        if (remaining_time <= 0) {
            light->state = RED;
            light->last_change_time = current_time;
            light->red_duration = RED_DURATION;
            remaining_time = light->red_duration;
        }
    }

    light->remaining_time = remaining_time > 0 ? remaining_time : 0;
}

// Update the state of all traffic lights
void update_all_traffic_lights() {
    read_and_adjust_traffic_light_timings(); // Adjust timings based on prediction
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

// Write the state and remaining time of all traffic lights to a file
void write_traffic_states_to_file() {
    FILE *file = fopen("../webserver/traffic_states.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < INTERSECTION_COUNT; i++) {
        TrafficLight *light = &traffic_lights[i];
        const char* state_str = (light->state == RED) ? "RED" : (light->state == GREEN) ? "GREEN" : "YELLOW";
        fprintf(file, "Intersection %d: %s (Remaining Time: %d seconds)\n", light->intersection_id, state_str, light->remaining_time);
    }

    fflush(file);
    fclose(file);
}