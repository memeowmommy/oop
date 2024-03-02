#pragma once
#include <iostream>
#include <functional> // для функций
using namespace std;

namespace prpr
{
	class derivative //родительский класс производной
	{
	protected:
		double x_0{0.0}; //икс нулевое         
		double dx{0.0}; //шаг          
		double accuracy{0}; //погрешность  

		//функция calculating принимает функцию fun и значение x_0, и возвращает значение типа double
		//virtual - может быть переопределена в производных классах LEFT, RIGHT, CENTER
		virtual double calculating (const function <double(double)> &fun, double x_0) 
		{return 0;}

	public:
		//сеттеры для шага и икс нулевого
		void SetdX(double dX) { dx = dX;}
		void SetX_0 (double X_0) { x_0 = X_0;}

		//геттеры для погрешности, шага и икс нулевого
		double GetAcc() { return accuracy; }
		double GetdX() { return dx; }
		double GetX_0() { return x_0; }

		//конструктор производной, проверка шага
		derivative (double X_0, double dX)
		{
			x_0 = X_0;
		    dx = dX;
			if (dx == 0) { cout << "error :((" << endl; exit(0); } //шаг не может быть равен 0! невозможно посчитать
		}
	};

	//классы потомки c наследованием derivative
	class LEFT : public derivative 
	{
	public:
		//функции для вычисления производной
		LEFT(double X_1, double dX_1) : 
			derivative(X_1, dX_1) {x_0 = X_1; dx = dX_1; accuracy = dx;}
		double calculating(const function <double(double)>& fun, double x_0_l) override 
			//override указывает, что функция переопределяемая
		{return ((fun(x_0_l) - fun(x_0_l - dx)) / dx);}
	};

	class RIGHT: public derivative
	{
	public:
		RIGHT(double X_1, double dX_1) : 
			derivative(X_1, dX_1) { x_0 = X_1; dx = dX_1; accuracy = dx;}
		double calculating(const function <double(double)>& fun, double x_0_r) override 
		{return ((fun(x_0_r + dx) - fun(x_0_r)) / dx);}	
	};

	class CENTER: public derivative 
	{
	public:
		CENTER(double startX1, double step1) :derivative(startX1, step1) { x_0 = startX1; dx = step1; accuracy = dx * dx;}
		double  calculating(const std::function <double(double)>& fun, double x_0_c) override  
		{return ((fun(x_0_c + dx) - fun(x_0_c - dx)) / (2*dx));}
	};
}
