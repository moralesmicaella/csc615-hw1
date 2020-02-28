/************************************************************** 
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 1 - Traffic Light
* File: assignment1wpi.c
*
* Description:
*
**************************************************************/

#include <stdio.h>
#include <wiringPi.h>

#define GREEN 0
#define YELLOW 1
#define RED 2
#define CYCLE 2

int main(void) {
    wiringPiSetup(void);
    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(RED, OUTPUT);

    for (i = 0; i < CYCLE; i++) {
        printf("GO!");
        digitalWrite(GREEN, HIGH); delay(6000);
        digitalWrite(GREEN, LOW);

        printf("Proceed with caution...");
        digitalWrite(YELLOW, HIGH); delay(1500);
        digitalWrite(YELLOW, LOW);

        printf("STOP!");
        digitalWrite(RED, HIGH); delay(5000);
        digitalWrite(RED, LOW);
    }

    return 0;
}
