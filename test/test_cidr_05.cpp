/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test CIDR 05.
 * \date        05/01/2015 12:44:21 PM
 * \file        test_cidr_05.cpp
 * \version     1.1
 *
 *
 **/

#include <cassert>
#include <cidr.h>
#include <cstddef>
#include <trieable.h>

int main(int argc, char * args[])
{
    (void) argc; (void) args;

    Trieable * const t1 = new CIDR(0x7F000001, 23);
    assert(NULL != t1);
    Trieable const * const t1_const =t1;
    Trieable * const t2 = t1_const->copy();
    assert(NULL != t2);

    assert(t1_const->len() == t2->len());
    assert(t1_const->bit(0) == t2->bit(0));
    assert(t1_const->bit(1) == t2->bit(1));
    assert(t1_const->bit(31) == t2->bit(31));

    delete t1;
    delete t2;
    return 0;
}

