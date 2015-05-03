/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test CIDR 04
 * \date        04/30/2015 20:20:41
 * \file        test_cidr_04.cpp
 * \version     1.0
 *
 *
 **/

#include <cassert>
#include <cidr.h>

int main(int argc, char * args[])
{
    (void) argc; (void) args;

    CIDR const prefix(0x7F000001);

    assert(32 == prefix.len());
    assert(false == prefix.bit(0U));
    assert(true == prefix.bit(1U));
    assert(false == prefix.bit(30U));
    assert(true == prefix.bit(31U));

    return 0;
}

