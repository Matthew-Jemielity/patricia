/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test patricia trie 05
 * \date        05/03/2015 19:44:08
 * \file        test_patricia_trie_05.cpp
 * \version     1.0
 *
 *
 **/

#include <cassert>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <patricia.h>
#include <trieable.h>

class trieable_uint : public Trieable
{
public:
    trieable_uint(unsigned int i, unsigned char l) : i(i), l(l) {}
    virtual ~trieable_uint() {}
    virtual trieable_uint * copy() const
    { return new trieable_uint(*this); }
    virtual bool bit(std::size_t const position) const
    { return (1U == ((this->i >> (31U - position)) & 1U));}
    virtual std::size_t len() const
    { return static_cast<std::size_t>(this->l); }
private:
    unsigned int i;
    unsigned char l;
};

int main()
{
    Patricia trie;

    std::srand(std::time(0));
    for(unsigned int i = 0; i < 10000000; ++i)
    {
        unsigned int val = std::rand();
        unsigned int len = std::rand() % 33;
        trieable_uint t(val, len);
        Patricia::status result = trie.insert(t);
        assert((0 == result.status) || (EEXIST == result.status));
    }

    return 0;
}

