#include "traffic_light.h"
#include <unistd.h>

int main() {
    initialize_traffic_lights();

    while (1) {
        update_all_traffic_lights();
        print_all_traffic_light_states();
        sleep(1); // Sleep for 1 second
    }

    return 0;
}