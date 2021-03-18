#pragma once
#include "Date.h"
#include <list>
#include <optional>

struct DateSearchFlags
{
	bool year;
	bool month;
	bool day;
	bool hour;
};

class Database
{
public:

	//***********CLASS ENTRY*************//
	class Entry
	{
	private:
		std::string name;
		std::string text;
		Date date;
	public:
		bool operator==(const Entry& rhs) const;
		bool operator!=(const Entry& rhs) const;

		std::string GetName() const;
		std::string GetText() const;
		Date GetDate() const;

		void SetName(std::string);
		void SetText(std::string);

		std::string GetFormattedEntry() const;
	};
	//**********************************//

	Database& operator=(const Database&);

	bool load_fail = false;

	std::optional<Entry> GetEntry(const Entry& entry) const;
	std::list<Entry> GetEntry(const Date date, const DateSearchFlags dsf) const;
	std::list<Entry> GetEntry(const std::string name) const;
	void PutEntry(Entry& entry);
	bool EraseEntry(Entry& entry);
	bool LoadFile(std::string filename, const int key = 0);
	bool SaveFile(std::string filename, const int code = 0);
private:
	std::list<Entry> entries;
	std::string filename;
	
	std::string CodeString(std::string str, const int code = 3);
	std::string DecodeString(std::string str, const int key = 3);
};