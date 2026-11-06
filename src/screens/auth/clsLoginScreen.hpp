#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.hpp"
#include "clsMainScreen.h"
#include "Global.h"
#include "clsUtil.h"

class clsLoginScreen : protected clsScreen{
    
private:
    static bool _Login()
    {
        bool LoginFailed = false;
        short FailedLoginCount = 0;
        
        string Username, Password;
        do{
            if(LoginFailed)
            {
                FailedLoginCount++;
                cout << setw(37) << left << ""  << "Invalid Username/Password\n";
                cout << setw(37) << left << ""  << "attemts remaining: " << 3 - FailedLoginCount << endl;
                
            }
            
            if(FailedLoginCount == 3)
            {
                return false;
            }
            
            cout << endl;
            
            cout << setw(37) << left << "" << "Enter Username: ";
            cin >> Username;
            
            cout << setw(37) << left << "" << "Enter Password: ";
            cin >> Password;
            
            CurrentUser = clsUser::Find(Username, Password);
            
            LoginFailed = CurrentUser.IsEmpty();
            
        } while(LoginFailed);
        
        CurrentUser.RegisterLogIn();
        clsMainScreen:: ShowMainMenue();
        return true;
    }
    
    
public:
    static bool ShowLoginScreen()
    {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        _DrawScreenHeader("Login Screen");
        return _Login();
    }
};
