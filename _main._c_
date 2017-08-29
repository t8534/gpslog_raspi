/*
 * main.c
 * 
 * Copyright 2017  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

// http://www.raspberry-projects.com/pi/programming-in-c/compilers-and-ides/geany/creating-a-project


#if 0
#include <stdio.h>

int main(int argc, char **argv)
{
	printf("Start \n");
	//flush();
	return 0;
}
#endif


// serialRead test
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringSerial.h>

int main ()
{
  int fd ;
  
  printf("Test: readSerial: \n");
  

  if ((fd = serialOpen ("/dev/ttyAMA0", 38400)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

// Loop, getting and printing characters

  for (;;)
  {
    //putchar (serialGetchar (fd)) ;
    //printf (" -> %3d", serialGetchar (fd)) ;
    printf (" -> %d \n", serialGetchar (fd)) ;
    fflush (stdout) ;
  }
}


////////////////////////////////////////////////
// serialTest

#if 0
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int fd ;
  int count ;
  unsigned int nextTime ;

  if ((fd = serialOpen ("/dev/ttyAMA0", 115200)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  nextTime = millis () + 300 ;

  for (count = 0 ; count < 256 ; )
  {
    if (millis () > nextTime)
    {
      printf ("\nOut: %3d: ", count) ;
      fflush (stdout) ;
      serialPutchar (fd, count) ;
      nextTime += 300 ;
      ++count ;
    }

    delay (3) ;

    while (serialDataAvail (fd))
    {
      printf (" -> %3d", serialGetchar (fd)) ;
      fflush (stdout) ;
    }
  }

  printf ("\n") ;
  return 0 ;
}

#endif
