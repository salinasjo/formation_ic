#include "include/test.h"

#include <iostream>

using namespace std;

Test::Test()
{
    //ctor
    cout << "Ctor Test" << endl;
}

Test::~Test()
{
    //dtor
    //cout << "Dtor Test" << endl;
}

Test::Test(unsigned int i)
{
    _Counter = i;
}
