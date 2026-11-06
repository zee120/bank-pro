#pragma once
#include "ClsDate.h"
#include "Person.h"
#include "ClsString.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class BankClient : public person
{
private:
    enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
    enMode _mode;
    string _accountNumber;
    string _pinCode;
    float _accountBalance;
    bool _MarkForDelete = false;
    
    static BankClient ConvertLineToClientObject(string Line, string Delim = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::SplitInVector(Line, Delim);
        return BankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }
    
    static BankClient GetEmptyClientObject()
    {
        return BankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    
    static string _ConverClientObjectToLine(BankClient Client, string Seperator = "#//#")
    {
        string stClientRecord = "";
        stClientRecord += Client.FirstName() + Seperator;
        stClientRecord += Client.LastName() + Seperator;
        stClientRecord += Client.Email() + Seperator;
        stClientRecord += Client.Phone() + Seperator;
        stClientRecord += Client._accountNumber + Seperator;
        stClientRecord += Client._pinCode + Seperator;
        stClientRecord += to_string(Client._accountBalance);

        return stClientRecord;
    }
    
    static  vector <BankClient> _LoadClientsDataFromFile()
    {
        vector <BankClient> vClients;
        
        fstream MyFile;
        MyFile.open("data/Clients.txt", ios::in);//read Mode
        
        if (MyFile.is_open())
        {
            string Line;
            
            while (getline(MyFile, Line))
            {
                BankClient Client = ConvertLineToClientObject(Line);
                vClients.push_back(Client);
            }
            
            MyFile.close();
        }
        return vClients;
    }
    
    static void _SaveCleintsDataToFile(vector <BankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("data/Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {
            for (BankClient C : vClients)
            {
                if(C._MarkForDelete == false)
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }
    
    void _Update()
    {
        vector <BankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (BankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }

        _SaveCleintsDataToFile(_vClients);

    }
    
    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }
    
    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("data/Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }

    }
    
    string _PrepareTransferLogRecord(float Amount,BankClient DestinationClient,
                                         string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clssDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance()) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance()) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }
    
    void _RegisterTransferLog(float Amount, BankClient DestinationClient, string UserName)
    {
        string stDataLine = _PrepareTransferLogRecord( Amount,  DestinationClient, UserName);
        fstream MyFile;
        
        MyFile.open("data/TransfersLog.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    
    
public:
    BankClient(enMode Mode, string FirstName, string LastName,
               string Email, string Phone, string AccountNumber, string PinCode,
               float AccountBalance):
    person(FirstName, LastName, Email, Phone)
    {
        _mode = Mode;
        _accountNumber = AccountNumber;
        _pinCode = PinCode;
        _accountBalance = AccountBalance;
    }
    
    bool IsEmpty()
    {
        return (_mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _accountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _pinCode = PinCode;
    }

    string PinCode()
    {
        return _pinCode;
    }

    void SetAccountBalance(float AccountBalance)
    {
        _accountBalance = AccountBalance;
    }

    float AccountBalance()
    {
        return _accountBalance;
    }

    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName();
        cout << "\nLastName    : " << LastName();
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email();
        cout << "\nPhone       : " << Phone();
        cout << "\nAcc. Number : " << _accountNumber;
        cout << "\nPassword    : " << _pinCode;
        cout << "\nBalance     : " << _accountBalance;
        cout << "\n___________________\n";
    }
    
    static BankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open("data/Clients.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                BankClient Client = ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();

        }
        return GetEmptyClientObject();
    }
    
    static BankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("data/Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                BankClient Client = ConvertLineToClientObject(Line);
                if (Client._accountNumber == AccountNumber && Client._pinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();

        }
        return GetEmptyClientObject();
    }
    
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    
    enSaveResults Save()
    {
        switch (_mode)
        {
            case enMode::EmptyMode:
            {
                return enSaveResults::svFaildEmptyObject;
            }

            case enMode::UpdateMode:
            {
                _Update();
                return enSaveResults::svSucceeded;
                break;
            }
                
            case enMode::AddNewMode:
            {
                //This will add new record to file or database
                if (BankClient::IsClientExist(_accountNumber))
                {
                    return enSaveResults::svFaildAccountNumberExists;
                }
                else
                {
                    _AddNew();
                    //We need to set the mode to update after add new
                    _mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
                break;
            }
        }

    }

    static bool IsClientExist(string AccountNumber)
    {
        BankClient Client1 = BankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }
    
    
    static BankClient GetAddNewClientObject(string AccountNumber)
    {
           return BankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }
    
    
    static vector<BankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }
    
    static double GetTotalBalances()
    {
        double TotalBalances = 0;
        vector<BankClient>vClients = _LoadClientsDataFromFile();
        
        for(BankClient Client : vClients )
        {
            TotalBalances += Client.AccountBalance();
        }
        
        return TotalBalances;
    }
    
    
    void Deposit(double Amount)
    {
        _accountBalance += Amount;
        Save();
    }
    
    bool withdraw(double Amount)
    {
        if(Amount > _accountBalance)
        {
            return false;
        }
        else
        {
            _accountBalance -= Amount;
            Save();
            return true;
        }
    }
    
    bool Transfer(float Amount, BankClient &DestinationClient, string UserName)
    {
        if (Amount > AccountBalance())
        {
            return false;
        }
    
        withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);
        return true;
    }
    
    
    
    bool Delete()
       {
        vector<BankClient> Clients;
        Clients = _LoadClientsDataFromFile();
        
        for(BankClient &C : Clients)
        {
            if(C._accountNumber == _accountNumber)
            {
                C._MarkForDelete = true;
                break;
            }
        }
        
        _SaveCleintsDataToFile(Clients);
        *this = GetEmptyClientObject();
        return true;

       }
    
    struct stTransferLogRecord
    {
        string Date;
        string SenderAccountNumber;
        string ReceiverAccountNumber;
        float Amount;
        float ReceiverAccountBalance;
        float SenderAccountBalance;
        string UserName;
    };

    
    static stTransferLogRecord ConvertTrasferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTransferLogRecord Record;
        vector<string> TransferLogDataLine = clsString::SplitInVector(Line, Seperator);
        Record.Date = TransferLogDataLine[0];
        Record.SenderAccountNumber = TransferLogDataLine[1];
        Record.ReceiverAccountNumber = TransferLogDataLine[2];
        Record.Amount = stoi(TransferLogDataLine[3]);
        Record.ReceiverAccountBalance = stoi(TransferLogDataLine[4]);
        Record.SenderAccountBalance = stoi(TransferLogDataLine[5]);
        Record.UserName = TransferLogDataLine[6];
        
        return Record;
        
    }
    
    static vector<stTransferLogRecord> GetTransfersLogList()
    {
        vector<stTransferLogRecord> TransferLogList;
        
        fstream MyFile;
        MyFile.open("data/TransfersLog.txt", ios::in);
        
        if(MyFile.is_open())
        {
            string line;
            stTransferLogRecord Record;
            while(getline(MyFile, line))
            {
                Record = ConvertTrasferLogLineToRecord(line);
                TransferLogList.push_back(Record);
            }
            
            MyFile.close();
        }
        return TransferLogList;
    }
    
    
    

};


