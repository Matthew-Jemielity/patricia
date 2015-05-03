/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test Atende 06
 * \date        05/03/2015 22:29:30
 * \file        test_atende_06.cpp
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

    for(unsigned int i = 0; i < 256; ++i)
    {
        assert(0 == db.add(0x7F000000 + i, 32));
    }

    for(unsigned int i = 0; i < 256; ++i)
    {
        assert(32 == db.check(0x7F000000 + i));
    }

    return 0;
}

