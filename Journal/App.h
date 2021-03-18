#pragma once
#include "Database.h"

class App
{
private:

	static constexpr char filename[] = "Data.dat";
	static constexpr int code = 0;

	class IO* pIOSystem;
	Database* pDatabase;

public:
	App() = delete;
	App(IO* io);
	~App();

	void LoadFile(std::string filename);
	void Go();
};