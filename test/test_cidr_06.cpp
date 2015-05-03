/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test cidr 06
 * \date        05/02/2015 11:41:30 AM
 * \file        test_cidr_06.cpp
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

    CIDR c1(0x7F000001, 30);
    CIDR c2(0x7F000001, 29);
    CIDR c3(0x7F000002, 32);
    CIDR c4(0x7F000001, 32);
    Trieable::diff_result result;

    result = c1.diff(c1);
    assert(false == result.diff);
    result = c1.diff(c2);
    assert((true == result.diff) && (29 == result.bit));
    result = c3.diff(c4);
    assert((true == result.diff) && (30 == result.bit));
    result = c3.diff(c4, 33);
    assert(false == result.diff);

    return 0;
}

