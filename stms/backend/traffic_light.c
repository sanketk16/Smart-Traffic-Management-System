
// #include "traffic_light.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <unistd.h>

// // Definitions for the duration of each traffic light state
// #define RED_DURATION 10
// #define GREEN_DURATION 10
// #define YELLOW_DURATION 3

// // Number of intersections to manage
// #define INTERSECTION_COUNT 5

// // Array of traffic lights for each intersection
// TrafficLight traffic_lights[INTERSECTION_COUNT];

// // Initialize a single traffic light
// void initialize_traffic_light(TrafficLight *light, int intersection_id) {
//     light->intersection_id = intersection_id;
//     light->state = RED;  // Start all lights on RED
//     light->last_change_time = time(NULL);
//     light->red_duration = RED_DURATION;
//     light->green_duration = GREEN_DURATION;
//     light->yellow_duration = YELLOW_DURATION;
//     light->emergency_mode = false;
//     light->pedestrian_request = false;
// }

// // Initialize all traffic lights
// void initialize_traffic_lights() {
//     for (int i = 0; i < INTERSECTION_COUNT; i++) {
//         initialize_traffic_light(&traffic_lights[i], i + 1);
//     }
// }

// // Update the state of a single traffic light
// void update_traffic_light_state(TrafficLight *light) {
//     time_t current_time = time(NULL);
//     double elapsed = difftime(current_time, light->last_change_time);

//     // Debugging: Print the elapsed time for each state
//     printf("Intersection %d: %s for %.f seconds\n", light->intersection_id, 
//            (light->state == RED) ? "RED" : (light->state == GREEN) ? "GREEN" : "YELLOW", elapsed);

//     if (light->state == RED && elapsed >= light->red_duration) {
//         light->state = GREEN;
//         light->last_change_time = current_time;
//     } else if (light->state == GREEN && elapsed >= light->green_duration) {
//         light->state = YELLOW;
//         light->last_change_time = current_time;
//     } else if (light->state == YELLOW && elapsed >= light->yellow_duration) {
//         light->state = RED;
//         light->last_change_time = current_time;
//     }
// }

// // Update the state of all traffic lights
// void update_all_traffic_lights() {
//     for (int i = 0; i < INTERSECTION_COUNT; i++) {
//         update_traffic_light_state(&traffic_lights[i]);
//     }
// }

// // Print the state of all traffic lights
// void print_all_traffic_light_states() {
//     for (int i = 0; i < INTERSECTION_COUNT; i++) {
//         TrafficLight *light = &traffic_lights[i];
//         const char* state_str = (light->state == RED) ? "RED" : (light->state == GREEN) ? "GREEN" : "YELLOW";
//         printf("Intersection %d: Traffic Light is %s\n", light->intersection_id, state_str);
//     }
// }

// // // Write the state of all traffic lights to a file in the webserver directory
// void write_traffic_states_to_file() {
//     FILE *file = fopen("../webserver/traffic_states.txt", "w");
//     if (file == NULL) {
//         perror("Error opening file");
//         exit(EXIT_FAILURE); // Exit if we can't open the file
//     }

//     for (int i = 0; i < INTERSECTION_COUNT; i++) {
//         TrafficLight *light = &traffic_lights[i];
//         const char* state_str = (light->state == RED) ? "RED" : (light->state == GREEN) ? "GREEN" : "YELLOW";
//         fprintf(file, "Intersection %d: %s\n", light->intersection_id, state_str);
//     }

//     fflush(file); // Flush the file buffer to make sure data is written
//     fclose(file);
// }


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

// Read traffic prediction and adjust light durations
// void read_and_adjust_traffic_light_timings() {
//     FILE *file = fopen("traffic_prediction.txt", "r");
//     if (file != NULL) {
//         float traffic_prediction;
//         fscanf(file, "%f", &traffic_prediction);
//         fclose(file);

//         // Simple logic: Increase green duration for high traffic, decrease otherwise
//         if (traffic_prediction > 50) {
//             GREEN_DURATION = 15;  // longer green light
//         } else {
//             GREEN_DURATION = 5;   // shorter green light
//         }
//     } else {
//         perror("Error opening traffic prediction file");
//     }
// }

void read_and_adjust_traffic_light_timings() {
    FILE *file = fopen("traffic_prediction.txt", "r");
    if (file != NULL) {
        float traffic_prediction;
        fscanf(file, "%f", &traffic_prediction);
        fclose(file);

        // Define minimum and maximum durations for green light
        const int min_green_duration = 5;  // Minimum green light duration in seconds
        const int max_green_duration = 20; // Maximum green light duration in seconds

        // Define the scale of prediction values (adjust as needed)
        const float max_prediction_value = 100.0;

        // Scale the duration of the green light based on the traffic prediction
        float scale_factor = traffic_prediction / max_prediction_value;
        GREEN_DURATION = (int)(min_green_duration + (max_green_duration - min_green_duration) * scale_factor);

        // Ensure that the green duration is within the defined bounds
        if (GREEN_DURATION < min_green_duration) {
            GREEN_DURATION = min_green_duration;
        }
        if (GREEN_DURATION > max_green_duration) {
            GREEN_DURATION = max_green_duration;
        }
    } else {
        perror("Error opening traffic prediction file");
    }
}

// Update the state of a single traffic light
// void update_traffic_light_state(TrafficLight *light) {
//     time_t current_time = time(NULL);
//     double elapsed = difftime(current_time, light->last_change_time);

//     printf("Intersection %d: %s for %.f seconds\n", light->intersection_id, 
//            (light->state == RED) ? "RED" : (light->state == GREEN) ? "GREEN" : "YELLOW", elapsed);

//     if (light->state == RED && elapsed >= light->red_duration) {
//         light->state = GREEN;
//         light->last_change_time = current_time;
//         light->green_duration = GREEN_DURATION; // Update duration based on prediction
//     } else if (light->state == GREEN && elapsed >= light->green_duration) {
//         light->state = YELLOW;
//         light->last_change_time = current_time;
//     } else if (light->state == YELLOW && elapsed >= light->yellow_duration) {
//         light->state = RED;
//         light->last_change_time = current_time;
//         light->red_duration = RED_DURATION; // Update duration based on prediction
//     }
// }

// Update the state of a single traffic light and calculate the remaining time
void update_traffic_light_state(TrafficLight *light) {
    time_t current_time = time(NULL);
    double elapsed = difftime(current_time, light->last_change_time);
    int remaining_time = 0;

    if (light->state == RED) {
        remaining_time = light->red_duration - (int)elapsed;
        if (remaining_time <= 0) {
            light->state = GREEN;
            light->last_change_time = current_time;
            light->green_duration = GREEN_DURATION; // Update duration based on prediction
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
            light->red_duration = RED_DURATION; // Update duration based on prediction
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

// Write the state of all traffic lights to a file
// void write_traffic_states_to_file() {
//     FILE *file = fopen("../webserver/traffic_states.txt", "w");
//     if (file == NULL) {
//         perror("Error opening file");
//         exit(EXIT_FAILURE); // Exit if we can't open the file
//     }

//     for (int i = 0; i < INTERSECTION_COUNT; i++) {
//         TrafficLight *light = &traffic_lights[i];
//         const char* state_str = (light->state == RED) ? "RED" : (light->state == GREEN) ? "GREEN" : "YELLOW";
//         fprintf(file, "Intersection %d: %s\n", light->intersection_id + 1, state_str);
//     }

//     fflush(file); // Flush the file buffer to make sure data is written
//     fclose(file);
// }

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