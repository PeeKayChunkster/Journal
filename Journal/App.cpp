#include "App.h"
#include "Exception.h"

App::App(IO* pio) : pIOSystem(pio)
{}

bool App::Start(std::wstring filename)
{
	try
	{
		pDatabase = new Database(filename);
		pIOSystem->ShowMainMenu();
	}
	catch (const Exception& exc)	// Bad exception
	{
		pIOSystem->OutputString(exc.GetMessage());
		return false;
	}
	catch (const wchar_t* message)	// database wasn't found on disk, need to create new database
	{
		pIOSystem->OutputString(message);
		return true;
	}
}

void App::ExecuteCommand(IO::IOCOMMAND command, Database::Entry* pEntry)
{
	switch (command)
	{
	case IO::IOCOMMAND::CREATE_ENTRY:
		if (pEntry != nullptr)
		{
			pDatabase->PutEntry(*pEntry);
			pIOSystem->OutputString(L"Entry created.\n");
		}
		break;
	case IO::IOCOMMAND::ERASE_ENTRY:
		if (pEntry != nullptr)
		{
			if (pDatabase->EraseEntry(*pEntry))
			{
				pIOSystem->OutputString(L"Entry erased.");
			}
			else
			{
				pIOSystem->OutputString(L"Entry wasn't found");
			}
		}
		break;
	case IO::IOCOMMAND::PRINT_ENTRY:
		if (pEntry != nullptr)
		{
			auto ent = pDatabase->GetEntry(*pEntry);
			if (ent.has_value())
			{
				pIOSystem->OutputString(ent.value().GetFormattedEntry());
			}
			else
			{
				pIOSystem->OutputString(L"Requested entry wasn't found.\n");
			}
		}
	}

		
}

void App::Go()
{
	
}
