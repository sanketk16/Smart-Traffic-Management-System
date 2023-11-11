#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <stdbool.h>
#include <time.h>

// Enumeration for traffic light states
typedef enum { RED, GREEN, YELLOW } TrafficLightState;

// Struct to represent an intersection with a traffic light and pedestrian crossing
typedef struct {
    int intersection_id;
    TrafficLightState state;
    time_t last_change_time;
    unsigned int red_duration;
    unsigned int green_duration;
    unsigned int yellow_duration;
    bool emergency_mode; // Flag for emergency vehicle priority
    bool pedestrian_request; // Flag for pedestrian crossing request
} TrafficLight;

// Function prototypes
void initialize_traffic_light(TrafficLight *light, int intersection_id);
void initialize_traffic_lights();
void adjust_light_timing(TrafficLight *light, int traffic_flow);
bool check_for_emergency_vehicle(int intersection_id);
bool check_for_pedestrian_request(int intersection_id);
void update_traffic_light_state(TrafficLight *light);
void update_all_traffic_lights();
void print_all_traffic_light_states();
void simulate_traffic_light_control_system();

#endif // TRAFFIC_LIGHT_H