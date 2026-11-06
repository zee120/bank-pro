#pragma once
#include<iostream>
#include "clsScreen.h"
#include "ClsInputValidate.h"
#include<string>
#include <iomanip>
#include "clsUser.hpp"

class clsDeleteUserScreen : protected clsScreen
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
    
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("Delete User");
        string UserName = "";
        cout << setw(37) << left << "" << "User Name: ";
        UserName = clsInputValidate:: ReadString();
        
        while(!clsUser::IsUserExist(UserName))
        {
            cout << endl;
            cout << setw(37) << left << "" <<"Account Number Not Found. Please enter another one: ";
            UserName = clsInputValidate:: ReadString();
        }
        
        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);
        
        char answer = 'n';
        cout << endl;
        cout << setw(37) << left << "" <<"Are you sure you want to delete this User y/n: ";
        cin >> answer;
        
        if(answer == 'y' || answer == 'Y')
        {
            if(User.Delete())
            {
                cout << endl;
                cout << setw(37) << left << "" <<"User Deleted Successfuly\n";
                _PrintUser(User);
                
            }
            
            else
            {
                cout << endl;
                cout << setw(37) << left << "" <<"Error Clients was not Deleted";
            }
        }
    }
    
    
    
    
    
    
};
