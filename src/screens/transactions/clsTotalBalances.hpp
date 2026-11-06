/*
 Total Balances Screen
 ---------------------
 Displays all clients with their balances and the total sum.
 Also prints the total in words using clsUtil::NumberToText.
*/
#pragma once
#include<iostream>
#include "clsScreen.h"
#include<string>
#include <iomanip>
#include "ClsBankClient.h"
#include "ClsInputValidate.h"
#include "clsUtil.h"
class clsTotalBalances : clsScreen
{
private:
    
    // Helper: print a single row with account number, client name, and balance
    static void _PrintClientRecordBalanceLine(BankClient Client)
    {
        cout << "| " << setw(25) << left << Client.AccountNumber();
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance();
    }
    
public:
    
    /*
     Main entry point for the Total Balances screen.
     Steps:
     1) Draw header
     2) Load all clients
     3) Print table header
     4) Print each client's balance row
     5) Print the total and its text representation
    */
    static void ShowTotalBalances()
    {
        clsScreen::_DrawScreenHeader("Total Balances");
        
        vector<BankClient> vClients = BankClient:: GetClientsList();
        cout << setw(40) << left << "" << "Client List (" << vClients.size() << ") Client(s).";
        cout << "\n______________________________________________________________________";
        cout << "_________________________________________\n" << endl;
    
        cout << "| " << left << setw(25) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
    
        cout << "\n______________________________________________________________________";
        cout << "_________________________________________\n" << endl;
    
        double TotalBalances = BankClient:: GetTotalBalances();
    
        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
        {
            for (BankClient Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            }
        }
    
        cout << "\n______________________________________________________________________";
        cout << "_________________________________________\n" << endl;
    
        cout << "Total Balances = " << TotalBalances << "--";
        cout << "(" << clsUtil::NumberToText(TotalBalances) << ")" << endl;
    }
    
    
};

