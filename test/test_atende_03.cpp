/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test Atende 03
 * \date        05/03/2015 22:13:30
 * \file        test_atende_03.cpp
 * \version     1.0
 *
 *
 **/

#include <atende.h>
#include <cassert>
#include <cerrno>
#include <cstdlib>
#include <ctime>

int main(int argc, char * args[])
{
    (void) argc; (void) args;

    Atende db;

    assert(0 == db.add(0x00000000, 0));

    std::srand(std::time(0));
    for(unsigned int i = 0; i < 10000000; ++i)
    {
        assert(0 == db.check(std::rand()));
    }

    return 0;
}

