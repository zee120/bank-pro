/*
 Deposit Screen
 --------------
 Handles depositing money into an existing client account.
 The flow validates the account number, prints the client card,
 asks for the amount, and confirms before applying the deposit.
*/
#pragma once
#include<iostream>
#include "clsScreen.h"
#include<string>
#include <iomanip>
#include "ClsBankClient.h"
#include "ClsInputValidate.h"
class clsDeposit : protected clsScreen
{
private:
    
    // Helper: pretty-print a client's card details for context
    static void _PrintClient(BankClient Client)
       {
           cout << setw(37) << left << ""  << "Client Card:\n";
           cout << setw(37) << left << ""  << "___________________\n";
           cout << setw(37) << left << ""  << "FirstName   : " << Client.FirstName() << endl;
           cout << setw(37) << left << ""  << "LastName    : " << Client.LastName() << endl;
           cout << setw(37) << left << ""  << "Full Name   : " << Client.FullName()<< endl;
           cout << setw(37) << left << ""  << "Email       : " << Client.Email() << endl;
           cout << setw(37) << left << ""  << "Phone       : " << Client.Phone() << endl;
           cout << setw(37) << left << ""  << "Acc. Number : " << Client.AccountNumber() << endl;
           cout << setw(37) << left << ""  << "Password    : " << Client.PinCode() << endl;
           cout << setw(37) << left << ""  << "Balance     : " << Client.AccountBalance() << endl;
           cout << setw(37) << left << ""  << "___________________\n";
       }
    

    
    
    
public:
/*
 Main entry point for the Deposit screen.
 Steps:
 1) Draw header
 2) Read and validate account number
 3) Show client details
 4) Read deposit amount and confirm
 5) Apply deposit and display the new balance
*/
    static void ShowDepositScreen()
    {
        clsScreen::_DrawScreenHeader("Deposit Menu");
        cout << setw(37) << left << "" << "Enter Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();
        
        while(!(BankClient:: IsClientExist(AccountNumber)))
        {
            cout << setw(37) << left << "" << "Client is not exist\n";
            cout << setw(37) << left << "" << "Enter new Account no.: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        
        BankClient Client = BankClient:: Find(AccountNumber);
        _PrintClient(Client);
        
        cout << setw(37) << left << "" << "Enter Deposit Amount: ";
        double Amount = clsInputValidate:: ReadDblNumber();
        
        cout << endl << setw(37) << left << "" << "Are you sure you want to deposit " << Amount << " to Client No." << Client.AccountNumber() << " ? Y/N: ";
        char Answer = 'N';
        cin >> Answer;
        
        if (Answer =='Y' || Answer == 'y')
        {
            Client.Deposit(Amount);
            cout << setw(37) << left << "" << "Amount Deposited Successfully.\n";
            cout << setw(37) << left << "" << "New Balance of " << Client.FirstName() << " is " << Client.AccountBalance() << endl;
        }
        else
        {
            cout << setw(37) << left << "" << "Operation Failed\n";
        }
    }
};

