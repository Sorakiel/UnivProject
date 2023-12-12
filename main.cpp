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


class Numbers{
public:
    int number;
    vector <int> divizors;
    string perfect,prime;
    int solve(string equation){
            return atoi(equation.c_str());
    }
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


pair<pair<string,char>,string> decomposition_equation(string equation){
    char op;string fraction_first = equation,fraction_second = equation;
    if (equation.find("+")<1000){
        op = '+';
        fraction_first = fraction_first.erase(fraction_first.find("+"),80);
        fraction_second = fraction_second.erase(0,fraction_second.find('+')+1);
    }else if(equation.find("-")<1000){
        op = '-';
        fraction_first = fraction_first.erase(fraction_first.find("-"),80);
        fraction_second = fraction_second.erase(0,fraction_second.find('-')+1);
    };


    return pair<pair<string,char>,string>{{fraction_first,op},fraction_second};
}

void output(){
    string equation = "None";
    while (equation != "0") {
        cout << "Ввод: ";
        cin >> equation;
        if (equation.find("+",1) > 100000 and equation.find("-",1) > 100000) {
            Numbers num1; Numbers num2;
            cout << " Проверка: \n"; num1.number = num1.solve(equation.substr(equation.find(",")+1,80)) ; num2.number = num2.solve(equation.substr(0,equation.find(",")+2)); cout << "----------------" << endl;
            isNumMap(num1.number);
            num1.perfect = isPerfectNumber(num1.number); num1.prime = IsPrimeNumber(num1.number);num1.Print();
            num2.perfect = isPerfectNumber(num2.number); num2.prime = IsPrimeNumber(num2.number);num2.Print();
            cout <<"|Наименьшее общее кратное: "<< lcm(num1.number,num2.number) << endl << "|Наибольшее общий делитель:"<< gcd(num1.number,num2.number) <<endl << "----------------" <<endl;
        }
        else if (equation.find("+",1) < 1000 or equation.find("-",1) > 0) {
            cout << "Калькулятор: \n Ответ: ";Calc(decomposition_equation(equation).first.first, decomposition_equation(equation).first.second, decomposition_equation(equation).second);
        }
    }
};
int main() {
    output();
    return 0;
}