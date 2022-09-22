#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

using namespace std;

class Shop
{
    //Инкапсуляция
    private:
        int Months;
        string Name;
        string Address;
        int yearFoundation;
        int Number;
        int* totalProfit;
    public:
        string path = "C:/Users/intre/source/repos/Lab2C++/Number3/info.txt"; //Путь по умолчанию
        //Конструкторы
        Shop() {    }
        Shop(string _name, string _address, int _yearFoundation, int _number, int *_totalProfit, int _months)
        {
            Name = _name;
            Address = _address;
            yearFoundation = _yearFoundation;
            Number = _number;
            Months = _months;
            totalProfit = new int[Months];
            for (int i = 0; i < _months; i++)
            {
                totalProfit[i] = _totalProfit[i];
            }
        }
        void setInfo(string _name, string _address, int _yearFoundation, int _number, int *_totalProfit)
        {
            Name = _name;
            Address = _address;
            yearFoundation = _yearFoundation;
            Number = _number;
            for (int i = 0; i < 3; i++)
            {
                totalProfit[i] = _totalProfit[i];
            }
        }
        //Сеттеры
        string getName() { return Name; }
        string getAddress() { return Address; }
        int getNumber() { return Number; }
        int getYear() { return yearFoundation; }
        int getMonths() { return Months; }
        int *getProfit() { return totalProfit; }
        void Print(Shop shop) //Вывод в консоль информации о магазине
        {
            cout << endl;
            cout << "Имя: " << shop.getName() << " Адрес: " << shop.getAddress() << " Год основания: " << shop.getYear() << " Номер: " << shop.getNumber() << " Брибыль: " << shop.TotalProfit();
        }
        int TotalProfit() //Расчёт общей прибыли
        {
            int ansver = 0;
            for (int i = 0; i < Months; i++)
            {
                ansver += totalProfit[i];
            }
            return ansver;
        }
        int AverageProfit() //Расчёт средней прибыли
        {
            int* difference = new int[Months - 1];
            for (int i = 0, j = 1; j < Months; i++, j++)
            {
                difference[i] = totalProfit[j] - totalProfit[i];
            }
            int ansver = 0;
            for (int i = 0; i < Months - 1; i++)
            {
                ansver += difference[i];
            }
            ansver /= (Months - 1);
            return ansver;
        }
        void serialize()//ЧЗапись в файл по умолчанию
        {
            ofstream ofs;
            ofs.open(path, ofstream::in);
            if (ofs.is_open())
            {
                ofs.write((char*)&(*this), sizeof(Shop));
            }
            else
            {
                cout << "Ошибка!!!" << endl;
            }
            ofs.close();
        }
        void deserialize()//Чтение из файла по умолчанию
        {
            ifstream ifs;
            ifs.open(path);
            if (ifs.is_open())
            {
                ifs.read((char*)&(*this), sizeof(Shop));
                (*this).Print(*this);
            }
            else
            {
                cout << "Ошибка!!!" << endl;
            }
            ifs.close();
        }
        void serialize(const std::string& filename)//Запись в файл, указанный пользователем
        {
            string newPath = "C:/Users/intre/source/repos/Lab2C++/Number3/" + filename;
            ofstream ofs;
            ofs.open(newPath, ofstream::in);
            if (ofs.is_open())
            {
                ofs.write((char*)&(*this), sizeof(Shop));
            }
            else
            {
                cout << "Ошибка!!!" << endl;
            }
            ofs.close();
        }
        void deserialize(const std::string& filename) //Чтение из файла, указанного пользователем
        {
            string newPath = "C:/Users/intre/source/repos/Lab2C++/Number3/" + filename;
            ifstream ifs;
            ifs.open(newPath);
            if (ifs.is_open())
            {
                Shop shop = *this;
                while (ifs.read((char*)&shop, sizeof(Shop)));
                {
                    shop.Print(shop);
                }
            }
            else
            {
                cout << "Ошибка!!!" << endl;
            }
            ifs.close();
        }
};
//Функция расчета и вывода рейтинга магазинов по общему количеству прибыли
void ratingTotalProfitSort(Shop a, Shop b, Shop c)
{
    cout << "Рейтинг магазинов по их общей прибыли за все месяцы: " << endl;
    Shop max = a;
    Shop min = a;
    Shop ave = a;
    if (a.TotalProfit() > b.TotalProfit() && a.TotalProfit() > c.TotalProfit())
    {
        max = a;
        if (b.TotalProfit() > c.TotalProfit())
        {
            ave = b;
            min = c;
        }
        else
        {
            ave = c;
            min = b;
        }
    }
    if (a.TotalProfit() < b.TotalProfit() && a.TotalProfit() < c.TotalProfit())
    {
        min = a;
        if (b.TotalProfit() > c.TotalProfit())
        {
            max = b;
            ave = c;
        }
        else
        {
            max = c;
            ave = b;
        }
    }
    cout << "Название: " << max.getName() << "\tОбщая прибыль: " << max.TotalProfit() << endl;
    cout << "Название: " << ave.getName() << "\t\tОбщая прибыль: " << ave.TotalProfit() << endl;
    cout << "Название: " << min.getName() << "\t\tОбщая прибыль: " << min.TotalProfit() << endl;
    cout << endl;
}
//Функция расчета и вывода рейтинга магазинов по стреднему приросту прибыли
void ratingAverageProfitSort(Shop a, Shop b, Shop c)
{
    cout << "Рейтинг магазинов по их среднему приросту прибыли за все месяцы: " << endl;
    Shop max = a;
    Shop min = a;
    Shop avar = a;
    if (a.AverageProfit() > b.AverageProfit() && a.AverageProfit() > c.AverageProfit())
    {
        max = a;
        if (b.AverageProfit() > c.AverageProfit())
        {
            avar = b;
            min = c;
        }
        else
        {
            avar = c;
            min = b;
        }
    }
    if (a.AverageProfit() < b.AverageProfit() && a.AverageProfit() < c.AverageProfit())
    {
        min = a;
        if (b.AverageProfit() > c.AverageProfit())
        {
            max = b;
            avar = c;
        }
        else
        {
            max = c;
            avar = b;
        }
    }
    cout << "Название: " << max.getName() << "\tСредний прирост прибыли: " << max.AverageProfit() << endl;
    cout << "Название: " << avar.getName() << "\t\tСредний прирост прибыли: " << avar.AverageProfit() << endl;
    cout << "Название: " << min.getName() << "\t\tСредний прирост прибыли: " << min.AverageProfit() << endl;
    cout << endl;
}

//В главной функции демонстрируется работа класса на примерах
int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    //Создание массивов с данными о прибыли за каждый из 3-х месяцев
    int array1[3] = { 250, 210, 230 };
    int array2[3] = { 300, 240, 430 };
    int array3[3] = { 145, 525, 530 };
    //Создание объектов класса в стеке и куче
    Shop a("ATB", "Московская, 1, Макеевка", 2010, 246, array1, 3);
    Shop* b = new Shop("MMC", "Донецкая, 48, Макеевка", 2009, 146, array2, 3);
    Shop* c = new Shop("Eterna", "Магистральная, 4, 101 офис, Макеевка", 2015, 636, array3, 3);
    ratingAverageProfitSort(a, *b, *c);
    ratingTotalProfitSort(a, *b, *c);
    a.serialize(); //Запись в файл по умолчанию
    Shop a1;
    Shop b1 = *b;
    b1.serialize("myNameFile.txt"); //Запись в файл указанный пользователем
    a.deserialize("myNameFile.txt");//Чтение из файла указанного пользователем
    a1.deserialize(); //Чтение из файла по умолчанию
}
