﻿#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void print_menu()
{
    cout << "1.Добавить трубу" << endl
        << "2.Добавить КС" << endl
        << "3.Просмотр объектов" << endl
        << "4.Редактировать трубу" << endl
        << "5.Редактировать КС" << endl
        << "6.Сохранить" << endl
        << "7.Загрузить" << endl
        << "0.Выход" << endl
        << "Введите комманду" << endl;
}

template <typename T>

T get_pozitive_number(T min, T max)
{
    T x;
    while ((cin >> x).fail() || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ошибка, введите подходящее число\n";
    }
    return x;
}

struct tube
{
    double length;
    double diameter;
    bool status;
};

struct CS
{
    string name;
    int number_of_shops;
    int number_of_shops_in_work;
    double efficiency;
};

void edit_tube(tube& t)
{
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0. ";
    cin >> t.status;
}

void save_tube(const tube& t)
{
    ofstream file_out;
    file_out.open("data.txt", ios::out);
    if (file_out.is_open())
    {
        file_out << t.length << endl << t.diameter << endl << t.status << endl;
        file_out.close();
    }
}

tube load_tube()
{
    tube t;
    ifstream file_in;
    file_in.open("data.txt", ios::in);
    if (file_in.is_open())
    {
        file_in >> t.length;
        file_in >> t.diameter;
        file_in >> t.status;
        file_in.close();
    }return t;
}

istream& operator >> (istream& in, tube& p)
{
    cout << "Введите длину: ";
    p.length = get_pozitive_number(0.0000001, 9999999.0);
    cout << "Введите диаметр: ";
    p.diameter = get_pozitive_number(0.0000001, 9999999.0);
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0. ";
    cin >> p.status; // ALERT! RED SPY INCAMING
    return in;
}

ostream& operator << (ostream& out, const tube& p)
{
    out << "Длина = " << p.length << endl
        << "Диаметр = " << p.diameter << endl
        << "Состояние работы: " << p.status << endl;
    return out;
}

void edit_CS(CS& t)
{
    cout << "Сколько теперь цехов в работе: ";
    cin >> t.number_of_shops_in_work;
}

void save_CS(const CS& t)
{
    ofstream file_out;
    file_out.open("data2.txt", ios::out);
    if (file_out.is_open())
    {
        file_out << t.name << endl << t.number_of_shops << endl << t.number_of_shops_in_work << endl << t.efficiency << endl;
        file_out.close();
    }
}

CS load_CS()
{
    CS t;
    ifstream file_in;
    file_in.open("data2.txt", ios::in);
    if (file_in.is_open())
    {
        file_in >> t.name;
        file_in >> t.number_of_shops;
        file_in >> t.number_of_shops_in_work;
        file_in >> t.efficiency;
        file_in.close();
    }return t;
}

istream& operator >> (istream& in, CS& p)
{
    cout << "Введите название КС: ";
    in >> p.name;
    cout << "Введите число цехов: ";
    p.number_of_shops = get_pozitive_number(1, 9999);
    cout << "Введите число работающих цехов: ";
    p.number_of_shops_in_work = get_pozitive_number(0, p.number_of_shops);
    cout << "Введите эффективность: ";
    p.efficiency = get_pozitive_number(0, 99999999);
    return in;
}

ostream& operator << (ostream& out, const CS& p)
{
    out << "Название = " << p.name << endl
        << "Число цехов = " << p.number_of_shops << endl
        << "Число цехов в работе: " << p.number_of_shops_in_work << endl
        << "Эффективность:" << p.efficiency << endl;
    return out;
}

int main()
{
    setlocale(0, "");
    tube t;
    CS c;
    //vector <tube> tubes;
    while (true)
    {
        print_menu();
        switch (get_pozitive_number(0,7))
        {
        case 1:
        {
            cin >> t;
            break; //Добавить трубу
        }
        case 2:
        {
            cin >> c;
            break; //Добавить КС
        }
        case 3:
        {
            cout << t << endl;
            cout << c << endl;
            break; //Просмотр объектов
        }
        case 4:
        {
            edit_tube(t);
            break; //Редактировать трубу
        }
        case 5:
        {
            edit_CS(c);
            break; //Редактировать КС
        }
        case 6:
        {
            save_tube(t);
            save_CS(c);
            break; //Сохранить
        }
        case 7:
        {
            t = load_tube();
            c = load_CS();
            break; //Загрузить
        }
        case 0:
        {
            return 0; //Выход
        }
        default:
        {
            cout << "Ошибка, введена несуществующая комманда" << endl;
        }
        }
    }
}
