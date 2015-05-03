/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Patricia (path-compressed) bitwise trie.
 * \date        04/30/2015 19:57:24
 * \file        patricia.h
 * \version     1.3
 * \see Trieable
 *
 * This patricia trie has been enhanced for specific use with binary prefixes.
 * This includes storage of variable length data and search always trying to
 * return the longest prefix of searched object.
 * Objects compatible with this patricia trie implement class Trieable.
 **/

#ifndef PATRICIA_TRIE_H__
# define PATRICIA_TRIE_H__

#include <cstddef>
#include <trieable.h>

class Patricia
{
public:
    Patricia();
    ~Patricia();

    /**
     * \brief Status structure for basic trie operations.
     */
    typedef struct
    {
        /**
         * \brief Status code.
         *
         * The code is compatible with errno, i.e zero means success,
         * nonzero means failure of some kind. Failure code may be
         * checked for its symbolic name, which will point to type of
         * failure that occured.
         */
        int status;
    }
    status_s;
    /**
     * \brief Inserts copy of given Trieable object into the trie.
     * \param val Trieable object, which will be copied into trie.
     * \return Structure with status: zero - success, else - error code.
     *
     * Note that Trieable value with len() == 0 will be treated as prefix
     * for all other objects, thus always placed in the root node.
     * Possible status codes:
     * 0 - Trieable value successfuly inserted into the trie;
     * ENOMEM - failed allocation for trie node or value copy; trie unchanged;
     * EEXIST - Trieable value already exists in the trie; trie unchanged.
     * EEXIST error code may be treated as success if needed.
     */
    status_s insert(Trieable const& val);
    /**
     * \brief Removes given exact Trieable object from the trie.
     * \param val Exact copy (data and length) of object to remove.
     * \return Structure with status: zero - success, else error code.
     *
     * Note that in case of Trieable value with len() == 0 the data will not
     * be checked. If a value with len() == 0 exists in the root node, it will
     * be removed.
     * Possible status codes:
     * 0 - Trieable value successfuly removed from the trie;
     * ENODATA - Trieable value doesn't exists in the trie; trie unchanged.
     * ENODATA status code may be treated as success if needed.
     */
    status_s remove(Trieable const& val);
    /**
     * \brief Status structure for trie search operation.
     */
    typedef struct
    {
        /**
         * \brief Status code.
         *
         * The code is compatible with errno, i.e zero means success,
         * nonzero means failure of some kind. Failure code may be
         * checked for its symbolic name, which will point to type of
         * failure that occured.
         */
        int status;
        /**
         * \brief Result of search.
         *
         * If exact result is not found, the search will return the Trieable
         * object with prefix closest to the given search term. If no such
         * prefix exists, the result will be NULL.
         * Note that the object remains owner of the pointer. User should not
         * try to free it.
         */
        Trieable const * result;
    }
    search_status_s;
    /**
     * \brief Searches for given Trieable object or its closest prefix.
     * \param val Trieable object to search for.
     * \result Structure containing status code and search result, if any.
     *
     * Possible error codes:
     * 0 - exact Trieable object match found and returned;
     * EEXIST - exact Trieable object not found, but closest prefix found;
     * ENODATA - neither the Trieable object nor any closest prefix was found.
     * In case status code is ENODATA, the result will be NULL. Status code
     * of EEXISTS may be treated as success if needed.
     */
    search_status_s search(Trieable const& val);

    /**
     * \brief Debug function printing current state of the trie.
     */
    void print();

    struct node_s; /* forward declaration */
    typedef struct node_s node;
    struct node_s
    {
        node * parent;
        /**
         * The child[0] points to data branching from parent at position
         * child[0]->branch_bit with bit value at this position equal to zero.
         * Similarly child[1] points to data branching from parent at position
         * child[1]->branch_bit with bit value at this position equal to one.
         */
        node * child[2];
        Trieable * val;
        /**
         * Bit position at which this node starts diverging from parent node.
         */
        std::size_t branch;
    };
private:
    typedef struct
    {
        node root;
    }
    trie;

    trie patricia;
};

#endif /* PATRICIA_TRIE_H__ */

