/*Создать шаблонный класс Array3d<> который хранит одномерный массив, 
но выдает наружу его как трехмерные. 
Переопределить операторы индексации [][][], <<
Сделать методы:
GetValue0(int i) ->[][] 
GeValue1(int j) ->[][]  
GetValues2(int k) -> [][]
GetValues0_1(int i, int j) -> []
GetValues0_2(int i, int k) ->[]
GetValues1_2(in j, int k) -> []
и аналогичные методы для SetValues.
Сделать статический метод CreateFill для создания массива и присваивания 
всех элементов одному значению*/

#include<iostream>
#include<vector>
using namespace std;

template<class T, int x, int y, int z> // шаблон задает размерность массива (x, y, z)

// класс трехмерного массива
class Array3d
{
private:
    vector<T> m_v; //вектор
    int m_size = x * y * z; //размер массива

public:
    //объект класса конструируется с помощью вектора
    Array3d(vector<T> vec)
    {
        if ((x <= 0) or (y <= 0) or (z <= 0))
        {
            cout << "Vector doesn't exist :(" << endl; //массив не существует
            exit(2);
        }
        //заполняем вектор нулями
        while (m_size != 0)
        {
            m_v.push_back(0);
            m_size--;
        }
    }

    //геттер
    T Getter(int i, int j, int k)
    {return m_v[i * y * z + j * z + k];} //получение элемента массива по 3 индексам

    //сеттер
    void Setter(int i, int j, int k, T el)
    {m_v[i * y * z + j * z + k] = el;} //задание элемента массива по 3 индексам

    friend ostream& operator << (ostream& outp, const Array3d& arr) //оператор для удобства вывода массива
    {
        for (int i = 0; i < x; i++) //3 подмассива по x
        {
            outp << "SUBARRAY " << i << ":" << endl;
            for (int j = 0; j < y; j++)
            {
                for (int k = 0; k < z; k++)
                {
                    outp << arr.m_v[i * y * z + j * z + k] << " "; 
                }
                outp << endl;
            }
        }
        return outp;
    }

    //геттеры для получения вектора 
    vector<vector<T>> GetValues0(int i) //получение вектора векторов из элементов по x
    {
        vector<vector<T>> result(y, vector<T>(z));
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
            {
                result[j][k] = m_v[i * y * z + j * z + k];
            }
        }
        return result;
    }

    vector<vector<T>> GetValues1(int j) //получение вектора векторов из элементов по y
    {
        vector<vector<T>> result(x, vector<T>(z));
        for (int i = 0; i < x; i++)
        {
            for (int k = 0; k < z; k++)
            {
                result[i][k] = m_v[i * y * z + j * z + k];
            }
        }
        return result;
    }

    vector<vector<T>> GetValues2(int k) //получение вектора векторов из элементов по z
    {
        vector<vector<T>> result(x, vector<T>(y));
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                result[i][j] = m_v[i * y * z + j * z + k];
            }
        }
        return result;
    }

    vector<T> GetValues0_1(int i, int j) //получение вектора векторов из элементов по (x,y)
    {
        vector<T> result(z);
        for (int k = 0; k < z; k++)
        { 
            result[k] = m_v[i * y * z + j * z + k]; 
        }
        return result;
    }

    vector<T> GetValues0_2(int i, int k) //получение вектора векторов из элементов по (x,z)
    {
        vector<T> result(y);
        for (int j = 0; j < y; j++)
        {
            result[j] = m_v[i * y * z + j * z + k];
        }
        return result;
    }

    vector<T> GetValues1_2(int j, int k) //получение вектора векторов из элементов по (y,z)
    {
        vector<T> result(x);
        for (int i = 0; i < x; i++)
        {
            result[i] = m_v[i * y * z + j * z + k];
        }
        return result;
    }
};



int main()
{
    vector<int> vec(27, 0); //вектор из 27 элементов
    Array3d<int, 3, 3, 3> arr(vec);

    //заполнение массива значениями от 1 до 27 (3^3)
    int s = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                arr.Setter(i, j, k, s);
                s++;
            }
        }
    }

    //вывод массива в консоль c помощью подмассивов
    cout << "ARRAY:" << endl;
    cout << arr << endl;

    //значения элементов массива по заданным индексам
    cout << "Getter(0,0,0) = " << arr.Getter(0, 0, 0) << endl;
    cout << "Getter(1,1,1) = " << arr.Getter(1, 1, 1) << endl;
    cout << "Getter(2,2,2) = " << arr.Getter(2, 2, 2) << endl;
    cout << "" << endl;

    //значения элементов массива по заданным индексам в виде векторов
    vector<int> values0_1 = arr.GetValues0_1(0, 1);
    vector<int> values0_2 = arr.GetValues0_2(0, 2);
    vector<int> values1_2 = arr.GetValues1_2(1, 2);

    //вывод этих векторов
    cout << "GetValues0_1(0,1) = (";
    for (int i = 0; i < values0_1.size(); i++) 
    {
        cout << values0_1[i] << " ";
    }
    cout << ")" << endl;

    cout << "GetValues0_2(0,2) = (";
    for (int i = 0; i < values0_2.size(); i++)
    {
        cout << values0_2[i] << " ";
    }
    cout << ")" << endl;

    cout << "GetValues1_2(1,2) = (";
    for (int i = 0; i < values1_2.size(); i++)
    {
        cout << values1_2[i] << " ";
    }
    cout << ")" << endl;
    cout << "" << endl;

    //значения элементов массива по заданным индексам в виде подвекторов
    vector<vector<int>> value0 = arr.GetValues0(0);
    vector<vector<int>> value1 = arr.GetValues1(1);
    vector<vector<int>> value2 = arr.GetValues2(2);

    //вывод подвекторов
    cout << "GetValue0(0):" << endl;
    for (int i = 0; i < value0.size(); i++)
    {
        for (int j = 0; j < value0[i].size(); j++)
        {
            cout << value0[i][j] << " "; 
        }
        cout << endl;
    }
    cout << endl;

    cout << "GetValues1(1):" << endl;
    for (int i = 0; i < value1.size(); i++)
    {
        for (int j = 0; j < value1[i].size(); j++)
        {
            cout << value1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "GetValues2(2):" << endl;
    for (int i = 0; i < value2.size(); i++)
    {
        for (int j = 0; j < value2[i].size(); j++)
        {
            cout << value2[i][j] << " "; 
        }
        cout << endl;
    }
}