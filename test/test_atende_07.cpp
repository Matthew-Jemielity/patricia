/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test Atende 07
 * \date        05/03/2015 22:41:30
 * \file        test_atende_07.cpp
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
    assert(0 == db.add(0x7F000001, 30));
    assert(0 == db.del(0x7F000001, 24));

    assert(30 == db.check(0x7F000001));

    return 0;
}

