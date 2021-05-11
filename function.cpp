#include "function.h"

using namespace std;

// start ATM Simulation
void function(vector<string> &listData, int *denomination, int *bankMoney, vector<string> &history)
{
    bool running = true;
    while (running)
    {
        int accountNumber = 0;
        char defaultSelection = '0';
        char choose;
        Render(defaultSelection);
        cout << "Lua chon cua ban la: \n";
        fflush(stdin);
        cin >> choose;
        cin.ignore();
        if (choose == '1')
        {
            system("cls");
            Render('1');
            int select = 1;
            if (select == 1)
            {
                string id, password;
                getListData(listData, accountNumber);
                cout << "Nhap id" << endl;
                getline(cin, id);
                if (checkIDAppear(id, listData) == false)
                {
                    cout << "Tai khoan khong ton tai! \n";
                    cout << "1. Thoat \n";
                    while (true)
                    {
                        int exitSelection;
                        cin >> exitSelection;
                        if (exitSelection == 1)
                        {
                            cout << "Dang thoat ...";
                            Sleep(1500);
                            system("cls");
                            break;
                        }
                        else
                        {
                            cout << "Dang thoat ...";
                            Sleep(1500);
                            system("cls");
                            break;
                        }
                    }
                }
                else
                {
                    while (true)
                    {
                        cout << "Vui long nhap pass: \n";
                        fflush(stdin);
                        getline(cin, password);
                        getListData(listData, accountNumber);
                        int wrongTime = getWrongTime(id, listData);
                        string correctPassword = getCorrectPassword(id, listData);

                        if (wrongTime >= 5)
                        {
                            cout << "Tai khoan cua ban da bi khoa! ";
                            Sleep(3000);
                            break;
                        }

                        // trường hợp nhập sai pass
                        if (compare2string(password, correctPassword) == false)
                        {
                            if (wrongTime < 5)
                            /* kiểm tra xem tài khoản có bị khoá không,
                        nếu chưa bị khoá thì tăng số lần sai */
                            {
                                cout << "Ban da nhap sai mat khau: " << endl;
                                wrongTime++;
                                updateWrongTime(id, listData, wrongTime, accountNumber);
                                updateListData(listData, accountNumber);
                                // wrongTime++;
                                cout << "Ban da nhap sai " << wrongTime << " lan" << endl;
                                cout << "Ban con lai " << 5 - wrongTime << " lan nhap sai" << endl;
                                // getListData(listData);
                            }
                            else // điều kiện tài khoản đã bị khoá
                            {
                                cout << "Tai khoan ban da bi khoa! \n";
                                cout << "ATM se thoat ve man hinh chinh... \n";
                                Sleep(2000);
                                system("cls");
                                
                                break;
                            }
                        }

                        else if (compare2string(password, correctPassword) == true) // điều kiện nhập đúng pass
                        {
                            wrongTime = 0;
                            updateWrongTime(id, listData, wrongTime, accountNumber);
                            updateListData(listData, accountNumber);
                            // getListData(listData);
                            cout << "Ban da nhap dung pass" << endl;
                            cout << "Vui long doi..." << endl;
                            Sleep(1500);
                            choose = '3';
                            Render(choose);
                            char selectFunction;
                            cin >> selectFunction;

                            // function nop tien
                            if (selectFunction == '1')
                            {
                                getBankMoney(bankMoney);
                                int money[9];
                                long long IdBalance = 0;
                                for (int i = 0; i < 9; i++)
                                {
                                    cout << denomination[i] << ": \n";
                                    cin >> money[i];
                                    bankMoney[i] += money[i];
                                    cout << denomination[i] * money[i] << endl;
                                    IdBalance += denomination[i] * money[i];
                                    system("cls");
                                    Render('4');
                                }
                                cout << "Ban da nop tien thanh cong ";
                                cout << IdBalance << " !" << endl;
                                getAddressCustomer(id, listData);
                                long long Balance = getCurrentBalance(id, listData);
                                Balance += IdBalance;
                                setBankBalance(listData, id, Balance);
                                updateListData(listData, accountNumber);
                                updateBankMoney(bankMoney);
                                string time = getTime();
                                getListHistory(history);
                                updateListHistoryWithdrawalAndDeposit(time, id, 1, IdBalance, history);
                                cout << "Dang thoat... \n";
                                Sleep(1500);
                                break;
                            }

                            // function rut tien
                            if (selectFunction == '2')
                            {
                                long long balance = getCurrentBalance(id, listData);
                                getBankMoney(bankMoney);
                                Render('5');
                                cout << "So tien toi thieu co the rut la: "
                                     << getMinimumWithdrawalValue(bankMoney, denomination) << endl;
                                cout << "So tien toi da co the rut la: "
                                     << getMaxinumWithdrawalValue(bankMoney, denomination) << endl;
                                cout << "So du kha dung: " << balance << endl;
                                long long request = 0;
                                cout << "Vui long nhap so tien can rut: ";
                                cin >> request;
                                if (avaiableToWithDrawal(bankMoney, denomination, request) == false)
                                {
                                    cout << "So tien khong hop le. " << endl;
                                    cout << "Nhap ki tu bat ki " << endl;
                                    char exit;
                                    cin >> exit;
                                    system("cls");
                                    break;
                                }
                                else
                                {
                                    Render('5');
                                    balance -= request;
                                    cout << "Ban da rut thanh cong " << request << endl;
                                    updateBankMoneyAfterWithDrawal(bankMoney, denomination, request);
                                    updateBankMoney(bankMoney);
                                    setBankBalance(listData, id, balance);
                                    updateListData(listData, accountNumber);
                                    string time = getTime();
                                    getListHistory(history);
                                    updateListHistoryWithdrawalAndDeposit(time, id, 2, request, history);
                                    break;
                                }
                            }
                            if (selectFunction == '3')
                            {
                                cout << "Dang thoat... " << endl;
                                Sleep(1500);
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (choose == '2')
        {
            getListData(listData, accountNumber);
            Render('6');
            string name, id, pass;
            long long balance = 0;
            int wrongTime = 0;
            cout << "Vui long nhap ten : ";
            getline(cin, name);
            cout << "Vui long nhap id : ";
            getline(cin, id);
            while (checkIDAppear(id, listData))
            {
                cout << "Vui long chon id khac : ";
                getline(cin, id);
            }
            cout << "Vui long nhap pass: ";
            getline(cin, pass);
            accountNumber++;
            listData.push_back(name);
            listData.push_back(id);
            listData.push_back(pass);
            listData.push_back("0");
            listData.push_back("0");
            updateListData(listData, accountNumber);
            vector<string> tempHistory;
            string time = getTime();
            getListHistory(history);
            writeAccountCreate(time, id, pass, history);
            break;
        }
        if (choose == '3')
            running = false;
        if (choose != '1' && choose != '2' && choose != '3')
        {
            system("cls");
            Render(defaultSelection);
            cout << "Vui long chon lai " << endl;
        }
    }
}
