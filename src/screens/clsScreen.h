#pragma once
#include<iostream>
#include<string>
#include <iomanip>
#include "clsUser.hpp"
#include "Global.h"
#include "ClsDate.h"

using namespace std;


class clsScreen{
    
private:
    void _showLoginCredentials()
    {
        
    }
    
    
protected:
    static void _DrawScreenHeader(string Title,string SubTitle = "")
        {
            cout << "\n______________________________________________________________________";
            cout << "_________________________________________\n" << endl;
            cout << setw(37) << left << "\t\t\t\t" << Title << endl;
            if (SubTitle != "")
            {
                cout << setw(37) << left << "\t\t\t" <<SubTitle;
            }
            cout << "\n______________________________________________________________________";
            cout << "_________________________________________\n" << endl;
        
            cout <<  "Current User: " <<  CurrentUser.FullName() << endl;
            cout <<  "Current Date: " <<  clssDate::DateToString(clssDate:: GetSystemDate())<< endl;
        }
    
    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if(!CurrentUser.CheckAccessPermission(Permission)){
            cout << "\t\t\t\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t\t\t\t  Access Denied! User not authorized.";
            cout << "\n\t\t\t\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        
        return true;
    }
    
    
    
};
