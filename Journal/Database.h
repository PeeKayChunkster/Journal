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
		bool operator==(const Entry& rhs) const;
		bool operator!=(const Entry& rhs) const;

		std::wstring GetName() const;
		std::wstring GetText() const;
		Date GetDate() const;
		std::wstring GetFormattedEntry() const;
	};

	Database() = delete;
	Database(std::wstring filename);
	~Database();
	Database& operator=(const Database&);

	std::list<Entry> GetEntry(Entry entry) const;
	std::list<Entry> GetEntry(Date date) const;
	std::list<Entry> GetEntry(std::wstring  name) const;
	bool PutEntry(Entry entry);

private:
	std::list<Entry> entries;
	std::wstring filename;

	bool LoadFile(std::wstring filename);
	bool SaveFile(std::wstring filename);
};