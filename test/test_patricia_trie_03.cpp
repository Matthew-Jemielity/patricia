/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test patricia trie 03
 * \date        05/02/2015 10:48:08
 * \file        test_patricia_trie_03.cpp
 * \version     1.1
 *
 *
 **/

#include <cassert>
#include <cerrno>
#include <cstddef>
#include <patricia.h>
#include <trieable.h>

class trieable_uchar : public Trieable
{
public:
    trieable_uchar(unsigned char i, unsigned char l) : i(i), l(l) {}
    virtual ~trieable_uchar() {}
    virtual trieable_uchar * copy() const
    { return new trieable_uchar(*this); }
    virtual bool bit(std::size_t const position) const
    { return (1U == ((this->i >> (7U - position)) & 1U));}
    virtual std::size_t len() const
    { return static_cast<std::size_t>(this->l); }
private:
    unsigned char i;
    unsigned char l;
};

int main()
{
    Patricia trie;

    for(unsigned int i = 0; i < 2; ++i)
    {
        trieable_uchar t(i << 7, 1);
        assert(0 == trie.insert(t).status);
    }

    for(unsigned int i = 0; i < 4; ++i)
    {
        trieable_uchar t(i << 6, 2);
        assert(0 == trie.insert(t).status);
    }

    for(unsigned int i = 0; i < 8; ++i)
    {
        trieable_uchar t(i << 5, 3);
        assert(0 == trie.insert(t).status);
    }

    for(unsigned int i = 0; i < 16; ++i)
    {
        trieable_uchar t(i << 4, 4);
        assert(0 == trie.insert(t).status);
    }

    for(unsigned int i = 0; i < 32; ++i)
    {
        trieable_uchar t(i << 3, 5);
        assert(0 == trie.insert(t).status);
    }

    for(unsigned int i = 0; i < 64; ++i)
    {
        trieable_uchar t(i << 2, 6);
        assert(0 == trie.insert(t).status);
    }

    for(unsigned int i = 0; i < 128; ++i)
    {
        trieable_uchar t(i << 1, 7);
        assert(0 == trie.insert(t).status);
    }

    for(unsigned int i = 0; i < 256; ++i)
    {
        trieable_uchar t(i, 8);
        assert(0 == trie.insert(t).status);
    }

    for(unsigned int i = 0; i < 256; ++i)
    {
        trieable_uchar t(i, 8);
        assert(0 == trie.search(t).status);
    }

    for(unsigned int i = 0; i < 128; ++i)
    {
        trieable_uchar t(i << 1, 7);
        assert(0 == trie.remove(t).status);
    }

    for(unsigned int i = 0; i < 256; ++i)
    {
        trieable_uchar t(i, 8);
        assert(0 == trie.remove(t).status);
    }

    return 0;
}

