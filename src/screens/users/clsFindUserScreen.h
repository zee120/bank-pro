#pragma once
#include<iostream>
#include "clsScreen.h"
#include "ClsInputValidate.h"
#include<string>
#include <iomanip>
#include "clsUser.hpp"

class clsFindUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
       {
           cout << setw(37) << left << ""  << "User Card:\n";
           cout << setw(37) << left << ""  << "___________________\n";
           cout << setw(37) << left << ""  << "FirstName   : " << User.FirstName() << endl;
           cout << setw(37) << left << ""  << "LastName    : " << User.LastName() << endl;
           cout << setw(37) << left << ""  << "Full Name   : " << User.FullName()<< endl;
           cout << setw(37) << left << ""  << "Email       : " << User.Email() << endl;
           cout << setw(37) << left << ""  << "Phone       : " << User.Phone() << endl;
           cout << setw(37) << left << ""  << "User Name   : " << User.UserName() << endl;
           cout << setw(37) << left << ""  << "Password    : " << User.Password() << endl;
           cout << setw(37) << left << ""  << "Permissions : " << User.Permission() << endl;
           cout << setw(37) << left << ""  << "___________________\n";
       }
    
public:
    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("Search Users");
        string UserName = "";
        
        cout <<setw(37) << left << "" << "Search for User\n";
        cout <<setw(37) << left << "" << "_______________________\n";
        
        cout <<setw(37) << left << "" << "Enter User Name : ";
        UserName = clsInputValidate::ReadString();
        
        clsUser User = clsUser::Find(UserName);
        
        if(!User.IsEmpty())
        {
            cout <<setw(37) << left << "" << "User Found \n";
        }
        
        else
        {
            cout << setw(37) << left << "" << "User Was not Found :-(\n";
        }
        
        _PrintUser(User);
        
        
    }
};
