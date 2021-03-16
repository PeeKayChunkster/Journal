#pragma once
#include <string>

class Exception
{
private:
	std::wstring message;

public:
	Exception()
	{
		message = L"Esception!\nMessage wasn't specified.";
	}
	Exception(std::wstring m)
	{
		message = L"Exception!\n" + m;
	}

	std::wstring GetMessage() const
	{
		return message;
	}
};