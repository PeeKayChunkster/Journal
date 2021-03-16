#include "Database.h"
#include <sstream>
#include <fstream>
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
		throw L"Data file wasn't found. Creating new database.";
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

std::optional<Database::Entry> Database::GetEntry(const Entry& entry) const
{
	std::list<Entry>::const_iterator iter = entries.begin();
	while (iter != entries.end())
	{
		if (*iter == entry)
		{
			return std::optional<Entry>(*iter);
		}
	}
	return std::optional<Entry>();
}

std::list<Database::Entry> Database::GetEntry(const Date date) const
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

std::list<Database::Entry> Database::GetEntry(const std::wstring name) const
{
	std::list<Entry> foundList;
	std::list<Entry>::const_iterator iter = entries.begin();
	while (iter != entries.end())
	{
		if (iter->GetName() == name)
		{
			foundList.push_back(*iter);
		}
	}
	return foundList;
}

void Database::PutEntry(Entry& entry)
{
	entries.emplace_back(entry);
}

bool Database::EraseEntry(Entry& entry)
{
	std::list<Entry>::const_iterator iter = entries.begin();
	while (iter != entries.end())
	{
		if (*iter == entry)
		{
			entries.erase(iter);
			return true;
		}
	}
	return false;
}

bool Database::LoadFile(std::wstring filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in)
	{
		if (in.bad())
		{
			throw Exception(L"Could't load a file with name \"" + filename + L"\"");
			return false;
		}
		else
		{
			return false;
		}
	}
	
	entries.clear();
	int entrySize;
	Entry buffer;
	while (true)
	{
		in.read(reinterpret_cast<char*>(&entrySize), sizeof(int));
		in.read(reinterpret_cast<char*>(&buffer), entrySize);
		if (!in)
		{
			break;
		}
		entries.push_back(buffer);
	}
	in.close();
	return true;
}

bool Database::SaveFile(std::wstring filename)
{
	std::ofstream out(filename, std::ios::binary);
	if (!out)
	{
		throw Exception(L"Could't save a file with name \"" + filename + L"\"");
		return false;
	}

	entries.clear();
	int entrySize;
	for(Entry& e : entries)
	{
		entrySize = sizeof(e);
		out.write(reinterpret_cast<char*>(&entrySize), sizeof(int));
		out.write(reinterpret_cast<char*>(&e), sizeof(e));
	}
	out.close();
	return true;
}

//*****************************//