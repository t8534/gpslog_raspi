all: output_file_name

output_file_name: main.o
	gcc main.o -lwiringPi -o gps_test

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *o gps_test
