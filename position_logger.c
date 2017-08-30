// position_logger.c
//
// TODO:
// 1.
// The serial_readline() is buggy, correct it and check also parsers.
//
// 2.
// How tests passed if serial_readline() buggy ?
//
// 3.
// How tests are working.
//
// 4.
// Add error support for gps.
//
// 5.
// Add init and config feature for gps.



#include <stdio.h>
#include <stdlib.h>
#include <gps.h>


int main(void) {
    // Open
    gps_init();

    loc_t data;

    while (1) {
        gps_location(&data);

        printf("%lf %lf\n", data.latitude, data.longitude);
    }

    return EXIT_SUCCESS;
}

