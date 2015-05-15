/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Data structures for CIDR IP notation.
 * \date        04/30/2015 18:12:18
 * \file        cidr.h
 * \version     1.6
 *
 * http://en.wikipedia.org/wiki/Classless_Inter-Domain_Routing#CIDR_notation
 **/

#ifndef CIDR_H__
# define CIDR_H__

# include <cstddef>
# include <trieable.h>

/**
 * \brief Describes IP address range according to CIDR notation.
 */
class CIDR : public Trieable
{
public:
    /**
     * \brief Construct a CIDR notation object with default mask of 32.
     * \param ip Base address, encoding: 127.0.0.1 -> 0x7F000001.
     */
    explicit CIDR(unsigned int const ip);
    /**
     * \brief Construct a CIDR notation object from passed base and mask.
     * \param ip Base address, encoding: 127.0.0.1 -> 0x7F000001.
     * \param mask Mask; values lower than 0 -> 0, higher than 32 -> 32.
     */
    CIDR(unsigned int const ip, char const mask);
    virtual ~CIDR();
    /* default copy constructor and assignment operator are sufficient */
    /**
     * \brief A "virtual copy contructor".
     * \return Pointer to a newly allocated copy of this object.
     */
    virtual CIDR* copy() const;
    /**
     * \see Trieable::bit
     */
    virtual bool bit(std::size_t const position) const;
    /**
     * \see Trieable::len
     */
    virtual std::size_t len() const;

private:
    /** \brief Base IP address, i.e. 127.0.0.1 encoded as 32bit 0x7F000001. */
    unsigned int base;
    /** \biref Mask, values range from 0 to 32 */
    unsigned int mask:6;
};

#endif /* CIDR_H__ */

