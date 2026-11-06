#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <iostream>
using namespace std;


class clsString
{
    
    
private:
    string _value;
    

    
    
public:
    //Class related
    
    clsString()
    {
        _value = " ";
    }
    
    clsString(string Value)
    {
        _value = Value;
    }
    
    void SetValue(string Value)
    {
        _value = Value;
    }
    
    string Value()
    {
        return _value;
    }
    
    
    
    
    //Static Class Methods
    
    static short Length(string sentence)
    {
        return sentence.length();
    }
    
    static short CountWords(string sentence)
    {
        string delimeter =" ";
        string sWord;
        short WordCount = 0;
        short pos = 0;
        while((pos = sentence.find(delimeter)) != std::string::npos)
        {
            sWord = sentence.substr(0, pos);
            if(sWord != "")
            {
                WordCount++;
            }
            
            sentence.erase(0, pos + delimeter.length());
        }
        if(sentence != "")
        {
            WordCount++;
        }
        
        return WordCount;
    }
    
    static string FirstLetterInWords(string sentence)
    {
        bool isFirstLetter = true;
        string FirstLetterOfEachWord;
        
        
        for (short i = 0; i < sentence.length(); i++)
        {
            if (sentence[i] != ' ' && isFirstLetter)
            {
                FirstLetterOfEachWord += sentence[i];
            }
            isFirstLetter = (sentence[i] == ' ' ? true : false);
        }
        
        return FirstLetterOfEachWord;
    }
    
    static string UpperCaseFirstLetter(string sentence)
    {
        bool IsFirstLetter = true;
    
        for(short i = 0; i < sentence.length(); i++)
        {
            if(sentence[i] != ' ' && IsFirstLetter)
            {
                sentence[i] = toupper(sentence[i]);
            }
            IsFirstLetter = (sentence[i] == ' ')? true : false;
        }
        return sentence;
    }
    
    static string LowerCaseFirstLetter(string sentence)
    {
        bool IsFirstLetter = true;
        for(short i = 0; i < sentence.length(); i++)
        {
            if(sentence[i] != ' ' && IsFirstLetter)
            {
                sentence[i] = tolower(sentence[i]);
            }
            IsFirstLetter = (sentence[i] == ' ')? true : false;
        }
        return sentence;
    }
    
    static string InvertAllLettersCase(string sentence)
    {
        for(short i = 0; i < sentence.length(); i++)
        {
            sentence[i] = isupper(sentence[i]) ? tolower(sentence[i]) : toupper(sentence[i]);
        }
        return sentence;
    }
    
    static short CapitalLettersCounts(string sentence)
    {
        short count = 0;
        for(short i = 0; i < sentence.length(); i++)
        {
            if(sentence[i] != ' ' && isupper(sentence[i]) && !isdigit(sentence[i]) && !ispunct(sentence[i]))
            {
                count++;
            }
        }
        return count;
    }
    
    static short SmallLettersCount(string sentence)
    {
        short count = 0;
        for(short i = 0; i < sentence.length(); i++)
        {
            if(sentence[i] != ' ' && !isupper(sentence[i]) && !isdigit(sentence[i]) && !ispunct(sentence[i]))
            {
                count++;
            }
        }
        return count;
    }
    
    static short CountCharInWords(string sentence, char character, bool MatchCase)
    {
        short count = 0;
        for(short i = 0; i < sentence.length(); i++)
        {
            if(MatchCase)
            {
                if(sentence[i] == character)
                {
                    count++;
                }
            }
            else
            {
                if(tolower(sentence[i]) == tolower(character))
                    count++;
            }
        }
        return count;
    }
    
    static bool IsVowel(char character)
    {
        char ch = tolower(character);
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
    }

    static short CountVowels(string sentence)
    {
        short vowelCount = 0;
        for(short i = 0; i < sentence.length(); i++)
        {
            if(IsVowel(sentence[i]))
                vowelCount++;
        }
        return vowelCount;
    }
    
    static void PrintVowels(string sentence)
    {
        cout << "Vowwels in string are: ";
        for(short i = 0; i < sentence.length(); i++)
        {
            if(IsVowel(sentence[i]))
                cout << sentence[i] << "  ";
        }
        cout << endl;
    }
    
    static void PrintEachWord(string sentence)
    {
        string delim = " "; // delimeter
    
        cout << "Your string :\n";
        short pos = 0;
        string sWord; // define a string variable
    
        //use find() funvtion to the position of the delimeters
        while((pos = sentence.find(delim)) != std::string::npos)
        {
            sWord = sentence.substr(0, pos); // store the word
            if(sWord != "")
                cout << sWord << endl;
            //erase untill position and move to next word
            sentence.erase(0, pos + delim.length());
        }
        if(sentence != "")
            //print last word in a string
            cout << sentence << endl;
    }
    
