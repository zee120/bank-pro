#pragma once
#include<iostream>
#include "clsScreen.h"
#include<string>
#include <iomanip>
#include "ClsBankClient.h"

class clsAddNewClient : protected clsScreen
{
private:
    static void ReadClientInfo(BankClient& Client)
    {
        cout <<setw(37) << left << ""  << "Enter FirstName: ";
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
    static void AddNewClient()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }
        
        _DrawScreenHeader("Adding New Client");
        
        string AccountNumber = "";
        cout << endl << endl;
        cout <<setw(37) << left << "" << "Adding\n";
        cout <<setw(37) << left << "" << "________________________________________\n";
        cout <<setw(37) << left << "" << "Please choose a number for the account: ";
        AccountNumber = clsInputValidate::ReadString();
    
        while(BankClient::IsClientExist(AccountNumber))
        {
            cout <<setw(37) << left << "" << "Account number is already exist. please try again: ";
            AccountNumber = clsInputValidate:: ReadString();
        }
    
        BankClient NewClient = BankClient::GetAddNewClientObject(AccountNumber);
    
        ReadClientInfo(NewClient);
        BankClient:: enSaveResults SaveResults;
        SaveResults = NewClient.Save();
    
        switch(SaveResults){
            case BankClient::enSaveResults::svFaildEmptyObject:
            {
                cout <<setw(37) << left << "" << "Save was not successful because Object was empty";
                break;
            }
    
            case BankClient::enSaveResults::svFaildAccountNumberExists:
            {
                cout <<setw(37) << left << "" <<  "Error account was not saved because account number is used!\n";
                break;
            }
    
            case BankClient::enSaveResults::svSucceeded:
                cout <<setw(37) << left << "" << "Account was saved successfuly";
                break;
    
        }
    
    }
};
