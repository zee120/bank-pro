#pragma once
#include<iostream>
#include "clsScreen.h"
#include<string>
#include <iomanip>
#include "ClsBankClient.h"

class clsDeleteClient: protected clsScreen{
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
    
    static void DeletClient()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;// this will exit the function and it will not continue
        }
        
        clsScreen ::_DrawScreenHeader("Delete Client");
        string AccountNumber = "";
        cout << setw(37) << left << "" <<"Please enter client number: ";
        AccountNumber = clsInputValidate::ReadString();
    
        while(!BankClient:: IsClientExist(AccountNumber))
        {
            cout << endl;
            cout << setw(37) << left << "" <<"Account Number Not Found. Please enter another one: ";
            AccountNumber = clsInputValidate:: ReadString();
        }
        BankClient Client1 = BankClient :: Find(AccountNumber);
        _PrintClient(Client1);
    
        char answer = 'n';
        cout << endl;
        cout << setw(37) << left << "" <<"Are you sure you want to delete this Client y/n: ";
        cin >> answer;
    
        if(answer == 'y' || answer == 'Y')
        {
            if(Client1.Delete())
            {
                cout << endl;
                cout << setw(37) << left << "" <<"Client Deleted Successfuly\n";
                _PrintClient(Client1);
            }
    
            else
            {
                cout << endl;
                cout << setw(37) << left << "" <<"Error Clients was not Deleted";
            }
        }
    
    }
    
    
};
