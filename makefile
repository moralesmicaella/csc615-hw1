all: assignment1wpi.c assignment1b.c
	gcc -Wall -o assignment1wpi assignment1wpi.c -lwiringPi
	gcc -Wall -o assignment1b assignment1b.c 

assignment1wpi: assignment1wpi.c
	gcc -Wall -o assignment1wpi assignment1wpi.c -lwiringPi

assignment1b: assignmnet1b.c
	gcc -Wall -o assignment1b assignment1b.c 

clean:
	rm assignment1wpi assignment1b
