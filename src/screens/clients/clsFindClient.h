#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "clsScreen.h"




class clsFindClient : protected clsScreen{
private:
    
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
    static void FindClient()

    {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;// this will exit the function and it will not continue
        }
        
        string AccountNumber = "";
        string PinCode = "";
        
        clsScreen ::_DrawScreenHeader("Find a Client");
        cout <<setw(37) << left << "" << "Search for Client\n";
        cout <<setw(37) << left << "" << "_______________________\n";
        
        cout <<setw(37) << left << "" << "Enter Client Number : ";
        AccountNumber = clsInputValidate::ReadString();
        

        BankClient Client1 = BankClient::Find(AccountNumber);
        
        if (!Client1.IsEmpty())
        {
            cout << setw(37) << left << "" << "Client Found :-)\n";
        }
        
        else
        {
            cout << setw(37) << left << "" << "Client Was not Found :-(\n";
        }
        
        _PrintClient(Client1);
        
        
        
    }
    
};




