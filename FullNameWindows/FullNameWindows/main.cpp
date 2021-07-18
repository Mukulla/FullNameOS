#include <windows.h>
#include <tchar.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>

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
std::string TCHARToString(TCHAR someChar[]);

bool WorkDone = false;

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
		if (WorkDone)
		{
			return;
		}			

		try
		{
			GetNameWindows();
		}
		catch (const std::exception&)
		{
			std::cout << "Failed to read full name current system" << std::endl;
		}
		
		break;
	case 27:
		exit(1);
		break;
	}
}

void GetNameWindows()
{	
    DWORD BufferSize = MAX_PATH;
	TCHAR  tempoBuffer[MAX_PATH];

	LPCWSTR subKeyReg = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	std::string fullNameWindows;

	
	Info.push_back(" ");
    RegGetValue(HKEY_LOCAL_MACHINE, subKeyReg, L"ProductName", RRF_RT_ANY, NULL, tempoBuffer, &BufferSize);
	fullNameWindows = "Operating System: " + TCHARToString(tempoBuffer);
    //Info.push_back(TCHARToString(tempoBuffer));

	RegGetValue(HKEY_LOCAL_MACHINE, subKeyReg, L"CurrentBuild", RRF_RT_ANY, NULL, tempoBuffer, &BufferSize);
	fullNameWindows += " ( Build " + TCHARToString(tempoBuffer) + " ), ";
	//Info.push_back(TCHARToString(tempoBuffer));

	RegGetValue(HKEY_LOCAL_MACHINE, subKeyReg, L"ReleaseId", RRF_RT_ANY, NULL, tempoBuffer, &BufferSize);
	fullNameWindows += TCHARToString(tempoBuffer);

	Info.push_back(fullNameWindows);	
	
	GetWindowsDirectory(tempoBuffer, MAX_PATH);
	Info.push_back("SystemRoot " + TCHARToString(tempoBuffer));

	WorkDone = true;
}

std::string TCHARToString(TCHAR someChar[])
{
	std::wstring arr_w(someChar);
	std::string tempo(arr_w.begin(), arr_w.end());

	return tempo;
}