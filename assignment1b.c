/************************************************************** 
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 1 - Traffic Light
* File: assignment1b.c
*
* Description:
*
**************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define GREEN_PIN 18
#define YELLOW_PIN 23
#define RED_PIN 25
#define CYCLE 2

#define OUTPUT "out"
#define HIGH "1"
#define LOW "0"

int write_to_fs(int write_max, char* format, char* path){
    int fd = open(path, O_WRONLY);
    if(fd == -1) {
        fprintf(stderr, "Failed to open %s\n", path);
        return -1;
    }
    
    ssize_t bytes_written = write(fd, format, write_max);
    if(bytes_written == -1) {
        fprintf(stderr, "Failed to write %s on file\n", format);
        return -1;
    }
    close(fd);

    return 0;
}


int gpio_export(int pin) {
    char export_path[] = "/sys/class/gpio/export";
    
    int max_size = 3;
    char buffer[max_size];
    snprintf(buffer, max_size, "%d", pin);

    if(write_to_fs(max_size, buffer, export_path) == -1) {
        fprintf(stderr, "Failed to export pin %s\n", buffer);
        return -1;
    }

    return 0;
}

int gpio_unexport(int pin) {
    char export_path[] = "/sys/class/gpio/unexport";
    
    int max_size = 3;
    char buffer[max_size];
    snprintf(buffer, max_size, "%d", pin);

    if(write_to_fs(max_size, buffer, export_path) == -1) {
        fprintf(stderr, "Failed to unexport pin %s\n", buffer);
        return -1;
    }

    return 0;
}

int gpio_set_direction(int pin, char* dir) {
    int direction_max_size = 50;
    char direction_path[direction_max_size];
    snprintf(direction_path, direction_max_size, "/sys/class/gpio/gpio%d/direction", pin);

    if(write_to_fs(3, dir, direction_path) == -1) {
        fprintf(stderr, "Failed to set the direction of pin %d\n", pin);
        return -1;
    }

    return 0;
}

int gpio_write(int pin, char* value) {
    int value_max_size = 50;
    char value_path[value_max_size];

    int max_size = 3;

    snprintf(value_path, value_max_size, "/sys/class/gpio/gpio%d/value", pin);
    if(write_to_fs(max_size, value, value_path) == -1) {
        fprintf(stderr, "Failed to write on pin %d\n", pin);
        return -1;
    }

    return 0;
}

int main(void) {
    gpio_export(GREEN_PIN);
    gpio_set_direction(GREEN_PIN, OUTPUT);
    
    gpio_export(YELLOW_PIN);
    gpio_set_direction(YELLOW_PIN, OUTPUT);
    
    gpio_export(RED_PIN);
    gpio_set_direction(RED_PIN, OUTPUT);

    for (int i = 0; i < CYCLE; i++) {
        if (gpio_write(GREEN_PIN, HIGH) == 0) {
            printf("GO!\n"); 
            sleep(6);
        } 
        gpio_write(GREEN_PIN, LOW); 

        if (gpio_write(YELLOW_PIN, HIGH) == 0) {
            printf("Proceed with caution...\n");
            sleep(1.5);
        } 
        gpio_write(YELLOW_PIN, LOW);

        if (gpio_write(RED_PIN, HIGH) == 0) {
            printf("STOP!\n");
            sleep(5);
        } 
        gpio_write(RED_PIN, LOW);
    }

    gpio_unexport(GREEN_PIN);
    gpio_unexport(YELLOW_PIN);
    gpio_unexport(RED_PIN);
    
    return 0;
}
