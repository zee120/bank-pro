#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsInputValidate.h"
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsClientList.h"
#include "clsAddNewClient.h"
#include "clsDeleteClient.h"
#include "clsUpdateClient.h"
#include "clsFindClient.h"
#include "clsTransactionMenu.h"
#include "clsManageUserMenu.hpp"
#include "Global.h"
#include "clsLoginRegister.hpp"

using namespace std;



class clsMainScreen : protected clsScreen
{
private:
    enum enMainMenueOptions {
                eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
                eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
                eManageUsers = 7, eLoginRegister = 8, eExit = 9
            };

    static void _clearConsole()
    {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    }
    
    static short _ReadMainMenueOption()
    {
        cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 9]: ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1,9,"\t\t\t\t\t\t\t\t\t\tEnter Number between 1 to 9? ");
        return Choice;
    }

    static  void _GoBackToMainMenue()
    {
        char BackToMainMenuKey = 'p';
        char UserKey;
        cout << endl << setw(37) << left << ""<<"Press 'p' key to go back to Main Menue...";
        cin >> UserKey;
        
        while (BackToMainMenuKey != tolower(UserKey)) {
            cin >> UserKey;
        }
        _clearConsole();
        ShowMainMenue();
    }
           
    static void _ShowAllClientsScreen()
    {
        //cout << "\nClient List Screen Will be here...\n";
        clsClientList:: ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        //cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClient:: AddNewClient();
        
    }

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClient::DeletClient();
    }
    
    static void _ShowUpdateClientScreen()
    {
        //cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClient::UpdateClient();
    }
    
    static void _ShowFindClientScreen()
    {
        //cout << "\nFind Client Screen Will be here...\n";
        clsFindClient:: FindClient();
    }
    
    static void _ShowTransactionsMenue()
    {
        //cout << "\nTransactions Menue Will be here...\n";
        clsTransactionMenu:: ShowTransactionMenu();
    }
    
    static void _ShowManageUsersMenue()
    {
        //cout << "\nUsers Menue Will be here...\n";
        clsManageUserMenu:: ShowMangeUserMenu();
    }
    
//    static void _ShowEndScreen()
//    {
//        cout << "\nEnd Screen Will be here...\n";
//    }
    
    static void _LogOut()
    {
        //empty the golabal user
        CurrentUser = clsUser::Find("", "");
        
        //then it will go back to the main function.
    }
    
    static void _showLoginRegisterScreen()
    {
        //cout << "\nLogin Register will be here...\n";
         
        clsLoginRegister:: ShowLoginRegisterScreen();
    }
    
    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
            case enMainMenueOptions::eListClients:
            
                _clearConsole();
                _ShowAllClientsScreen();
                _GoBackToMainMenue();
                break;
            
            case enMainMenueOptions::eAddNewClient:
                _clearConsole();
                _ShowAddNewClientsScreen();
                _GoBackToMainMenue();
                break;
            case enMainMenueOptions::eDeleteClient:
                _clearConsole();
                _ShowDeleteClientScreen();
                _GoBackToMainMenue();
                break;
            case enMainMenueOptions::eUpdateClient:
                _clearConsole();
                _ShowUpdateClientScreen();
                _GoBackToMainMenue();
                break;
            case enMainMenueOptions::eFindClient:
                _clearConsole();
                _ShowFindClientScreen();
                _GoBackToMainMenue();
                break;
            case enMainMenueOptions::eShowTransactionsMenue:
                _clearConsole();
                _ShowTransactionsMenue();
                //ShowMainMenue();  //it then goes directly to main menu instead of typing 'p'
                _GoBackToMainMenue();
                break;
            case enMainMenueOptions::eManageUsers:
                _clearConsole();
                _ShowManageUsersMenue();
                _GoBackToMainMenue();
                break;
            case enMainMenueOptions::eLoginRegister:
                _clearConsole();
                _showLoginRegisterScreen();
                _GoBackToMainMenue();
                break;
                
            case enMainMenueOptions::eExit:
                _LogOut();
                //Login();
                break;
            }
        }
    
public:
    
    static void ShowMainMenue()
    {
        _DrawScreenHeader("Main Screen");

        cout << setw(37) << left <<""<< "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Show login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }

        
};
