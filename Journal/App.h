#pragma once
#include "Database.h"
#include "IO.h"

class App
{
private:
	IO* pIOSystem;
	Database* pDatabase;

public:
	App() = delete;
	App(IO* io);

	bool Start(std::wstring filename);
	void ExecuteCommand(IO::IOCOMMAND command, Database::Entry* pEntry);
	void Go();
};