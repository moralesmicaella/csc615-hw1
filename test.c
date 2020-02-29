

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GREEN_PIN 18
#define YELLOW_PIN 23
#define RED_PIN 25

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define DIRECTION_MAX 40
#define BUFFER_MAX 3
#define VALUE_MAX 40

static int
GPIOExport(int pin)
{
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open export for writing!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

static int
GPIOUnexport(int pin)
{
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open unexport for writing!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

static int
GPIODirection(int pin, int dir)
{
	static const char s_directions_str[]  = "in\0out";
	char path[DIRECTION_MAX];
	int fd;

	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio direction for writing!\n");
		return(-1);
	}

	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
		fprintf(stderr, "Failed to set direction!\n");
		return(-1);
	}

	close(fd);
	return(0);
}

static int
GPIOWrite(int pin, int value)
{
	static const char s_values_str[] = "01";

	char path[VALUE_MAX];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for writing!\n");
		return(-1);
	}

	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 5)) {
		fprintf(stderr, "Failed to write value!\n");
		return(-1);
	}

	close(fd);
	return(0);
}
int
main(int argc, char *argv[])
{
	int repeat = 10;

	/*
	 * Enable GPIO pins
	 */
	if (-1 == GPIOExport(GREEN_PIN))
		return(1);
	if (-1 == GPIOExport(YELLOW_PIN))
		return(1);
	if (-1 == GPIOExport(RED_PIN))
		return(1);

	/*
	 * Set GPIO directions
	 */
	if (-1 == GPIODirection(GREEN_PIN, OUT))
		return(2);

	for (int i = 0; i < 2; i++) {
        printf("GO!\n");
        GPIOWrite(GREEN_PIN, HIGH); sleep(6);
        GPIOWrite(GREEN_PIN, LOW); 

        printf("Proceed with caution...\n");
        GPIOWrite(YELLOW_PIN, HIGH); sleep(1.5);
        GPIOWrite(YELLOW_PIN, LOW);

        printf("STOP!\n");
        GPIOWrite(RED_PIN, HIGH); sleep(5);
        GPIOWrite(RED_PIN, LOW);
    }

	/*
	 * Disable GPIO pins
	 */
	if (-1 == GPIOUnexport(GREEN_PIN))
		return(4);
	if (-1 == GPIOUnexport(YELLOW_PIN))
		return(4);
	if (-1 == GPIOUnexport(RED_PIN))
		return(4);

	return(0);
}
