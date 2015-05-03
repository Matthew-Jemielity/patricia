/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test Atende 01
 * \date        05/03/2015 21:57:30
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
    assert(EEXIST == db.add(0x7F000001, 24));
    assert(24 == db.check(0x7F000023));
    assert(ENODATA == db.del(0x7F000001, 23));
    assert(0 == db.del(0x7F000001, 24));

    return 0;
}

