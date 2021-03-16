#include "Database.h"
#include <sstream>
#include <algorithm>
#include "Exception.h"


bool Database::Entry::operator==(const Entry& rhs) const
{
	return (name == rhs.name && text == rhs.text && date == rhs.date);
}

bool Database::Entry::operator!=(const Entry& rhs) const
{
	return !(*this == rhs);
}

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
Database::Database(std::wstring fn)
{
	filename = fn;

	if (!LoadFile(filename))
	{
		throw "Data file wasn't found. Creating new database.";
	}
}

Database& Database::operator=(const Database& rhs)
{
	entries.clear();
	filename = rhs.filename;
	for (const Entry e : rhs.entries)
	{
		entries.push_back(e);
	}
	return *this;
}

Database::~Database()
{
	if(!SaveFile(filename)) 
	{
		throw Exception(L"Couldn't save file on a disk.");
	}
}

std::list<Database::Entry> Database::GetEntry(Entry entry) const
{
	std::list<Entry> foundList;
	std::list<Entry>::const_iterator iter = entries.begin();
	while (iter != entries.end())
	{
		if (*iter == entry)
		{
			foundList.push_back(*iter);
		}
	}
	return foundList;
}

std::list<Database::Entry> Database::GetEntry(Date date) const
{
	std::list<Entry> foundList;
	std::list<Entry>::const_iterator iter = entries.begin();
	while (iter != entries.end())
	{
		if (iter->GetDate() == date)
		{
			foundList.push_back(*iter);
		}
	}
	return foundList;
}

std::list<Entry> Database::GetEntry(std::wstring name) const
{
	return std::list<Entry>();
}

bool Database::PutEntry(Entry entry)
{
	return false;
}

//*****************************//