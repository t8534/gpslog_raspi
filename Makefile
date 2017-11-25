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



#
#CXXFLAGS =	-O2 -g -Wall -fmessage-length=0
#
#OBJS =		test1.o
#
#LIBS =
#
#TARGET =	test1.exe
#
#$(TARGET):	$(OBJS)
#	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
#
#all:	$(TARGET)
#
#clean:
#	rm -f $(OBJS) $(TARGET)
#


#####################################################################
# headers subdirs
#IDIRS = -I. -I"C:/MinGW/include" -I"C:/MinGW/include/lib/gcc/mingw32/4.5.0/include" -I"C:/MinGW/include/lib/gcc/mingw32/4.5.0/include-fixed" -I./libs/sdl/include -I./libs/sdl/include/SDL
#
#CC=gcc   
#CFLAGS=-c -Wall $(IDIRS) 
#
##CXX=g++
##CXXFLAGS=-c -Wall $(IDIRS) 
#
#LDFLAGS=
##LDLIBS= -L./libs/sdl/include -L./libs/sdl/include/SDL -L./libs/sdl/libs -lSDLmain -lSDL
#LDLIBS= -L./libs/sdl/libs -lmingw32 -lSDLmain -lSDL 
##LDLIBS= -lmingw32
#
#
## all source subdirs for linker and compilator
#VPATH = ./ libs libs/sdl libs/sdl/libs
#
#all : t1.exe
#
#t1.exe : t1.o   
#	$(CC) -o t1.exe t1.o 
#
#clean:
#	rm -f t1.exe t1.o


########################################################################
## headers subdirs
##IDIRS = -I. -I"C:/MinGW/include" -I"C:/MinGW/include/lib/gcc/mingw32/4.5.0/include" -I"C:/MinGW/include/lib/gcc/mingw32/4.5.0/include-fixed" -I./libs/sdl/include -I./libs/sdl/include/SDL
#IDIRS = -I./lib/include/SDL2 
#
#CC=gcc   
#CFLAGS=-c -v -Wall $(IDIRS) 
#
##CXX=g++
##CXXFLAGS=-c -Wall $(IDIRS) 
#
#LDFLAGS= 
#LDLIBS= -L./lib/libs -lmingw32 -lSDL2main -lSDL2
#
#
#%.o: %.c
#	$(CC) $(CFLAGS) $<
#
#
## all source subdirs for linker and compilator
##VPATH = ./ libs libs/sdl libs/sdl/libs
#
#all : t3_sdl2.exe
#
## At linker below library paths and libraries must be at the end of line.
#t3_sdl2.exe : t3_sdl2.o   
#	$(CC) -o t3_sdl2.exe t3_sdl2.o $(LDLIBS)
#
#
#clean:
#	rm -f t3_sdl2.exe t3_sdl2.o
#
#
#####################################################################


#####################################################################
# Another version, to check

#oled:oled.o sh1106.o
#	gcc -Wall -o oled oled.o sh1106.o -lbcm2835
#sh1106.o:sh1106.c sh1106.h
#	gcc -Wall -c sh1106.c -lbcm2835
#oled.o:oled.c sh1106.h 
#	gcc -Wall -c oled.c -lbcm2835
#clean:
#	rm sh1106.o oled.o oled

#####################################################################


#####################################################################
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

PROJ_DIR=.
SRC_DIR=./src_new
BUILD_DIR=./build

 
IDIRS = -I. -I${SRC_DIR}/sys -I${SRC_DIR}/gps -I${SRC_DIR}/mcal -I${SRC_DIR}/tests -I${SRC_DIR}/utils 
 
CC=gcc 
 
RM=rm 
 
CFLAGS=-g3 -Wall ${IDIRS}
 
OBJS =	${BUILD_DIR}/mcal_uart.o ${BUILD_DIR}/ring_buff.o ${BUILD_DIR}/get_msg_listeners.o ${BUILD_DIR}/get_msg.o ${BUILD_DIR}/getmsg_tests.o ${BUILD_DIR}/position_logger.o 
 
LIBS = -lm 
 
all: position_logger 
 
#position_logger: 
#	${CC} ${CFLAGS} ${IDIRS} -c -o ${BUILD_DIR}/mcal_uart.o mcal_uart.c 
#	${CC} ${CFLAGS} ${IDIRS} -c -o ${BUILD_DIR}/ring_buff.o ring_buff.c 
#	${CC} ${CFLAGS} ${IDIRS} -c -o ${BUILD_DIR}/get_msg.o get_msg.c
#	${CC} ${CFLAGS} ${IDIRS} -c -o ${BUILD_DIR}/get_msg_listeners.o get_msg_listeners.c	
#	${CC} ${CFLAGS} ${IDIRS} -c -o ${BUILD_DIR}/getmsg_tests.o getmsg_tests.c	 
#	${CC} ${CFLAGS} ${IDIRS} -c -o ${BUILD_DIR}/position_logger.o position_logger.c 
#	${CC} ${CFLAGS} -o ${BUILD_DIR}/position_logger ${OBJS} ${LIBS} 
 
position_logger: 
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/ring_buff.o ${SRC_DIR}/utils/ring_buff.c
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/mcal_uart.o ${SRC_DIR}/mcal/mcal_uart.c 
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/get_msg.o ${SRC_DIR}/gps/get_msg.c
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/get_msg_listeners.o ${SRC_DIR}/gps/get_msg_listeners.c	
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/getmsg_tests.o ${SRC_DIR}/tests/getmsg_tests.c	 
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/position_logger.o position_logger.c 
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
	${RM} ${BUILD_DIR}/*.o 


