/*
 Transaction Menu Screen
 -----------------------
 This screen presents transaction-related actions to the user and routes
 to the corresponding screens (Deposit, Withdraw, Total Balances, Transfer).
 It also enforces access rights using clsScreen::CheckAccessRights.
*/
#pragma once
#include<iostream>
#include "clsScreen.h"
#include<string>
#include <iomanip>
#include "ClsBankClient.h"
#include "ClsInputValidate.h"
#include "clsDeposit.hpp"
#include "clsWithdraw.h"
#include "clsTotalBalances.hpp"
#include "clsTransfer.hpp"
#include "clsTransferLog.hpp"



class clsTransactionMenu : protected clsScreen{
private:
    enum enTransactionMenuOptions {Deposit = 1, Withdraw = 2, TotalBalances = 3, eTransfer = 4, eShowTransferLog = 5, Exit = 6 };
    
    // Simple console clearing by printing multiple newlines (portable fallback)
    static void _clearConsole()
    {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    }
    
    /*
     Waits for the user to press 'p' (case-insensitive) to return to the
     Transaction Menu, then clears the console and redraws the menu.
    */
    static  void _GoBackToTransMenue()
    {
        char BackToTransMenuKey = 'p';
        char UserKey;
        cout << endl << setw(37) << left << ""<<"Press 'p' key to go back to Transaction Menue...";
        cin >> UserKey;
        
        while (BackToTransMenuKey != tolower(UserKey)) {
            cin >> UserKey;
        }
        _clearConsole();
        ShowTransactionMenu();
    }
    
    /*
     Reads the user's choice for the transaction menu.
     Ensures the value is within the allowed range using input validation.
    */
    static short _ReadTransactionMenueOption()
    {
        cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 6]: ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1,6,"\t\t\t\t\t\t\t\t\t\tEnter Number between 1 to 6: ");
        return Choice;
    }
    
    // Route to the Deposit screen implementation
    static void _ShowDepositScreen()
    {
        //cout << "Dedpsit screen will be here";
        clsDeposit::ShowDepositScreen();
    }
    
    // Route to the Withdraw screen implementation
    static void _ShowWithdrawScreen()
    {
        //cout << "Withdraw screen will be here";
        clsWithdraw::ShowWithdrawScreen();
    }
    
    // Route to the Total Balances report screen
    static void _ShowTotalBalancesScreen()
    {
        //cout << "Total balances screen will be here";
        clsTotalBalances:: ShowTotalBalances();
    }
    
    // Route to the Transfer screen implementation
    static void _ShowTransferScreen()
    {
        clsTransfer:: ShowTransferScreen();
    }
    
    static void _ShowTransferLogScreen()
    {
        clsTrasferLog:: ShowTransferLogScreen();
    }
    
    static void _Exit()
    {
        
    }
    
    /*
     Executes the selected transaction option by routing to the appropriate screen
     and then returns to the transaction menu when the flow completes.
    */
    static void _PreformTransactionMenu(enTransactionMenuOptions UserChoice)
    {
        switch(UserChoice)
        {
            case enTransactionMenuOptions:: Deposit:
                _clearConsole();
                _ShowDepositScreen();
                _GoBackToTransMenue();
                break;
                
            case enTransactionMenuOptions:: Withdraw:
                _clearConsole();
                _ShowWithdrawScreen();
                _GoBackToTransMenue();
                break;
                
            case enTransactionMenuOptions:: TotalBalances:
                _clearConsole();
                _ShowTotalBalancesScreen();
                _GoBackToTransMenue();
                break;
            case enTransactionMenuOptions:: eTransfer:
                _clearConsole();
                _ShowTransferScreen();
                _GoBackToTransMenue();
                break;
            case enTransactionMenuOptions:: eShowTransferLog:
                _clearConsole();
                _ShowTransferLogScreen();
                _GoBackToTransMenue();
                break;
                
            // Exit returns to the previous menu (no screen to show)
            case enTransactionMenuOptions:: Exit:
                _clearConsole();
                break;
        }
            
    }
    
public:
    
    static void ShowTransactionMenu()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;// this will exit the function and it will not continue
        }
        
        
        _DrawScreenHeader("Transaction Screen");

        cout << setw(37) << left <<""<< "===========================================\n";
        cout << setw(37) << left << "" << "\t\tTransaction\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances\n";
        cout << setw(37) << left << "" << "\t[4] Transfer\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Logs\n";
        cout << setw(37) << left << "" << "\t[6] Exit\n";
        cout << setw(37) << left << "" << "===========================================\n";
        
        _PreformTransactionMenu((enTransactionMenuOptions) _ReadTransactionMenueOption());
    }
    
};
