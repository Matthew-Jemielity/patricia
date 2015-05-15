/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Trieable methods implementation.
 * \date        05/02/2015 11:03:03 AM
 * \file        trieable.cpp
 * \version     1.0
 *
 *
 **/

#include <algorithm>
#include <cstddef>
#include <trieable.h>

Trieable::difference
Trieable::diff(Trieable const& object) const
{
    return diff(object, 0U);
}

Trieable::difference
Trieable::diff(Trieable const& object, std::size_t const start) const
{
    bool different = (this->len() != object.len());
    std::size_t const end = std::min(this->len(), object.len());

    std::size_t position;
    for(position = start; position < end; ++position)
    {
        if(this->bit(position) != object.bit(position))
        {
            different = true;
            break;
        }
    }

    difference const result = {different, position};
    return result;
}

