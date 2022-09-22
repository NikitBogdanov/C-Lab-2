#include <iostream>

using namespace std;

class Vector
{
    private:
        int* array;
        int size = 0;
    public:
        int& operator[](int index)
        {
            this->size = index;
            return array[index];
        }
        Vector(const int index)
        {
            size = index;
            array = new int[index]; //{1, 1, 1, 9, 9, 9};
        }
        ~Vector()
        {
            delete[] array;
        }
        Vector& operator ++()
        {
            for (int i = 0; i < size; i++)
            {
                this->array[i]++;
            }
            return *this;
        }
        Vector& operator --()
        {
            for (int i = 0; i < size; i++)
            {
                this->array[i]--;
            }
            return *this;
        }
        Vector& operator ++(int)
        {
            for (int i = 0; i < size; i++)
            {
                this->array[i]++;
            }
            return *this;
        }
        Vector& operator --(int)
        {
            for (int i = 0; i < size; i++)
            {
                this->array[i]--;
            }
            return *this;
        }
};

class Matrix
{
    private:
        int** array;
        int Rows = 0;
        int Columns = 0;
    public:
        //Конструктор для инициализации массива
        Matrix(const int rows, const int columns)
        {
            array = new int* [rows, columns];
            for (int i = 0; i < rows; i++)
            {
                array[i] = new int[columns];
            }
        }
        //Деструктор для очистки памяти
        ~Matrix()
        {
            delete[] array;
        } 
        //Перегрузка операторов инкремента и декремента 
        //как префиксного так и постфиксного
        Matrix& operator ++()
        {
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns; i++)
                {
                    this->array[i, j]++;
                }
            }
            return *this;
        }
        Matrix& operator --()
        {
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns; i++)
                {
                    this->array[i, j]--;
                }
            }
            return *this;
        }
        Matrix& operator ++(int)
        {
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns; i++)
                {
                    this->array[i, j]++;
                }
            }
            return *this;
        }
        Matrix& operator --(int)
        {
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns; i++)
                {
                    this->array[i, j]--;
                }
            }
            return *this;
        }
        //Возврат элемента массива по индексам
        double at(int i, int j)
        {
            int temp = *(*(array + i) + j);
            return temp;
        }
        //Добавление значения элементу массива по индексам
        void setAt(int i, int j, int val)
        {
            *(*(array + i) + j) = val;
        }
};

//Функция расчёта факториала
int getFactorial(int value, int sumij, int NumberOfRevolutions)
{
    if (sumij == 0)
    {
        return 1;
    }
    else if (NumberOfRevolutions >= sumij)
    {
        return value;
    }
    else
    {
        value *= (sumij - NumberOfRevolutions);
        NumberOfRevolutions++;
        getFactorial(value, sumij, NumberOfRevolutions);
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    //Размер двумерного массива
    int row = 5;
    int col = 5;
    int evenNumbered = 0; //Переменная для расчёта количества нечётных строк
    Matrix newMatrix(row, col);
    cout << endl;
    //Цикл для заполнения и вывода матрицы
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            newMatrix.setAt(i, j, getFactorial(1, i + j, 0));
            cout << newMatrix.at(i, j) << " ";
            evenNumbered == i % 2 == 0 ? evenNumbered : evenNumbered++;
        }
        cout << endl;
    }
    evenNumbered++;
    int vectorSize = col * evenNumbered;
    int index = 0;
    Vector newVector(col * evenNumbered);
    cout << endl;
    //Цикл для заполнения и вывода вектора
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if ((i + 1) % 2 != 0)
            {
                newVector[index] = newMatrix.at(i, j);
                cout << newVector[index] << " ";
                index++;
            }
        }
    }
    cout << endl;
}

