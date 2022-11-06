#include "CCS.h"
#include "utils.h"
using namespace std;

int CS::MaxID = 0;

CS::CS()
{
    //cout << "CS::CS()" << endl;
    id = ++MaxID;
    number_of_shops = 0;
    number_of_shops_in_work = 0;
    efficiency = 0;
    name = "Неизвестно";
}

CS::CS(const CS& c)
{
    //cout << "CS::CS(const CS& c)" << endl;
    number_of_shops = c.number_of_shops;
    number_of_shops_in_work = c.number_of_shops_in_work;
    efficiency = c.efficiency;
    name = c.name;
}

std::string CS::get_name() const
{
    return name;
}

void CS::set_name(std::string new_name)
{
    name = new_name;
}

int CS::get_MaxID()
{
    return MaxID;
}

int CS::get_ID() const
{
    return id;
}

void CS::set_ID(int ID)
{
    id = ID;
}

istream& operator >> (istream& in, CS& p)
{
    cout << "Введите название КС: ";
    getline(cin >> ws, p.name);
    cout << "Введите число цехов: ";
    p.number_of_shops = get_pozitive_number(1, 999999999);
    cout << "Введите число работающих цехов: ";
    p.number_of_shops_in_work = get_pozitive_number(0, p.number_of_shops);
    cout << "Введите эффективность: ";
    p.efficiency = get_pozitive_number(0.0, 99999999.0);
    return in;
}

ostream& operator << (ostream& out, const CS& p)
{ 
    out << "ID = " << p.id << endl
        << "MaxID = " << CS::MaxID << endl
        << "Название = " << p.name << endl
        << "Число цехов = " << p.number_of_shops << endl
        << "Число цехов в работе: " << p.number_of_shops_in_work << endl
        << "Эффективность:" << p.efficiency << endl;
    return out;
}
