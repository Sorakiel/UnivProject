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
            sum = sum + i;
            i++;
        }
    }

    if (sum == n) {
        return "|Является совершенным";
    }
    else {
        return "|Не является совершенным";
    }

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
    return pair<int, int>(atoi(fraction[0].c_str()), atoi(fraction[1].c_str()));
}

//Калькулятор
pair<int, pair<char, int>> Calc(string num1, char op, string num2) {
    int num1Unfolded[2] = { decompos(num1).first, decompos(num1).second };
    int num2Unfolded[2] = { decompos(num2).first, decompos(num2).second };
    char slash = '/';
    int numer, denom;
    switch (op) {
        case '+':
            numer = num1Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num1Unfolded[1]) + num2Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num2Unfolded[1]);
            denom = lcm(num1Unfolded[1], num2Unfolded[1]);
            cout << numer << '/' << denom << endl;
            return { numer, {slash, denom} };
        case '-':
            numer = num1Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num1Unfolded[1]) - num2Unfolded[0] * (lcm(num1Unfolded[1], num2Unfolded[1]) / num2Unfolded[1]);
            denom = lcm(num1Unfolded[1], num2Unfolded[1]);
            cout << numer << '/' << denom << endl;
            return { numer, {slash, denom} };
        default:    cout << "op is undefined";
    }
}


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
    void Print() {
        cout << "[Число: " << number << endl
             << perfect << endl
             << prime << endl
             << "----------------" << endl;
    }
};

pair<pair<string, char>, string> decomposition_equation(string equation) {
    char op; string fraction_first = equation, fraction_second = equation;
    if (equation.find("+") < 1000) {
        op = '+';
        fraction_first = fraction_first.erase(fraction_first.find("+", 1), 80);
        fraction_second = fraction_second.erase(0, fraction_second.find('+', 1) + 1);
    }
    else if (equation.find("-") < 1000) {
        op = '-';
        fraction_first = fraction_first.erase(fraction_first.find("-", 1), 80);
        fraction_second = fraction_second.erase(0, fraction_second.find('-', 1) + 1);
    };
    return pair<pair<string, char>, string>{ {fraction_first, op}, fraction_second};
}



/*
struct isWhat {
    int a;
    vector <int> b;
    string c;
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

const vector <vector<int>> gcd_test = { {14, 28, 14}, {-231, -140, 7}, {0, 0, 0}, {0, 13, 13} };
const vector <vector<int>> lcm_test = { {14, 28, 14}, {0, 0, 0}, {-231, -140, 4620}, {0, 28, 0} };
const vector <vector<int>> findDivizors_test = { 25,{1, 5, 25} };
const vector <isWhat> IsPrimeNumber_test = { {14,{1,2,7,14}, "|Не является простым"}, {0,{}, "|Не является простым"}, {1,{1}, "|Не является простым"}, {11,{1,11}, "|Является простым"} };
const vector <isWhat> IsPerfectNumber_test = { {14,{1,2,7,14}, "|Не является совершенным"}, {28,{1,2,4,7,14,28},"|Является совершенным"}, {0,{},"|Не является совершенным"}, {-4,{1,2,4}, "|Не является совершенным"} };
const vector <FractionChange> decompos_test = { {"5/6", 5, 6}, {"1/2", 1, 2} };

 int Tests() {
    for (auto test : gcd_test) {
        assert(gcd(test[0], test[1]) == test[2]);
    }
    for (auto test : lcm_test) {
        assert(lcm(test[0], test[1]) == test[2]);
    }
    for (auto test : IsPrimeNumber_test) {
        assert(IsPrimeNumber(test.a, test.b) == test.c);
    }
    for (auto test : IsPerfectNumber_test) {
        assert(isPerfectNumber(test.a, test.b) == test.c);
    }
    return 0;
}
*/




void output() {
    string equation = "None";
    map<int, vector <int>> user_numbers;
    while (equation != "0") {
        cout << "Ввод: ";
        getline(cin, equation);
        if (equation.find("+", 1) > 100000 and equation.find("-", 1) > 100000) {

            Numbers num1; Numbers num2;
            cout << " Проверка: \n";
            num1.number = num1.solve(equation.substr(0, equation.find(" ") + 2));
            num2.number = num2.solve(equation.substr(equation.find(" ") + 1, 80));

            cout << "----------------" << endl;
            //isNumMap(num1.number);
            num1.features(user_numbers); num1.Print();
            num2.features(user_numbers); num2.Print();
            cout << "|Наименьшее общее кратное: " << lcm(num1.number, num2.number) << endl << "|Наименьший общий делитель:" << gcd(num1.number, num2.number) << endl << "----------------" << endl;
        }
        else if (equation.find("+", 1) < 1000 or equation.find("-", 1) > 0) {
            cout << "Калькулятор: \n Ответ: "; Calc(decomposition_equation(equation).first.first, decomposition_equation(equation).first.second, decomposition_equation(equation).second);
        }
    }
};
int main() {
    //Tests();
    output();
    return 0;
}