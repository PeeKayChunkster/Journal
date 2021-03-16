#pragma once
#include "Database.h"
#include "IO.h"

class App
{
private:
	IO* IOSystem;
	Database database;

public:
	App(IO* io);

	void Go();
};