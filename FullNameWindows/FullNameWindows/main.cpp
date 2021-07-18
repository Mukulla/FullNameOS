#include <windows.h>
#include <tchar.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>

#define TOTAL_BYTES_READ 1024
#define OFFSET_BYTES 1024
#define BUFFER 8192

#if defined(UNICODE) || defined(_UNICODE)
#define tcout std::wcout
#else
#define tcout std::cout
#endif

std::vector<std::string> Info;

void FillVector();
void Greetings();
void HandleKeys();
void GetNameWindows();

int main( int argc, _TCHAR* argv[] )
{
	int code;
	bool doWork = true;

	FillVector();

	while (doWork)
	{
		system("cls");

		Greetings();
		HandleKeys();
	}
}

void FillVector()
{
	Info.push_back("Getter Full Name Windows OS");
	Info.push_back(" ");
	Info.push_back("Press Escape to Exit Program");
	Info.push_back("Press Enter to Execute Code");
}

void Greetings()
{
	for(std::string item : Info)
	{
		std::cout << item << std::endl;
	}
}

void HandleKeys()
{
	switch (_getch())
	{
	case 13:
		GetNameWindows();
		break;
	case 27:
		exit(1);
		break;
	}
}

void GetNameWindows()
{
	TCHAR  infoBuf[MAX_PATH];
	GetWindowsDirectoryW(infoBuf, MAX_PATH);
	//GetSystemDirectory(infoBuf, MAX_PATH);

	std::wstring arr_w(infoBuf);
	std::string tempo(arr_w.begin(), arr_w.end());

	Info.push_back(tempo);
	//tcout << infoBuf << std::endl;

    char value[255];
    DWORD BufferSize = BUFFER;
    RegGetValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"SystemRoot", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
    //std::cout << value << std::endl;
    Info.push_back(value);
}