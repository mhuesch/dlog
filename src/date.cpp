#include <ctime>
#include "date.h"

date::date() : date::date(std::time(nullptr))
{
}

date::date(const time_t& time) : date::date(time, localtime(&time))
{
}

date::date(const time_t& time, const tm* tm_obj) :
    m_time(time),
    m_day(tm_obj->tm_mday),
    m_month(tm_obj->tm_mon),
    m_year(tm_obj->tm_year)
{
}

int date::day() const
{
    return this->m_day;
}

int date::month() const
{
    // Since tm objects contain months from 0-11.
    // We could also just set m_month to +1 in the
    // constructor, but we'll keep the original
    // values just in case this class will ever need them.
    return this->m_month + 1;
}

int date::year() const
{
    return this->m_year;
}

bool date::is_yesterday(const date& yesterday) const
{
    if (this->m_year != yesterday.m_year) {
        return this->m_year - 1 == yesterday.m_year
            && this->m_month == 0 && yesterday.m_month == 11
            && this->m_day == 1 && yesterday.m_day == yesterday.days_in_month();
    }

    if (this->m_month != yesterday.m_month) {
        return this->m_month - 1 == yesterday.m_month
            && this->m_day == 1 && yesterday.m_day == yesterday.days_in_month();
    }

    return this->m_day - 1 == yesterday.m_day;
}

bool date::is_yesterday(const time_t& yesterday) const
{
    return date::is_yesterday(date(yesterday));
}

bool date::is_leap_year() const
{
    // Algorithm from https://stackoverflow.com/posts/11595914
    return (this->m_year & 3) == 0 && ((this->m_year % 25) != 0 || (this->m_year & 15) == 0);
}

int date::days_in_month() const
{
    switch (this->m_month) {
        case 0:   // January
        case 2:   // March
        case 4:   // May
        case 6:   // July
        case 7:   // August
        case 9:   // October
        case 11:  // December
            return 31;
        case 3:   // April
        case 5:   // June
        case 8:   // September
        case 10:  // November
            return 30;
        case 1:   // February
            return this->is_leap_year() ? 29 : 28;
        default:
            return -1;
    }
}

bool date::operator<(const date& other) const
{
    return this->m_year < other.m_year
       || (this->m_year == other.m_year && this->m_month < other.m_month)
       || (this->m_year == other.m_year && this->m_month == other.m_month && this->m_day < other.m_day);
}

bool date::operator>(const date& other) const
{
    return this->m_year > other.m_year
       || (this->m_year == other.m_year && this->m_month > other.m_month)
       || (this->m_year == other.m_year && this->m_month == other.m_month && this->m_day > other.m_day);
}

bool date::operator<=(const date& other) const
{
    return this->operator==(other) || this->operator<(other);
}

bool date::operator>=(const date& other) const
{
    return this->operator==(other) || this->operator>(other);
}

bool date::operator==(const date& other) const
{
    return this->m_day == other.m_day
        && this->m_month == other.m_month
        && this->m_year == other.m_year;
}

bool date::operator!=(const date& other) const
{
    return !this->operator==(other);
}