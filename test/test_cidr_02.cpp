/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       CIDR test 02
 * \date        04/30/2015 18:15:39
 * \file        test_cidr_02.cpp
 * \version     1.0
 *
 *
 **/

#include <cassert>
#include <cidr.h>

int main(int argc, char * args[])
{
    (void) argc; (void) args;

    CIDR const prefix1(0x7F000001, -1);
    CIDR const prefix2(0x7F000001, 0);
    CIDR const prefix3(0x7F000001, 32);
    CIDR const prefix4(0x7F000001, 33);

    assert(0 == prefix1.len());
    assert(0 == prefix2.len());
    assert(32 == prefix3.len());
    assert(32 == prefix4.len());

    return 0;
}

