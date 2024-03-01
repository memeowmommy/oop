#include <iostream>
#include "header.hpp"
using namespace std;


int main()
{
    string name1 = "biba"; //имя певрого юзера
    string name2 = "boba"; //имя второго юзера
    string mail = "me4meow@gmail.com"; //почта 
    string phone = "1234567890"; //номер телефона
    string location = "bfu"; //местоположение

    User* User1 = new User(123456, name1, mail, phone, location, MALE); //создаем юзеров
    User* User2 = new User(9876543, name2, mail, phone, location, FEMALE);

    auto* userRepository = new MemoryUserRepository();
    //добавляем пользователей
    userRepository->Add(User1);
    userRepository->Add(User2);

    cout << "Get by ID: ";
    cout << userRepository->getById(9876543)->getName() << endl; //выводим имя из айди
    cout << "Get by email: ";
    cout << userRepository->getByEmail(mail)->getName() << endl; //из почты 
    cout << endl;

    vector<User*> tmp = userRepository->getByLocation("bfu");
    
    cout << "TEST 1" << endl;
    for (User* user : tmp)
    {
        cout << user->getName() << "\t";
    }
    cout << endl;
    cout << endl;
   
   // выводим юзеров
    tmp = userRepository->Get(0, 1);
    cout << "TEST 2" << endl;
    for (User* user : tmp)
    {
        cout << user->getName() << "\t";  
    }
    cout << endl;
    cout << endl;

    cout << "Current number of users: " << userRepository->GetSize() << endl; //сколько пользователей
    cout << endl;
    userRepository->Delete(User2);
    userRepository->Delete(User1); //удаляем юзеров
    cout << "Current number of users: " << userRepository->GetSize() << endl; //проверяем количество юзеров
    cout << endl;
    
    userRepository->Add(User1); //снова добавляем юзеров после удаления
    userRepository->Add(User2);
    userRepository->Update(User2, User1); //кладем данные 1 юзера в данные второго

    //выводим юзеров
    cout << "TEST 3" << endl;
    tmp = userRepository->Get(0, 1);
    for (User* user : tmp)
    {
       cout << user->getName() << "\t";
    }
    cout << endl;
}