#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

enum class COLOR //енам класс цветов для шрифта
{
	RED,
	YELLOW,
	WHITE,
	GREEN,
	MAGENTA
};

class Letter //класс буквы, хранящий массив строк, составляющих эту букву
{
private:
	int m_width = 0; //ширина буквы
	int m_height = 0; //высота буквы
	vector <string> m_symbols{}; //вектор слайсов букв
	string m_file_name; //строка для имени файла, где лежит шрифт

public:
	
	Letter(const string file_name, int width, int let_number) : m_file_name(file_name)//инициализация имени файла
	{
		string temp = ""; //пустные строки
		string outp = ""; 
		ifstream in(file_name); //открываем файл со шрифтом
		//читаем файл
		if (in.is_open())
		{
			while (getline(in, temp))
			{
				for (int x = width * let_number; x < (width * let_number + width); x++)
				{
					outp += temp[x];
				}

				m_symbols.push_back(outp); //добавляем строчки буквы в вектор
				m_height++;

				temp = "";
				outp = "";
			}
		}
	}
	//костыль для пробела между словами
	Letter(int width, int height, string symbol) : m_height(height) //быстрая инициализация высоты букв
	{
		string temp = "";
		string outp = "";

		for (int x = 0; x < width; x++)
		{
			temp += symbol;
		}

		for (int y = 0; y < height; y++)
		{
			m_symbols.push_back(temp);
		}
	}

	//конструктор копирования
	Letter(const Letter& p)
	{
		m_width = p.m_width;
		m_height = p.m_height;
		m_symbols = p.m_symbols;
		m_file_name = p.m_file_name;
	}

	//геттеры
	int GetHeight() { return m_height; }
	string GetsymbolString(int x) { return m_symbols[x]; } //опр. слайс

	//склеивание букв (переопределение операторов)
	Letter operator + (const Letter& letter) const
	{
		Letter temp(letter);
		
		if (this->m_height != letter.m_height) { cout << "wrong size ^-^" << endl; } //ошибка
		else if (this->m_height == letter.m_height)
		{
			temp.m_height = this->m_height;
			for (int x = 0; x < m_height; x++)
			{
				temp.m_symbols[x] = this->m_symbols[x] + letter.m_symbols[x];
			}
			return temp;
		}
	}

	Letter& operator += (const Letter& letter)  //перегруженные операторы для склеивания букв в предложения
	{
		if (this->m_height != letter.m_height) { cout << "wrong size ^-^" << endl; } //ошибка
		else if (this->m_height == letter.m_height)
		{
			for (int x = 0; x < m_height; x++)
			{
				m_symbols[x] += letter.m_symbols[x];
			}
			return *this;
		}
	}

	//вывод букв по слайсам
	void PrintLetter()
	{
		for (int x = 0; x < m_height; x++)
		{
			cout << m_symbols[x] << endl;
		}
	}
};

//
vector<Letter> FontSetUp(const string name, int width, int alf_size)
{
	vector<Letter> alf{}; //алфавит массив
	int alf_width = width;
	ifstream in(name); // окрытие файла
	for (int i = 0; i < alf_size; i++) 
	{
		Letter temp(name, width, i);
		alf.push_back(temp); //заполняем алфавит из файла
		//temp.PrintLetter();
		//cout << endl;
	}

	Letter space(width, alf[0].GetHeight(), " "); //добавляем пробел в конец алфавита
	alf.push_back(space);
	return alf;
}

//класс шрифта
class Fontik
{
private:
	int m_size; //размер шрифта
	COLOR m_color; //цвет шрифта
	int m_alf_size = 27; //26 букв алфавита + пробел
	vector<Letter> m_alf{}; // алфавит из букв
	string m_input_text; //введенный текст
	int m_width;//ширина основания буквы алфавита

public:
	//конструктор
	Fontik(int size, COLOR color, int alf_size) : m_size{ size }, m_color{ color }, m_alf_size{ alf_size + 1 } //инициализация
	{
		if (m_size == 5) { m_alf = FontSetUp("5.txt", 8, alf_size - 1); m_width = 8; } //у меня ширина буквы 8 символов
		if (m_size == 7) { m_alf = FontSetUp("7.1.txt", 10, alf_size - 1); m_width = 10; } //у меня ширина буквы 10 символов
	}
	//задает текст
	void SetText(string text)
	{m_input_text = text;}

	//функция вывода текста
	void PrintТext()
	{
		Letter temp(m_width, m_alf[0].GetHeight(), "");

		for (int x = 0; x < m_input_text.length(); x++)
		{
			if ((int(m_input_text[x]) > 64) and (int(m_input_text[x]) < 91)) { temp += m_alf[int(m_input_text[x]) - 65]; }
			else if ((int(m_input_text[x]) > 96) and (int(m_input_text[x]) < 123)) { temp += m_alf[int(m_input_text[x]) - 97]; }
			else if (int(m_input_text[x]) == 32) { temp += m_alf[m_alf_size - 2]; }
		}
	}

	friend ostream& operator << (ostream& out, Fontik text) //перегруженный оператор вывода в поток
	{   
		Letter temp(text.m_width, text.m_alf[0].GetHeight(), ""); //пустая буква

		for (int x = 0; x < text.m_input_text.length(); x++)
		{
			if ((int(text.m_input_text[x]) > 64) and (int(text.m_input_text[x]) < 91)) 
			{ temp += text.m_alf[int(text.m_input_text[x]) - 65]; }
			else if ((int(text.m_input_text[x]) > 96) and (int(text.m_input_text[x]) < 123)) 
			{ temp += text.m_alf[int(text.m_input_text[x]) - 97]; }
			else if (int(text.m_input_text[x]) == 32) 
			{ temp += text.m_alf[text.m_alf_size - 2]; } //обращение к последнем эл-ту в массиве (всегда пробел)
		}

		if (text.m_color == COLOR::RED) { cout << "\033[31m"; }
		if (text.m_color == COLOR::YELLOW) { cout << "\033[33m"; }
		if (text.m_color == COLOR::WHITE) { cout << "\033[0m"; }
		if (text.m_color == COLOR::GREEN) { cout << "\033[32m"; }
		if (text.m_color == COLOR::MAGENTA) { cout << "\033[35m"; }
	

		for (int x = 0; x < temp.GetHeight(); x++)
		{
			out << temp.GetsymbolString(x) << endl;
		}
		out << "\033[0m"; //остальной текст в консоли не перекрашиваем
		return out;
	}
};

int main()
{
	Fontik f(7, COLOR::GREEN, 27);
	f.SetText("MEOW  b a r k"); //пишем внутри текст
	cout << endl;
	cout << f; //выводим
}