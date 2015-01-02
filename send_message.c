// file: send_message.c
//
// LCM example program.
//
// compile with:
//  $ gcc -o send_message send_message.c -llcm
//
// On a system with pkg-config, you can also use:
//  $ gcc -o send_message send_message.c `pkg-config --cflags --libs lcm`

#include <stdio.h>
#include <lcm/lcm.h>

#include "exlcm_example_t.h"

int
main(int argc, char ** argv)
{
    lcm_t * lcm = lcm_create("udpm://239.255.76.67:7667?ttl=1"); // initialize LCM
    if(!lcm)
        return 1;

    exlcm_example_t my_data = {     // initialize variables
        .timestamp = 0,
        .position = { 1, 2, 3 },
        .orientation = { 1, 0, 0, 0 },
    };
    int16_t ranges[15]; // Define array variable
    int i;
    for(i = 0; i < 15; i++)
        ranges[i] = i;

    my_data.num_ranges = 15;  // Set variable range
    my_data.ranges = ranges;  // Hand over variable pointer 
    my_data.name = "example string";
    my_data.enabled = 1;

    exlcm_example_t_publish(lcm, "EXAMPLE", &my_data); // Seralize data
                                         // EXAMPLE means channel name
    while(1){

	my_data.timestamp += 1;
	exlcm_example_t_publish(lcm, "EXAMPLE", &my_data);
	sleep(1);

    }

    lcm_destroy(lcm);    // destroy LCM 
    return 0;
}



