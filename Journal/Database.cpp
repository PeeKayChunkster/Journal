#include "Database.h"
#include <sstream>
#include <fstream>
#include "Exception.h"

//***	ENTRY STUFF		***//

bool Database::Entry::operator==(const Entry& rhs) const
{
	return (name == rhs.name && text == rhs.text && date == rhs.date);
}

bool Database::Entry::operator!=(const Entry& rhs) const
{
	return !(*this == rhs);
}

std::string Database::Entry::GetName() const
{
	return name;
}

std::string Database::Entry::GetText() const
{
	return text;
}

Date Database::Entry::GetDate() const
{
	return date;
}

void Database::Entry::SetName(std::string n)
{
	name = n;
}

void Database::Entry::SetText(std::string t)
{
	text = t;
}

std::string Database::Entry::GetFormattedEntry() const
{
	std::ostringstream ss;
	ss << date.GetFormattedLong() << "Name: \n" << GetName() << std::endl << "Text: \n" << GetText() << std::endl;
	return ss.str();
}

//******************************//







//***	DATABASE STUFF		***//

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

std::list<Database::Entry> Database::GetEntry(const Date date, const DateSearchFlags dsf) const
{
	std::list<Entry> foundList;
	std::list<Entry>::const_iterator iter;
	for (iter = entries.begin(); iter != entries.end(); iter++)
	{
		if (dsf.year)
		{
			if (iter->GetDate().GetYear() == date.GetYear())
			{
				if (dsf.month)
				{
					if (iter->GetDate().GetMonth() == date.GetMonth())
					{
						if (dsf.day)
						{
							if (iter->GetDate().GetDay() == date.GetDay())
							{
								if (dsf.hour)
								{
									if (iter->GetDate().GetHour() == date.GetHour())
									{
										foundList.push_back(*iter);
									}
								}
								else
								{
									foundList.push_back(*iter);
								}
							}
						}
						else
						{
							foundList.push_back(*iter);
						}
					}
				}
				else
				{
					foundList.push_back(*iter);
				}
			}
		}
	}
	return foundList;
}

std::list<Database::Entry> Database::GetEntry(const std::string name) const
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

bool Database::LoadFile(std::string filename, const int key)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in)
	{
		if (in.bad())
		{
			throw Exception("Could't load a file with name \"" + filename + "\"");
			return false;
		}
		else
		{
			load_fail = true;
			return false;	// could not find file
		}
	}
	
	entries.clear();
	int entrySize;
	while (true)
	{
		Entry* buffer = new Entry();
		in.read(reinterpret_cast<char*>(&entrySize), sizeof(int));
		in.read(reinterpret_cast<char*>(buffer), entrySize);

		if (key != 0)	// Decode entry
		{
			buffer->SetName(DecodeString(buffer->GetName(), key));
			buffer->SetText(DecodeString(buffer->GetText(), key));
		}

		if (!in)
		{
			break;
		}
		entries.push_back(*buffer);
	}
	in.close();
	return true;
}

bool Database::SaveFile(std::string filename, const int code)
{
	if (entries.size() == 0) return true;

	std::ofstream out(filename, std::ios::binary);
	if (!out)
	{
		throw Exception("Could't save a file with name \"" + filename + "\"");
		return false;
	}

	int entrySize;
	for(Entry& e : entries)
	{
		if (code != 0)	// code entry strings
		{
			e.SetName(CodeString(e.GetName(), code));
			e.SetText(CodeString(e.GetText(), code));
		}

		entrySize = sizeof(e);
		out.write(reinterpret_cast<char*>(&entrySize), sizeof(int));
		out.write(reinterpret_cast<char*>(&e), sizeof(e));
	}
	out.close();
	return true;
}

std::string Database::CodeString(std::string str, const int code)
{
	for (char& c : str)
	{
		c += code;
	}
	return str;
}

std::string Database::DecodeString(std::string str, const int key)
{
	for (char& c : str)
	{
		c -= key;
	}
	return str;
}

//*****************************//