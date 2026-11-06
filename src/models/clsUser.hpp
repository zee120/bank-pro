#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "ClsString.h"
#include <vector>
#include <fstream>
#include "ClsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public person
{
public:
    struct stLoginRegisterRecord;
    
private:
    enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 3};
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    
    
    bool _MarkForDelete = false;
    
    string _PrepareLogInRecord( string Seperator = "#//#")
        {
            string LoginRecord = "";
            LoginRecord += clssDate::GetSystemDateTimeString() + Seperator;
            LoginRecord += _UserName + Seperator;
        
            LoginRecord += to_string(_Permissions);
            return LoginRecord;
        }
   
    
    
    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;
        vector<string> LoginRegisterDataLine = clsString::SplitInVector(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Permission = stoi(LoginRegisterDataLine[2]);
        
        return LoginRegisterRecord;
        
    }
    
    
    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUsersData;
        vUsersData = clsString::SplitInVector(Line, Seperator);
        
        return clsUser(enMode::UpdateMode, vUsersData[0], vUsersData[1], vUsersData[2], vUsersData[3], vUsersData[4], clsUtil::DecryptText(vUsersData[5]), stoi(vUsersData[6]));
    }
    
    static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string Line = "";
        Line += User.FirstName() + Seperator;
        Line += User.LastName() + Seperator;
        Line += User.Email() + Seperator;
        Line += User.Phone() + Seperator;
        Line += User.UserName() + Seperator;
        Line += clsUtil:: EncryptText(User.Password()) + Seperator;
        Line += to_string(User.Permission());
        
        return Line;
    }
    
    static vector <clsUser> _LoadUsersDataFromFile()
    {
        vector <clsUser> vUsers;
        
        fstream MyFile;
        MyFile.open("data/Users.txt", ios::in);   //Read Mode
        
        if(MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }
        return vUsers;
    }
    
    
    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {
        fstream MyFile;
        MyFile.open("data/Users.txt", ios::out);   //Write Mode
        
        string Line = "";
        
        if(MyFile.is_open())
        {
            for(clsUser User : vUsers)
            {
                if(User._MarkForDelete == false)
                {
                    //we only write records that are not marked for delete
                    Line = _ConvertUserObjectToLine(User);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
        
    }
    
    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();
        for (clsUser& U : _vUsers)
        {
            if (U.UserName() == _UserName)
            {
                U = *this;
                break;
            }

        }
        _SaveUsersDataToFile(_vUsers);
    }
    
    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("data/Users.txt", ios::out | ios::app);
        
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }
    
    void _AddNew()
    {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }
    
    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    
public:
    
    enum enPermissions
    {
            eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
            pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 128
    };
    
    

    
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions) :
    person(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
        
    }
    
    
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    
    bool MarkedForDeleted()
    {
        return _MarkForDelete;
    }
    
    string UserName()
    {
        return _UserName;
    }
    void SerUserName(string UserName)
    {
        _UserName = UserName;
    }
    
    string Password()
    {
        return _Password;
    }
    
    void SetPassword(string Password)
    {
        _Password = Password;
    }
    
    int Permission()
    {
        return _Permissions;
    }
    
    void SetPermission(int Permission)
    {
        _Permissions = Permission;
    }
    
    
    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("data/Users.txt" , ios:: in);
        if(MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }
    
    static clsUser Find(string UserName, string Password)
        {

            fstream MyFile;
            MyFile.open("data/Users.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsUser User = _ConvertLinetoUserObject(Line);
                    if (User.UserName() == UserName && User.Password() == Password)
                    {
                        MyFile.close();
                        return User;
                    }

                }

                MyFile.close();

            }
            return _GetEmptyUserObject();
        }
    
        static bool IsUserExist(string UserName)
        {

            clsUser User = clsUser::Find(UserName);
            return (!User.IsEmpty());
        }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

       enSaveResults Save()
       {

           switch (_Mode)
           {
               case enMode::EmptyMode:
               {
                   if (IsEmpty())
                   {
                       return enSaveResults::svFaildEmptyObject;
                   }
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
                   if (clsUser::IsUserExist(_UserName))
                   {
                       return enSaveResults::svFaildUserExists;
                   }
                   else
                   {
                       _AddNew();
                       //We need to set the mode to update after add new
                       _Mode = enMode::UpdateMode;
                       return enSaveResults::svSucceeded;
                   }
                   break;
               }
           }

       }
    
    bool Delete()
    {
        vector<clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();
        
        if(_vUsers.size() > 0)
        {
            for(clsUser &_User : _vUsers)
            {
                if(_User._UserName == _UserName)
                {
                    _User._MarkForDelete = true;
                    break;
                }
            }
            
            _SaveUsersDataToFile(_vUsers);
            *this = _GetEmptyUserObject();
            return true;
        }
        
        return false;
    }

    
    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if(this -> Permission() == enPermissions:: eAll){
            return true;
        }
        
        if((Permission & this -> Permission()) == Permission){ //bitwise and operation
            return true;
        }
        return false;
    }
    
    void RegisterLogIn()
    {

        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("data/LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permission;
    };
    
    static vector<stLoginRegisterRecord> GetLogInRegisterList()
        {

        vector<stLoginRegisterRecord> vLoginRegisterRecords;
        
        fstream MyFile;
        MyFile.open("data/LoginRegister.txt", ios:: in);

        if (MyFile.is_open())
        {
            string Line;
            stLoginRegisterRecord LoginRegisterRecord;
            while(getline(MyFile, Line))
            {
                LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
                vLoginRegisterRecords.push_back(LoginRegisterRecord);
            }

            MyFile.close();
        }
        return vLoginRegisterRecords;

    }
};
