//#include <iostream>
//#include "ClsBankClient.h"
//#include "ClsInputValidate.h"
//#include "clsUtil.h"
//
//using namespace std;
//
//void PrintClientRecordBalanceLine(BankClient Client)
//{
//
//    cout << "| " << setw(15) << left << Client.AccountNumber();
//    cout << "| " << setw(20) << left << Client.FullName();
//    cout << "| " << setw(12) << left << Client.AccountBalance();
//
//}
//
//void ShowTotalBalances()
//{
//    vector<BankClient> vClients = BankClient:: GetClientsList();
//    cout << "\n\t\t\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
//    cout << "\n______________________________________________________________________";
//    cout << "_________________________________________\n" << endl;
//    
//    cout << "| " << left << setw(15) << "Accout Number";
//    cout << "| " << left << setw(20) << "Client Name";
//    cout << "| " << left << setw(12) << "Balance";
//    
//    cout << "\n______________________________________________________________________";
//    cout << "_________________________________________\n" << endl;
//    
//    double TotalBalances = BankClient:: GetTotalBalances();
//    
//    if (vClients.size() == 0)
//        cout << "\t\t\t\tNo Clients Available In the System!";
//    else
//    {
//        for (BankClient Client : vClients)
//        {
//            PrintClientRecordBalanceLine(Client);
//            cout << endl;
//        }
//    }
//    
//    cout << "\n______________________________________________________________________";
//    cout << "_________________________________________\n" << endl;
//    
//    cout << "\n_______________________________________________________";
//       cout << "_________________________________________\n" << endl;
//       cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
//    cout << "\t\t  ( " << clsUtil::NumberToText(TotalBalances) << ")" << endl;
//}
//
//int main()
//{
//    ShowTotalBalances();
//    return 0;
//}
