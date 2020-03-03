/******************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 1 - Traffic Light
* File: assignment1wpi.c
*
* Description:
* This file uses the WiringPi GPIO access library to create 
* a traffic light. The green LED turns on for 6 seconds, followed
* by the yellow LED for 1.5 seconds, and lastly, the red LED  
* for 5 seconds. 
* To compile this file, enter make
* To run this file, enter ./assignment1wpi
******************************************************************/

#include <stdio.h>
#include <wiringPi.h>

#define GREEN 1
#define YELLOW 4
#define RED 6
#define CYCLE 2

int main(void) {
    wiringPiSetup();
    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(RED, OUTPUT);

    for (int i = 0; i < CYCLE; i++) {
        printf("GO!\n");
        digitalWrite(GREEN, HIGH); delay(6000);
        digitalWrite(GREEN, LOW);

        printf("Proceed with caution...\n");
        digitalWrite(YELLOW, HIGH); delay(1500);
        digitalWrite(YELLOW, LOW);

        printf("STOP!\n");
        digitalWrite(RED, HIGH); delay(5000);
        digitalWrite(RED, LOW);
    }

    return 0;
}
