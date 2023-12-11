#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;


//функция поиска делителей числа
vector <int> findDivizors(int n) {
    vector <int> divizors;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            divizors.emplace_back(i);
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
string IsPrimeNumber(int n) {
    vector <int> divizors = findDivizors(n);
    if (divizors.size() == 2) {
        return "|Является простым";
    }
    else {
        return "|Не является простым";
    }
}

//проверка совершенных чисел
string isPerfectNumber(int n) {
    int sum = 0,i=0;
    if (n <= 0) {
        return "|Не является совершенным";
    }
    vector <int> divizors = findDivizors(n);
    while ( i < divizors.size()){
        if (i<=n){
            sum = sum+i;
            i++;
        }
    }

    /*for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }*/
    if (sum == n){
        return "|Является совершенным";
    }else{
        return "|Не является совершенным";
    }

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
        default:    cout << "op is undefined";
    }
}

/*void UnitTests() {
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
 */
class Numbers{
    public:
        int number;
        vector <int> divizors;
        string perfect,prime;
        void Print(){
            cout << "[Число: " << number << endl
            << perfect << endl
            << prime << endl
            << "----------------" << endl;
        }
};

map<int,vector <int>> user_numbers;
void isNumMap(int n) {
    if (user_numbers.find(n) == user_numbers.end()){
        user_numbers.emplace(n, (findDivizors(n)));
    };
};
int main() {
    int number = -1; char op; string calc_num1, calc_num2;
    while (number) {
        cout << "Меню: \n  \tКаклькулятор - '1'. \n \tПроверка 2 чисел НОД, НОК, простоту, совершенность - '2' \n Ввод: ";
        cin >> number;
        if (number == 2) {
            Numbers num1; Numbers num2;
            cout << "Калькулятор: \nВведите два числа через пробел: "; cin >> num1.number >> num2.number; cout << "----------------" << endl;
            isNumMap(num1.number);
            num1.perfect = isPerfectNumber(num1.number); num1.prime = IsPrimeNumber(num1.number);num1.Print();
            num2.perfect = isPerfectNumber(num2.number); num2.prime = IsPrimeNumber(num2.number);num2.Print();
            cout <<"|Наибольшее общий делитель: "<< lcm(num1.number,num2.number) << endl << "|Наименьшее общее кратное: "<< gcd(num1.number,num2.number) <<endl << "----------------" <<endl;
        }
        else if (number == 1) {
            cout << "Проверка: \nВведите первое число: "; cin >> calc_num1; cout << "Введите оператор(+/-): "; cin >> op; cout << "Введите второе число: "; cin >> calc_num2;cout << "Ответ: ";Calc(calc_num1, op, calc_num2);
        };
    } return 0;
}
