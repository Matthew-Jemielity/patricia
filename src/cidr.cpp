/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Definitions of CIDR helper functions.
 * \date        04/30/2015 18:22:36
 * \file        cidr.cpp
 * \version     1.5
 **/

#include <algorithm>
#include <cidr.h>
#include <cstddef>

CIDR::CIDR(unsigned int const ip) : base(ip), mask(32U)
{
    /* do nothing */
}

CIDR::CIDR(unsigned int const ip, char const mask)
    : base(ip), mask(std::max(0, std::min(static_cast<int>(mask), 32)))
{
    /* do nothing */
}

CIDR::~CIDR()
{
    /* do nothing */
}

CIDR *
CIDR::copy() const
{
    return new CIDR(*this);
}

bool
CIDR::bit(std::size_t const position) const
{
    return (1U == ((this->base >> (31U - position)) & 1U));
}

std::size_t
CIDR::len() const
{
    return static_cast<std::size_t>(this->mask);
}

