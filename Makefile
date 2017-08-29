# origfor main.c - working
#all: output_file_name
#
#output_file_name: main.o
#	gcc main.o -lwiringPi -o gps_test
#
#main.o: main.c
#	gcc -c main.c
#
#clean:
#	rm -rf *o gps_test

CC=/usr/bin/gcc

RM=/bin/rm

CFLAGS=-g3 -Wall -lm

PROJ_DIR=.
BUILD_DIR=./build

OBJS =	${BUILD_DIR}/gps.o ${BUILD_DIR}/serial.o ${BUILD_DIR}/nmea.o ${BUILD_DIR}/position_logger.o

LIBS = -lm


all: position_logger

position_logger:
	${CC} ${CFLAGS} -I${PROJ_DIR}/libgps -c -o ${BUILD_DIR}/gps.o gps.c
	${CC} ${CFLAGS} -I${PROJ_DIR}/libgps -c -o ${BUILD_DIR}/serial.o serial.c
	${CC} ${CFLAGS} -I${PROJ_DIR}/libgps -c -o ${BUILD_DIR}/nmea.o nmea.c
	${CC} ${CFLAGS} -I${PROJ_DIR} -c -o ${BUILD_DIR}/position_logger.o position_logger.c
	${CC} ${CFLAGS} -o ${BUILD_DIR}/position_logger ${OBJS} ${LIBS}



#Example
#OBJS =	src/test_d_ar.o test_c.o
#LIBS =
#TARGET =	test_c.exe
#$(TARGET):	$(OBJS)
#	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
#
#all:	$(TARGET)



# Example
#FILES_LIST= ../src/nmea.c ../src/serial.c ../src/gps.c \
#			all_tests.c nmea_test.c gps_test.c serial_test.c helpers.c
#
#all:
#	${CC} ${CFLAGS} \
#		-o ${TESTS_BIN} ${FILES_LIST} -I../src/ -lm \
#		`pkg-config --cflags --libs check`




clean:
	${RM} ${BUILD_DIR}/*


