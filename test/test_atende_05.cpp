/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test Atende 05
 * \date        05/03/2015 22:25:30
 * \file        test_atende_05.cpp
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

    for(unsigned int i = 0; i < 33; ++i)
    {
        assert(0 == db.add(0x7F000001, i));
    }
    assert(32 == db.check(0x7F000001));

    return 0;
}

