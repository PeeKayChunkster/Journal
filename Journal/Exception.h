#pragma once
#include <string>

class Exception
{
private:
	std::string message;

public:
	Exception()
	{
		message = "Esception!\nMessage wasn't specified.";
	}
	Exception(std::string m)
	{
		message = "Exception!\n" + m;
	}

	std::string GetMessage() const
	{
		return message;
	}
};