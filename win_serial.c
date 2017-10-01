#include <stdio.h>
#include "windows.h"
#include "win_serial.h"


// Below example is from pdf.
// There is another good article:
// https://www.codeproject.com/Articles/3061/Creating-a-Serial-communication-on-Win
//


// Error support
/*
As you've probably noticed, after each system-call, I've included a comment saying you should handle errors.
This is ALWAYS good programming practice, but is especially important with I/O functions, since they do
tend to fail more often that most functions. In any event, all the above functions return 0 whenever they fail
and something other than 0 on success. To find out exactly what the error was, you can call the function
GetLastError(), which returns the error code as a DWORD. To convert this into a string that makes sense,
you can use the FormatMessage function as follows:
*/

char lastError[1024];
//call this fuunction:
#if 0
FormatMessage(
              FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
              NULL,
              GetLastError(),
              MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
              lastError,
              1024,
              NULL);
#endif


void serialTest()
{

  // Open
  HANDLE hSerial;
  hSerial = CreateFile("COM1",
	                    GENERIC_READ | GENERIC_WRITE,
	                    0,
	                    0,
	                    OPEN_EXISTING,
	                    FILE_ATTRIBUTE_NORMAL,
	                    0);

  if ( hSerial==INVALID_HANDLE_VALUE )
  {
    if( GetLastError()==ERROR_FILE_NOT_FOUND )
    {
      //serial port does not exist. Inform user.
      printf("Err: Open port: serial port does not exist \n");
    }
    //some other error occurred. Inform user.
    printf("Err: Open port: some other error occurred \n");
  }

  //Setting paramteres
  DCB dcbSerialParams = {0};
  dcbSerial.DCBlength = sizeof(dcbSerialParams);

  if ( !GetCommState(hSerial, &dcbSerialParams) )
  {
    //error getting state
    printf("Err: Setting parameters: error getting state \n");
  }

  dcbSerialParams.BaudRate=CBR_9600;
  dcbSerialParams.ByteSize=8;
  dcbSerialParams.StopBits=ONESTOPBIT;
  dcbSerialParams.Parity=NOPARITY;

  if ( !SetCommState(hSerial, &dcbSerialParams ) )
  {
    //error setting serial port state
    printf("Err: Setting parameters: error setting serial port state \n");
  }


  // Setting timeouts
  COMMTIMEOUTS timeouts={0};
  timeouts.ReadIntervalTimeout=50;
  timeouts.ReadTotalTimeoutConstant=50;
  timeouts.ReadTotalTimeoutMultiplier=10;
  timeouts.WriteTotalTimeoutConstant=50;
  timeouts.WriteTotalTimeoutMultiplier=10;
  if ( !SetCommTimeouts(hSerial, &timeouts ) )
  {
    //error occureed. Inform user
	  printf("Err: Setting timeouts: error occured \n");
  }


  //todo: any loop with condition here
  //Reading/Writing data
  //Note that dwBytesRead will contain the number of bytes actually read by the ReadFile operation.
  //Writing data is exactly the same, except the function is called WriteFile.
  //char szBuff[n + 1] = {0};
  char szBuff[4096 + 1] = {0};
  DWORD dwBytesRead = 0;
  if ( !ReadFile(hSerial, szBuff, n, &dwBytesRead, NULL) )
  {
    //error occurred. Report to user.
	printf("Err: Read data: error occured \n");

  }
  printf ("%s \n", szBuff);


  //Close
  CloseHandle(hSerial);


}
