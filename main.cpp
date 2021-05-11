#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "account.h"
#include "render.h"
#include "function.h"
using namespace std;
vector<string> history;
vector<string> listData;
int denomination[] = {1000, 2000, 5000, 10000, 20000,
                      50000, 100000, 200000, 500000};
int bankMoney[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int main()
{
    // chạy atm
    function(listData, denomination, bankMoney, history);
}
