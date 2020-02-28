all: blink.c assignment1wpi.c assignment1b.c
	gcc -Wall -o blink blink.c -lwiringPi
	gcc -Wall -o assignment1wpi assignment1wpi.c -lwiringPi
	gcc -Wall -o assignment1b assignment1b.c -lwiringPi

blink: blink.c
	gcc -Wall -o blink blink.c -lwiringPi

assignment1wpi: assignment1wpi.c
	gcc -Wall -o assignment1wpi assignment1wpi.c -lwiringPi

assignment1b: assignmnet1b.c
	gcc -Wall -o assignment1b assignment1b.c -lwiringPi

clean:
	rm blink assignment1wpi
