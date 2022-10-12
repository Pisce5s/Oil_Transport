#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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
    t.status = get_pozitive_number(0, 1);
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

void load_tube(tube& t)
{
    ifstream file_in;
    file_in.open("data.txt", ios::in);
    if (file_in.is_open())
    {
        file_in >> t.length;
        file_in >> t.diameter;
        file_in >> t.status;
        file_in.close();
    }
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

ostream& operator << (ostream& out, const tube& p)
{
    out << "Длина = " << p.length << endl
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

void edit_CS(CS& t)
{
    int oper;
    cout << "+1 для добавления цеха, -1 для убавления " << endl;
    cin >> oper;
    switch (oper)
    {
    case -1:
        if ((t.number_of_shops_in_work - 1) < 0)
        {
            cout << "Число цехов в работе не может быть меньше 0" << endl;
            edit_CS(t);
        }
        else
        {
            t.number_of_shops_in_work -= 1;
        }
        break;
    case 1:
        if (t.number_of_shops < (t.number_of_shops_in_work + 1))
        {
            cout << "Число цехов в работе не может быть больше числа цехов" << endl;
            edit_CS(t);
        }
        else
        {
            t.number_of_shops_in_work += 1;
        }
        break;
    default:
        cout << "Ошибка, введите указанные выше значения";
        break;
    }
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

CS load_CS(CS& t)
{
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
    getline(cin >> ws, p.name);
    cout << "Введите число цехов: ";
    p.number_of_shops = get_pozitive_number(1, 9999);
    cout << "Введите число работающих цехов: ";
    p.number_of_shops_in_work = get_pozitive_number(0, p.number_of_shops);
    cout << "Введите эффективность: ";
    p.efficiency = get_pozitive_number(0.0, 99999999.0);
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

bool is_data_correct(const tube& t)
{
    if ((t.length < 0) or (t.diameter < 0) or ((t.status != 0) and (t.status != 1)))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

bool is_data_correct(const CS& t)
{
    if ((t.number_of_shops < 0) or (t.number_of_shops_in_work < 0) or (t.number_of_shops_in_work > t.number_of_shops))
    {
        return 0;
    }
    else
    {
        return 1;
    }
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
            if (is_data_correct(t) == 1)
            {
                cout << t << endl;
            }
            else
            {
                cout << "Трубы нет" << endl;
            }

            if (is_data_correct(c) == 1)
            {
                cout << c << endl;
            }
            else
            {
                cout << "КС нет" << endl;
            }
            break; //Просмотр объектов
        }
        case 4:
        {
            if (is_data_correct(t) == 1)
            {
                edit_tube(t);;
            }
            else
            {
                cout << "Трубы нет" << endl;
            }
            //edit_tube(t);
            break; //Редактировать трубу
        }
        case 5:
        {
            if (is_data_correct(c) == 1)
            {
                edit_CS(c);;
            }
            else
            {
                cout << "КС нет" << endl;
            }
            break; //Редактировать КС
        }
        case 6:
        {
            if (is_data_correct(t) == 1)
            {
                save_tube(t);
            }
            if (is_data_correct(c) == 1)
            {
                save_CS(c);;
            }
            break; //Сохранить
        }
        case 7:
        {
            load_tube(t);
            load_CS(c);
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