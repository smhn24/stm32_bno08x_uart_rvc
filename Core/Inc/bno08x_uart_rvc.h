#ifndef __BNO08X_UART_RVC_H__
#define __BNO08X_UART_RVC_H__

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_LENGTH 19
#define START_CHAR 0xAA
#define MILLI_G_TO_MMS2 9.8 //? Scalar to convert milli-gs to mm/s^2
#define DEGREE_SCALE 0.01   //? To convert the degree values
// #define MILLI_G_TO_MMS2 0.0098067 //? Scalar to convert milli-gs to m/s^2
// #define DEGREE_SCALE 10     //? To convert the milli degree values

typedef struct BNO08x
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
    int16_t accel_X;
    int16_t accel_Y;
    int16_t accel_Z;
} BNO08x_t;

void update_bno(BNO08x_t *bno, const uint8_t *sorted_buffer);
void sort_buffer(const uint8_t *buffer, uint8_t *sorted_buffer);

#endif
