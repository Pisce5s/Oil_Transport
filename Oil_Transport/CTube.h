#pragma once
#include <iostream>
class tube
{
    int id;
    static int MaxID;
public:
    double length;
    double diameter;
    bool status;

    tube();
    tube(const tube& t);
    //~tube();

    static int get_MaxID();

    int get_ID() const;
    void set_ID(int ID);

    friend std::ostream& operator << (std::ostream& out, const tube& p);
    friend std::istream& operator >> (std::istream& in, tube& p);
};