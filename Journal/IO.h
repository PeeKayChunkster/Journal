#pragma once
#include <string>



class IO
{
public:
	enum class IOCOMMAND { CREATE_ENTRY, ERASE_ENTRY, PRINT_ENTRY };

	IO() = delete;
	IO(App* app)
	{
		app = app;
	}

	virtual void OutputString(std::wstring) = 0;
	virtual void ShowMainMenu() = 0;
	virtual void ShowCreateEntryMenu() = 0;
	virtual void ShowEraseEntryMenu() = 0;
	virtual void ShowPrintEntryMenu() = 0;

private:
	class App* app;

	void ExecuteCommand(IOCOMMAND c, Database::Entry* pEntry = nullptr)	// send IOCCOMMAND to App::ExecuteCommand()
	{
		app->ExecuteCommand(c, pEntry);
	}

};