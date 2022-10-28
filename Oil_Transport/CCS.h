#pragma once
#include <string>
#include <iostream>
class CS
{
    int id;
public:
    static int MaxID;
    std::string name;
    int number_of_shops;
    int number_of_shops_in_work;
    double efficiency;
    CS();
    //CS(std::string name);
    CS(const CS& c);
    //~CS();
    std::string get_name() const;
    void set_name(std::string);

    int get_MaxID() const;

    friend std::ostream& operator << (std::ostream& out, const CS& p);
    friend std::istream& operator >> (std::istream& in, CS& p);
};

