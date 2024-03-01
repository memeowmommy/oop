#pragma once
#include <thread> //для sleep_for()
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<class T> //шаблон с классом
class IRepository //родительский класс
{
public:
    //virtual чтобы функции согли быть переопределены
    virtual void Add(T* item) {}; //добавление
    virtual void Update(T* oneitem, T* twoitem) {}; //обновление
    virtual void Delete(T* item) {}; //удаление
    
    virtual vector<T*> Get(unsigned int beginIndex, unsigned int endIndex) { return {}; } //вектор для индексов юзеров

    virtual ~IRepository() = default; //деструктор
};

enum Gender //енам класс для пола
{
    MALE,
    FEMALE
};

class User //родительский класс ЮЗЕР
{
private:
    int m_id; //айди
    string m_name; //имя 
    string m_mail; //поча
    string m_phone; //телефон
    string m_location; //местоположение
    Gender m_gender; //пол

public:
    User(int id, string& name, string& mail, string& phone, string& location, Gender gender) :
    m_id(id), m_name(name), m_mail(mail), m_phone(phone), m_location(location), m_gender(gender) {} //конструктор+инициализация

    //сеттеры
    int setId(int id) { m_id = id; } 
    string setName(string name) { m_name = name; }
    string setEmail(string mail) { m_mail = mail; }
    string setPhone(string phone) { m_phone = phone; }
    string setCity(string location) { m_location = location; }
    Gender setGender(Gender gender) { m_gender = gender; }

    //геттеры
    int getId() { return m_id; }
    string getName() { return m_name; }
    string getEmail() { return m_mail; }
    string getPhone() { return m_phone; }
    string getCity() { return m_location; }
    Gender getGender() { return m_gender; }

    bool operator==(const User& rhs) const //перегруженные операторы сравнения
    {
        return (m_id == rhs.m_id && m_name == rhs.m_name && m_mail == rhs.m_mail && m_phone == rhs.m_phone && m_location == rhs.m_location && m_gender == rhs.m_gender);
    }

    bool operator!=(const User& rhs) const 
    {
        return !(rhs == *this);
    }
};

//класс потомок с наследованием IRepository<User>
class UserRepository : public IRepository<User> 
{
public:
    //геттеры
    virtual User* getById(int id) { return nullptr; }; //указатель на объект класса юзер, возвращаем пустой указатель
    virtual User* getByName(const string& name) { return nullptr; }
    virtual User* getByEmail(const string& mail) { return nullptr; }
    virtual vector<User*> getByLocation(const string& location) { return {}; } //вектор
    virtual vector<User*> getByGender(Gender gender) { return {}; }

    ~UserRepository() override = default; //деструктор
};

template<class T> //шаблон класса
//класс потомок с наследованием IRepository<Т>
class MemoryRepository : public IRepository<T> 
{
protected:
    vector<User*> m_users{}; //вектор 
public:
    unsigned int GetSize() { return m_users.size(); } //размер вектора - количество пользователей

    //override для переопределения
    void Add(User* user) override { m_users.push_back(user);} //добавление юзеров

    void Update(User* first, User* second) override //обновление юзеров
    {
        this_thread::sleep_for(chrono::milliseconds(500)); //приостанавливает выполнение программы на 500 миллисекунд
        cout << "Updating..." << endl;
        for (auto& m_user : m_users) 
        {
            if (*first == *m_user)  { m_user = second;} 
        }
        cout << "Updating..." << endl;
    }

    void Delete(User* item) override //удаление юзеров
    {
        cout << "Deleting..." << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); //приостанавливает выполнение программы на 500 миллисекунд
        for (int i = 0; i < m_users.size(); i++) 
        {
            if (*item == *m_users[i]) 
            {
                m_users.erase(m_users.begin()+i);
                --i;
            }
        }
    }

    vector<User*> Get(unsigned int beginIndex, unsigned int endIndex) override //получение юзеров
    {
        vector<User*> returnUsers{};
        if (beginIndex >= m_users.size() || endIndex < beginIndex) 
        {
            throw exception("out of range");
        }

        for (; beginIndex <= endIndex; beginIndex++) 
        { 
            returnUsers.push_back(m_users[beginIndex]); 
        }
        return returnUsers;
    }
    virtual ~MemoryRepository() = default; //деструктор
};

//класс потомок с наследованиями
class MemoryUserRepository : public MemoryRepository<User>, public UserRepository 
{
public:
    //определяем функции
    using MemoryRepository<User>::Add;
    using MemoryRepository<User>::Update;
    using MemoryRepository<User>::Delete;
    using MemoryRepository<User>::Get;

    User* getById(int id) override //получение юзера по айди
    {
        for (User* user : MemoryRepository<User>::m_users) 
        {
            if (user->getId() == id)  { return user; }  
        }
        return nullptr;
    }

    User* getByName(const string& name) override //получение юзера по имени
    {
        for (User* user : MemoryRepository<User>::m_users) 
        {  
            if (user->getName() == name)  { return user; }  
        }
        return nullptr;
    }

    User* getByEmail(const string& mail) override //получение по почте
    {
        for (User* user : MemoryRepository<User>::m_users) 
        {
            if (user->getEmail() == mail)  {return user; } 
        }
        return nullptr;
    }

    vector<User*> getByLocation(const string& location) override //получение по местоположению
    {
        vector<User*> returnUsers{};
        for (User* user : MemoryRepository<User>::m_users) 
        { 
            if (user->getCity() == location)  { returnUsers.push_back(user); } 
        }
        return returnUsers;
    }

    vector<User*> getByGender(Gender gender) override //получение юзер по полу
    {
        vector<User*> returnUsers{};
        for (User* user : MemoryRepository<User>::m_users) 
        { 
            if (user->getGender() == gender)  { returnUsers.push_back(user); } 
        }
        return returnUsers;
    }
    virtual ~MemoryUserRepository() = default; //деструктор
};