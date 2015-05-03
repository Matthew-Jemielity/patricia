/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Implementation of IP manager.
 * \date        05/03/2015 21:41:05
 * \file        atende.cpp
 * \version     1.1
 *
 *
 **/

#include <atende.h>
#include <cassert>
#include <cerrno>
#include <cidr.h>
#include <patricia.h>

int
Atende::add(unsigned int ip, char mask)
{
    CIDR prefix(ip, mask);
    return this->container.insert(prefix).status;
}

int
Atende::del(unsigned int ip, char mask)
{
    CIDR prefix(ip, mask);
    return this->container.remove(prefix).status;
}

char
Atende::check(unsigned int ip)
{
    CIDR address(ip);
    Patricia::search_status_s const found = this->container.search(address);
    if(ENODATA == found.status)
    {
        return static_cast<char>(-1);
    }
    assert(NULL != found.result);
    CIDR const * result = dynamic_cast<CIDR const *>(found.result);
    assert(NULL != result); /* CIDR is Trieable subclass */
    return static_cast<char>(result->len());
}

