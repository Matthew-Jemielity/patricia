/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test Atende 02
 * \date        05/03/2015 21:59:30
 * \file        test_atende_01.cpp
 * \version     1.0
 *
 *
 **/

#include <atende.h>
#include <cassert>
#include <cerrno>

int main(int argc, char * args[])
{
    (void) argc; (void) args;

    Atende db;

    assert(0 == db.add(0x7F000001, 24));
    assert(0 == db.add(0x7F000001, 32));
    assert(24 == db.check(0x7F000023));
    assert(32 == db.check(0x7F000001));
    assert(-1 == db.check(0x7F000101));

    return 0;
}

