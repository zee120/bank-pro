#pragma once
#include<iostream>
#include "clsScreen.h"
#include<string>
#include <iomanip>
#include "ClsBankClient.h"


class clsUpdateClient : protected clsScreen{
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
    
    static void _ReadClientInfo(BankClient& Client)
    {
        cout << setw(37) << left << ""  << "Enter FirstName: ";
        Client.setFirstName(clsInputValidate::ReadString());
        cout << endl;
        
        cout <<setw(37) << left << ""  << "Enter LastName: ";
        Client.setLastName(clsInputValidate::ReadString());
        cout << endl;
        
        cout <<setw(37) << left << ""  << "Enter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());
        cout << endl;
        
        cout <<setw(37) << left << ""  << "Enter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());
        cout << endl;
        
        cout <<setw(37) << left << ""  << "Enter PinCode: ";
        Client.SetPinCode(clsInputValidate::ReadString());
        cout << endl;
        
        cout <<setw(37) << left << ""  << "Enter starting Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
        cout << endl;
    }

    
public:
    static void UpdateClient()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue
        }
        
        clsScreen ::_DrawScreenHeader("Update Client");
        string accountNumber = "";
    
        cout <<setw(37) << left << ""  << "Please enter accout number: ";
        accountNumber = clsInputValidate::ReadString();
        cout << endl;
    
        while(!BankClient:: IsClientExist(accountNumber))
        {
            cout <<setw(37) << left << ""  << "Account number is not found choose another one: ";
            accountNumber = clsInputValidate::ReadString();
            cout << endl;
        }
    
        BankClient Client = BankClient::Find(accountNumber);
        _PrintClient(Client);
    
        cout << setw(37) << left << ""  << "Update Client Info:\n";
        cout << setw(37) << left << "" << "____________________\n";
        _ReadClientInfo(Client);
        cout << setw(37) << left << "" << "____________________\n";
    
        BankClient:: enSaveResults SaveResult;
        SaveResult = Client.Save();
    
        switch (SaveResult) {
            case BankClient::enSaveResults::svFaildEmptyObject:
                cout << setw(37) << left << "" << "Save was not successful because Object was empty";
                break;
    
            case BankClient::enSaveResults::svSucceeded:
                cout << setw(37) << left << "" << "Account was saved successfuly";
                break;
    
            case BankClient::svFaildAccountNumberExists:
                break;
        }
    
    }
    
};
