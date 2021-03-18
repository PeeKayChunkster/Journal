#include "IOWinConsole.h"
#include <iostream>
#include "Database.h"
#include <conio.h>

void IOWinConsole::OutputString(std::string str)
{
	std::cout << str;
}

void IOWinConsole::Start(Database* pD)
{
	pDatabase = pD;
	while (true)
	{
		Clear(true);
		std::wcout << MAIN_MENU << '>';
		char c;
		c = _getch();
		switch (c)
		{
		case 'A':
		case 'a':
			AddEntry();
			break;
		case 'P':
		case 'p':
			PrintEntry();
			break;
		case EXIT:
			return;
		default:
			OutputString(UNKNOWN_OPERATION);
			break;
		}
	}
}

void IOWinConsole::AddEntry() 
{
	Clear();
	OutputString(ADDENTRY_MENU1);
	std::string name;
	std::getline(std::cin, name, '\n');
	Clear();
	OutputString(ADDENTRY_MENU2);
	std::string text;
	std::getline(std::cin, text, (char)SAVE_TEXT);
	Clear();
	OutputString(ADDENTRY_MENU3);
	char c;
	while (true)
	{
		c = _getch();
		if (c == 'y' || c == 'Y')
		{
			Database::Entry entry;
			entry.SetName(name);
			entry.SetText(text);
			pDatabase->PutEntry(entry);
			OutputString(ADDENTRY_MENU4);
			return;
		}
		else if(c == 'n' || c == 'N')
		{
			OutputString(ADDENTRY_MENU5);
			return;
		}
	}
}

void IOWinConsole::PrintEntry()
{
	Clear();
	OutputString(PRINTENTRY_MENU1);
	char c;
	c = _getch();
	switch (c)
	{
	case 'D':
	case 'd':
		Date date;
		int year, month, day, hour;
		Clear();
		OutputString(PRINTENTRY_ASK_YEAR);
		std::cin >> year;
		date.SetYear(year);
		Clear();
		OutputString(PRINTENTRY_ASK_MONTH);
		std::cin >> month;
		date.SetMonth(month);
		Clear();
		OutputString(PRINTENTRY_ASK_DAY);
		std::cin >> day;
		date.SetDay(day);
		Clear();
		OutputString(PRINTENTRY_ASK_HOUR);
		std::cin >> hour;
		date.SetHour(hour);
		Clear();
		DateSearchFlags dsf;
		dsf.year = Date::ValidYear(year);
		dsf.month = Date::ValidMonth(month);
		dsf.day = Date::ValidDay(day);
		dsf.hour = Date::ValidHour(hour);
		pDatabase->GetEntry(date, dsf);
	}
}

void IOWinConsole::Clear(bool waitForInput)
{
	if(waitForInput)
		_getch();
	system("CLS");
}

/*
std::string IOWinConsole::GetInputString(const char delim, bool echo)
{
	std::string str;
	char c;
	while (true)
	{
		c = _getch();
		if (c == BACKSPACE)
		{
			if (!str.empty())
			{
				str.pop_back();
				putwchar(c);
				putwchar(' ');
				putwchar(c);
			}
		}
		else if (c == delim)
		{
			putwchar('\n');
			return str;
		}
		else if (c == 13)
		{
			str.push_back(c);
			if (echo)
			{
				_putch('\n');
			}
		}
		else
		{
			str.push_back(c);
			if (echo)
			{
				putwchar(c);
			}
		}
	}
}
*/
