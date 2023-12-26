#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
//функция поиска делителей числа
map<int, vector <int>> findDivizors(int n, map<int, vector <int>>& user_numbers) {
    vector <int> divizors;
    if (user_numbers.find(n) == user_numbers.end()) {
        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                divizors.emplace_back(i);
            }
        }
        user_numbers[n] = divizors;
        return user_numbers;
    }else{
        return user_numbers;
    }
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
string IsPrimeNumber(int n, map<int, vector <int>>& user_numbers) {
    if (user_numbers[n].size() == 2) {
        return "|Является простым";
    }
    else {
        return "|Не является простым";
    }
}

//проверка совершенных чисел
string isPerfectNumber(int n, map<int, vector <int>>& user_numbers) {
    int sum = 0, i = 0;
    if (n <= 0) {
        return "|Не является совершенным";
    }
    while (i < user_numbers[n].size()) {
        if (i <= n) {
            sum = sum + user_numbers[n].at(i);
            i++;
        }
    }
    if (sum == 2*n) {
        return "|Является совершенным";
    }
    else {
        return "|Не является совершенным";
    }
}


//Перевод строки в числа и оператор
void decomposition_equation(string equation, map<int,int> &calc_nums,char &op) {
    string f_first = equation, f_second = equation;
    if (equation.find("+") < 1000) {
        op = '+';
        f_first = f_first.erase(f_first.find("+", 1), 80);
        f_second = f_second.erase(0, f_second.find('+', 1) + 2);
    }
    else if (equation.find("-") < 1000) {
        op = '-';
        f_first = f_first.erase(f_first.find("-", 1), 80);
        f_second = f_second.erase(0, f_second.find('-', 1) + 2);
    };
    calc_nums[0] = atoi(f_first.substr(0, equation.find("/")).c_str());
    calc_nums[1] = atoi(f_first.substr(equation.find("/") + 1, 80).c_str());
    calc_nums[2] = atoi(f_second.substr(0, equation.find("/")).c_str());
    calc_nums[3] = atoi(f_second.substr(equation.find("/") + 1, 80).c_str());
}

//Калькулятор
pair<int, int> Calc(string equation) {
    char op;
    map<int,int> calc_nums;
    decomposition_equation(equation,calc_nums,op);
    int num1Unfolded[2] = {calc_nums[0],calc_nums[1]};
    int num2Unfolded[2] = {calc_nums[2],calc_nums[3]};

    char slash = '/';
    int numer, denom;
    switch (op) {
        case '+':
            numer = num1Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num1Unfolded[1]) + num2Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num2Unfolded[1]);
            denom = lcm(num1Unfolded[1], num2Unfolded[1]);
            cout << numer << '/' << denom << endl;
            return { numer, denom};
        case '-':
            numer = num1Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num1Unfolded[1]) - num2Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num2Unfolded[1]);
            denom = lcm(num1Unfolded[1], num2Unfolded[1]);
            cout << numer << '/' << denom << endl;
            return { numer, denom};
        default:    cout << "op is undefined";
    }
}

//Класс хранящий число из строки и его свойства + функция вывода
class Numbers {
public:
    int number;
    string perfect, prime;
    int solve(string equation) {
        return atoi(equation.c_str());
    }
    void features(map<int, vector <int>>& user_numbers) {
        findDivizors(number,user_numbers);
        perfect = isPerfectNumber(number, user_numbers);
        prime = IsPrimeNumber(number, user_numbers);
    }
    void Print(map<int, vector <int>>& user_numbers) {
        features(user_numbers);
        cout << "[Число: " << number << endl
             << perfect << endl
             << prime << endl
             << "----------------" << endl;
    }
};

struct FeaturesCheck {
    int a;
    vector <int> b;
    string c;
};

struct CalcCheck {
    string a;
    pair<int, int> b;
};


struct FractionChange {
    string a;
    int b;
    int c;
};
struct StringToNum {
    string a;
    int b;
};


const vector <vector<int>> gcd_test = { {14, 28, 14}, {-231, -140, 7}, {-135, 0, -135}, {0, 13, 13} };
const vector <vector<int>> lcm_test = { {14, 28, 28}, {-231, -140, 4620}, {-135, 0, 0}, {0, 13, 0} };
const vector <CalcCheck> calc_test = {{"1/2 + 1/2",{2,2}}};
const vector <FeaturesCheck> IsPrimeNumber_test = { {14,{1,2,7,14}, "|Не является простым"}, {0,{}, "|Не является простым"}, {1,{1}, "|Не является простым"}, {11,{1,11}, "|Является простым"} };
const vector <FeaturesCheck> IsPerfectNumber_test = { {14,{1,2,7,14}, "|Не является совершенным"}, {28,{1,2,4,7,14,28},"|Является совершенным"}, {0,{},"|Не является совершенным"}, {-4,{1,2,4}, "|Не является совершенным"} };


void Tests(map<int, vector <int>>& user_numbers) {
    for (auto test : gcd_test) {
        assert(gcd(test[0], test[1]) == test[2]);
    }
    for (auto test : lcm_test) {
        assert(lcm(test[0], test[1]) == test[2]);
    }
    for (auto test : calc_test) {
        assert(Calc(test.a) == test.b);
    }
    for (auto test : IsPrimeNumber_test) {
        user_numbers[test.a] = test.b;
        assert(IsPrimeNumber(test.a, user_numbers) == test.c);
    }
    for (auto test : IsPerfectNumber_test) {
        user_numbers[test.a] = test.b;
        assert(isPerfectNumber(test.a, user_numbers) == test.c);
    }
}




//Вывод программы
void output() {
    string equation = "None"; map<int, vector <int>> user_numbers;
    Tests(user_numbers);
    while (equation != "0") {
        cout << "Ввод: ";
        getline(cin, equation);
        if (equation.find("+", 1) > 100000 and equation.find("-", 1) > 100000) {
            Numbers first_number; Numbers second_number;
            cout << " Проверка: \n";
            first_number.number = first_number.solve(equation.substr(0, equation.find(" ") + 2));
            second_number.number = second_number.solve(equation.substr(equation.find(" ") + 1, 80));
            cout << "----------------" << endl;
            first_number.Print(user_numbers);
            second_number.Print(user_numbers);
            cout << "|Наименьшее общее кратное: " << lcm(first_number.number, second_number.number) << endl << "|Наибольший общий делитель:" << gcd(first_number.number, second_number.number) << endl << "----------------" << endl;
        }
        else if (equation.find("+", 1) < 1000 or equation.find("-", 1) > 0) {
            cout << "Калькулятор: \n Ответ: "; Calc(equation);
        }
    }
};
int main() {
    output();
    return 0;
}