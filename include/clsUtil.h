#pragma once
#include "ClsDate.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>







/**
 * @brief A collection of general-purpose utility functions.
 *
 * This class provides helpers for:
 * - Random number and character generation
 * - Generating random words/keys
 * - Filling and shuffling arrays
 * - Swapping values (overloads for several types)
 * - Simple text encryption/decryption (Caesar-style shift)
 * - Converting integers to English words
 *
 * Implementation notes and caveats:
 * - Randomness: Call Srand() once at program start to seed the PRNG. Functions here use C rand()/srand().
 * - Character ranges are ASCII-based (not Unicode-aware).
 * - GetRandomCharacter(enCharType::MixChars) currently chooses only from small letters, capital letters, and digits.
 *   The switch-case for MixChars is effectively unreachable due to the early reassignment; see comments below.
 * - Tabs(): prints to std::cout as a side effect while also returning a string of tabs.
 * - EncryptText()/DecryptText(): the loop uses `<= Text.length()` which attempts to access one-past-the-end; see warnings.
 * - NumberToText(): supports positive integers up to billions; returns an empty string for 0 and does not handle negatives.
 */
class clsUtil
{
public:
    /**
     * @brief Character category used by random character/word generators.
     *
     * Note: The identifier name "SamallLetter" is kept for backward compatibility (typo of "Small").
     */
    enum enCharType{
        SamallLetter = 1,  ///< Lowercase ASCII letters 'a'..'z'
        CapitalLetter = 2, ///< Uppercase ASCII letters 'A'..'Z'
        Digit = 3,         ///< ASCII digits '0'..'9'
        MixChars = 4,      ///< See GetRandomCharacter(): currently maps to Small/Capital/Digit only
        SpecialCharacter = 5 ///< ASCII punctuation range 33..47 (e.g., !"#$%&'()*+,-./)
    };
    
    /**
     * @brief Seed the C PRNG with the current time.
     * @note Call once at program startup. Requires <ctime> for time().
     */
    static void  Srand()
    {
        // Seeds the random number generator in C++, called only once
        srand((unsigned)time(NULL));
    }
    
    /**
     * @brief Generate a random integer in the inclusive range [From, To].
     * @param From Lower bound (inclusive).
     * @param To Upper bound (inclusive). Must be >= From.
     * @return A uniformly distributed integer between From and To.
     */
    static  int RandomNumber(int From, int To)
    {
        // Function to generate a random number
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }
    
    /**
     * @brief Return a random character according to the specified category.
     *
     * Behavior details:
     * - If CharType == MixChars, the function randomly remaps CharType to one of {SamallLetter, CapitalLetter, Digit}.
     *   As a result, the switch-case for MixChars below is not reached in normal flow.
     * - SpecialCharacter currently uses ASCII range 33..47 (common punctuation). It does not include all punctuation.
     *
     * @param CharType The desired character category.
     * @return A random ASCII character.
     */
    static char GetRandomCharacter(enCharType CharType)
    {
        // updated this method to accept mixchars
        if (CharType == MixChars)
        {
            // Capital/Samll/Digits only
            CharType = (enCharType)RandomNumber(1, 3);
        }
        switch (CharType)
        {
            case enCharType::SamallLetter:
            {
                return char(RandomNumber(97, 122)); // 'a'..'z'
                break;
            }
            case enCharType::CapitalLetter:
            {
                return char(RandomNumber(65, 90)); // 'A'..'Z'
                break;
            }
            case enCharType::SpecialCharacter:
            {
                return char(RandomNumber(33, 47)); // '!'..'/' subset of punctuation
                break;
            }
            case enCharType::Digit:
            {
                return char(RandomNumber(48, 57)); // '0'..'9'
                break;
            }
            case enCharType::MixChars:
            {
                // Note: Due to the early remapping above, control should not reach this branch.
                return char(RandomNumber(33, 122));
                break;
            }
        }
    }
    
    /**
     * @brief Generate a random ASCII word of a given length using the specified character category.
     * @param CharType Character category to use.
     * @param Length Number of characters to generate.
     * @return A string containing random characters.
     */
    static string GenerateWord(enCharType CharType, short Length)
    {
        string Word;

        for (int i = 1; i <= Length; i++)
        {
            Word = Word + GetRandomCharacter(CharType);
        }
            return Word;
    }

    
    /**
     * @brief Generate a key in the form XXXX-XXXX-XXXX-XXXX using the specified character category.
     * @param CharType Category for each segment (default: CapitalLetter).
     * @return A formatted key string.
     */
    static string  GenerateKey(enCharType CharType = CapitalLetter)
    {

        string Key = "";


        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);