    static vector<string> SplitInVector(string sentence, string delimeter)
    {
        vector<string> Vwords;
        short pos = 0;
        while((pos = sentence.find(delimeter)) != sentence.npos)
        {
            if(sentence.substr(0, pos) != "")
            {
                Vwords.push_back(sentence.substr(0, pos));
            }
            sentence.erase(0, pos + delimeter.length());
        }
        if(sentence != "")
        {
            Vwords.push_back(sentence);
        }
        return Vwords;
    }
    
    static string joinVecctorString(vector <string> Vstrings, string delim)
    {
        string Swort;
        for(string i : Vstrings)
        {
            Swort += i + delim;
        }
        return Swort.substr(0, Swort.length() - delim.length()); // to remove last delim
    }
    
    static string joinString(string arrWords[100], short arrLength, string delim)
    {
        string Swort;
        for(short i = 0; i < arrLength; i++)
        {
            Swort += arrWords[i] + delim;
        }
        return Swort.substr(0, Swort.length() - delim.length()); // to remove last delim
    }
    
    static string TrimLeft(string sentence)
    {
        for(short i = 0; i < sentence.length(); i++)
        {
            if(sentence[i] != ' ')
                return sentence.substr(i, sentence.length() - i);
        }
        return "";
    }
    
    static string TrimRight(string s1)
    {
        for(short i = s1.length() - 1; i >= 0; i--)
        {
            if(s1[i] != ' ')
                return s1.substr(0, i);
        }
        return "";
    }
    
    static string Trim(string s1)
    {
        return TrimLeft(TrimRight(s1));
    }
    
    static string reverseString(string sentence)
    {
        vector<string> Vwords = SplitInVector(sentence, " ");
        string reveresed = "";
    
        //declear iterator
        vector<string> :: iterator iter = Vwords.end();
        while(iter != Vwords.begin())
           {
               --iter;
               reveresed += *iter + " ";
           }
        //remove last space
        reveresed = reveresed.substr(0, reveresed.length() - 1);
        return reveresed;
    }
    
    static string ReplceWord(string originalSentence, string targetWord, string NewWord)
    {
        string newSentence = originalSentence;
        short pos = 0;
        while((pos = newSentence.find(targetWord)) != string:: npos)
        {
            //.replace is a built in function
            newSentence = newSentence.replace(pos, targetWord.length(), NewWord);
        }
        return newSentence;
    }
    
    static string erasePunct(string sentence)
    {
        string NewSentence = "";
        for(short i = 0; i < sentence.length(); i++)
        {
            if(!ispunct(sentence[i]))
            {
                NewSentence += sentence[i];
            }
        }
        return NewSentence;
    }
    
    
    
    
    //Object Class Methods
    
    short Length()
    {
        return Length(_value);
    }
    
    string FirstLetterInWords()
    {
        return FirstLetterInWords(_value);
    }
    
    void UpperCaseFirstLetter()
    {
        _value = UpperCaseFirstLetter(_value);
    }
    
    void LowerCaseFirstLetter()
    {
        _value = LowerCaseFirstLetter(_value);
    }
    
    void InvertAllLettersCase()
    {
        _value = InvertAllLettersCase(_value);
    }
    
    short CapitalLettersCounts()
    {
        return CapitalLettersCounts(_value);
    }
    
    short SmallLettersCount()
    {
        return SmallLettersCount(_value);
    }
    
    short CountCharInWords(char ch, bool matchCase = true)
    {
        return CountCharInWords(_value, ch, matchCase);
    }
    
    short CountVowels()
    {
        return CountVowels(_value);
    }
    
    void PrintVowels()
    {
        PrintVowels(_value);
    }
    
    void PrintEachWord()
    {
        PrintEachWord(_value);
    }
    
    short CountWords()
    {
        return CountWords(_value);
    }
    
    vector<string> SplitInVector(string delimeter)
    {
        return SplitInVector(_value, delimeter);
    }
    
    void TrimLeft()
    {
        _value = TrimLeft(_value);
    }
    
    void TrimRight()
    {
        _value = TrimRight(_value);
    }
    
    void Trim()
    {
        _value = Trim(_value);
    }
    
    void reverseString()
    {
        _value = reverseString(_value);
    }
    
    string ReplceWord(string TargerWord, string NewWord)
    {
        return ReplceWord(_value, TargerWord, NewWord);
    }
    
    void erasePunct()
    {
        _value = erasePunct(_value);
    }
};
