#include <tchar.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>

void Greetings();
void HandleKeys();

int main( int argc, _TCHAR* argv[] )
{
	int code;
	bool doWork = true;

	while (doWork)
	{
		Greetings();
		HandleKeys();

		system("cls");
	}
}

void Greetings()
{
	std::cout << "Getter Full Name Windows OS" << std::endl;
	std::cout << std::endl;

	std::cout << "Press Escape to Exit Program" << std::endl;
	std::cout << "Press Enter to Execute Code" << std::endl;
}

void HandleKeys()
{
	switch (_getch())
	{
	case 13:
		break;
	case 27:
		exit(1);
		break;
	}
}