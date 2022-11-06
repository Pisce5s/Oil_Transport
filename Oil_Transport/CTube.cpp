#include "CTube.h"
#include "utils.h"
using namespace std;

int tube::MaxID = 0;

tube::tube()
{
	//cout << "tube::tube()" << endl;
    id = 0;
    length = 0;
    diameter = 0;
    status = false;
}

tube::tube(const tube& t)
{
	//cout << "tube::tube(const tube& t)" << endl;
    id = MaxID++;
    length = t.length;
    diameter = t.diameter;
    status = t.status;
}

//tube::~tube()
//{
//	cout << "tube::~tube()" << endl;
//}

int tube::get_MaxID()
{
    return MaxID;
}

ostream& operator << (ostream& out, const tube& p)
{
    out << "ID = " << p.id << endl
        //<< "MaxID = " << tube::MaxID << endl
        << "Длина = " << p.length << endl
        << "Диаметр = " << p.diameter << endl
        << "Состояние работы: ";
    if (p.status == 0)
    {
        out << "Не работает" << endl;
    }
    else
    {
        out << "Работает" << endl;
    }
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