#include<iostream>
#include<vector>
#include<functional>
#include "header.hpp"
using namespace std;

//класс потомок с наследованим класса PropChanged 
class ChangedClass : PropChanged 
{
private:
	int m_par; //элемент 
	vector<function<void(int)>> audios; //вектор записей
public:
	ChangedClass(int par) { m_par = par; }

	void SetPar(int par) //сеттер
	{
		for (const auto& listener : audios) 
		{ 
			listener(m_par); 
		}
	}
	//override указывает, что функция переопределяемая
	void AddListener(const function<void(int)>& listener) override 
	{ audios.push_back(listener); } //добавляем слушателя в вектор записей
	void RemoveListener() override 
	{ audios.pop_back(); } //убираем слушателя из вектора записей
};

//класс потомок с наследованим класса PropChanging
class ChangingClass : PropChanging
{
private:
	int m_par; //элемент
	vector<function<void(int, int, bool&) >> audios; //вектор записей
public:
	ChangingClass(int par) { m_par = par; }

	void SetPar(int par) //сеттер
	{
		bool flag;
		for (const auto& listener : audios) 
		{ 
			listener(m_par, par, flag); 
		}
		if (flag == true) { return; }
		m_par = par;
	}

	void AddListener(const function<void(int, int, bool&)>& listener) override { audios.push_back(listener); }
	void RemoveListener() override { audios.pop_back(); }
};

//класс потомок с наследованием CollectionChanged
class Collection : CollectionChanged
{
private:
	vector<int> tools; 
	vector<function<void(int, int, Status) >> audios; //записи

public:
	void add(int val) //добавляем значения
	{
		tools.push_back(val);
		for (const auto& listener : audios) 
		{
			listener(0, val, Status::ADDED);
		}
	}

	void change(int ind, int new_val) //меняем значения
	{
		tools.at(ind) = new_val;
		for (const auto& listener : audios) 
		{ 
			listener(ind+1, new_val, Status::CHANGED); 
		}
	}

	void remove(int ind) //удаляем значения
	{
		int tmp = tools.at(ind);
		tools.erase(tools.begin() + ind);
		for (const auto& listener : audios) 
		{ 
			listener(ind+1, tmp, Status::REMOVED); 
		}
	}

	void AddListener(const function<void(int, int, Status)>& listener) override //добавляем слушателей
	{ audios.push_back(listener); } //добавляем в вектор

	void RemoveListener() override //удаляем слушателей
	{ audios.pop_back(); } //удаляем из вектора
};


int main()
{
	cout << "TEST 1:" << endl;
	ChangedClass Changed(47); //изменяем элемент
	function<void(int)> listener1 = Mode_1; //выводим какой элемент изменен

	Changed.AddListener(listener1); //добавляем 1 слушателя 
	Changed.SetPar(6); 
	cout << endl;

	cout << "TEST 2:" << endl;

	ChangingClass Changing(122); //изменяем элемент
	function<void(int, int, bool&)> listener2 = Mode_2;
	function<void(int, int, bool&)> listener3 = Mode_3;

	Changing.AddListener(listener2); //добавляем 2 слушателя
	Changing.AddListener(listener3); //добавляем 3 слушателя
	Changing.SetPar(4423);
	cout << endl;

	cout << "TEST 3:" << endl;
	Collection collection;
	function<void(int, int, Status)> listener4 = Mode_4;

	collection.AddListener(listener4); //добавляем 4 слушателя
	collection.add(4); //добавлен первый элемент
	collection.add(4244); //добавлен второй элемент
	collection.change(1, 191); //второй элемент изменен на 191 (индекс второго элемента равен 1)
	collection.remove(1); //второй элемент удален

}