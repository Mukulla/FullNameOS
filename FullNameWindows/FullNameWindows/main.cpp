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

std::vector<std::wstring> Info;

void FillVector();
void Greetings();
void HandleKeys();
void GetNameWindows();
std::wstring GetRegSubKey(LPCWSTR subKeysPath, std::wstring surrentsubKeysPath);
std::wstring TCHARToString(TCHAR someChar[]);
LPWSTR ConvertToLPWSTR(const std::wstring& someString);
std::wstring GetStringWithBitWindows();
BOOL Is64BitWindows();
void ResetTCHAR(TCHAR* SomeText);

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
	LPCWSTR spacer = L" ";
	LPCWSTR subKeysPath = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	
	std::vector<std::wstring> subKeys;
	subKeys.push_back(L"ProductName");
	subKeys.push_back(L"CurrentBuild");
	//subKeys.push_back(L"CSDVersion");
	subKeys.push_back(L"BuildLabEx");
	subKeys.push_back(L"ReleaseId");
	subKeys.push_back(L"SystemRoot");

	std::wstring fullNameWindows;

	
	Info.push_back(L" ");

	fullNameWindows = L"Operating System: " + GetRegSubKey(subKeysPath, subKeys[0]);
	fullNameWindows += spacer + GetStringWithBitWindows();
	fullNameWindows += L" (Build " + GetRegSubKey(subKeysPath, subKeys[1]) + L"),";
	fullNameWindows += spacer + GetRegSubKey(subKeysPath, subKeys[2]);
	fullNameWindows += spacer + GetRegSubKey(subKeysPath, subKeys[3]);

	Info.push_back(L"SystemRoot " + GetRegSubKey(subKeysPath, subKeys[4]));
	Info.push_back(fullNameWindows);

	WorkDone = true;
}

std::wstring GetRegSubKey(LPCWSTR subKeysPath, std::wstring surrentsubKeysPath)
{
	DWORD bufferSize = BUFFER_SIZE;
	TCHAR tempoBuffer[BUFFER_SIZE];

	RegGetValue(HKEY_LOCAL_MACHINE, subKeysPath, ConvertToLPWSTR(surrentsubKeysPath), RRF_RT_ANY, NULL, tempoBuffer, &bufferSize);

	return TCHARToString(tempoBuffer);
}

std::wstring TCHARToString(TCHAR someChar[])
{
	std::wstring tempo(someChar);
	return tempo;
}

LPWSTR ConvertToLPWSTR(const std::wstring& someString)
{
	LPWSTR ws = new wchar_t[someString.size() + 1];
	std::copy(someString.begin(), someString.end(), ws);
	ws[someString.size()] = 0;
	return ws;
}

std::wstring GetStringWithBitWindows()
{
	if (Is64BitWindows())
	{
		return L"64 bit";
	}
	return L"32 bit";
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

void ResetTCHAR(TCHAR* SomeText)
{
	for (size_t i = 0; i < BUFFER_SIZE; ++i)
	{
		SomeText[i] = '\0';
	}
}