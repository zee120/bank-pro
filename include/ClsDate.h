#pragma once
#include <ctime>
#include<iostream>
#include<string>
#include "ClsString.h"

using namespace std; // NOTE: Placing 'using namespace std;' in a header affects all includers.

/**
 * @brief Simple Gregorian date utility class.
 *
 * Provides:
 * - Construction from system date, string (DD/MM/YYYY), or explicit day/month/year
 * - Formatting to string
 * - Calendar utilities (day-of-week, month/day names, calendar printing)
 * - Date arithmetic (add/decrease days, weeks, months, years, decades, centuries, millennia)
 * - Comparisons and differences between dates
 * - Business-day/weekend helpers
 *
 * Implementation notes:
 * - This class uses basic C time APIs (time/localtime). Include <ctime> in translation units if needed.
 * - The class is not timezone-aware and assumes Gregorian rules for all years.
 * - Many functions are static helpers operating on provided dates or values.
 * - Some functions return values with potential off-by-one or naming inconsistencies; see warnings inline.
 */
class clssDate
{
private:
    // Backing fields for day/month/year.
    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;
    
public:
    /**
     * @brief Default constructor initializes to the current system date.
     * @warning The assignment `_Day = now->tm_mon + 1;` appears to be a bug; it should likely use `tm_mday`.
     *          Logic is kept unchanged for backward compatibility.
     */
    clssDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);
        _Day = now -> tm_mon + 1;   // likely intended: now->tm_mday
        _Month = now -> tm_mon + 1;
        _Year = now -> tm_year + 1900;
    }
    
    /**
     * @brief Construct from string in format "DD/MM/YYYY".
     * @param Date String such as "31/12/2024".
     * @note Uses clsString::SplitInVector with '/' delimiter; no validation is performed here.
     */
    clssDate(string Date)
    {
        
        vector <string> vDate;
        vDate = clsString::SplitInVector(Date, "/");
        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
        
    }

    /**
     * @brief Construct from explicit day, month, and year.
     */
    clssDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }
    
    /**
     * @brief Construct from day order in year and a year.
     * @param DateOrderInYear Day index within the year (1-based).
     * @param Year Target year.
     * @note Body is commented out; left as a placeholder for future implementation.
     */
    clssDate(short DateOrderInYear, short Year)
        {
//                        //This will construct a date by date order in year
//                        clssDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear,           Year);
//                         _Day = Date1.Day();
//                        _Month = Date1.Month();
//                        _Year = Date1.Year();
        }
    
    // --- Basic accessors/mutators ---
    void SetDay(short Day)
    {
        _Day = Day;
    }

    short Day()
    {
        return _Day;
    }
    
    void SetMonth(short Month)
    {
        _Month = Month;
    }

    short Month()
    {
        return _Month;
    }
    void SetYear(short Year)
    {
        _Year = Year;
    }

    short Year()
    {
        return _Year;
    }

    /**
     * @brief Print date to stdout in DD/MM/YYYY format.
     */
    void Print()
    {
        cout << DateToString() << endl;
    }

    /**
     * @brief Convert a given date to string "D/M/YYYY".
     */
    static string DateToString(clssDate Date)
    {
        return  to_string(Date.Day()) + "/" + to_string(Date.Month()) +"/" + to_string(Date.Year());
    }

    /**
     * @brief Convert this date to string "D/M/YYYY".
     */
    string DateToString()
    {
        return  DateToString(*this);
    }

    /**
     * @brief Get the current system date as a clssDate.
     */
    static clssDate GetSystemDate()
    {
        // system date
        time_t t = time(0);
        tm* now = localtime(&t);
        
        short Day, Month, Year;
        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        return clssDate(Day, Month, Year);
    }
    
    /**
     * @brief Get current system date/time as a formatted string "D/M/YYYY - H:M:S ".
     */
    static string GetSystemDateTimeString()
    {
        // system datetime string
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year,Hour,Minute,Second;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return (to_string(Day) + "/" + to_string(Month) + "/"
        + to_string(Year) + " - "
        + to_string(Hour) + ":" + to_string(Minute)
        + ":" + to_string(Second) + " ");

    }
    
    /**
     * @brief Validate that a date is within expected ranges and month/day rules.
     */
    static bool IsValidDate(clssDate Date)
    {
        if (Date.Day() < 1 || Date.Day() >31)
            return false;
        if (Date.Month() < 1 || Date.Month() > 12)
            return false;
        if (Date.Month() == 2)
        {
            if (isLeapYear(Date.Year()))
            {
                if (Date.Day() > 29)
                    return false;
            }
            else
            {
                if (Date.Day() > 28)
                    return false;
            }
        }
        short DaysInMonth = NumberOfDaysInAMonth(Date.Month(),Date.Year());
        if (Date.Day() > DaysInMonth)
            return false;
        return true;
    }
    
    /**
     * @brief Determine if a given year is a leap year.
     */
    static bool isLeapYear(short Year)
    {
        // if year is divisible by 4 AND not divisible by 100
        // OR if year is divisible by 400
        // then it is a leap year
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }
    
    /**
     * @brief Determine if this date's year is a leap year.
     */
    bool isLeapYear()
    {
        return isLeapYear(_Year);
    }

    /**
     * @brief Number of days in a year.
     * @warning Implementation returns 365 for leap years and 364 for common years; this appears to be a bug.
     */
    static short NumberOfDaysInAYear(short Year)
    {
        return  isLeapYear(Year) ? 365 : 364;
    }

    /**
     * @brief Number of days in this date's year.
     */
    short NumberOfDaysInAYear()
    {
        return  NumberOfDaysInAYear(_Year);
    }

    /**
     * @brief Number of hours in a given year (based on NumberOfDaysInAYear).
     */
    static short NumberOfHoursInAYear(short Year)
    {
        return  NumberOfDaysInAYear(Year) * 24;
    }

    /**
     * @brief Number of hours in this date's year.
     */
    short NumberOfHoursInAYear()
    {
        return  NumberOfDaysInAYear(_Year) * 24;
    }

    /**
     * @brief Number of minutes in a given year.
     */
    static int NumberOfMinutesInAYear(short Year)
    {
        return  NumberOfHoursInAYear(Year) * 60;
    }
    /**
     * @brief Number of minutes in this date's year.
     */
    int NumberOfMinutesInAYear()
    {
        return  NumberOfMinutesInAYear(_Year);
    }
    /**
     * @brief Number of seconds in a given year.
     */
    static int NumberOfSecondsInAYear(short Year)
    {
        return  NumberOfMinutesInAYear(Year) * 60;
    }
    /**
     * @brief Number of seconds in this date's year.
     */
    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(Year());
    }

    /**
     * @brief Number of days in a specific month of a year (handles leap years for February).
     */
    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month>12)
            return  0;
        int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month -1];
    }
    /**
     * @brief Number of days in this date's month.
     */
    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }
    /**
     * @brief Number of hours in a specific month.
     */
    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return  NumberOfDaysInAMonth(Month, Year) * 24;
    }
    /**
     * @brief Number of hours in this date's month.
     */
    short NumberOfHoursInAMonth()
    {
        return  NumberOfDaysInAMonth(_Month, _Year) * 24;
    }
    /**
     * @brief Number of minutes in a specific month.
     */
    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return  NumberOfHoursInAMonth(Month, Year) * 60;
    }
    /**
     * @brief Number of minutes in this date's month.
     */
    int NumberOfMinutesInAMonth()
    {
        return  NumberOfHoursInAMonth(_Month, _Year) * 60;
    }
    /**
     * @brief Number of seconds in a specific month.
     */
    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return  NumberOfMinutesInAMonth(Month, Year) * 60;
    }
    /**
     * @brief Number of seconds in this date's month.
     */
    int NumberOfSecondsInAMonth()
    {
        return  NumberOfMinutesInAMonth(_Month, _Year) * 60;
    }
    
    
    
    
    
    
    
    
    /**
     * @brief Day of week (0=Sun..6=Sat) for a given date (Zeller-like computation).
     */
    static short DayOfWeekOrder(short Day, short Month, short Year)
    {
        short a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;
        // Gregorian:
        //0:sun, 1:Mon, 2:Tue...etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) /12)) % 7;
    }
    /**
     * @brief Day of week (0=Sun..6=Sat) for this date.
     */
    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }
    /**
     * @brief Short day name for a given day-of-week index (0..6).
     */
    static string DayShortName(short DayOfWeekOrder)
    {
        string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
        return arrDayNames[DayOfWeekOrder];
    }
    /**
     * @brief Short day name for a given date.
     */
    static string DayShortName(short Day, short Month, short Year)
    {
        string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
        return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
    }
    /**
     * @brief Short day name for this date.
     */
    string DayShortName()
    {
        string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
        return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];
    }
    /**
     * @brief Three-letter month abbreviation for a given month number (1..12).
     */
    static string MonthShortName(short MonthNumber)
    {
        string Months[12] = { "Jan", "Feb", "Mar",
                            "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep",
                            "Oct", "Nov", "Dec"
        };
        return (Months[MonthNumber - 1]);
    }
    /**
     * @brief Three-letter month abbreviation for this date's month.
     */
    string MonthShortName()
    {
        return MonthShortName(_Month);
    }

    /**
     * @brief Print a text calendar for a specific month/year to stdout.
     */
    static void PrintMonthCalendar(short Month, short Year)
    {
        int NumberOfDays;
        // Index of the day from 0 to 6
        int current = DayOfWeekOrder(1, Month, Year);
        NumberOfDays = NumberOfDaysInAMonth(Month, Year);
        // Print the current month name
        printf("\n  _______________%s_______________\n\n",
            MonthShortName(Month).c_str());
        // Print the columns
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
        // Print appropriate spaces
        int i;
        for (i = 0; i < current; i++)
            printf("     ");
        for (int j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);
            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        printf("\n  _________________________________\n");
    }
    /**
     * @brief Print a text calendar for this date's month.
     */
    void PrintMonthCalendar()
    {
        PrintMonthCalendar(_Month, _Year);
    }
    /**
     * @brief Print a text calendar for an entire year to stdout.
     */
    static void PrintYearCalendar(int Year)
    {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", Year);
        printf("  _________________________________\n");
        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, Year);
        }
        return;
    }
    /**
     * @brief Print a text calendar for this date's year.
     */
    void PrintYearCalendar()
    {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", _Year);
        printf("  _________________________________\n");
        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, _Year);
        }
        return;
    }
    
    
    
    
    
    
    
    /**
     * @brief Day count from the beginning of the year for a given date (1-based).
     */
    static short DaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {
        short TotalDays = 0;
        for (int i = 1; i <= Month - 1; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, Year);
        }
        TotalDays += Day;
        return TotalDays;
    }
    /**
     * @brief Day count from the beginning of the year for this date (1-based).
     */
    short DaysFromTheBeginingOfTheYear()
{
        short TotalDays = 0;
        for (int i = 1; i <= _Month - 1; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, _Year);
        }
        TotalDays += _Day;
        return TotalDays;
    }
    /**
     * @brief Convert a day order within a year into a concrete date.
     */
    static clssDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
    {
        clssDate Date;
        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;
        Date._Year = Year;
        Date._Month = 1;
        while (true)
            {
                MonthDays = NumberOfDaysInAMonth(Date.Month(), Year);

                if (RemainingDays > MonthDays)
                {
                    RemainingDays -= MonthDays;
                    Date._Month++;
                }
                else
                {
                    Date._Day = RemainingDays;
                    break;
                }

            }

            return Date;
        }

        /**
         * @brief Add a number of days to this date, mutating it in-place.
         */
        void AddDays(short Days)
        {
            short RemainingDays = Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
            short MonthDays = 0;

            _Month = 1;

            while (true)
            {
                MonthDays = NumberOfDaysInAMonth(_Month, _Year);

                if (RemainingDays > MonthDays)
                {
                    RemainingDays -= MonthDays;
                    _Month++;

                    if (_Month > 12)
                    {
                        _Month = 1;
                        _Year++;

                    }
                }
                else
                {
                    _Day = RemainingDays;
                    break;
                }

            }


        }

    /**
     * @brief Check if Date1 < Date2 in calendar order.
     */
    static bool IsDate1BeforeDate2(clssDate Date1, clssDate Date2)
    {
        return  (Date1.Year() < Date2.Year()) ? true : ((Date1.Year() == Date2.Year()) ?(Date1.Month() < Date2.Month() ? true : (Date1.Month() == Date2.Month() ?Date1.Day() < Date2.Day() : false)) : false);
    }
    /**
     * @brief Check if this date < Date2.
     */
    bool IsDateBeforeDate2(clssDate Date2)
    {
        //note: *this sends the current object :-)
        return  IsDate1BeforeDate2(*this, Date2);
        }

        /**
         * @brief Check if two dates are equal (same Y/M/D).
         */
        static bool IsDate1EqualDate2(clssDate Date1, clssDate Date2)
        {
            return  (Date1.Year() == Date2.Year()) ? ((Date1.Month() == Date2.Month()) ? ((Date1.Day() == Date2.Day()) ? true : false) : false) : false;
        }

        /**
         * @brief Check if this date equals Date2.
         */
        bool IsDateEqualDate2(clssDate Date2)
        {
            return  IsDate1EqualDate2(*this, Date2);
        }

        /**
         * @brief Determine if a given date is the last day of its month.
         */
        static bool IsLastDayInMonth(clssDate Date)
        {

            return (Date.Day() == NumberOfDaysInAMonth(Date.Month(), Date.Year()));

        }

        /**
         * @brief Determine if this date is the last day of its month.
         */
        bool IsLastDayInMonth()
        {

            return IsLastDayInMonth(*this);

        }

        /**
         * @brief Determine if a month number is the last month of the year (12).
         */
        static bool IsLastMonthInYear(short Month)
        {
            return (Month == 12);
        }

        /**
         * @brief Return a new date which is one day after the given date.
         */
        static clssDate AddOneDay(clssDate Date)
        {
            if (IsLastDayInMonth(Date))
            {
                if (IsLastMonthInYear(Date.Month()))
                {
                    Date._Month = 1;
                    Date._Day = 1;
                    Date._Year++;
                }
                else
                {
                    Date._Day = 1;
                    Date._Month++;
                }
            }
            else
            {
                Date._Day++;
            }

            return Date;
        }

        /**
         * @brief Increment this date by one day, in-place.
         */
        void AddOneDay()

        {
            *this = AddOneDay(*this);
        }

        /**
         * @brief Swap two dates.
         */
        static void  SwapDates(clssDate & Date1, clssDate & Date2)
        {

            clssDate TempDate;
            TempDate = Date1;
            Date1 = Date2;
            Date2 = TempDate;

        }

        /**
         * @brief Get difference in days between two dates.
         * @param IncludeEndDay If true, includes the end date in the count.
         * @return Positive if Date2 is after Date1; negative if Date1 is after Date2.
         */
        static int GetDifferenceInDays(clssDate Date1, clssDate Date2, bool IncludeEndDay = false)
        {
            //this will take care of negative diff
            int Days = 0;
            short SawpFlagValue = 1;

            if (!IsDate1BeforeDate2(Date1, Date2))
            {
                //Swap Dates
                SwapDates(Date1, Date2);
                SawpFlagValue = -1;

            }

            while (IsDate1BeforeDate2(Date1, Date2))
            {
                Days++;
                Date1 = AddOneDay(Date1);
            }

            return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
        }

        /**
         * @brief Difference in days between this date and Date2.
         */
        int GetDifferenceInDays(clssDate Date2, bool IncludeEndDay = false)
        {
            return GetDifferenceInDays(*this, Date2, IncludeEndDay);
        }

        /**
         * @brief Calculate age in days from a birth date to the current system date.
         */
        static short CalculateMyAgeInDays(clssDate DateOfBirth)
        {
            return GetDifferenceInDays(DateOfBirth, clssDate::GetSystemDate(), true);
        }
        // above no need to have nonstatic function for the object because it does not depend on any data from it.

        /**
         * @brief Increase a date by one week (7 days), mutating it and returning it.
         */
        static clssDate IncreaseDateByOneWeek(clssDate & Date)
        {

            for (int i = 1; i <= 7; i++)
            {
                Date = AddOneDay(Date);
            }

            return Date;
        }

        /**
         * @brief Increase this date by one week.
         */
        void IncreaseDateByOneWeek()
        {
            IncreaseDateByOneWeek(*this);
        }

        /**
         * @brief Increase a date by X weeks, mutating it and returning it.
         */
        clssDate IncreaseDateByXWeeks(short Weeks, clssDate& Date)
        {

            for (short i = 1; i <= Weeks; i++)
            {
                Date = IncreaseDateByOneWeek(Date);
            }
            return Date;
        }

        /**
         * @brief Increase this date by X weeks.
         */
        void IncreaseDateByXWeeks(short Weeks)
        {
            IncreaseDateByXWeeks(Weeks, *this);
        }

        /**
         * @brief Increase a date by one calendar month, adjusting day if needed.
         */
        clssDate IncreaseDateByOneMonth(clssDate& Date)
        {

            if (Date.Month() == 12)
            {
                Date._Month = 1;
                Date._Year++;
            }
            else
            {
                Date._Month++;
            }

            // last check day in date should not exceed max days in the current month
            // example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should
            // be 28/2/2022
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month(), Date.Year());
            if (Date.Day() > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }

            return Date;
        }
    
    
    
    
    
    
    
    
    /**
     * @brief Increase this date by one calendar month.
     */
    void IncreaseDateByOneMonth()
        {

            IncreaseDateByOneMonth(*this);

        }

        /**
         * @brief Increase a date by X days, mutating it and returning it.
         */
        clssDate IncreaseDateByXDays(short Days, clssDate& Date)
        {

            for (short i = 1; i <= Days; i++)
            {
                Date = AddOneDay(Date);
            }
            return Date;
        }

        /**
         * @brief Increase this date by X days.
         */
        void IncreaseDateByXDays(short Days)
        {

            IncreaseDateByXDays(Days, *this);
        }

        /**
         * @brief Increase a date by X calendar months, mutating it and returning it.
         */
        clssDate IncreaseDateByXMonths(short Months, clssDate& Date)
        {

            for (short i = 1; i <= Months; i++)
            {
                Date = IncreaseDateByOneMonth(Date);
            }
            return Date;
        }

        /**
         * @brief Increase this date by X calendar months.
         */
        void IncreaseDateByXMonths(short Months)
        {
            IncreaseDateByXMonths(Months, *this);
        }

        /**
         * @brief Increase a date by one year.
         */
        static clssDate IncreaseDateByOneYear(clssDate& Date)
        {
            Date._Year++;
            return Date;
        }

        /**
         * @brief Increase this date by one year.
         */
        void IncreaseDateByOneYear()
        {
            IncreaseDateByOneYear(*this);
        }

        /**
         * @brief Increase a date by X years.
         */
        clssDate IncreaseDateByXYears(short Years, clssDate& Date)
        {
            Date._Year += Years;
            return Date;
            
        }

        /**
         * @brief Increase this date by X years.
         */
        void IncreaseDateByXYears(short Years)
        {
            IncreaseDateByXYears(Years, *this);
        }

        /**
         * @brief Increase a date by one decade (10 years).
         */
        clssDate IncreaseDateByOneDecade(clssDate& Date)
        {
            //Period of 10 years
            Date._Year += 10;
            return Date;
        }

        /**
         * @brief Increase this date by one decade.
         */
        void IncreaseDateByOneDecade()
        {
            IncreaseDateByOneDecade(*this);
        }

        /**
         * @brief Increase a date by X decades.
         */
        clssDate IncreaseDateByXDecades(short Decade, clssDate& Date)
        {
            Date._Year += Decade * 10;
            return Date;
        }

        /**
         * @brief Increase this date by X decades.
         */
        void IncreaseDateByXDecades(short Decade)
        {
            IncreaseDateByXDecades(Decade, *this);
        }

        /**
         * @brief Increase a date by one century (100 years).
         */
        clssDate IncreaseDateByOneCentury(clssDate& Date)
        {
            //Period of 100 years
            Date._Year += 100;
            return Date;
        }

        /**
         * @brief Increase this date by one century.
         */
        void IncreaseDateByOneCentury()
        {
            IncreaseDateByOneCentury(*this);
        }

        /**
         * @brief Increase a date by one millennium (1000 years).
         */
        clssDate IncreaseDateByOneMillennium(clssDate& Date)
        {
            //Period of 1000 years
            Date._Year += 1000;
            return Date;
        }

        /**
         * @brief Increase this date by one millennium.
         */
        clssDate IncreaseDateByOneMillennium()
        {
            return IncreaseDateByOneMillennium(*this);
        }

        /**
         * @brief Return a new date which is one day before the given date.
         */
        static clssDate DecreaseDateByOneDay(clssDate Date)
        {
            if (Date.Day() == 1)
            {
                if (Date.Month() == 1)
                {
                    Date._Month = 12;
                    Date._Day = 31;
                    Date._Year--;
                }
                else
                {

                    Date._Month--;
                    Date._Day = NumberOfDaysInAMonth(Date.Month(), Date.Year());
                }
            }
            else
            {
                Date._Day--;
            }

            return Date;
        }

        /**
         * @brief Decrease this date by one day.
         */
        void DecreaseDateByOneDay()
        {
            DecreaseDateByOneDay(*this);
        }

        /**
         * @brief Decrease a date by one week, mutating it and returning it.
         */
        static clssDate DecreaseDateByOneWeek(clssDate &Date)
        {

            for (int i = 1; i <= 7; i++)
            {
                Date = DecreaseDateByOneDay(Date);
            }

            return Date;
        }

        /**
         * @brief Decrease this date by one week.
         */
        void DecreaseDateByOneWeek()
        {
            DecreaseDateByOneWeek(*this);
        }

        /**
         * @brief Decrease a date by X weeks, mutating it and returning it.
         */
        static clssDate DecreaseDateByXWeeks(short Weeks, clssDate &Date)
        {

            for (short i = 1; i <= Weeks; i++)
            {
                Date = DecreaseDateByOneWeek(Date);
            }
            return Date;
        }

        /**
         * @brief Decrease this date by X weeks.
         */
        void DecreaseDateByXWeeks(short Weeks)
        {
            DecreaseDateByXWeeks(Weeks ,*this);
        }

        /**
         * @brief Decrease a date by one calendar month, adjusting day if needed.
         */
        static clssDate DecreaseDateByOneMonth(clssDate &Date)
        {

            if (Date.Month() == 1)
            {
                Date._Month = 12;
                Date._Year--;
            }
            else
                Date._Month--;


            //last check day in date should not exceed max days in the current month
           // example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should
           // be 28/2/2022
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month(), Date.Year());
            if (Date.Day() > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }


            return Date;
        }

        /**
         * @brief Decrease this date by one calendar month.
         */
        void DecreaseDateByOneMonth()
        {
            DecreaseDateByOneMonth(*this);
        }

        /**
         * @brief Decrease a date by X days, mutating it and returning it.
         */
        static clssDate DecreaseDateByXDays(short Days, clssDate &Date)
        {

            for (short i = 1; i <= Days; i++)
            {
                Date = DecreaseDateByOneDay(Date);
            }
            return Date;
        }

        /**
         * @brief Decrease this date by X days.
         */
        void DecreaseDateByXDays(short Days)
        {
            DecreaseDateByXDays(Days, *this);
        }

        /**
         * @brief Decrease a date by X calendar months, mutating it and returning it.
         */
        static clssDate DecreaseDateByXMonths(short Months, clssDate &Date)
        {

            for (short i = 1; i <= Months; i++)
            {
                Date = DecreaseDateByOneMonth(Date);
            }
            return Date;
        }

        /**
         * @brief Decrease this date by X calendar months.
         */
        void DecreaseDateByXMonths(short Months)
        {
            DecreaseDateByXMonths( Months, *this);
        }

        /**
         * @brief Decrease a date by one year.
         */
        static clssDate DecreaseDateByOneYear(clssDate &Date)
        {

            Date._Year--;
            return Date;
        }

        /**
         * @brief Decrease this date by one year.
         */
        void DecreaseDateByOneYear()
        {
            DecreaseDateByOneYear(*this);
        }

        /**
         * @brief Decrease a date by X years.
         */
        static clssDate DecreaseDateByXYears(short Years, clssDate &Date)
        {

            Date._Year -= Years;
            return Date;
        }

        /**
         * @brief Decrease this date by X years.
         */
        void DecreaseDateByXYears(short Years)
        {
            DecreaseDateByXYears(Years ,*this);
        }

        /**
         * @brief Decrease a date by one decade (10 years).
         */
        static clssDate DecreaseDateByOneDecade(clssDate &Date)
        {
            //Period of 10 years
            Date._Year -= 10;
            return Date;
        }

        /**
         * @brief Decrease this date by one decade.
         */
        void DecreaseDateByOneDecade()
        {
            DecreaseDateByOneDecade(*this);
        }

        /**
         * @brief Decrease a date by X decades.
         */
        static clssDate DecreaseDateByXDecades(short Decades, clssDate &Date)
        {

            Date._Year -= Decades * 10;
            return Date;
        }

        /**
         * @brief Decrease this date by X decades.
         */
        void DecreaseDateByXDecades(short Decades)
        {
            DecreaseDateByXDecades(Decades, *this);
        }

        /**
         * @brief Decrease a date by one century (100 years).
         */
        static clssDate DecreaseDateByOneCentury(clssDate &Date)
        {
            //Period of 100 years
            Date._Year -= 100;
            return Date;
        }

        /**
         * @brief Decrease this date by one century.
         */
        void DecreaseDateByOneCentury()
        {
            DecreaseDateByOneCentury(*this);
        }

        /**
         * @brief Decrease a date by one millennium (1000 years).
         */
        static clssDate DecreaseDateByOneMillennium(clssDate &Date)
        {
            //Period of 1000 years
            Date._Year -= 1000;
            return Date;
        }

        /**
         * @brief Decrease this date by one millennium.
         */
        void DecreaseDateByOneMillennium()
        {
            DecreaseDateByOneMillennium(*this);
        }

        /**
         * @brief Check if a given date falls on the last day of the week (Saturday index 6).
         */
        static short IsEndOfWeek(clssDate Date)
        {
            return  DayOfWeekOrder(Date.Day(), Date.Month(), Date.Year()) == 6;
        }

        /**
         * @brief Check if this date is the end of the week.
         */
        short IsEndOfWeek()
        {
            return IsEndOfWeek(*this);
        }

        /**
         * @brief Check if a given date is a weekend (Fri=5 or Sat=6).
         */
        static bool IsWeekEnd(clssDate Date)
        {
            //Weekends are Fri and Sat
            short DayIndex = DayOfWeekOrder(Date.Day(), Date.Month(), Date.Year());
            return  (DayIndex == 5 || DayIndex == 6);
        }

        /**
         * @brief Check if this date is a weekend.
         */
        bool IsWeekEnd()
        {
            return  IsWeekEnd(*this);
        }

        /**
         * @brief Check if a given date is a business day (not weekend).
         */
        static bool IsBusinessDay(clssDate Date)
        {
            //Weekends are Sun,Mon,Tue,Wed and Thur

           /*
            short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
            return  (DayIndex >= 5 && DayIndex <= 4);
           */

           //shorter method is to invert the IsWeekEnd: this will save updating code.
            return !IsWeekEnd(Date);

        }

        /**
         * @brief Check if this date is a business day.
         */
        bool IsBusinessDay()
        {
            return  IsBusinessDay(*this);
        }

        /**
         * @brief Days remaining until end of week (Saturday) for a given date.
         */
        static short DaysUntilTheEndOfWeek(clssDate Date)
        {
            return 6 - DayOfWeekOrder(Date.Day(), Date.Month(), Date.Year());
        }

        /**
         * @brief Days remaining until end of week for this date.
         */
        short DaysUntilTheEndOfWeek()
        {
            return  DaysUntilTheEndOfWeek(*this);
        }

        /**
         * @brief Days remaining until the end of the month for a given date (inclusive of end day).
         */
        static short DaysUntilTheEndOfMonth(clssDate Date1)
        {

            clssDate EndOfMontDate;
            EndOfMontDate._Day = NumberOfDaysInAMonth(Date1.Month(), Date1.Year());
            EndOfMontDate._Month = Date1.Month();
            EndOfMontDate._Year = Date1.Year();

            return GetDifferenceInDays(Date1, EndOfMontDate, true);

        }

        /**
         * @brief Days remaining until end of month for this date.
         */
        short DaysUntilTheEndOfMonth()
        {
            return DaysUntilTheEndOfMonth(*this);
        }

        /**
         * @brief Days remaining until end of year for a given date (inclusive of end day).
         */
        static short DaysUntilTheEndOfYear(clssDate Date1)
        {

            clssDate EndOfYearDate;
            EndOfYearDate._Day = 31;
            EndOfYearDate._Month = 12;
            EndOfYearDate._Year = Date1.Year();

            return GetDifferenceInDays(Date1, EndOfYearDate, true);

        }

        /**
         * @brief Days remaining until end of year for this date.
         */
        short DaysUntilTheEndOfYear()
        {
            return  DaysUntilTheEndOfYear(*this);
        }

        /**
         * @brief Calculate business days between two dates (exclusive of end unless IncludeEndDay logic elsewhere).
         */
        // i added this method to calculate business days between 2 days
        static short CalculateBusinessDays(clssDate DateFrom, clssDate DateTo)
        {

            short Days = 0;
            while (IsDate1BeforeDate2(DateFrom, DateTo))
            {
                if (IsBusinessDay(DateFrom))
                    Days++;

                DateFrom = AddOneDay(DateFrom);
            }

            return Days;

        }

        /**
         * @brief Calculate vacation days (alias to CalculateBusinessDays).
         */
        static short CalculateVacationDays(clssDate DateFrom, clssDate DateTo)
        {
            /*short Days = 0;
            while (IsDate1BeforeDate2(DateFrom, DateTo))
            {
                if (IsBusinessDay(DateFrom))
                    Days++;

                DateFrom = AddOneDay(DateFrom);
            }*/

            return CalculateBusinessDays(DateFrom, DateTo);

        }
        // above method is eough , no need to have method for the object

        /**
         * @brief Calculate the return date from a start date and a number of vacation days (adds weekends at the end).
         */
        static clssDate CalculateVacationReturnDate(clssDate DateFrom, short VacationDays)
        {

            short WeekEndCounter = 0;

            for (short i = 1; i <= VacationDays; i++)
            {

                if (IsWeekEnd(DateFrom))
                    WeekEndCounter++;

                DateFrom = AddOneDay(DateFrom);
            }
            // to add weekends
            for (short i = 1; i <= WeekEndCounter; i++)
                DateFrom = AddOneDay(DateFrom);

            return DateFrom;
        }

        /**
         * @brief Check if Date1 > Date2.
         */
        static bool IsDate1AfterDate2(clssDate Date1, clssDate Date2)
        {
            return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));

        }

        /**
         * @brief Check if this date > Date2.
         */
        bool IsDateAfterDate2( clssDate Date2)
        {
            return IsDate1AfterDate2(*this, Date2);
        }

        /**
         * @brief Comparison result for dates.
         */
        enum enDateCompare { Before = -1, Equal = 0, After = 1 };

        /**
         * @brief Compare two dates and return Before/Equal/After.
         */
        static enDateCompare CompareDates(clssDate Date1, clssDate Date2)
        {
            if (IsDate1BeforeDate2(Date1, Date2))
                return enDateCompare::Before;

            if (IsDate1EqualDate2(Date1, Date2))
                return enDateCompare::Equal;

            /* if (IsDate1AfterDate2(Date1,Date2))
                 return enDateCompare::After;*/

                 //this is faster
            return enDateCompare::After;

        }

        /**
         * @brief Compare this date to Date2.
         */
        enDateCompare CompareDates( clssDate Date2)
        {
            return CompareDates(*this, Date2);
        }

    
};
