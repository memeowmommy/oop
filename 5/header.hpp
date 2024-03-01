#pragma once
#include <functional>
#include <iostream>
using namespace std;

enum class Status //enum класс для статусов ДОБАВЛЕН/УДАЛЕН/ИЗМЕНЁН
{
	ADDED,
	REMOVED,
	CHANGED
};

//интерфейс INotifyPropertyChanging
class PropChanging //класс родитель 
{
	//virtual чтобы функции могли быть переопределена в потомках
	virtual void AddListener(const function<void(int, int, bool&)>& listener) {} //добавление слушателя 
	virtual void RemoveListener() {} //удаление слушателя
};

///интерфейс INotifyPropertyChanged 
class PropChanged //класс родитель 
{
public:
	virtual void AddListener(const function<void(int)>& listener) {}
	virtual void RemoveListener() {}
};

//интерфейс INotifyCollectionChanged
class CollectionChanged //класс родитель 
{
public:
	virtual void AddListener(const function<void(int, int, Status)>& listener) {}
	virtual void RemoveListener() {}
};

//режим 1 показывает изменение
void Mode_1(int value) { cout << "Mode 1 is changed to " << value << endl; }
//режим 2 включает в себя два статуса
void Mode_2(int old_value, int new_value, bool& f)
{
	if (new_value >= old_value)
	{
		f = true;
		cout << "Mode 2 isn't changed." << endl; //не изменен
	}
	else
	{
		f = false;
		cout << "Mode 2 is changed." << endl; //изменен
	}
}
//режим 3 включает в себя два статуса
void Mode_3(int old_value, int new_value, bool& f)
{
	if (max(old_value, new_value) / min(old_value, new_value) == 2)
	{
		f = true;
		cout << "Mode 3 isn't changed." << endl;
	}
	else
	{
		f = false;
		cout << "Mode 3 is changed." << endl;
	}
}
//режим 4 включчает в себя удаление, изменение, добавление
void Mode_4(int ind, int value, Status status)
{
	cout << "Mode 4: ";
	//свитч для переключения между статусами
	switch (status) 
	{
	case Status::REMOVED:
		cout << ind << " element deleted " << endl; 
		break;
	case Status::ADDED:
		cout << "Element " << value << " added" << endl;
		break;
	case Status::CHANGED:
		cout << "The " << ind << " element changed to " << value << endl; 
		break;
	}
}
