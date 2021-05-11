#include "account.h"
using namespace std;
void writeAccountCreate(const string &time, const string &id,
                        const string &pass, const vector<string> &history)
{
    remove("history.txt");
    ofstream file ("history.txt");
    for(int i = 0; i < history.size(); i++)
    {
        file << history[i] << endl;
    }
    file << "=======================" << endl;
    file << time;
    file << "Account has been created" << endl;
    file << "ID : " << id << endl;
    file << "Password : " << pass << endl;
}
void getListHistory(vector<string> &history)
{
    fstream file;
    file.open("history.txt");
    string s;
    getline(file, s);
    while (!file.eof())
    {
        getline(file, s);
        history.push_back(s);
    }
}
void updateListHistoryWithdrawalAndDeposit(const string &time, const string &id,
                                           const int &option, const long long &balance,
                                           const vector<string> &history)
{
    remove("history.txt");
    ofstream file ("history.txt");
    for(int i = 0; i < history.size(); i++)
    {
        file << history[i] << endl;
    }
    if (option == 1) // trường hợp nộp tiền
    {
        file << "=======================" << endl;
        file << time;
        file << "ID : " << id << endl;
        file << "Da nop : " << balance << endl;
    }
    else if (option == 2) // trường hợp rút tiền
    {
        file << "=======================" << endl;
        file << time;
        file << "ID : " << id << endl;
        file << "Da rut : " << balance << endl;
    }
}
string getTime()
{
    time_t now = time(0);
    string t = ctime(&now);
    return t;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    else if (b <= a)
        return b;
}
// lấy data khách hàng vào trong database
void getListData(vector<string> &listData, int &accountNumber)
{
    fstream file;
    file.open("dataBase.txt");
    string s;
    file >> accountNumber;
    getline(file, s);
    while (!file.eof())
    {
        getline(file, s);
        listData.push_back(s);
    }
}

// update lại data vào trong database
void updateListData(vector<string> &listData, int &accountNumber)
{
    remove("dataBase.txt");
    ofstream file("dataBase.txt");
    file << accountNumber << endl;
    for (int i = 0; i < accountNumber * 6; i++)
    {
        file << listData[i] << endl;
    }
}

// chuyển một số thành string
string convertNumber(int number)
{
    vector<int> split;
    int tempNumber = number;
    if (tempNumber == 0)
        return "0";
    else
    {
        while (tempNumber > 0)
        {
            split.push_back(tempNumber % 10);
            tempNumber /= 10;
        }
        string temp = "";
        for (int i = split.size() - 1; i >= 0; i--)
        {
            temp += char(split[i] + 48);
        }
        return temp;
    }
}

// chuyển từ một string số thành số
long long convertStringToNumber(const string &s)
{
    long long number = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (i != s.size() - 1)
        {
            number += int(s[i]) - 48;
            number *= 10;
        }
        else
        {
            number += int(s[i]) - 48;
        }
    }
    return number;
}

