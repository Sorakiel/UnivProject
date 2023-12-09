#include <cassert>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


//функция поиска делителей числа
vector <int> findDivizors(int n) {
    vector <int> divizors;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            divizors.push_back(i);
        }
    }
    return divizors;
}

//Нахождение НОД
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = abs(a % b);
        a = temp;
    }
    return a;
}

//нахождение наименьшего общего кратного
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

//проверка числа на простоту
bool IsPrimeNumber(int n) {
    vector <int> divizors = findDivizors(n);
    if (divizors.size() == 2) {
        return true;
    }
    else {
        return false;
    }
}

//проверка совершенных чисел
bool isPerfectNumber(int n) {
    if (n <= 0) {
        return false;
    }
    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum == n;
}
//Калькулятор
int typeChange(string digit) {
    return atoi(digit.c_str());
}

// Получает числитель и знаменатель
pair<int, int> decompos(string isnum) {
    string fraction[2];
    int pos = 0;

    for (int i = 0; i < isnum.length(); i++) {
        if (isnum[i] != '/') {
            fraction[pos] = fraction[pos] + isnum[i];
        } if (isnum[i] == '/') {
            pos++;
        }
    }
    return pair<int, int>(typeChange(fraction[0]), typeChange(fraction[1]));
}

pair<int,pair<char,int>> Calc(string num1, char op, string num2) {
    int num1Unfolded[2] = { decompos(num1).first, decompos(num1).second };
    int num2Unfolded[2] = { decompos(num2).first, decompos(num2).second };
    char slash = '/';
    int numer, denom;
    switch (op) {
    case '+':
        numer = num1Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num1Unfolded[1]) + num2Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num2Unfolded[1]);
        denom = lcm(num1Unfolded[1], num2Unfolded[1]);
        cout << numer << '/' << denom << endl;
        return {numer, {slash, denom}};
    case '-':
        numer = num1Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num1Unfolded[1]) - num2Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num2Unfolded[1]);
        denom = lcm(num1Unfolded[1], num2Unfolded[1]);
        cout << numer << '/' << denom << endl;
        return {numer, {slash, denom}};
    }
}

void UnitTests() {
    //Блок проверок на простоту
    assert(IsPrimeNumber(14) == false); //Не простое
    assert(IsPrimeNumber(11) == true); //Простое
    assert(IsPrimeNumber(0) == false); //Не простое
    assert(IsPrimeNumber(1) == false);// Не простое
    //Блок проверок на совершенность
    assert(isPerfectNumber(14) == false); //Не совершенное
    assert(isPerfectNumber(28) == true); //Cовершенное
    assert(isPerfectNumber(0) == false); // Не совершенное
    assert(isPerfectNumber(-4) == false); //Не совершенное
    //Проверка нахождения НОД
    assert(gcd(14, 28) == 14);
    assert(gcd(-231, -140) == 7);
    assert(gcd(0, 13) == 13);
    //Проверка нахождения НОК
    assert(lcm(14, 28) == 28);
    assert(lcm(-231, -140) == 4620);
    assert(lcm(0, 28) == 0);
    cout << "All tests OK" << endl;
    //Проверка калькулятора
    //assert(calc('1/2','+', '1/3')=='5/6');
}

int main() {
    UnitTests();
    int number;
    cout << "Каклькулятор - введите '1'.Проверка 2 чисел НОД, НОК, простоту, совершенность, введите '2'" << endl << "Ввод: ";cin >> number;
    if (number == 2) {
        int number1, number2;
        cout << "Введите 2 два числа через пробел: "; cin >> number1 >> number2;
        cout << "Число " << number1 << (IsPrimeNumber(number1) ? " является простым" : " НЕ является простым") << endl << "Число " << number2 << (IsPrimeNumber(number1) ? " является простым" : " НЕ является простым") << endl << "Число " << number1 << (isPerfectNumber(number1) ? " является совершенным" : " НЕ является совершенным") << endl << "Число " << number2 << (isPerfectNumber(number2) ? " является совершенным" : " НЕ является совершенным") << endl << "НОД: " << gcd(number1, number2) << ", НОК: " << lcm(number1, number2) << endl;
    }
    else if (number == 1) {
        string num1, num2;
        char op;
        cout << "Введите первое число: "; cin >> num1; cout << "Введите оператор(+/-): "; cin >> op; cout << "Введите второе число: "; cin >> num2;
        Calc(num1, op, num2);
    } return 0;
}