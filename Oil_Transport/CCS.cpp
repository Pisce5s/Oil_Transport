#include "CCS.h"
using namespace std;

CS::CS()
{
    cout << "CS::CS()" << endl;
    //number_of_shops = 0;
    //number_of_shops_in_work = 0;
    //efficiency = 0;
    //name = "Неизвестно";
}

CS::CS(std::string name)
{
    //name = name;
}

CS::CS(const CS& c)
{
    cout << "CS::CS(const CS& c)" << endl;
}

CS::~CS()
{
    cout << "CS::~CS()" << endl;
}

std::string CS::get_name() const
{
    return name;
}

void CS::set_name(std::string new_name)
{
    name = new_name;
}