        return Key;
    }
    
    /**
     * @brief Print a series of generated keys to std::cout.
     * @param NumberOfKeys How many keys to generate and print.
     * @param CharType Category used for each key segment.
     */
    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {

        for (int i = 1; i <= NumberOfKeys; i++)
        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }

    }
    
    /**
     * @brief Fill an integer array with random numbers in [From, To].
     * @param arr Target array (size up to 100).
     * @param arrLength Number of elements to fill.
     * @param From Lower bound (inclusive).
     * @param To Upper bound (inclusive).
     */
    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
       {
           for (int i = 0; i < arrLength; i++)
               arr[i] = RandomNumber(From, To);
       }

    /**
     * @brief Fill a string array with random words.
     * @param arr Target array (size up to 100).
     * @param arrLength Number of elements to fill.
     * @param CharType Character category for generated words.
     * @param Wordlength Length of each generated word.
     */
    static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateWord(CharType, Wordlength);

    }
    
    /**
     * @brief Fill a string array with generated keys (XXXX-XXXX-XXXX-XXXX).
     * @param arr Target array (size up to 100).
     * @param arrLength Number of elements to fill.
     * @param CharType Character category for each key segment.
     */
    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateKey(CharType);
    }

    /**
     * @brief Swap two integers by reference.
     */
    static  void Swap(int& A, int& B)
    {
        int Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    /**
     * @brief Swap two doubles by reference.
     */
    static  void Swap(double& A, double& B)
    {
        double Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    /**
     * @brief Swap two booleans by reference.
     */
    static  void Swap(bool& A, bool& B)
    {
        bool Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    /**
     * @brief Swap two chars by reference.
     */
    static  void Swap(char& A, char& B)
    {
        char Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    /**
     * @brief Swap two strings by reference.
     */
    static  void Swap(string& A, string& B)
    {
        string Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    /**
     * @brief Swap two dates using clssDate::SwapDates.
     * @param A First date.
     * @param B Second date.
     * @see clssDate::SwapDates
     */
    static  void Swap(clssDate& A, clssDate& B)
    {
        clssDate::SwapDates(A, B);
    }
    
    /**
     * @brief Shuffle an integer array in-place using random pairwise swaps.
     * @param arr Array to shuffle (size up to 100).
     * @param arrLength Number of elements.
     * @note This is not a Fisher–Yates shuffle and may introduce bias.
     */
    static  void ShuffleArray(int arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }

    }

    /**
     * @brief Shuffle a string array in-place using random pairwise swaps.
     * @param arr Array to shuffle (size up to 100).
     * @param arrLength Number of elements.
     * @note This is not a Fisher–Yates shuffle and may introduce bias.
     */
    static  void ShuffleArray(string arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }
    
    /**
     * @brief Build a string containing a number of tab characters and also print them.
     * @param NumberOfTabs The number of tabs to include.
     * @return The string of tabs.
     * @warning This function prints to std::cout as a side effect while building the string.
     */
    static string  Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t; // side effect: prints cumulative tabs
        }
        return t;
    }

    /**
     * @brief Encrypt text by shifting each character by EncryptionKey positions (Caesar cipher).
     * @param Text Input text to encrypt (ASCII-oriented).
     * @param EncryptionKey Shift amount (can be negative if desired).
     * @return Encrypted text.
     * @warning The loop uses `<= Text.length()` which attempts to access one past the last character, causing undefined behavior.
     *          Consider changing to `i < Text.length()` if you decide to modify logic in the future.
     */
    static string  EncryptText(string Text, short EncryptionKey = 5)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] + EncryptionKey);
        }
        return Text;
    }

    /**
     * @brief Decrypt text by shifting each character backward by EncryptionKey positions (inverse Caesar cipher).
     * @param Text Input text to decrypt (ASCII-oriented).
     * @param EncryptionKey Shift amount used during encryption.
     * @return Decrypted text.
     * @warning The loop uses `<= Text.length()` which attempts to access one past the last character, causing undefined behavior.
     *          Consider changing to `i < Text.length()` if you decide to modify logic in the future.
     */
    static string  DecryptText(string Text, short EncryptionKey = 5)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] - EncryptionKey);

        }
        return Text;
    }
    
    /**
     * @brief Convert a positive integer into its English words representation.
     *
     * Examples:
     * - 0 -> "" (empty string)
     * - 5 -> "Five "
     * - 42 -> "Forty Two "
     * - 123 -> "One Hundred Twenty Three "
     *
     * @param Number A non-negative integer. Negative numbers are not handled.
     * @return A string with a trailing space in most cases; empty string for 0.
     * @note Grammar uses forms like "Hundreds ", "Thousands ", "Millions ", etc. as implemented.
     */
    static string NumberToText(int Number)
      {

          if (Number == 0)
          {
              return "";
          }

          if (Number >= 1 && Number <= 19)
          {
              string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
          "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
            "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

              return  arr[Number] + " ";

          }

          if (Number >= 20 && Number <= 99)
          {
              string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
              return  arr[Number / 10] + " " + NumberToText(Number % 10);
          }

          if (Number >= 100 && Number <= 199)
          {
              return  "One Hundred " + NumberToText(Number % 100);
          }

          if (Number >= 200 && Number <= 999)
          {
              return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
          }

          if (Number >= 1000 && Number <= 1999)
          {
              return  "One Thousand " + NumberToText(Number % 1000);
          }

          if (Number >= 2000 && Number <= 999999)
          {
              return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
          }

          if (Number >= 1000000 && Number <= 1999999)
          {
              return  "One Million " + NumberToText(Number % 1000000);
          }

          if (Number >= 2000000 && Number <= 999999999)
          {
              return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
          }

          if (Number >= 1000000000 && Number <= 1999999999)
          {
              return  "One Billion " + NumberToText(Number % 1000000000);
          }
          else
          {
              return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
          }


      }
};
