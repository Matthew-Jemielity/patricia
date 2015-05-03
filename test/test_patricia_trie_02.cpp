/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Test patricia trie 02
 * \date        05/02/2015 21:48:08
 * \file        test_patricia_trie_02.cpp
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
    unsigned char i;
    unsigned char l;
};

int main()
{
    Patricia trie;
    trieable_uchar t1(0x80, 1);
    trieable_uchar t2(0xC0, 2);
    trieable_uchar t3(0xE0, 3);
    trieable_uchar t4(0xF0, 4);
    assert(0 == trie.insert(t1).status);
    assert(0 == trie.insert(t2).status);
    assert(0 == trie.insert(t3).status);
    assert(0 == trie.insert(t4).status);

    Patricia::search_status_s found;

    found = trie.search(t1);
    assert((0 == found.status) && (1 == found.result->len()));
    found = trie.search(t2);
    assert((0 == found.status) && (2 == found.result->len()));
    found = trie.search(t3);
    assert((0 == found.status) && (3 == found.result->len()));
    found = trie.search(t4);
    assert((0 == found.status) && (4 == found.result->len()));

    trieable_uchar t5(0xF8, 5);
    found = trie.search(t5);
    assert((EEXIST == found.status) && (4 == found.result->len()));

    trieable_uchar t6(0x00, 1);
    assert(ENODATA == trie.search(t6).status);

    trieable_uchar t7(0x00, 0);
    assert(ENODATA == trie.search(t7).status);
    trie.insert(t7);
    assert(0 == trie.search(t7).status);

    found = trie.search(t6);
    assert((EEXIST == found.status) && (0 == found.result->len()));

    assert(0 == trie.remove(t4).status);
    found = trie.search(t4);
    assert((EEXIST == found.status) && (3 == found.result->len()));

    assert(0 == trie.remove(t7).status);
    found = trie.search(t6);
    assert((ENODATA == found.status) && (NULL == found.result));

    trieable_uchar t8(0xAA,8);
    assert(0 == trie.insert(t8).status);
    trieable_uchar t9(0xAB,8);
    found = trie.search(t9);
    assert((EEXIST == found.status) && (1 == found.result->len()));

    return 0;
}

