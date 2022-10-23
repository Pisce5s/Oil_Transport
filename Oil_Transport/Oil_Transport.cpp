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

bool is_data_correct(const tube& t)
{
    if ((t.length < 0) or (t.diameter < 0) or ((t.status != 0) and (t.status != 1)))
    { return 0; }
    else    { return 1; }
}

bool is_data_correct(const CS& c)
{
    if ((c.number_of_shops < 0) or (c.number_of_shops_in_work < 0) or (c.number_of_shops_in_work > c.number_of_shops))
    { return 0; }
    else    { return 1; }
}

void edit_tube(tube& t)
{
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0. ";
    t.status = get_pozitive_number(0, 1);
}

void save(ofstream& file_out, const tube& t, const CS& c)
{
        if (is_data_correct(t)) 
        {
            file_out << "tube" << endl << t.length << endl << t.diameter << endl << t.status << endl;
        }
        if (is_data_correct(c)) 
        { 
            file_out << "CS" << endl << c.name << endl << c.number_of_shops << endl << c.number_of_shops_in_work << endl << c.efficiency << endl;
        }
}

void load(tube& t, CS& c)
{
    ifstream file_in;
    file_in.open("data.txt", ios::in);
    if (file_in.is_open())
    {
        string keyword;
        file_in >> keyword;
        if (keyword == "tube")
        {
            file_in >> t.length;
            file_in >> t.diameter;
            file_in >> t.status;
            file_in >> keyword;
        }
        if (keyword == "CS")
        {
            getline(file_in >> ws, c.name);
            file_in >> c.number_of_shops;
            file_in >> c.number_of_shops_in_work;
            file_in >> c.efficiency;
        }
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
        else    {t.number_of_shops_in_work -= 1;}
        break;
    case 1:
        if (t.number_of_shops < (t.number_of_shops_in_work + 1))
        {
            cout << "Число цехов в работе не может быть больше числа цехов" << endl;
            edit_CS(t);
        }
        else    {t.number_of_shops_in_work += 1;}
        break;
    default:
        cout << "Ошибка, введите указанные выше значения" << endl;;
        cin.clear();
        cin.ignore(1000, '\n');
        edit_CS(t);
        break;
    }
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

tube& select_tube(vector<tube>& p)
{
    cout << "Введите индекс: ";
    unsigned int index = get_pozitive_number(1u, static_cast<unsigned int>(p.size()));
    //unsigned int index = get_pozitive_number(1, p.size());
    return p[index-1];
}

int main()
{
    setlocale(0, "");
    tube t;
    CS c;
    vector <tube> tubes;
    //vector <CS> CStations;
    while (true)
    {
        print_menu();
        switch (get_pozitive_number(0,7))
        {
        case 1:
        {
            cin >> t;
            tubes.push_back(t);
            break; //Добавить трубу
        }
        case 2:
        {
            cin >> c;
            break; //Добавить КС
        }
        case 3:
        {
            //if (is_data_correct(t))     {cout << t << endl;}
            if (is_data_correct(t)) { cout << select_tube(tubes) << endl; }
            else {cout << "Трубы нет" << endl;}

            if (is_data_correct(c))     {cout << c << endl;}
            else {cout << "КС нет" << endl;}
            break; //Просмотр объектов
        }
        case 4:
        {
            //if (is_data_correct(t))     {edit_tube(t);}
            if (is_data_correct(t)) { edit_tube(select_tube(tubes)); }
            else    {cout << "Трубы нет" << endl;}
            break; //Редактировать трубу
        }
        case 5:
        {
            if (is_data_correct(c))     {edit_CS(c);}
            else    {cout << "КС нет" << endl;}
            break; //Редактировать КС
        }
        case 6:
        {
            ofstream file_out;
            file_out.open("data.txt", ios::out);
            if (file_out.is_open())
            {
                for (tube t : tubes)
                    save(file_out, t, c);
                file_out.close();
            }
            break; //Сохранить
        }
        case 7:
        {
            load(t, c);
            tubes.push_back(t);
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