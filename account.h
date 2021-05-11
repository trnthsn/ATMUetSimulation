#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include "render.h"
using namespace std;
void writeAccountCreate(const string &time, const string &id,
                        const string &pass, const vector<string> &history);
void getListHistory(vector<string> &history);
void updateListHistoryWithdrawalAndDeposit(const string &time, const string &id,
                                           const int &option, const long long &balance,
                                           const vector<string> &history);
string getTime();
int min(int a, int b);
void getListData(vector<string> &listData, int &accountNumber);
void updateListData(vector<string> &listData, int &accountNumber);
string convertNumber(int number);
long long convertStringToNumber(const string &s);
bool compare2string(const string &a, const string &b);
bool checkIDAppear(const string &ID, vector<string> &listData);
long long getAddressCustomer(const string &ID, vector<string> &listData);
long long getCurrentBalance(const string &ID, vector<string> &listData);
bool checkPassword(const string &ID, const string &InputedPassword, vector<string> &listData);
bool checkCondition(const string &ID, vector<string> &listData);
string getCorrectPassword(const string &ID, vector<string> &listData);
int getWrongTime(const string &ID, vector<string> &listData);
void updateWrongTime(const string &ID, vector<string> &listData, int &newWrongTime, int &accountNumber);
void setBankBalance(vector<string> &listData, const string &ID, const long long &Balance);
void getBankMoney(int *bankMoney);
void updateBankMoney(int *bankMoney);
long long getMinimumWithdrawalValue(int *bankMoney, int *denomination);
long long getMaxinumWithdrawalValue(int *bankMoney, int *denomination);
bool checkRemainingMoney(int *bankMoney, int *denomination, long long &request);
bool avaiableToWithDrawal(int *bankMoney, int *denomination, long long &request);
void updateBankMoneyAfterWithDrawal(int *bankMoney, int *denomination,const long long &request);
#endif // ACCOUNT_H
