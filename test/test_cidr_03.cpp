/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test CIDR 03
 * \date        04/30/2015 18:41:20
 * \file        test_cidr_03.cpp
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

    Trieable * const t = new CIDR(0x7F000001, 23);
    assert(NULL != t);

    assert(false == t->bit(0U));
    assert(true == t->bit(1U));
    assert(23U == t->len());

    delete t;
    return 0;
}

