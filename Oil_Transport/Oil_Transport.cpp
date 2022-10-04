#include <iostream>
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
        << "0.Выход" << endl;
}

int input_correct_number()
{
    unsigned short int x;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите положительное число\n";
        cin >> x;
    } while (cin.fail() || (x <= 0));
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

tube input_tube()
{
    tube t;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите длину: ";
        cin >> t.length;
    } while (cin.fail() || t.length <= 0);
    cout << "Введите диаметр: ";
    cin >> t.diameter;
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0. ";
    cin >> t.status; // ALERT! RED SPY INCAMING
    return t;
}

void print_tube(const tube& t)
{
    cout << "Длина = " << t.length << endl
        << "Диаметр = " << t.diameter << endl
        << "Состояние работы: " << t.status << endl;
}

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

int main()
{
    setlocale(0, "");
    tube t;
    /*vector <tube> tubes;*/
    while (true)
    {
        print_menu();
        switch (input_correct_number(/*0,7*/))
        {
        case 1:
        {
            t = input_tube();
            print_tube(t);
            break; //Добавить трубу
        }
        case 2:
        {
            break; //Добавить КС
        }
        case 3:
        {
            print_tube(t);
            break; //Просмотр объектов
        }
        case 4:
        {
            edit_tube(t);
            break; //Редактировать трубу
        }
        case 5:
        {
            break; //Редактировать КС
        }
        case 6:
        {
            save_tube(t);
            break; //Сохранить
        }
        case 7:
        {
            t = load_tube();
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
