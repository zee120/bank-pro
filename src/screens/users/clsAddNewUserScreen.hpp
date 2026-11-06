#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsUser.hpp"
#include "ClsInputValidate.h"
#include<string>
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser &User)
    {
        cout <<setw(37) << left << ""  << "Enter FirstName: ";
        User.setFirstName(clsInputValidate::ReadString());
        cout << endl;
        
        cout <<setw(37) << left << ""  << "Enter LastName: ";
        User.setLastName(clsInputValidate::ReadString());
        cout << endl;
        
        cout <<setw(37) << left << ""  << "Enter Email: ";
        User.SetEmail(clsInputValidate::ReadString());
        cout << endl;
        
        cout <<setw(37) << left << ""  << "Enter Phone: ";
        User.SetPhone(clsInputValidate::ReadString());
        cout << endl;
        
        cout <<setw(37) << left << ""  << "Enter Password: ";
        User.SetPassword(clsInputValidate::ReadString());
        cout << endl;
        
        User.SetPermission(_ReadPermissionToSet());
        cout << endl;
    }
    
    
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
    
    static int _ReadPermissionToSet()
    {
        int Permissions = 0;
        char Answer = 'n';
        
        cout <<setw(37) << left << "" << "Do you want to give full access? y/n: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }
        cout << endl;

        cout <<setw(37) << left << "" << "Do you want to give access to : \n ";
        
        
        cout <<setw(37) << left << "" << "Show Client List? y/n: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pListClients;
        }
        cout << endl;
        
        cout <<setw(37) << left << "" << "Add New Client? y/n: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }
        cout << endl;
        
        cout <<setw(37) << left << "" << "Delete Client? y/n: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }
        cout << endl;

        cout <<setw(37) << left << "" << "Update Client? y/n: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }
        cout << endl;

        cout <<setw(37) << left << "" << "Find Client? y/n: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }
        cout << endl;
        
        cout <<setw(37) << left << "" << "Transactions? y/n: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }
        cout << endl;

        
        cout <<setw(37) << left << "" << "Manage Users? y/n ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }
        cout << endl;
        
        cout <<setw(37) << left << "" << "Show login Register? y/n ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }

        return Permissions;
        
    }
    
    
    
public:
    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("Adding New User");
        
        string UserName = "";

        cout <<setw(37) << left << "" << "Please Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName))
        {
            cout <<setw(37) << left << "" << "UserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        
        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
        
        _ReadUserInfo(NewUser);
        
        
        clsUser:: enSaveResults SaveResult;
        SaveResult = NewUser.Save();
        
        switch (SaveResult)
        {
            case  clsUser::enSaveResults::svSucceeded:
            {
                cout <<setw(37) << left << "" << "User Addeded Successfully :-)\n";
                _PrintUser(NewUser);
                break;
            }
                
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout <<setw(37) << left << "" << "Error User was not saved because it's Empty";
                break;

            }
                    
            case clsUser::enSaveResults::svFaildUserExists:
            {
                cout <<setw(37) << left << "" << "Error User was not saved because UserName is used!\n";
                break;

            }
        }
    }
    
};
