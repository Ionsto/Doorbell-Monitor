#include "Serial.h"
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#define EXPORT extern "C" _declspec(dllexport)

EXPORT double WinMinimize(char* handle) {
	LPCSTR window = TEXT(handle);
	HWND hWnd = FindWindow(NULL, window);
	ShowWindow(hWnd, SW_MINIMIZE);
	return 0;
}
int main(int argc, char ** args)
{
	CSerial connection = CSerial();
	char lpBuffer[500];
	if (connection.Open(3, 9600))
	{
		std::cout << ("Port open passed") << std::endl;
		//flush it
		std::cout << connection.ReadDataWaiting() << std::endl;
		connection.ReadData(lpBuffer, 500);
	}
	else
	{
		std::cout << ("Port open failed") << std::endl;
		return 0;
	}
	WinMinimize("PC Doorbell monitor.exe");
	try {
		while (true)
		{
			int nBytesRead = connection.ReadData(lpBuffer, 500);
			for (int i = 0; i < nBytesRead; ++i)
			{
				std::cout << lpBuffer[i];
			}
			if (nBytesRead > 0)
			{
				std::cout << (char)7;
				Sleep(600);
				std::cout << (char)7;
			}
			Sleep(1000);
		}
	}
	catch (int err)
	{
		//We don't care too much tbh
	}
	//Techinicaly done when we go out of scope, but still a good idea
	connection.Close();
}