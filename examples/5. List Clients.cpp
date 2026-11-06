//#include <iostream>
//#include "ClsBankClient.h"
//#include "ClsInputValidate.h"
//
//using namespace std;
//
//void PrintClientRecordLine(BankClient Client)
//{
//
//    cout << "| " << setw(15) << left << Client.AccountNumber();
//    cout << "| " << setw(20) << left << Client.FullName();
//    cout << "| " << setw(15) << left << Client.Phone();
//    cout << "| " << setw(24) << left << Client.Email();
//    cout << "| " << setw(10) << left << Client.PinCode();
//    cout << "| " << setw(12) << left << Client.AccountBalance();
//
//}
//
//void ShowClientsList()
//{
//    vector<BankClient> vClients = BankClient:: GetClientsList();
//    cout << "\n\t\t\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
//    cout << "\n______________________________________________________________________";
//    cout << "_________________________________________\n" << endl;
//    
//    cout << "| " << left << setw(15) << "Accout Number";
//    cout << "| " << left << setw(20) << "Client Name";
//    cout << "| " << left << setw(15) << "Phone";
//    cout << "| " << left << setw(24) << "Email";
//    cout << "| " << left << setw(10) << "Pin Code";
//    cout << "| " << left << setw(12) << "Balance";
//    
//    cout << "\n______________________________________________________________________";
//    cout << "_________________________________________\n" << endl;
//    
//    if (vClients.size() == 0)
//        cout << "\t\t\t\tNo Clients Available In the System!";
//    
//    else
//    {
//        for (BankClient Client : vClients)
//            {
//                PrintClientRecordLine(Client);
//                cout << endl;
//            }
//    }
//    
//    cout << "\n______________________________________________________________________";
//    cout << "_________________________________________\n" << endl;
//}
//
//
//int main()
//{
//    ShowClientsList();
//    return 0;
//}
