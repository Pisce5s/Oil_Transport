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
        << "8.Удалить" << endl
        << "0.Выход" << endl
        << "Введите комманду" << endl;
}

//bool is_data_correct(const tube& t)
//{
//    if ((t.length < 0) or (t.diameter < 0) or ((t.status != 0) and (t.status != 1)))
//    { return 0; }
//    else    { return 1; }
//}

//bool is_data_correct(const CS& c)
//{
//    if ((c.number_of_shops < 0) or (c.number_of_shops_in_work < 0) or (c.number_of_shops_in_work > c.number_of_shops))
//    { return 0; }
//    else    { return 1; }
//}

void edit_tube(tube& t)
{
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0. ";
    t.status = get_pozitive_number(0, 1);
}

void save_tube(ofstream& file_out, const tube& t)
{
    //if (is_data_correct(t))
    //{
        file_out << t.length << endl << t.diameter << endl << t.status << endl;
    //}
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
    unsigned int index = get_pozitive_number(1u, static_cast<unsigned int>(p.size()));
    //unsigned int index = get_pozitive_number(1, p.size());
    return p[index-1];
}

CS& select_CS(unordered_map<int, CS>& c)
{
    cout << "Введите индекс: ";
    unsigned int index = get_pozitive_number(1u, static_cast<unsigned int>(c.size()));
    //unsigned int index = get_pozitive_number(1, c.size());
    return c[index - 1];
}

unsigned int select_tube_index(unordered_map<int, tube>& p)
{
    cout << "Введите индекс: ";
    unsigned int index = get_pozitive_number(1u, static_cast<unsigned int>(p.size()));
    return (index - 1);
}

unsigned int select_CS_index(unordered_map<int, CS>& c)
{
    cout << "Введите индекс: ";
    unsigned int index = get_pozitive_number(1u, static_cast<unsigned int>(c.size()));
    return (index - 1);
}

void del_item(unordered_map<int, tube>& p, unordered_map<int, CS>& c)
{
    bool select_c;
    cout << "Введите: 0 - для удаления трубы, 1 - для удаления КС" << endl;
    select_c = get_pozitive_number(false, true);
    if (select_c)
    {
        c.erase(select_CS_index(c));
    }
    else
    {
        p.erase(select_tube_index(p));
    }
}

int main()
{
    setlocale(0, "");
    //vector <tube> tubes;
    //vector <CS> CStations;

    unordered_map<int, tube> tubes;
    unordered_map<int, CS> CStations;

    //emplace

    while (true)
    {
        print_menu();
        switch (get_pozitive_number(0,8))
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
        case 0:
        {
            return 0; //Выход
        }
        default:
        {
            cout << "Ошибка, введена несуществующая манда" << endl;
        }
        }
    }
}