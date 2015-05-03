/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       IP prefix management.
 * \date        05/03/2015 21:17:26
 * \file        atende.h
 * \version     1.0
 *
 *
 **/

#include <patricia.h>

/**
 * \brief Manages IP prefixes (IP address/mask).
 */
class Atende
{
public:
    /**
     * \brief Adds IP prefix to the container.
     * \param ip IP base as 32bit uint, 127.0.0.1 -> 0x7F000001
     * \param mask Bit mask, [0..32].
     * \return Status code, zero on success, else errno-compatible code.
     *
     * If mask is lower than zero it will become zero. Mask higher than 32
     * will be changed to 32. Adding exisiting prefix doesn't change contents
     * of the container.
     * Possible status codes:
     * 1. 0 - success, ip prefix added to container;
     * 2. ENOMEM - failed allocation when copying ip prefix to trie;
     * 3. EEXIST - prefix already exists in the container.
     */
    int add(unsigned int ip, char mask);
    /**
     * \brief Removes an existing prefix form the container.
     * \param ip IP base, same as in add().
     * \param mask Bit mask, same as in add().
     * \return Status code, zero on success, else errno-compatible code.
     *
     * Similarly to add, mask must be in range [0..32]. Removal of prefix
     * containing more specified prefixes (with higher mask) doesn't remove
     * those prefixes. Only specific record is deleted.
     * Possible status codes:
     * 1. 0 - success, ip prefix removed from container;
     * 2. ENODATA - given ip prefix doesn't exist in the container.
     */
    int del(unsigned int ip, char mask);
    /**
     * \brief Checks for routing rules for given IP address.
     * \param ip IP address as 32bit uint, 127.0.0.1 -> 0x7F000001.
     * \return Bit mask [0..32] on success, -1 on error.
     *
     * -1 will be returned if no routing rule exists to handle given IP
     *  address. Otherwise the bit mask of the routing rule found will
     *  be returned. The routing rule will be the most specific possible
     *  one (with highest mask value).
     */
    char check(unsigned int ip);

private:
    Patricia container;
};

