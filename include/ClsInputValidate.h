#pragma once
#include <limits>
#include <iostream>
#include <string>
#include "ClsString.h"
#include "ClsDate.h"

/**
 * @brief Input validation and safe-reading helpers for console applications.
 *
 * Capabilities:
 * - Range checks for numeric types (short, int, float, double)
 * - Safe reading of numbers and strings from std::cin with error recovery
 * - Date range validation using clssDate helpers
 *
 * Notes:
 * - Range checks are inclusive: From <= value <= To.
 * - Read*NumberBetween helpers will keep prompting until a valid value is entered.
 * - Some method names contain typos but are preserved for backward compatibility (e.g., IsValideDate).
 */
class clsInputValidate
{
  
public:
    /**
     * @brief Check whether a short lies within an inclusive range.
     */
    static bool IsNumberBetween(short Number, short From, short To)
    {
        if(Number <= To && Number >= From)
            return true;
        return false;
    }
    
    /**
     * @brief Check whether an int lies within an inclusive range.
     */
    static bool IsNumberBetween(int Number, int From, int To)
    {
        if(Number <= To && Number >= From)
            return true;
        return false;
    }
    
    /**
     * @brief Check whether a float lies within an inclusive range.
     */
    static bool IsNumberBetween(float Number, float From, float To)
    {
        if(Number <= To && Number >= From)
            return true;
        return false;
    }
    
    /**
     * @brief Check whether a double lies within an inclusive range.
     */
    static bool IsNumberBetween(double Number, double From, double To)
    {
        if(Number <= To && Number >= From)
            return true;
        return false;
    }
    
    /**
     * @brief Check whether a date is between two bounds (inclusive), regardless of order of bounds.
     */
    bool IsDateBetween(clssDate Date, clssDate from, clssDate To)
    {
        // Date>=From && Date<=To
        if((clssDate:: IsDate1BeforeDate2(Date, from) || clssDate:: IsDate1EqualDate2(Date, from))
           &&
           (clssDate:: IsDate1AfterDate2(Date, To) || clssDate:: IsDate1EqualDate2(Date, To)))
        {
            return true;
        }
        
        // Date>=To && Date<=From
        if ((clssDate::IsDate1AfterDate2(Date, To) ||clssDate::IsDate1EqualDate2(Date, To))
            &&
            (clssDate::IsDate1BeforeDate2(Date, from) ||clssDate::IsDate1EqualDate2(Date, from))
            )
        {
            return true;
        }
        return false;
    }
    
    /**
     * @brief Read a short from std::cin with validation loop.
     * @param ErrorMessage Message printed when parsing fails.
     */
    static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again: ")
    {
        short Number;
        while(!(cin >> Number)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }
    
    /**
     * @brief Read a short within [From, To] from std::cin.
     */
    static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        short Number = ReadShortNumber();
        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadShortNumber();
        }
        return Number;
    }
    
    /**
     * @brief Read an int from std::cin with validation loop.
     */
    static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again: ")
    {
        int Number;
        while(!(cin >> Number)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }
    
    /**
     * @brief Read an int within [From, To] from std::cin.
     */
    static int ReadIntNumberBetween(int From, int To, string ErrorMessage="Number is not within range, Enter again:\n")
    {
        int Number=ReadIntNumber();
        
        while (!IsNumberBetween(Number,From,To))
        {
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }
        return Number;
    }
    
    /**
     * @brief Read a float from std::cin with validation loop.
     */
    static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        float Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    /**
     * @brief Read a float within [From, To] from std::cin.
     * @warning On invalid range input, this function re-prompts using ReadDblNumber() (double) rather than ReadFloatNumber().
     *          This discrepancy is preserved for compatibility but may be unintended.
     */
    static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        float Number = ReadFloatNumber();

        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }
        return Number;
    }
    
    /**
     * @brief Read a double from std::cin with validation loop.
     */
    static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        double Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    /**
     * @brief Read a double within [From, To] from std::cin.
     */
    static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        double Number = ReadDblNumber();

        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }
        return Number;
    }

    /**
     * @brief Validate a date using clssDate::IsValidDate.
     * @note Name contains a typo (IsValideDate) kept for compatibility.
     */
    static bool IsValideDate(clssDate Date)
    {
        return clssDate::IsValidDate(Date);
    }
    
    /**
     * @brief Read a full line string from std::cin, consuming leading whitespace.
     */
    static string ReadString()
    {
        string  S1="";
        // Usage of std::ws will extract all the whitespace character
        getline(cin >> ws, S1);
        return S1;
    }
};

