#include <windows.h>
#include <tchar.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>

#define BUFFER_SIZE 1024

#if defined(UNICODE) || defined(_UNICODE)
#define tcout std::wcout
#else
#define tcout std::cout
#endif

void FillVector();
void Greetings();
void HandleKeys();
void GetNameWindows();
std::wstring GetRegSubKey(LPCWSTR subKeysPath, LPCWSTR surrentsubKeysPath);
std::wstring GetStringWithBitWindows();
BOOL Is64BitWindows();

std::vector<std::wstring> Info;
bool WorkDone = false;

int main( int argc, _TCHAR* argv[] )
{
	FillVector();

	while (1)
	{
		system("cls");

		Greetings();
		HandleKeys();
	}
}

void FillVector()
{
	Info.push_back(L"Getter Full Name Windows OS");
	Info.push_back(L" ");
	Info.push_back(L"Press Escape to Exit Program");
	Info.push_back(L"Press Enter to Execute Code");
}

void Greetings()
{
	for(int i = 0; i < Info.size(); ++i)
	{
		std::wcout << Info[i] << std::endl;
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
			Info.push_back(L"Failed to read fullname current system");
		}		
		break;
	case 27:
		exit(1);
		break;
	}
}

void GetNameWindows()
{
	LPCWSTR subKeysPath = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	
	LPCWSTR subKeys[5];
	subKeys[0] = L"ProductName";
	subKeys[1] = L"CurrentBuild";
	subKeys[2] = L"CSDVersion";
	subKeys[3] = L"SystemRoot";

	std::wstring fullNameWindows;

	
	Info.push_back(L" ");

	fullNameWindows = L"Operating System:" + GetRegSubKey(subKeysPath, subKeys[0]);
	fullNameWindows += GetStringWithBitWindows();
	fullNameWindows += L" (Build " + GetRegSubKey(subKeysPath, subKeys[1]) + L"),";
	fullNameWindows += GetRegSubKey(subKeysPath, subKeys[2]);

	Info.push_back(L"SystemRoot " + GetRegSubKey(subKeysPath, subKeys[3]));
	Info.push_back(fullNameWindows);

	WorkDone = true;
}

std::wstring GetRegSubKey(LPCWSTR subKeysPath, LPCWSTR surrentsubKeysPath)
{
	DWORD bufferSize = BUFFER_SIZE;
	TCHAR tempoBuffer[BUFFER_SIZE];

	if (RegGetValue(HKEY_LOCAL_MACHINE, subKeysPath, surrentsubKeysPath, RRF_RT_ANY, NULL, tempoBuffer, &bufferSize) == 0)
	{
		std::wstring tempo(tempoBuffer);
		return L" " + tempo;
	}
	return L"";
}

std::wstring GetStringWithBitWindows()
{
	return Is64BitWindows() ? L" 64 bit" : L" 32 bit";
}

BOOL Is64BitWindows()
{
	#if defined(_WIN64)
		return TRUE;  // 64-bit programs run only on Win64
	#elif defined(_WIN32)
		// 32-bit programs run on both 32-bit and 64-bit Windows
		// so must sniff
		BOOL f64 = FALSE;
		return IsWow64Process(GetCurrentProcess(), &f64) && f64;
	#else
		return FALSE; // Win64 does not support Win16
	#endif
}