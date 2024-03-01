#include <iostream>
#include <functional>
#include "meow.hpp"
using namespace std;

int main()
{
	// X = 2, шаг = 0.001
	prpr::LEFT leftd(2, 0.001); 
	
	prpr::CENTER centd(2, 0.001);

	prpr::RIGHT rigd(2, 0.001);

	//функция вычисляет значение (x^4)/4 
	function<double(double)> fun = [](double x) { return 0.25* pow(x, 4.0); }; // f(x)=(x^4)/4 => f'(x)=x^3
	
	//выводим результат
	cout << "left derivative = " << leftd.calculating(fun, leftd.GetX_0()) << endl;
	cout << "accuracy = " << leftd.GetAcc() << endl;
	cout << " " << endl;
	cout << "central derivative = " << centd.calculating(fun, centd.GetX_0()) << endl; // должно быть 2^3=8
	cout << "accuracy = " << centd.GetAcc() << std::endl;
	cout << " " << endl;
	cout << "right derivative = " << rigd.calculating(fun, rigd.GetX_0()) << endl;
	cout << "accuracy = " << rigd.GetAcc() << endl;
}

