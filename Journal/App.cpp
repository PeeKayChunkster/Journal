#include "App.h"
#include "Exception.h"
#include "IO.h"

App::App(IO* pio) : pIOSystem(pio)
{
	pDatabase = new Database();
	pDatabase->LoadFile(filename, code);
	if (pDatabase->load_fail)
	{
		pIOSystem->OutputString(std::string("Couldn't load file with name \"") + filename + "\". Creating new database.\n");
	}
}

App::~App()
{
	pDatabase->SaveFile(filename, code);
	delete pDatabase;
}

void App::LoadFile(std::string filename)
{
	try
	{
		pDatabase->LoadFile(filename);
	}
	catch (const Exception& exc)
	{
		pIOSystem->OutputString(exc.GetMessage());
	}
}

void App::Go()
{
	pIOSystem->Start(pDatabase);
}
