/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Interface for class usable in a trie.
 * \date        04/30/2015 18:34:46
 * \file        trieable.h
 * \version     1.2
 *
 *
 **/

#ifndef TRIEABLE_H__
# define TRIEABLE_H__

#include <cstddef>

class Trieable
{
public:
    virtual ~Trieable() {}
    virtual Trieable* copy() const = 0;
    /**
     * \brief Get value of bit at given position in the data.
     * \param position Position from beginning of data to get.
     * \return Value is true if bit is set, false otherwise.
     * \remark Given position must be in [0..len()) else result is undefined.
     *
     * Implementation should decide what is the beginning of data.
     * This choice must be consistent for all objects.
     */
    virtual bool bit(std::size_t const position) const = 0;
    /**
     * \brief Type returned by diff method.
     *
     * If different is false, then value of bit is unspecified.
     */
    typedef struct
    {
        /**
         * True if two Trieable objects differ.
         */
        bool diff;
        /**
         * Position of first differing bit.
         */
        std::size_t bit;
    }
    difference;
    /**
     * \brief Tests whether two Trieable objects differ.
     * \param object Object to compare with this object.
     * \return difference structure.
     * \see difference
     *
     * If objects have different lengths, then comparison will stop after
     * lower length is reached. Differing lengths mean that difference will
     * be true, but bitwise comparison will still be done. If bits are the
     * same for entire lower length, then differing bit will be set to the
     * value of lower length. If objects do not differ then returned
     * boolean will be false and value of returned bit is unspecified.
     * If start position is greater that lower length, then only length
     * comparison will be done.
     */
    difference diff(Trieable const& object) const;

    /**
     * \brief Tests whether two Trieable objects differ.
     * \param object Object to compare with this object.
     * \param start Bit from which to begin comparison, zero by default.
     * \return difference structure.
     * \see difference
     *
     * If objects have different lengths, then comparison will stop after
     * lower length is reached. Differing lengths mean that difference will
     * be true, but bitwise comparison will still be done. If bits are the
     * same for entire lower length, then differing bit will be set to the
     * value of lower length. If objects do not differ then returned
     * boolean will be false and value of returned bit is unspecified.
     * If start position is greater that lower length, then only length
     * comparison will be done.
     */
    difference diff(Trieable const& object, std::size_t start) const;
    /**
     * \brief Total bit length of data held in this object.
     * \return Non-zero count of bits of data in this object.
     *
     * It may differ per object.
     */
    virtual std::size_t len() const = 0;
};

#endif /* TRIEABLE_H__ */

