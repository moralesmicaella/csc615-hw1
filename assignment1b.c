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
#define HIGH 1
#define LOW 0

int write_to_fs(int write_max, char* format, char* path){
    char buffer[write_max];
    ssize_t bytes_formatted, bytes_written;

    int fd = open(path, O_WRONLY);
    if(fd == -1) {
        fprintf(stderr, "Failed to open file\n");
        return -1;
    }

    bytes_formatted = snprintf(buffer, write_max, format);
    if(bytes_formatted == -1) {
        fprintf(stderr, "Failed to format what to write\n");
        return -1;
    }
    
    bytes_written = write(fd, buffer, bytes_formatted);
    if(bytes_written == -1) {
        fprintf(stderr, "Failed to write on file\n");
        return -1;
    }
    close(fd);

    return 0;
}


void gpio_export(int pin) {
    char export_path[] = "/sys/class/gpio/export";
    char buffer[3];
    snprintf(buffer, 3, "%d", pin);
    if(write_to_fs(5, buffer, export_path) == -1) {
        fprintf(stderr, "Failed to export pin %d\n", pin);
    }
}

void gpio_unexport(int pin) {
    char export_path[] = "/sys/class/gpio/unexport";
    char buffer[3];
    snprintf(buffer, 3, "%d", pin);
    if(write_to_fs(5, buffer, export_path) == -1) {
        fprintf(stderr, "Failed to unexport pin %d\n", pin);
    }
}

void gpio_set_direction(int pin, char dir[]) {
    char buffer[5];
    ssize_t bytes_formatted, bytes_written;
    
    int direction_max = 50;
    char path[direction_max];
    snprintf(path, direction_max, "/sys/class/gpio/gpio%d/direction", pin);
    int fd = open(path, O_WRONLY);
    if(fd == -1) {
        fprintf(stderr, "Failed to open file\n");
    }

    bytes_formatted = snprintf(buffer, 5, "out");
    if(bytes_formatted == -1) {
        fprintf(stderr, "Failed to format what to write\n");
    }
    
    bytes_written = write(fd, buffer, bytes_formatted);
    if(bytes_written == -1) {
        fprintf(stderr, "Failed to write on file\n");
    }
    close(fd);
}

void gpio_set_dir(int pin, char dir[]) {
    int direction_max = 50;
    char direction_path[direction_max];

    snprintf(direction_path, direction_max, "/sys/class/gpio/gpio%d/direction", pin);
    if(write_to_fs(5, dir, direction_path) == -1) {
        fprintf(stderr, "Failed to set the direction of pin %d\n", pin);
    }
}

void gpio_write(int pin, int value) {
    char buffer[10];
    ssize_t bytes_formatted, bytes_written;
    int value_max = 60;
    char path[value_max];

    snprintf(path, value_max, "/sys/class/gpio/gpio%d/value", pin);
    int fd = open(path, O_WRONLY);
    if(fd == -1) {
        fprintf(stderr, "Failed to open file for write\n");
        
    }

    bytes_formatted = snprintf(buffer, 10, "%d", value);
    if(bytes_formatted == -1) {
        fprintf(stderr, "Failed to format what to write\n");
        
    }
    
    bytes_written = write(fd, buffer, bytes_formatted);
    if(bytes_written == -1) {
        fprintf(stderr, "Failed to write on file\n");
        
    }
    close(fd);
}

void gpio_wr(int pin, char value[]) {
    int value_max = 50;
    char value_path[value_max];

    snprintf(value_path, value_max, "/sys/class/gpio/gpio%d/value", pin);
    if(write_to_fs(5, value, value_path) == -1) {
        fprintf(stderr, "Failed to write on pin %d\n", pin);
    }
}

int main(void) {
    gpio_export(GREEN_PIN);
    gpio_set_direction(GREEN_PIN, OUTPUT);
    
    gpio_export(YELLOW_PIN);
    gpio_set_direction(YELLOW_PIN, OUTPUT);
    
    gpio_export(RED_PIN);
    gpio_set_direction(RED_PIN, OUTPUT);

    for (int i = 0; i < CYCLE; i++) {
        printf("GO!\n");
        gpio_write(GREEN_PIN, HIGH); sleep(6);
        gpio_write(GREEN_PIN, LOW); 

        printf("Proceed with caution...\n");
        gpio_write(YELLOW_PIN, HIGH); sleep(1.5);
        gpio_write(YELLOW_PIN, LOW);

        printf("STOP!\n");
        gpio_write(RED_PIN, HIGH); sleep(5);
        gpio_write(RED_PIN, LOW);
    }

    gpio_unexport(GREEN_PIN);
    gpio_unexport(YELLOW_PIN);
    gpio_unexport(RED_PIN);
    
    return 0;
}
