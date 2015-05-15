/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test trieable 01
 * \date        05/02/2015 11:23:30 AM
 * \file        test_trieable_01.cpp
 * \version     1.0
 *
 *
 **/

#include <cassert>
#include <cidr.h>
#include <trieable.h>

int main(int argc, char * args[])
{
    (void) argc; (void) args;

    Trieable * t1 = new CIDR(0x7F000001, 30);
    Trieable * t2 = t1->copy();
    Trieable * t3 = new CIDR(0x7F000001, 29);
    Trieable * t4 = new CIDR(0x7F000002, 32);
    Trieable * t5 = new CIDR(0x7F000001, 32);
    assert((NULL!=t1) && (NULL!=t2) && (NULL!=t3) && (NULL!=t4) && (NULL!=t5));
    Trieable::difference result;

    result = t1->diff(*t2);
    assert(false == result.diff);
    result = t1->diff(*t3);
    assert((true == result.diff) && (29 == result.bit));
    result = t1->diff(*t1);
    assert(false == result.diff);
    result = t4->diff(*t5);
    assert((true == result.diff) && (30 == result.bit));
    result = t4->diff(*t5, 33);
    assert(false == result.diff);

    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete t5;
    return 0;
}

