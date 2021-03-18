#pragma once
#include <string>

class IO
{
public:

	virtual void OutputString(std::string) = 0;
	virtual void Start(class Database* pD) = 0;

protected:
	class Database* pDatabase = nullptr;
};