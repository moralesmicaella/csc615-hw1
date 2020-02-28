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

#define GREEN_PIN "17"
#define YELLOW_PIN "18"
#define RED_PIN "27"
#define CYCLE "2"

#define OUTPUT "out"
#define HIGH "1"
#define LOW "0"

int write_to_fs(int write_max, char format[], char path[], char file[]){
    char buffer[write_max];
    ssize_t bytes_formatted, bytes_written;

    int fd = open(path, O_WRONLY);
    if(fd == -1) {
        fprintf(stderr, "Failed to open %s", file);
        return -1;
    }

    bytes_formatted = snprintf(buffer, write_max, format);
    bytes_written = write(fd, buffer, bytes_formatted);
    if(bytes_written == -1) {
        fprintf(stderr, "Failed to write to %s", file);
        return -1;
    }
    close(fd);

    return 0;
}

void gpio_export(char pin[]) {
    char export_path[] = "/sys/class/gpio/export";
    
    write_to_fs(2, pin, export_path, "gpio export");
}

void gpio_set_direction(char pin[], char dir[]) {
    int direction_max = 35;
    char direction_path[direction_max];

    snprintf(direction_path, 3, "/sys/class/gpio/gpio%s/direction", pin);
    write_to_fs(3, dir, direction_path, "gpio direction");
}

void gpio_write(char pin[], char value[]) {
    int value_max = 30;
    char value_path[value_max];

    snprintf(value_path, value_max, "/sys/class/gpio/gpio%s/value", pin);
    write_to_fs(1, value, value_path, "gpio value");
}

int main(void) {
    gpio_export(GREEN_PIN);
    gpio_export(YELLOW_PIN);
    gpio_export(RED_PIN);

    gpio_set_direction(GREEN_PIN, OUTPUT);
    gpio_set_direction(YELLOW_PIN, OUTPUT);
    gpio_set_direction(RED_PIN, OUTPUT);

    for (int i = 0; i < CYCLE; i++) {
        printf("GO!");
        gpio_write(GREEN_PIN, HIGH); sleep(6);
        gpio_write(GREEN_PIN, LOW); 

        printf("Proceed with caution...");
        gpio_write(YELLOW_PIN, HIGH); sleep(1.5);
        gpio_write(YELLOW_PIN, LOW);

        printf("STOP!");
        gpio_write(RED_PIN, HIGH); sleep(5);
        gpio_write(RED_PIN, LOW);
    }
    
    return 0;
}