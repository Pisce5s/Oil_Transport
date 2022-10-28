#pragma once
#include <iostream>
class tube
{
    int id;
public:
    static int MaxID;
    double length;
    double diameter;
    bool status;

    tube();
    tube(const tube& t);
    //~tube();

    int get_MaxID() const;

    friend std::ostream& operator << (std::ostream& out, const tube& p);
    friend std::istream& operator >> (std::istream& in, tube& p);
};