#include <iostream>

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int acctNumber, double initialBalance) {
        this->accountNumber = acctNumber;
        this->balance = initialBalance;
        this->interestRate = 0.0;
    }

    void deposit(double amount) {
        if (amount > 0) {
            this->balance += amount;
            std::cout << "Внесено " << amount << " на аккаунт " << this->accountNumber << std::endl;
        }
        else {
            std::cerr << "АЩИБКА!" << std::endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && this->balance >= amount) {
            this->balance -= amount;
            std::cout << "Выведено " << amount << " с аккаунта " << this->accountNumber << std::endl;
            return true;
        }
        else {
            std::cerr << "АЩИБКА" << std::endl;
            return false;
        }
    }

    double getBalance() const {
        return this->balance;
    }

    double getInterest() const {
        return this->balance * this->interestRate / 12.0;
    }

    void setInterestRate(double rate) {
        this->interestRate = rate;
    }

    int getAccountNumber() const {
        return this->accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount) {
        if (from.withdraw(amount)) {
            to.deposit(amount);
            std::cout << "Успешно переведено из аккаунта " << from.getAccountNumber() << " на аккаунт " << to.getAccountNumber() << std::endl;
            return true;
        }
        else {
            std::cerr << "Неуспешный перевод с аккаунта " << from.getAccountNumber() << " на аккаунт " << to.getAccountNumber() << std::endl;
            return false;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    BankAccount acc1(1, 2500.0);
    BankAccount acc2(2, 500.0);

    acc1.deposit(200.0);
    acc1.setInterestRate(0.05); 

    std::cout << "Баланс на аккаунте " << acc1.getAccountNumber() << ": " << acc1.getBalance() << std::endl;

    transfer(acc1, acc2, 300.0);

    std::cout << "Баланс на аккаунте " << acc1.getAccountNumber() << ": " << acc1.getBalance() << std::endl;
    std::cout << "Баланс на аккаунте " << acc2.getAccountNumber() << ": " << acc2.getBalance() << std::endl;

    return 0;
}
