#pragma once
#include <string>
#include <iostream>
class CS
{
public:
    std::string name;
    int number_of_shops;
    int number_of_shops_in_work;
    double efficiency;
    CS();
    CS(std::string name);
    CS(const CS& c);
    ~CS();
    std::string get_name() const;
    void set_name(std::string);
};

