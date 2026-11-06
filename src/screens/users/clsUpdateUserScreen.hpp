#pragma once
#include<iostream>
#include "clsScreen.h"
#include "ClsInputValidate.h"
#include<string>
#include <iomanip>
#include "clsUser.hpp"

class clsUpdateUserScreen : protected clsScreen
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
    
    static void _ReadUserInfo(clsUser & User)
    {
        cout << setw(37) << left << ""  << "Enter FirstName: ";
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
        
        cout << setw(37) << left << ""  << "Permissions "<< endl;
        User.SetPermission(_ReadPermissionToSet());
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
    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("Updating User");
        
        string UserName = "";
        
        cout <<setw(37) << left << ""  << "Please enter User Name: ";
        UserName = clsInputValidate::ReadString();
        
        while(!clsUser::IsUserExist(UserName))
        {
            cout <<setw(37) << left << "" << "User Name is not exist. please try again: ";
            UserName = clsInputValidate:: ReadString();
            
        }
        
        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);
        
        char Answer = 'n';
        cout << setw(37) << left << ""  << "Do you want to update this user? y/n: ";
        cin >> Answer;
        if(Answer == 'y' || Answer == 'Y')
        {
            cout << setw(37) << left << ""  << "Update Client Info:\n";
            cout << setw(37) << left << "" << "____________________\n";
            _ReadUserInfo(User);
            cout << setw(37) << left << "" << "____________________\n";
            
            clsUser:: enSaveResults svResult;
            svResult = User.Save();
            
            switch(svResult)
            {
                case clsUser::enSaveResults::svFaildEmptyObject:
                    cout << setw(37) << left << "" << "Save was not successful because Object was empty";
                    break;
        
                case clsUser::enSaveResults::svSucceeded:
                    cout << setw(37) << left << "" << "Account was saved successfuly";
                    break;
        
                case clsUser::svFaildUserExists:
                    break;
            }
        }
        
        else
            cout << setw(37) << left << "" << "Update Canceled" << endl;
        
        
        
    }
};
