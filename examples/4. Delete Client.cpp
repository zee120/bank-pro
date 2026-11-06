//#include <iostream>
//#include "ClsBankClient.h"
//#include "ClsInputValidate.h"
//
//using namespace std;
//
//void DeletClient()
//{
//    string AccountNumber = "";
//    cout << "\nPlease enter client number: ";
//    AccountNumber = clsInputValidate::ReadString();
//    
//    while(!BankClient:: IsClientExist(AccountNumber))
//    {
//        cout << "\nAccount Number Not Found. Please enter another one: ";
//        AccountNumber = clsInputValidate:: ReadString();
//    }
//    BankClient Client1 = BankClient :: Find(AccountNumber);
//    Client1.Print();
//    
//    char answer = 'n';
//    cout << "\nAre you sure you want to delete this Client y/n: ";
//    cin >> answer;
//    
//    if(answer == 'y' || answer == 'Y')
//    {
//        if(Client1.Delete())
//        {
//            cout << "\nClient Deleted Successfuly";
//            Client1.Print();
//        }
//        
//        else
//        {
//            cout << "\n Error Clients was not Deleted";
//        }
//    }
//    
//}


//int main()
//{
//    DeletClient();
//    return 0;
//    
//}
