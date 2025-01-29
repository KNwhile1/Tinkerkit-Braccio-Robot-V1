void serial_Write(char choice[]) {
	
	HANDLE hComm;    // using the serial port
    char ComPortName[] = "\\\\.\\COM8";    // it depends on device
    BOOL Status;

    hComm = CreateFile(ComPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);    // opening the serial port

    DCB dcbSerialParams = {0};    // setting the parameters for the serial port
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);    // DCB = Data Control Block

    Status = GetCommState(hComm, &dcbSerialParams);    // retrieving the current settings

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    Status = SetCommState(hComm, &dcbSerialParams);    // configuring the port according to dcb structures

    COMMTIMEOUTS timeouts = {0};    // setting timeouts

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    char lpBuffer[10];    // determining the data to be written to the serial port

    strcpy(lpBuffer, choice);
    
	DWORD dNoOFBytestoWrite;
    DWORD dNoOfBytesWritten = 0;

    dNoOFBytestoWrite = sizeof(lpBuffer);    // calculating the amount of bytes

    Status = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);    // writing the data to the serial port
                       
    CloseHandle(hComm);    // closing the serial port
	
}


void serial_Read() {
	
	HANDLE hComm;    // using the serial port
    char ComPortName[] = "\\\\.\\COM8";    // it depends on device
    BOOL Status;
    DWORD dwEventMask;
    char TempChar;
    char SerialBuffer[256];
    DWORD NoBytesRead;

    hComm = CreateFile(ComPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);    // opening the serial port
    
    DCB dcbSerialParams = {0};    // setting the parameters for the serial port
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);    // DCB = Data Control Block

    Status = GetCommState(hComm, &dcbSerialParams);    // retrieving the current settings

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    Status = SetCommState(hComm, &dcbSerialParams);    // configuring the port according to dcb structures

    COMMTIMEOUTS timeouts = {0};    // setting timeouts
    
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(hComm, &timeouts) == FALSE)
        return;
    
    Status = SetCommMask(hComm, EV_RXCHAR);    // configuring windows for reception
    Status = WaitCommEvent(hComm, &dwEventMask, NULL);    // waiting for the reception
   
    int i = 0;
    do {
        Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);    // reading the data from the serial port
        SerialBuffer[i] = TempChar;
        i++;
    } while (NoBytesRead > 0);

    int j = 0;
    for (j = 0; j < i - 1; j++)
        printf("%c", SerialBuffer[j]);    // printing out the data

    CloseHandle(hComm);    // closing the serial port

}
