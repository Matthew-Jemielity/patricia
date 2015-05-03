/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test CIDR 01
 * \date        04/30/2015 18:51:03
 * \file        test_cidr_01.cpp
 * \version     1.2
 *
 *
 **/

#include <cassert>
#include <cidr.h>
#include <cstdio>

int main(int argc, char * args[])
{
    (void) argc; (void) args;

    CIDR const prefix(0x7F000001, 32);

    assert(false == prefix.bit(0U));
    assert(true == prefix.bit(1U));
    assert(true == prefix.bit(2U));
    assert(true == prefix.bit(3U));
    assert(true == prefix.bit(4U));
    assert(true == prefix.bit(5U));
    assert(true == prefix.bit(6U));
    assert(true == prefix.bit(7U));
    assert(false == prefix.bit(8U));
    assert(false == prefix.bit(10U));
    assert(false == prefix.bit(20U));
    assert(false == prefix.bit(30U));
    assert(true == prefix.bit(31U));

    return 0;
}

