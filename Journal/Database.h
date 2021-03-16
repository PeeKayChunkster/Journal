#pragma once
#include "Date.h"
#include <list>

class Database
{
public:
	class Entry
	{
	private:
		std::wstring name;
		std::wstring text;
		Date date;
	public:
		std::wstring GetName() const;
		std::wstring GetText() const;
		Date GetDate() const;
		std::wstring GetFormattedEntry() const;
	};

	Database() = delete;
	Database(std::wstring filename);
	~Database();
	Database& operator=(const Database&);

	std::list<Entry> GetEntry(Date date) const;
	bool PutEntry(Entry entry);

private:
	std::list<Entry> entries;

	bool LoadFile(std::wstring filename);
	bool SaveFile(std::wstring filename);
};