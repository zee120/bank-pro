/*
 Transfer Screen
 ---------------
 Handles transferring money between two client accounts.
 The flow validates source and destination accounts, shows both client cards,
 reads a transfer amount (not exceeding source balance), and confirms before executing.
*/
#pragma once
#include<iostream>
#include "clsScreen.h"
#include<string>
#include <iomanip>
#include "ClsBankClient.h"
#include "ClsInputValidate.h"
#include "clsUtil.h"

class clsTransfer : protected clsScreen
{
private:
    // Helper: pretty-print a client's card details (compact)
    static void _PrintClient(BankClient Client)
    {
        cout << setw(37) << left << ""  << "Client Card:\n";
        cout << setw(37) << left << ""  << "___________________\n";
        cout << setw(37) << left << ""  << "Full Name   : " << Client.FullName()<< endl;
        cout << setw(37) << left << ""  << "Phone       : " << Client.Phone() << endl;
        cout << setw(37) << left << ""  << "Acc. Number : " << Client.AccountNumber() << endl;
        cout << setw(37) << left << ""  << "Balance     : " << Client.AccountBalance() << endl;
        cout << setw(37) << left << ""  << "___________________\n";
    }

   /*
    Read an account number from input and validate that the client exists.
    Re-prompts until a valid account number is entered.
   */
   static string _ReadAccountNumber(string ClientDirection)
    {
        string AccountNumber;
       cout << setw(37) << left << "" << "Please Enter Account Number to Transfer " + ClientDirection + ": ";
        AccountNumber = clsInputValidate::ReadString();
        while (!BankClient::IsClientExist(AccountNumber))
        {
            cout << endl;
            cout << setw(37) << left << "" << "Account number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

   /*
    Read a transfer amount and ensure it does not exceed the source client's balance.
   */
   static double ReadAmount(BankClient SourceClient)
   {
       double Amount;

       cout << setw(37) << left << "" << "Enter Transfer Amount: ";

       Amount = clsInputValidate::ReadDblNumber();

       while (Amount > SourceClient.AccountBalance())
       {
           cout << setw(37) << left << "" << "Amount Exceeds the available Balance, Enter another Amount : ";
           Amount = clsInputValidate::ReadDblNumber();
       }
       return Amount;
   }

public:

    /*
     Main entry point for the Transfer screen.
     Steps:
     1) Draw header
     2) Read & show source client
     3) Read & show destination client
     4) Read amount (validated against source balance)
     5) Confirm and execute transfer
     6) Print both clients after the operation
    */
    static void ShowTransferScreen()
    {
      
        _DrawScreenHeader("Transfer Screen");

        BankClient SourceClient = BankClient::Find(_ReadAccountNumber("From"));

        _PrintClient(SourceClient);

        BankClient DestinationClient = BankClient::Find(_ReadAccountNumber("To"));

        _PrintClient(DestinationClient);

        double Amount = ReadAmount(SourceClient);

        
        cout << setw(37) << left << "" << "Are you sure you want to perform this operation? y/n: ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName()))
            {
                cout << setw(37) << left << "" << "Transfer done successfully\n";
            }
            else
            {
                cout << setw(37) << left << "" << "Transfer Faild \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);


    }
    
};

