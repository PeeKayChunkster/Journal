#pragma once
#include "Date.h"
#include <list>
#include <optional>

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

	std::optional<Entry> GetEntry(const Entry& entry) const;
	std::list<Entry> GetEntry(const Date date) const;
	std::list<Entry> GetEntry(const std::wstring name) const;
	void PutEntry(Entry& entry);
	bool EraseEntry(Entry& entry);

private:
	std::list<Entry> entries;
	std::wstring filename;

	bool LoadFile(std::wstring filename);
	bool SaveFile(std::wstring filename);
};