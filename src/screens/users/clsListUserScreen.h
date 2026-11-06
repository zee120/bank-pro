#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsUser.hpp"
#include<string>
#include <iomanip>

class clsListUserScreen : protected clsScreen
{
private:
    
    static void _PrintUserRecordLine(clsUser User)
    {
    
        cout << "| " << setw(15) << left << User.UserName();
        cout << "| " << setw(20) << left << User.FullName();
        cout << "| " << setw(15) << left << User.Phone();
        cout << "| " << setw(35) << left << User.Email();
        cout << "| " << setw(10) << left << User.Password();
        cout << "| " << setw(12) << left << User.Permission();
    }
    
public:
    
    static void ShowListUserScreen()
    {
        vector<clsUser> vUsers = clsUser::GetUsersList();
        _DrawScreenHeader("User List", "Total List (" + to_string(vUsers.size()) + ")");
        
        cout << "\n______________________________________________________________________";
        cout << "__________________________________________________\n" << endl;
    
        cout << "| " << left << setw(15) << "User_Name";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(35) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permission";
    
        cout << "\n______________________________________________________________________";
        cout << "__________________________________________________\n" << endl;
        
        if(vUsers.size() == 0)
        {
            cout << "\t\t\t\tNo Users Available In the System!";
        }
        
        else{
            for(clsUser User : vUsers)
            {
                _PrintUserRecordLine(User);
                cout << endl;
            }
            
            cout << "\n______________________________________________________________________";
            cout << "__________________________________________________\n" << endl;
        }
        
    }
    
    
};
