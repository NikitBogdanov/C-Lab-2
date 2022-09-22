#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Faction
{
    //Инкапсуляция
    private:
        int num_1 = 0;
        int num_2 = 0;
        static int counter; //Счётчик созданных объектов класса 
    public:
        Faction(int num1, int num2)
        {
            num_1 = num1;
            num_2 = num2;
            CounterUpdate();
        }
        static void CounterUpdate() // Функция для увеличения счетчика
        {
            counter++;
        }
        static int getCount() // Функция для возврата значения счётчика 
        {
            return counter;
        }
        static int gcd(int n, int m) //Функция нахождения наибольшего общего делителя
        {
            int min = n > m ? m : n;
            int temp_min = min;
            int max = n > m ? n : m;
            bool find_NOD = false;
            while (min > 1 && find_NOD == false)
            {
                if (max % min == 0 && temp_min % min == 0)
                {
                    find_NOD = true;
                    return min;
                }
                else
                {
                    min--;
                }
            }
        }
        void reduce() // Функция для сокращения дробей
        {
            int NOD = gcd(num_1, num_2);
            num_1 /= NOD;
            num_2 /= NOD;
        }
        //Перегрузка операторов
        Faction operator *(const Faction &f) 
        {
            CounterUpdate();
            return Faction(num_1 * f.num_1, num_2 * f.num_2);
        }
        Faction operator /(const Faction& f) 
        {
            CounterUpdate();
            return Faction(num_2 * f.num_1, num_1 * f.num_2);
        }
        Faction operator +(const Faction& f) 
        {
            CounterUpdate();
            int NOD = gcd(num_2, f.num_2);
            int temp_n2 = num_2;
            int temp_n1 = num_1;
            if (num_2 == f.num_2)
            {
                num_1 += f.num_1;
            }
            else
            {
                num_2 *= (f.num_2 / NOD);
                num_1 = (num_1 * (num_2 / temp_n2)) + (f.num_1 * (num_2 / f.num_2));
            }
            int temp2 = num_2;
            num_2 = temp_n2;
            temp_n2 = temp2;

            int temp1 = num_1;
            num_1 = temp_n1;
            temp_n1 = temp1;

            return Faction(temp_n1, temp_n2);
        }
        Faction operator -(const Faction& f) 
        {
            CounterUpdate();
            int temp_n1 = num_1;
            int temp_n2 = num_2;
            int NOD = gcd(num_2, f.num_2);
            if (num_2 == f.num_2)
            {
                num_1 -= f.num_1;
            }
            else
            {         
                num_2 *= (f.num_2 / NOD);
                num_1 = (num_1 * (num_2 / temp_n2)) - (f.num_1 * (num_2 / f.num_2));
            }
            int temp2 = num_2;
            num_2 = temp_n2;
            temp_n2 = temp2;

            int temp1 = num_1;
            num_1 = temp_n1;
            temp_n1 = temp1;

            return Faction(temp_n1, temp_n2);
        }
        //Функция для преобразования десятичной дроби (double) в обычную
        static void printAsFraction(double decimal_fraction)
        {
            int integer = (int)decimal_fraction;
            decimal_fraction -= (int)decimal_fraction;
            string temp = to_string(decimal_fraction);
            int colNumb = 0;
            string n = "";
            string m = "1";
            bool findDrod = false;
            for (int i = size(temp) - 1; i > - 1; i--)
            {
                if (findDrod == true)
                {
                    colNumb++;
                }
                else
                {
                    if (temp[i] != '0') { findDrod = true; colNumb++; }
                }
            }
            for (int i = 2; i < colNumb; i++)
            {
                n += temp[i];
                m += '0';
            }
            cout << "Целая часть: " << integer << "\tДробная часть: " << n << "/" << m << endl;
        }
        //Функция для преобразования десятичной дроби (char) в обычную
        static void printAsFraction(char* decimal_fraction)
        {
            double drob = atof(decimal_fraction); // Перевод из char в double
            printAsFraction(drob);
        }
        //Функция печати в консоль дроби
        void print()
        {
            cout << num_1 << "/" << num_2 << endl;
            cout << endl;
        }
};
int Faction::counter = 0; // Статический счётчик "counter"
int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    // Демонстрация работы класса
    cout << "Введите первую дробь: " << endl;
    cout << "Числитель: ";
    int n1;
    cin >> n1;
    cout << "Знаменатель: ";
    int m1;
    cin >> m1;
    cout << endl;
    cout << "Введите вторую дробь: " << endl;
    cout << "Числитель: ";
    int n2;
    cin >> n2;
    cout << "Знаменатель: ";
    int m2;
    cin >> m2;
    cout << endl;
    Faction f1(n1, m1);
    Faction f2(n2, m2);
    cout << "Введите десятичную дробь (пример: 0.01): ";
    cout << endl;
    double d;
    cin >> d;
    char drob[100];
    sprintf_s(drob, "%f", d);
    char* pdrod = drob;

    cout << "Умножение ";
    Faction f3 = f1 * f2;
    f3.print();
    cout << "Деление ";
    f3 = f1 / f2;
    f3.print();
    cout << "Сумма ";
    f3 = f1 + f2;
    f3.print();
    cout << "Разность ";
    f3 = f1 - f2; 
    f3.print();
    f1.printAsFraction(pdrod);
    cout << "Количество созданных дробей: " << Faction::getCount() << endl;
}