// so sánh 2 string xem có giống nhau không
bool compare2string(const string &a, const string &b)
{
    if (a.size() != b.size())
        return false;
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

// kiểm tra xem ID có tồn tại trong cơ sở dữ liệu không
bool checkIDAppear(const string &ID, vector<string> &listData)
{
    int n = listData.size();
    for (int i = 1; i < n; i += 6)
    {
        {
            if (compare2string(ID, listData[i]) == true)
                return true;
            else
                continue;
        }
    }
    return false;
}

long long getAddressCustomer(const string &ID, vector<string> &listData)
{
    int n = listData.size();
    for (int i = 1; i < n; i += 6)
    {

        if (compare2string(ID, listData[i]))
            return i;
    }
    return -1;
}

long long getCurrentBalance(const string &ID, vector<string> &listData)
{
    int CustomerAddress = getAddressCustomer(ID, listData);
    long long balance = convertStringToNumber(listData[CustomerAddress + 2]);
    return balance;
}

// kiểm tra xem password có nhập đúng hay không
bool checkPassword(const string &ID, const string &InputedPassword, vector<string> &listData)
{
    if (checkIDAppear(ID, listData))
    {
        int addressCustomerInDataBase = getAddressCustomer(ID, listData);
        if (compare2string(InputedPassword, listData[addressCustomerInDataBase + 1]) == false)
        {
            listData[addressCustomerInDataBase + 4] += 1;
            return false;
        }
        else
        {
            return true;
        }
    }
    else
        return false;
}

// kiểm tra xem tài khoản đã bị khoá chưa
bool checkCondition(const string &ID, vector<string> &listData)
{
    int addressCustomerInDataBase = getAddressCustomer(ID, listData);
    if (convertStringToNumber(listData[addressCustomerInDataBase + 4]) >= 6)
        return false;
    return true;
}

// lấy password của id trong database
string getCorrectPassword(const string &ID, vector<string> &listData)
{
    int addressCustomerInDataBase = getAddressCustomer(ID, listData);
    return listData[addressCustomerInDataBase + 1];
}

// lấy số lần nhập sai
int getWrongTime(const string &ID, vector<string> &listData)
{
    int addressCustomerInDataBase = getAddressCustomer(ID, listData);
    return convertStringToNumber(listData[addressCustomerInDataBase + 3]);
}

// cập nhật số lần điền sai mật khẩu
void updateWrongTime(const string &ID, vector<string> &listData, int &newWrongTime, int &accountNumber)
{
    int addressCustomerInDataBase = getAddressCustomer(ID, listData);
    listData[addressCustomerInDataBase + 3] = convertNumber(newWrongTime);
    updateListData(listData, accountNumber);
}

// thay đổi số dư vào trong cơ sở dữ liệu
void setBankBalance(vector<string> &listData, const string &ID, const long long &Balance)
{
    int addressCustomerInDataBase = getAddressCustomer(ID, listData);
    string StringBalance = convertNumber(Balance);
    listData[addressCustomerInDataBase + 2] = StringBalance;
}

void getBankMoney(int *bankMoney)
{
    fstream file("BankMoney.txt");
    for (int i = 0; i < 9; i++)
    {
        file >> bankMoney[i];
    }
}
void updateBankMoney(int *bankMoney)
{
    remove("BankMoney.txt");
    ofstream file("BankMoney.txt");
    for (int i = 0; i < 9; i++)
    {
        file << bankMoney[i] << endl;
    }
}

long long getMinimumWithdrawalValue(int *bankMoney, int *denomination)
{
    for (int i = 0; i < 9; i++)
    {
        if (bankMoney[i] >= 1)
        {
            return denomination[i];
        }
    }
    return 0;
}

long long getMaxinumWithdrawalValue(int *bankMoney, int *denomination)
{
    long long balance = 0;
    for (int i = 0; i < 9; i++)
    {
        balance += bankMoney[i] * denomination[i];
    }
    return balance;
}

bool checkRemainingMoney(int *bankMoney, int *denomination, long long &request)
{
    long long temp = request;
    for (int i = 8; i >= 0; i--)
    {
        int x = bankMoney[i];
        int y = min(x, temp / denomination[i]);
        temp -= y * denomination[i];
    }
    if (temp == 0)
        return true;
    return false;
}
// kiểm tra xem có thể rút số tiền đã yêu cầu không
bool avaiableToWithDrawal(int *bankMoney, int *denomination, long long &request)
{
    if (request % 1000 != 0)
        return false;
    if (request < getMinimumWithdrawalValue(bankMoney, denomination))
        return false;
    if (request > getMaxinumWithdrawalValue(bankMoney, denomination))
        return false;
    if (checkRemainingMoney(bankMoney, denomination, request) == false)
        return false;
    return true;
}
// update lại bank money sau khi rút tiền
void updateBankMoneyAfterWithDrawal(int *bankMoney, int *denomination, const long long &request)
{
    long long temp = request;
    for (int i = 8; i >= 0; i--)
    {
        int x = bankMoney[i];
        int y = min(x, temp / denomination[i]);
        bankMoney[i] -= y;
        temp -= y * denomination[i];
    }
}