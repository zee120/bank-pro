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
//void UpdateClient()
//{
//    string accountNumber = "";
//    
//    cout << "\nPlease enter accout number: ";
//    accountNumber = clsInputValidate::ReadString();
//    
//    while(!BankClient:: IsClientExist(accountNumber))
//    {
//        cout << "\nAccount number is not found choose another one: ";
//        accountNumber = clsInputValidate::ReadString();
//    }
//    
//    BankClient Client = BankClient::Find(accountNumber);
//    Client.Print();
//    
//    cout << "\n\nUpdate Client Info:";
//    cout << "\n____________________\n";
//    ReadClientInfo(Client);
//    cout << "\n____________________\n";
//    
//    BankClient:: enSaveResults SaveResult;
//    SaveResult = Client.Save();
//    
//    switch (SaveResult) {
//        case BankClient::enSaveResults::svFaildEmptyObject:
//            cout << "Save was not successful because Object was empty";
//            break;
//            
//        case BankClient::enSaveResults::svSucceeded:
//            cout << "Account was saved successfuly";
//            break;
//            
//
//        case BankClient::svFaildAccountNumberExists:
//            break;
//    }
//    
//}
//
//
//int main()
//{
//    UpdateClient();
//    return 0;
//    
//}
