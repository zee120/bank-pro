#pragma once
#include <iostream>
#include <string>
using namespace std;

class person
{
private:
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;
    
public:
    person(string FirstName, string LastName, string Email, string Phone)
    {
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }
    
    //Property set
    void setFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }
    void setLastName(string LastName)
    {
        _LastName = LastName;
    }
    void SetEmail(string Email)
    {
        _Email = Email;
    }
    void SetPhone(string Phone)
    {
        _Phone = Phone;
    }
    
    //Prperty Get
    string Phone()
    {
        return _Phone;
    }
      
    string Email()
    {
        return _Email;
    }
    
    string FirstName()
    {
        return _FirstName;
    }
    
    string LastName()
    {
        return _LastName;
    }

    string FullName()
    {
        return _FirstName + " " + _LastName;
    }

    void Print()
    {
        cout << "\nInfo:";
        cout << "\n___________________";
        cout << "\nFirstName: " << _FirstName;
        cout << "\nLastName : " << _LastName;
        cout << "\nFull Name: " << FullName();
        cout << "\nEmail    : " << _Email;
        cout << "\nPhone    : " << _Phone;
        cout << "\n___________________\n";

    }

    
};
