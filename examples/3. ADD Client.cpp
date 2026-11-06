//#include <iostream>
//#include "ClsBankClient.h"
//#include "ClsInputValidate.h"
//
//using namespace std;
//
//void ReadClientInfo(BankClient& Client)
//{
//    cout << "\nEnter FirstName: ";
//    Client.setFirstName(clsInputValidate::ReadString());
//
//    cout << "\nEnter LastName: ";
//    Client.setLastName(clsInputValidate::ReadString());
//
//    cout << "\nEnter Email: ";
//    Client.SetEmail(clsInputValidate::ReadString());
//
//    cout << "\nEnter Phone: ";
//    Client.SetPhone(clsInputValidate::ReadString());
//
//    cout << "\nEnter PinCode: ";
//    Client.SetPinCode(clsInputValidate::ReadString());
//
//    cout << "\nEnter Account Balance: ";
//    Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
//}
//
//
//void AddNewClient()
//{
//    string AccountNumber = "";
//    cout << "Adding new client\n";
//    cout << "\n____________________\n";
//    cout << "Please enter account number: ";
//    AccountNumber = clsInputValidate::ReadString();
//    
//    while(BankClient::IsClientExist(AccountNumber))
//    {
//        cout << "Account number is already exist. please try again: ";
//        AccountNumber = clsInputValidate:: ReadString();
//    }
//    
//    BankClient NewClient = BankClient::GetAddNewClientObject(AccountNumber);
//    
//    ReadClientInfo(NewClient);
//    BankClient:: enSaveResults SaveResults;
//    SaveResults = NewClient.Save();
//    
//    switch(SaveResults){
//        case BankClient::enSaveResults::svFaildEmptyObject:
//        {
//            cout << "\nSave was not successful because Object was empty";
//            break;
//        }
//            
//        case BankClient::enSaveResults::svFaildAccountNumberExists:
//        {
//            cout << "\nError account was not saved because account number is used!\n";
//            break;
//        }
//            
//        case BankClient::enSaveResults::svSucceeded:
//            cout << "\nAccount was saved successfuly";
//            break;
//            
//    }
//    
//}


//int main()
//{
//    AddNewClient();
//    return 0;
//}
