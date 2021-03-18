#include "Date.h"
#include <sstream>
#include <ctime>

Date::Date()
{
	SetCurrentDate();
}

bool Date::operator==(const Date& rhs) const
{
	return (year == rhs.year &&
		month == rhs.month &&
		day == rhs.day &&
		hour == rhs.hour &&
		minute == rhs.minute &&
		second == rhs.second);
}

bool Date::operator!=(const Date& rhs) const
{
	return !(*this == rhs);
}

void Date::SetYear(const int y)
{
	if (ValidYear(y))
	{
		year = y;
	}
}

void Date::SetMonth(const int m)
{
	if (ValidMonth(m))
	{
		month = m;
	}
}

void Date::SetDay(const int d)
{
	if (ValidDay(d))
	{
		day = d;
	}
}

void Date::SetHour(const int h)
{
	if (ValidHour(h))
	{
		hour = h;
	}
}

void Date::SetMinute(const int m)
{
	if (ValidMinute(m))
	{
		minute = m;
	}
}

void Date::SetSecond(const int s)
{
	if (ValidSecond(s))
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

bool Date::ValidYear(const int y)
{
	return y > 0;
}

bool Date::ValidMonth(const int m)
{
	return m >= 1 && m <= 12;
}

bool Date::ValidDay(const int d)
{
	return d >= 1 && d <= 31;
}

bool Date::ValidHour(const int h)
{
	return h >= 0 && h < 24;
}

bool Date::ValidMinute(const int m)
{
	return m >= 0 && m < 60;
}

bool Date::ValidSecond(const int s)
{
	return s >=0 && s < 60;
}

void Date::SetCurrentDate()
{
	time_t t = time(0);
	tm* sysTime = new tm();
	localtime_s(sysTime, &t);
	SetYear(sysTime->tm_year + 1900);
	SetMonth(sysTime->tm_mon);
	SetDay(sysTime->tm_mday);
	SetHour(sysTime->tm_hour);
	SetMinute(sysTime->tm_min);
	SetSecond(sysTime->tm_sec);
}

std::string Date::GetFormattedShort() const
{
	std::ostringstream date;
	date << day << "." << month << "." << year << std::endl;
	return date.str();
}

std::string Date::GetFormattedLong() const
{
	std::ostringstream date;
	date << GetFormattedShort() << hour << ":" << minute << ":" << second << std::endl;
	return date.str();
}
