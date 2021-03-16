#include "Database.h"
#include <sstream>


//***	ENTRY STUFF		***//
std::wstring Database::Entry::GetName() const
{
	return name;
}

std::wstring Database::Entry::GetText() const
{
	return text;
}

Date Database::Entry::GetDate() const
{
	return date;
}

std::wstring Database::Entry::GetFormattedEntry() const
{
	std::wostringstream ss;
	ss << date.GetFormattedLong() << GetName() << std::endl << GetText() << std::endl;
	return ss.str();
}

//******************************//


//***	DATABASE STUFF		***//
Database::Database()
{
	LoadFile()
}

//*****************************//