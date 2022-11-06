#include "CTube.h"
#include "utils.h"
using namespace std;

int tube::MaxID = 0;

tube::tube()
{
	//cout << "tube::tube()" << endl;
    id = ++MaxID;
    length = 0;
    diameter = 0;
    status = false;
}

tube::tube(const tube& t)
{
	//cout << "tube::tube(const tube& t)" << endl;
    id = t.id;
    length = t.length;
    diameter = t.diameter;
    status = t.status;
}

int tube::get_MaxID()
{
    return MaxID;
}

int tube::get_ID() const
{
    return id;
}

void tube::set_ID(int ID)
{
    id = ID;
}

ostream& operator << (ostream& out, const tube& p)
{
    out << "ID = " << p.id << endl
        << "MaxID = " << tube::MaxID << endl
        << "Длина = " << p.length << endl
        << "Диаметр = " << p.diameter << endl
        << "Состояние работы: ";
    if (p.status) { out << "Работает" << endl; }
    else { out << "Не работает" << endl; }
    return out;
}

istream& operator >> (istream& in, tube& p)
{
    cout << "Введите длину: ";
    p.length = get_pozitive_number(0.0000001, 9999999.0);
    cout << "Введите диаметр: ";
    p.diameter = get_pozitive_number(0.0000001, 9999999.0);
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0. ";
    p.status = get_pozitive_number(0, 1);
    return in;
}