/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test patricia trie 07
 * \date        05/03/2015 23:08:08
 * \file        test_patricia_trie_07.cpp
 * \version     1.0
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
    unsigned int i;
    unsigned char l;
};

int main()
{
    Patricia trie;

    trieable_uchar t1(0x00, 1);
    trieable_uchar t2(0x00, 3);
    trieable_uchar t3(0x00, 2);

    assert(0 == trie.insert(t1).status);
    assert(0 == trie.insert(t2).status);
    trie.print();
    assert(0 == trie.insert(t3).status);
    trie.print();

    return 0;
}

