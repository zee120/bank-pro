#pragma once
#include "clsManageUserMenu.hpp"
#include "clsScreen.h"
#include "ClsInputValidate.h"
#include "clsUser.hpp"
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.hpp"
#include "clsDeleteUserScreen.hpp"
#include "clsUpdateUserScreen.hpp"
#include "clsFindUserScreen.h"

class clsManageUserMenu : protected clsScreen
{
private:
    
    enum enManageUserMenuOptions { ListUsers = 1, AddNewUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, Exit = 6};
    
    static void _clearConsole()
    {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    }
    
    static  void _GoBackToManageUserMenue()
    {
        char BackToManageUserMenuKey = 'p';
        char UserKey;
        cout << endl << setw(37) << left << ""<<"Press 'p' key to go back to User Management Menue...";
        cin >> UserKey;
        
        while (BackToManageUserMenuKey != tolower(UserKey)) {
            cin >> UserKey;
        }
        _clearConsole();
        ShowMangeUserMenu();
    }
    
    static short _ReadManageUserMenueOption()
    {
        cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 6]: ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1,6,"\t\t\t\t\t\t\t\t\t\tEnter Number between 1 to 6? ");
        return Choice;
    }
    
    static void _ShowListUserScreen()
    {
        //cout << "List users screen will be here\n";
        clsListUserScreen:: ShowListUserScreen();
    }
    
    static void _ShowAddNewUserScreen()
    {
        //cout << "Add new user screen will be here\n";
        clsAddNewUserScreen:: ShowAddNewUserScreen();
    }
    
    static void _ShowDeleteUserScreen()
    {
        //cout << "Delete user screen will be here\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    
    static void _ShowUpdateUserScreen()
    {
        //cout << "Update user screen will be here\n";
        clsUpdateUserScreen :: ShowUpdateUserScreen();
    }
    
    static void _ShowFindUserScreen()
    {
        //cout << "Find User Screen Will be here\n";
        clsFindUserScreen::ShowFindUserScreen();
    }
    
    static void _Exit()
    {
        _clearConsole();
        //Will go back to main menu from 'preformMainMenu()' function
    }
    
    
    
    
    static void _PerformManageUserMenu(enManageUserMenuOptions UserChoice)
    {
        switch (UserChoice) {
            case enManageUserMenuOptions:: ListUsers:
                _clearConsole();
                _ShowListUserScreen();
                _GoBackToManageUserMenue();
                break;
                
            case enManageUserMenuOptions:: AddNewUser:
                _clearConsole();
                _ShowAddNewUserScreen();
                _GoBackToManageUserMenue();
                break;
            
            case enManageUserMenuOptions:: DeleteUser:
                _clearConsole();
                _ShowDeleteUserScreen();
                _GoBackToManageUserMenue();
                break;
            
            case enManageUserMenuOptions:: UpdateUser:
                _clearConsole();
                _ShowUpdateUserScreen();
                _GoBackToManageUserMenue();
                break;
            
            case enManageUserMenuOptions:: FindUser:
                _clearConsole();
                _ShowFindUserScreen();
                _GoBackToManageUserMenue();
                break;
                
            case enManageUserMenuOptions:: Exit:
                _clearConsole();
                //handled by main menu
                break;
        }
    }
    
    
    
public:
    
    static void ShowMangeUserMenu()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;// this will exit the function and it will not continue
        }
        
        _DrawScreenHeader("User Management");

        cout << setw(37) << left <<""<< "===========================================\n";
        cout << setw(37) << left << "" << "\t\tManage your users\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users\n";
        cout << setw(37) << left << "" << "\t[2] Add New User\n";
        cout << setw(37) << left << "" << "\t[3] Delete User\n";
        cout << setw(37) << left << "" << "\t[4] Update User\n";
        cout << setw(37) << left << "" << "\t[5] Find User\n";
        cout << setw(37) << left << "" << "\t[6] Exit\n";
        cout << setw(37) << left << "" << "===========================================\n";
        
        _PerformManageUserMenu((enManageUserMenuOptions) _ReadManageUserMenueOption());
    }
    
    
};
