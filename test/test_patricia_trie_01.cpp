/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test patricia trie 01
 * \date        05/02/2015 21:23:08 PM
 * \file        test_patricia_trie_01.cpp
 * \version     1.0
 *
 *
 **/

#include <cstddef>
#include <patricia.h>
#include <trieable.h>

class trieable_uint : public Trieable
{
public:
    trieable_uint(unsigned int i, unsigned int l) : i(i), l(l) {}
    virtual ~trieable_uint() {}
    virtual trieable_uint * copy() const
    { return new trieable_uint(*this); }
    virtual bool bit(std::size_t const position) const
    { return (1U == ((this->i >> (31U - position)) & 1U));}
    virtual std::size_t len() const
    { return static_cast<std::size_t>(this->l); }
private:
    unsigned int i;
    unsigned int l;
};

int main()
{
    Patricia trie;
    trie.print();
    trieable_uint t1(0x80000000,1);
    trie.insert(t1);
    trie.print();
    trieable_uint t3(0xE0000000,3);
    trie.insert(t3);
    trie.print();
    trieable_uint t2(0xC0000000,2);
    trie.insert(t2);
    trie.print();
    trieable_uint t4(0x80000000,2);
    trie.insert(t4);
    trie.print();
    return 0;
}

