// Oil_Transport.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

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
        << "0.Выход" << endl;
}

struct tube
{
    float length;
    float diameter;
    bool status;
};

struct CS
{
    string name;
    int number_of_shops;
    int number_of_shops_in_work;
    float efficiency;
};

tube input_tube()
{
    tube t;
    cout << "Введите длину: ";
    cin >> t.length;
    cout << "Введите диаметр: ";
    cin >> t.diameter;
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0. ";
    cin >> t.status; // ALERT! RED SPY INCAMING
    return t;
}

void print_tube(tube t)
{
    cout << "Длина = " << t.length << endl
        << "Диаметр = " << t.diameter << endl
        << "Состояние работы: " << t.status << endl;
}

void edit_tube(tube& t)
{
    cout << "Введите новую длину: ";
    cin >> t.length;
    cout << "Введите новый диаметр: ";
    cin >> t.diameter;
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0. ";
    cin >> t.status;
}

int input_correct_number(/*int min, int max*/)
{
    unsigned short int x;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите номер комманды\n";
        cin >> x;
    } while (cin.fail()/* || x < min || x > max*/);
    return x;
}

int main()
{
    setlocale(0, "");
    vector <tube> tubes;
    print_menu();
    while (true)
    {
        switch (input_correct_number(/*0,7*/))
        {
        case 1:
        {
            tube t = input_tube();
            print_tube(t);
            edit_tube(t);
            print_tube(t);
            break; //Добавить трубу
        }
        case 2:
        {
            break; //Добавить КС
        }
        case 3:
        {
            break; //Просмотр объектов
        }
        case 4:
        {
            break; //Редактировать трубу
        }
        case 5:
        {
            break; //Редактировать КС
        }
        case 6:
        {
            break; //Сохранить
        }
        case 7:
        {
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
