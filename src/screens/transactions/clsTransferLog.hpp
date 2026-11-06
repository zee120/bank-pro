#pragma once
#include<iostream>
#include "clsScreen.h"
#include<string>
#include <iomanip>
#include "ClsBankClient.h"
#include "ClsInputValidate.h"
#include "clsUtil.h"

class clsTrasferLog : protected clsScreen
{
private:
    static void _PrintTransferLogRecord(BankClient::stTransferLogRecord TransferLogRecord)
    {
        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.Date;
               cout << "| " << setw(8) << left << TransferLogRecord.SenderAccountNumber;
               cout << "| " << setw(8) << left << TransferLogRecord.ReceiverAccountNumber;
               cout << "| " << setw(8) << left << TransferLogRecord.Amount;
               cout << "| " << setw(10) << left << TransferLogRecord.ReceiverAccountBalance;
               cout << "| " << setw(10) << left << TransferLogRecord.SenderAccountBalance;
               cout << "| " << setw(8) << left << TransferLogRecord.UserName;
    }
    
public:

    static void ShowTransferLogScreen()
    {


        vector <BankClient::stTransferLogRecord> vTransferLogRecord = BankClient::GetTransfersLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (BankClient::stTransferLogRecord Record : vTransferLogRecord)
            {

                _PrintTransferLogRecord(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};
