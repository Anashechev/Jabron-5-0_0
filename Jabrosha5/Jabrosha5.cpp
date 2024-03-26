#include <iostream>
#include <iomanip>
#include <clocale>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    
    BankAccount(int accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
        interestRate = 0.0;
    }

    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Депозит в размере " << amount << " был успешно зачислен на счет." << endl;
        }
        else {
            cout << "Ошибка: Сумма депозита должна быть положительной." << endl;
        }
    }

    
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Снятие в размере " << amount << " было успешно выполнено." << endl;
        }
        else {
            cout << "Ошибка: Недостаточно средств на счете или некорректная сумма снятия." << endl;
        }
    }

    
    double getBalance() {
        return balance;
    }

    
    double getInterest() {
        double interest = balance * interestRate * (1.0 / 12.0);
        return interest;
    }

    
    void setInterestRate(double rate) {
        if (rate >= 0) {
            interestRate = rate;
        }
        else {
            cout << "Ошибка: Процентная ставка должна быть неотрицательной." << endl;
        }
    }

    
    int getAccountNumber() {
        return accountNumber;
    }

    
    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};


bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount > 0 && amount <= from.balance) {
        from.withdraw(amount);
        to.deposit(amount);
        return true;
    }
    else {
        cout << "Ошибка: Недостаточно средств на счете или некорректная сумма перевода." << endl;
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8"); 

    
    BankAccount account1(12345, 1000.0);
    BankAccount account2(67890, 500.0);

    
    account1.deposit(500.0);
    account2.withdraw(200.0);
    cout << "Баланс счета 1: " << account1.getBalance() << endl;
    cout << "Баланс счета 2: " << account2.getBalance() << endl;

    account1.setInterestRate(0.05); 
    cout << "Проценты на счете 1: " << fixed << setprecision(2) << account1.getInterest() << endl;

    
    if (transfer(account1, account2, 800.0)) {
        cout << "Перевод успешно выполнен." << endl;
    }

    cout << "Баланс счета 1: " << account1.getBalance() << endl;
    cout << "Баланс счета 2: " << account2.getBalance() << endl;

    return 0;
}