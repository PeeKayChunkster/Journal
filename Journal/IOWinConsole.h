#pragma once
#include "IO.h"

constexpr auto MAIN_MENU = 
	"(A)dd entry.\n"
	"(P)rint entry.\n"
	;
constexpr auto ADDENTRY_MENU1 = "Enter name of the entry:\n>";
constexpr auto ADDENTRY_MENU2 = "Enter text of the entry(ctrl+o to save entry):\n>";
constexpr auto ADDENTRY_MENU3 = "Save this entry?(y/n):\n>";
constexpr auto ADDENTRY_MENU4 = "Entry saved.\n";
constexpr auto ADDENTRY_MENU5 = "Entry deleted.\n";
constexpr auto PRINTENTRY_MENU1 =
"Search by (d)ate\n"
"Search by (n)ame\n"
"Print (l)ast x amount of entrys\n";
constexpr auto PRINTENTRY_ASK_YEAR = "Enter year:\n>";
constexpr auto PRINTENTRY_ASK_MONTH = "Enter month(1-12):\n>";
constexpr auto PRINTENTRY_ASK_DAY = "Enter day(1-31):\n>";
constexpr auto PRINTENTRY_ASK_HOUR = "Enter hour(0-23):\n>";
constexpr auto UNKNOWN_OPERATION = "Unknown operation.\n";
constexpr auto SAVE_TEXT = 15;
constexpr auto EXIT = 24;
constexpr auto BACKSPACE = 8;

class IOWinConsole : public IO
{
private:
	unsigned int buffer_lenght = 10000;

	void AddEntry();
	void PrintEntry();
	void Clear(bool waitForInput = false);
	//std::string GetInputString(const char delim, bool echo = true);

public:
	virtual void OutputString(std::string) override;
	virtual void Start(Database* pD) override;

	void OutputSeparator(char separator = '-', int numberOf = 100);
};