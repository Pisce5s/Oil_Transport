#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "CTube.h"
#include "CCS.h"
#include <unordered_map>
#include "utils.h"
#include <algorithm>

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
        << "13.Пакетное редактирование" << endl
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
    cout << "Введите индекс(ID): ";
    tube crutch;
    unsigned int index = get_pozitive_number(0u, (unsigned int)(crutch.get_MaxID()));
    //unsigned int index = get_pozitive_number(1, p.size());
    return p[index];
}

CS& select_CS(unordered_map<int, CS>& c)
{
    cout << "Введите индекс(ID): ";
    tube crutch;
    unsigned int index = get_pozitive_number(0u, (unsigned int)(crutch.get_MaxID()));
    //unsigned int index = get_pozitive_number(1, c.size());
    return c[index];
}

unsigned int select_tube_index(unordered_map<int, tube>& p)
{
    cout << "Введите индекс(ID): ";
    tube crutch;
    unsigned int index = get_pozitive_number(0u, (unsigned int)(crutch.get_MaxID()));
    return (index);
}

unsigned int select_CS_index(unordered_map<int, CS>& c)
{
    cout << "Введите индекс(ID): ";
    tube crutch;
    unsigned int index = get_pozitive_number(0u, (unsigned int)(crutch.get_MaxID()));
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

void change(tube& t, const bool& new_status) 
{
    if (new_status == 0)
        t.status = 0;
    else
        t.status = 1;
}

void change(CS& c, const bool& edit)
{
    if (edit == 1)
    {
        if (c.number_of_shops_in_work < c.number_of_shops)
            c.number_of_shops_in_work++;
    }
    else
    {
        if (c.number_of_shops_in_work > 0)
            c.number_of_shops_in_work--;
    }
}

void batch_editing(unordered_map<int, tube>& t)
{
    cout << "Введите 1 для редактирования всех найдённых элементов, для дальнейшего выбора введите 0" << endl;
    bool choiсe = get_pozitive_number(0, 1);
    if (choiсe)
    {
        cout << "Изменение состояния: 1 - выбранные работают, 0 - в нерабочем состоянии" << endl;
        bool choiсe_status = get_pozitive_number(0, 1);
        for (auto& a : t)
            change(a.second, choiсe_status);
    }
    else
    {
        vector<int> ID;
        cout << "Введите ID нужных труб, для завершения выбора введите -1" << endl;
        unsigned int select;
        while (1)
        {
            tube crutch;
            select = get_pozitive_number(-1, (int)(crutch.get_MaxID()));
            if (select == -1)
                break;
            if (t.count(select) == 1)
            {
                if (!(std::find(ID.begin(), ID.end(), select) != ID.end()))
                    ID.push_back(select);
                //else
                //ID.push_back(select);
            }
            else
            {
                cout << "Нет такого элемента" << endl;
            }
        }

        if (ID.size() > 0)
        {
            cout << "Изменение состояния: 1 - выбранные работают, 0 - в нерабочем состоянии" << endl;
            bool choiсe_status = get_pozitive_number(0, 1);
            for (const int& i : ID)
                change(t[i], choiсe_status);
        }
        else
            cout << "Не выбрано элементов для редактирования" << endl;
    }
}

void batch_editing(unordered_map<int, CS>& t)
{
    cout << "Введите 1 для редактирования всех найдённых элементов, для дальнейшего выбора введите 0" << endl;
    bool choiсe = get_pozitive_number(0, 1);
    if (choiсe)
    {
        cout << "Изменение состояния: 1 - добавить всем рабочий цех, 0 - убавить" << endl;
        bool choiсe_status = get_pozitive_number(0, 1);
        for (auto& a : t)
            change(a.second, choiсe_status);
    }
    else
    {
        vector<int> ID;
        cout << "Введите ID нужных КС, для завершения выбора введите -1" << endl;
        unsigned int select;
        while (1)
        {
            CS crutch;
            select = get_pozitive_number(-1, (int)(crutch.get_MaxID()));
            if (select == -1)
                break;
            if (t.count(select) == 1)
                if (!(std::find(ID.begin(), ID.end(), select) != ID.end()))
                {
                    ID.push_back(select);
                }
            else
            {
                cout << "Нет такого элемента" << endl;
            }
        }

        if (ID.size() > 0)
        {
            cout << "Изменение состояния: 1 - добавить всем рабочий цех, 0 - убавить" << endl;
            bool choiсe_status = get_pozitive_number(0, 1);
            for (const int& i : ID)
                change(t[i], choiсe_status);
        }
        else
            cout << "Не выбрано элементов для редактирования" << endl;
    }
}

int main()
{
    setlocale(0, "");

    unordered_map<int, tube> tubes;
    unordered_map<int, CS> CStations;

    vector<int> tubes_filt;
    vector<int> CStations_filt;

    while (true)
    {
        print_menu();
        switch (get_pozitive_number(0,13))
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
            cout << "-----ТРУБЫ-----" << endl;
            for (auto& t : tubes)
                cout << t.second << endl;
            cout << "-------КС-------" << endl;
            for (auto& c : CStations)
                cout << c.second << endl;
            break; //Просмотр объектов
        }
        case 4:
        {
            if (tubes.size() > 0)
                edit_tube(select_tube(tubes));
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
            break;
        }
        case 10:
        {
            cout << "Введите 0 для просмотра нерабочих труб, 1 - для работающих" << endl;
            bool status = false;
            status = get_pozitive_number(0, 1);
            tubes_filt.clear();
            for (int i : find_tube_by_filter(tubes, check_by_status, status))
            {
                cout << tubes[i] << endl;
                tubes_filt.push_back(i);
            }
            break;//Фильтр труб по состоянию
        }
        case 11:
        {
            cout << "Введите название" << endl;
            string name = "Unknown";
            cin >> name;
            CStations_filt.clear();
            for (int i : find_CS_by_filter(CStations, check_by_name, name))
            {
                cout << CStations[i] << endl;
                CStations_filt.push_back(i);
            }
            break;//Фильтр КС по названию
        }
        case 12:
        {
            cout << "Введите минимальный процент незадействованных цехов" << endl;
            double percent = 0;
            percent = get_pozitive_number(0.0, 100.0);
            CStations_filt.clear();
            for (int i : find_CS_by_filter(CStations, check_by_percent, percent))
            {
                cout << CStations[i] << endl;
                CStations_filt.push_back(i);
            }
            break;//Фильтр КС по проценту
        }
        case 13:
        {
            cout << "Введите 1 для редактирования отфильтрованных элементов, для работы со всеми введите 0" << endl;
            bool choice_filter = get_pozitive_number(0, 1);
            unordered_map<int, tube> tubes_to_do;
            unordered_map<int, CS> CS_to_do;
            if (choice_filter)
            {
                
            }
            else
            {
                tubes_to_do = tubes;
                CS_to_do = CStations;
            }
            if (tubes.size() + CStations.size() > 0)
            {
                cout << "Введите 1 для редактирования КС, для труб введите 0" << endl;
                bool choiсe = get_pozitive_number(0, 1);
                if (choiсe)
                    batch_editing(CStations);
                else
                    batch_editing(tubes);
            }
            else
                cout << "Нет элементов для пакетного редактирования" << endl;
            break;//Пакетное ред.
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