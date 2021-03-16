#include "Date.h"
#include <sstream>
#include <ctime>

Date::Date()
{
	SetCurrentDate();
}

bool Date::operator==(const Date& rhs)
{
	return (year == rhs.year &&
		month == rhs.month &&
		day == rhs.day &&
		hour == rhs.hour &&
		minute == rhs.minute &&
		second == rhs.second);
}

bool Date::operator!=(const Date& rhs)
{
	return !(*this == rhs);
}

void Date::SetYear(const int y)
{
	if (y > 0)
	{
		year = y;
	}
}

void Date::SetMonth(const int m)
{
	if (m > 0 && m < 12)
	{
		month = m;
	}
}

void Date::SetDay(const int d)
{
	if (d > 0 && d < 32)
	{
		day = d;
	}
}

void Date::SetHour(const int h)
{
	if (h >= 0 && h <= 24)
	{
		hour = h;
	}
}

void Date::SetMinute(const int m)
{
	if (m >= 0 && m < 60)
	{
		minute = m;
	}
}

void Date::SetSecond(const int s)
{
	if (s >= 0 && s <= 60)
	{
		second = s;
	}
}

int Date::GetYear() const
{
	return year;
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}

int Date::GetHour() const
{
	return hour;
}

int Date::GetMinute() const
{
	return minute;
}

int Date::GetSecond() const
{
	return second;
}

void Date::SetCurrentDate()
{
	time_t t = time(&t);
	auto sysTime = localtime(&t);
	SetYear(sysTime->tm_year);
	SetMonth(sysTime->tm_mon);
	SetDay(sysTime->tm_mday);
	SetHour(sysTime->tm_hour);
	SetMinute(sysTime->tm_min);
	SetSecond(sysTime->tm_sec);
}

std::wstring Date::GetFormattedShort() const
{
	std::wostringstream date;
	date << day << "." << month << "." << year << std::endl;
	return date.str();
}

std::wstring Date::GetFormattedLong() const
{
	std::wostringstream date;
	date << GetFormattedShort() << hour << ":" << minute << ":" << second << std::endl;
	return date.str();
}
