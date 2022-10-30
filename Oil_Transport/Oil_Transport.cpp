#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "CTube.h"
#include "CCS.h"
#include <unordered_map>
#include "utils.h"

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
        << "8.Удалить элемент" << endl
        << "9.Удалить всё" << endl
        << "10.Фильтр труб по состоянию" << endl
        << "11.Фильтр КС по названию" << endl
        << "12.Фильтр КС по проценту задействованных цехов" << endl
        << "0.Выход" << endl
        << "Введите комманду" << endl;
}

void edit_tube(tube& t)
{
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0. ";
    t.status = get_pozitive_number(0, 1);
}

void save_tube(ofstream& file_out, const tube& t)
{
    file_out << t.length << endl << t.diameter << endl << t.status << endl;
}

void save_CS(ofstream& file_out, const CS& c)
{
    file_out << c.name << endl << c.number_of_shops << endl << c.number_of_shops_in_work << endl << c.efficiency << endl;
}

void load_tube(ifstream& file_in, tube& t)
{
    file_in >> t.length;
    file_in >> t.diameter;
    file_in >> t.status;
}

void load_CS(ifstream& file_in, CS& c)
{
    getline(file_in >> ws, c.name);
    file_in >> c.number_of_shops;
    file_in >> c.number_of_shops_in_work;
    file_in >> c.efficiency;
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

tube& select_tube(unordered_map<int, tube>& p)
{
    cout << "Введите индекс: ";
    unsigned int index = get_pozitive_number(0u, static_cast<unsigned int>(p.size()-1));
    //unsigned int index = get_pozitive_number(1, p.size());
    return p[index];
}

CS& select_CS(unordered_map<int, CS>& c)
{
    cout << "Введите индекс: ";
    unsigned int index = get_pozitive_number(0u, static_cast<unsigned int>(c.size()-1));
    //unsigned int index = get_pozitive_number(1, c.size());
    return c[index];
}

unsigned int select_tube_index(unordered_map<int, tube>& p)
{
    cout << "Введите индекс: ";
    unsigned int index = get_pozitive_number(0u, static_cast<unsigned int>(p.size()-1));
    return (index);
}

unsigned int select_CS_index(unordered_map<int, CS>& c)
{
    cout << "Введите индекс(ID): ";
    unsigned int index = get_pozitive_number(0u, static_cast<unsigned int>(c.size()-1));
    return (index);
}

void del_item(unordered_map<int, tube>& p, unordered_map<int, CS>& c)
{
    bool select;
    cout << "Введите: 0 - для удаления трубы, 1 - для удаления КС" << endl;
    select = get_pozitive_number(false, true);
    if (select)
    {
        unsigned int select_c = select_CS_index(c);
        if (c.count(select_c) == 1)
            c.erase(select_c);
        else
        {
            cout << "Нет такого элемента" << endl;
            //del_item(p, c);
        }
    }
    else
    {
        unsigned int select_p = select_tube_index(p);
        if (c.count(select_p) == 1)
            p.erase(select_p);
        else
        {
            cout << "Нет такого элемента" << endl;
            //del_item(p, c);
        }
    }
}

template<typename T>
using tube_filter = bool(*)(const tube& c, T param);

bool check_by_status(const tube& c, bool param)
{
    return c.status == param;
}

template<typename T>
vector<int> find_tube_by_filter(unordered_map<int, tube>& tubes, tube_filter<T> f, T param)
{
    vector<int> ID;
    for (auto& c : tubes)
    {
        if (f(c.second, param))
            ID.push_back(c.first);
    }
    return ID;
}

template<typename T>
using CS_filter = bool(*)(const CS& c, T param);

bool check_by_name(const CS& c, string param)
{
    return c.name == param;
}

bool check_by_percent(const CS& c, double param)
{
    return (1 - (double)c.number_of_shops_in_work / (double)c.number_of_shops)*100 >= param;
}

template<typename T>
vector<int> find_CS_by_filter(unordered_map<int, CS>& CStations, CS_filter<T> f, T param)
{
    vector<int> ID;
    for (auto& c : CStations)
    {
        if (f(c.second, param))
            ID.push_back(c.first);
    }
    return ID;
}

int main()
{
    setlocale(0, "");

    unordered_map<int, tube> tubes;
    unordered_map<int, CS> CStations;

    while (true)
    {
        print_menu();
        switch (get_pozitive_number(0,12))
        {
        case 1:
        {
            tube t;
            cin >> t;
            tubes.emplace(t.get_MaxID(), t);
            break; //Добавить трубу
        }
        case 2:
        {
            CS c;
            cin >> c;
            CStations.emplace(c.get_MaxID(), c);
            break; //Добавить КС
        }
        case 3:
        {
            for (auto& t : tubes)
                cout << t.second << endl;
            for (auto& c : CStations)
                cout << c.second << endl;
            break; //Просмотр объектов
        }
        case 4:
        {
            if (tubes.size() > 0)
                edit_tube(select_tube(tubes));
            //if (is_data_correct(t))     { edit_tube(select_tube(tubes)); }
            //else    {cout << "Трубы нет" << endl;}
            break; //Редактировать трубу
        }
        case 5:
        {
            if (CStations.size() > 0)
                edit_CS(select_CS(CStations));
            break; //Редактировать КС
        }
        case 6:
        {
            ofstream file_out;
            file_out.open("data.txt", ios::out);
            if (file_out.is_open())
            {
                file_out << tubes.size() << endl;
                for (auto& t : tubes)
                    save_tube(file_out, t.second);
                file_out << CStations.size() << endl;
                for (auto& c : CStations)
                    save_CS(file_out, c.second);
                file_out.close();
            }
            break; //Сохранить
        }
        case 7:
        {
            ifstream file_in;
            file_in.open("data.txt", ios::in);
            if (file_in.is_open())
            {
                int count;
                file_in >> count;
                tubes.clear();
                tubes.reserve(count);
                while (count--)
                {
                    tube t;
                    load_tube(file_in, t);
                    tubes.emplace(t.get_MaxID(), t);
                }
                file_in >> count;
                CStations.clear();
                CStations.reserve(count);
                while (count--)
                {
                    CS c;
                    load_CS(file_in, c);
                    CStations.emplace(c.get_MaxID(), c);
                }
                file_in.close();
            }
            break; //Загрузить
        }
        case 8:
        {
            if ((CStations.size() + tubes.size()) > 0)
                del_item(tubes, CStations);
            else
            {
                cout << "Нет элементов для удаления" << endl;
            }
            break;
        }
        case 9:
        {
            tubes.clear();
            CStations.clear();
        }
        case 10:
        {
            cout << "Введите 0 для просмотра нерабочих труб, 1 - для работающих" << endl;
            bool status = false;
            status = get_pozitive_number(0, 1);
            for (int i : find_tube_by_filter(tubes, check_by_status, status))
                cout << tubes[i] << endl;
            break;//Фильтр труб по состоянию
        }
        case 11:
        {
            cout << "Введите название" << endl;
            string name = "Unknown";
            cin >> name;
            for (int i : find_CS_by_filter(CStations, check_by_name, name))
                cout << CStations[i] << endl;
            break;//Фильтр КС по названию
        }
        case 12:
        {
            cout << "Введите минимальный процент незадействованных цехов" << endl;
            double percent = 0;
            percent = get_pozitive_number(0.0, 100.0);
            for (int i : find_CS_by_filter(CStations, check_by_percent, percent))
                cout << CStations[i] << endl;
            break;//Фильтр КС по проценту
        }
        case 0:
        {
            return 0; //Выход
        }
        default:
        {
            cout << "Ошибка, введена несуществующая команда" << endl;
        }
        }
    }
}