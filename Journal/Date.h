#pragma once
#include <string>

class Date
{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
public:
	Date();

	void SetYear(const int);
	void SetMonth(const int);
	void SetDay(const int);
	void SetHour(const int);
	void SetMinute(const int);
	void SetSecond(const int);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;

	bool operator==(const Date& rhs) const;
	bool operator!=(const Date& rhs) const;

	void SetCurrentDate();
	std::wstring GetFormattedShort() const;
	std::wstring GetFormattedLong() const;
};