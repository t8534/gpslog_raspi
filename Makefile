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
# headers subdirs
#IDIRS = -I. -I"C:/MinGW/include" -I"C:/MinGW/include/lib/gcc/mingw32/4.5.0/include" -I"C:/MinGW/include/lib/gcc/mingw32/4.5.0/include-fixed" -I./libs/sdl/include -I./libs/sdl/include/SDL
IDIRS = -I./lib/include/SDL2 

CC=gcc   
CFLAGS=-c -v -Wall $(IDIRS) 

#CXX=g++
#CXXFLAGS=-c -Wall $(IDIRS) 

LDFLAGS= 
LDLIBS= -L./lib/libs -lmingw32 -lSDL2main -lSDL2


%.o: %.c
	$(CC) $(CFLAGS) $<


# all source subdirs for linker and compilator
#VPATH = ./ libs libs/sdl libs/sdl/libs

all : t3_sdl2.exe

# At linker below library paths and libraries must be at the end of line.
t3_sdl2.exe : t3_sdl2.o   
	$(CC) -o t3_sdl2.exe t3_sdl2.o $(LDLIBS)


clean:
	rm -f t3_sdl2.exe t3_sdl2.o


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

