// Oil_Transport.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

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

int input_correct_number(int min, int max)
{
    unsigned short int x;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите номер комманды\n";
        cin >> x;
    } while (cin.fail() || x < min || x > max);
    return x;
}

int main()
{
    setlocale(0, "");
    while (true)
    {
        print_menu();
        switch (input_correct_number(0,7))
        {
        case 1:
        {
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
