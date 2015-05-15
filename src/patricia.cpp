/**
 * \author      Mateusz Jemielity matthew.jemielity@gmail.com
 * \brief       Implementation of Patricia Trie.
 * \date        05/01/2015 12:02:03
 * \file        patricia_trie.cpp
 * \version     1.3
 *
 *
 **/

#include <cassert>
#include <cerrno>
#include <cstddef>
#include <patricia.h>

/* for print() */
#include <algorithm>
#include <iostream>
#include <queue>

static inline Patricia::node
fill_node(Patricia::node* const parent, Trieable* const val)
{
  Patricia::node const result = { parent, { NULL, NULL }, val, val->len() };
  return result;
}

/**
 * \brief Find first data node in the trie or return NULL.
 */
static inline Patricia::node*
first_data_node(Patricia::node* node)
{
  while ((NULL != node) && (NULL == node->val))
  {
    node = node->child[(NULL == node->child[0])];
  }
  return node;
}

static inline Patricia::status
insert_at(Patricia::node* const node, Trieable* const val)
{
  assert(NULL == node->val);
  node->val = val;
  Patricia::status const result = { (NULL == val) ? ENOMEM : 0 };
  return result;
}

static Patricia::status
insert_between(
  Patricia::node* const parent,
  Patricia::node* const child,
  Patricia::node* const inserted,
  Trieable* const val
)
{
  assert((NULL != parent)); /* child can be NULL */
  if ((NULL == inserted) || (NULL == val))
  {
    delete inserted;
    delete val;
    Patricia::status const result = { ENOMEM };
    return result;
  }

  parent->child[val->bit(parent->branch)] = inserted;
  *inserted = fill_node(parent, val);
  if (NULL != child)
  {
    Patricia::node const* const data = first_data_node(child);
    assert(NULL != data); /* otherwise child would be NULL */
    assert(val->len() < data->val->len()); /* branch value order in trie */
    inserted->child[data->val->bit(val->len())] = child;
    child->parent = inserted;
  }
  Patricia::status const result = { 0 };
  return result;
}

static Patricia::status
branch_at(
  Patricia::node* const child,
  Patricia::node* const branched,
  Patricia::node* const inserted,
  Trieable* const val
)
{
  assert(NULL != child);
  if ((NULL == branched) || (NULL == inserted) || (NULL == val))
  {
    delete branched;
    delete inserted;
    delete val;
    Patricia::status result = { ENOMEM };
    return result;
  }
  /* find first differing bit for child[] of the new branch node */
  Patricia::node const * const data = first_data_node(child);
  assert(NULL != data); /* otherwise child would be NULL */
  std::size_t const branch = child->parent->branch;
  Trieable::difference const diff = data->val->diff(*val, branch);
  assert(true == diff.diff); /* replacing parent's old child with branch */
  assert((branch < diff.bit) && (diff.bit < child->branch));
  assert(val->bit(branch) == data->val->bit(branch)); /* same prefix */

  child->parent->child[val->bit(branch)] = branched;
  branched->parent = child->parent;
  branched->child[data->val->bit(diff.bit)] = child;
  branched->child[val->bit(diff.bit)] = inserted;
  branched->branch = diff.bit;
  branched->val = NULL;
  child->parent = branched;
  *inserted = fill_node(branched, val);

  Patricia::status const result = { 0 };
  return result;
}

static void
compress_paths(Patricia::node* node)
{
  while (
    (NULL != node ) && (NULL == node->val) /* only nodes w/o vals */
    && (NULL != node->parent) /* can't remove root node */
    /* we can compress only if at most one child is present */
    && ((NULL == node->child[0]) || (NULL == node->child[1]))
  )
  {
    Patricia::node* const child = node->child[(NULL == node->child[0])];
    Patricia::node* const parent = node->parent;
    parent->child[(node != parent->child[0])] = child;
    if (NULL != child) { child->parent = parent; }
    delete node;
    node = parent;
  }
}

typedef struct
{
  int status;
  Patricia::node* prefix;
  Patricia::node* last;
}
internal_search_result;

static internal_search_result
internal_search(Trieable const& val, Patricia::node& root)
{
  /* 0-bit long prefixes match every address */
  if (0 == val.len())
  {
    int const status = (NULL != root.val) ? 0 : ENODATA;
    internal_search_result result = {status, &(root), &(root)};
    return result;
  }

  Patricia::node* current = &root;
  Patricia::node* next = current->child[val.bit(current->branch)];
  /* try to go down as far as possible */
  while ((NULL != next) && (next->branch <= val.len()))
  {
    /*
     * any node in next subtrie must have first next->branch bits
     * with the same values as val bits
     */
    Patricia::node const* const data = first_data_node(next);
    assert(NULL != data); /* else next would be NULL */

    for (std::size_t i = current->branch; i < next->branch; ++i)
    {
      if (data->val->bit(i) != val.bit(i))
      {
        /* goto is a quick way to get out of nested loops */
        goto NO_PREFIX_IN_THIS_BRANCH;
      }
    }
    /* next is a prefix of val */
    current = next;
    if (val.len() <= next->branch) { break; }
    next = next->child[val.bit(next->branch)];
  }
NO_PREFIX_IN_THIS_BRANCH:
  /* current is either root node or node with valid prefix */
  if (NULL == current->val)
  {
    internal_search_result no_prefix = { ENODATA, current, next };
    return no_prefix;
  }
  if (current->branch < val.len())
  {
    internal_search_result prefix = { EEXIST, current, next };
    return prefix;
  }
  internal_search_result match = { 0, current, next };
  return match;
}

Patricia::Patricia()
{
  trie const empty = { { NULL, { NULL, NULL }, NULL, 0 } };
  patricia = empty;
}

Patricia::~Patricia()
{
  node* data;
  while (NULL != (data = first_data_node(&(this->patricia.root))))
  {
    this->remove(*(data->val));
  }
}

Patricia::status
Patricia::insert(Trieable const& val)
{
  /* find biggest prefix of data in val */
  internal_search_result const found =
    internal_search(val, this->patricia.root);
  if (0 == found.status) /* exact match found, val is a duplicate */
  {
    status const result = { EEXIST };
    return result;
  }

  if (0 == val.len()) /* special case for root node */
  {
    assert(ENODATA == found.status); /* or we would have a match */
    return insert_at(found.prefix, val.copy());
  }
  if (NULL == found.last)
  {
    return insert_between(found.prefix, found.last,
        new Patricia::node, val.copy());
  }
  Patricia::node* const data = first_data_node(found.last);
  assert(NULL != data); /* else found.last would be NULL */
  Trieable::difference const diff =
    data->val->diff(val, found.prefix->branch);
  if (val.len() == diff.bit) /* val is a prefix of a node */
  {
    assert(val.len() <= found.last->branch);
    if (val.len() < found.last->branch)
    {
      return insert_between(found.last->parent, found.last,
          new Patricia::node, val.copy());
    }
    assert(NULL == found.last->val); /* or we would find a match */
    return insert_at(found.last, val.copy());
  }
  return branch_at(found.last, new Patricia::node,
      new Patricia::node, val.copy());
}

Patricia::status
Patricia::remove(Trieable const& val)
{
  internal_search_result const found =
    internal_search(val, this->patricia.root);
  if (0 != found.status) /* exact match doesn't exist in the trie */
  {
    status const result = { ENODATA };
    return result;
  }

  assert(NULL != found.prefix); /* because we have a match */
  delete found.prefix->val;
  found.prefix->val = NULL;
  compress_paths(found.prefix);

  status result = {0};
  return result;
}

Patricia::search_status
Patricia::search(Trieable const& val)
{
  internal_search_result const found =
    internal_search(val, this->patricia.root);
  /* internal search returned either root or prefix node */
  search_status result =
    { found.status, (ENODATA == found.status) ? NULL : found.prefix->val };
  return result;
}

void
Patricia::print() const
{
  std::queue<node const*> nodes;
  nodes.push(&(this->patricia.root));
  std::cout <<
      "[PARENT|SELF|BRANCH|CHILD[0]|CHILD[1]|VAL][FIRST 8 VAL BITS...]"
      << std::endl;
  while (!nodes.empty())
  {
    node const* current = nodes.front();
    std::cout << "[ " << current->parent << " | " << current << " | "
        << current->branch << " | " << current->child[0] << " | "
        << current->child[1] << " | " << current->val << " ]";
    if (NULL != current->val)
    {
      std::cout << "[ ";
      std::size_t const bits =
        std::min<std::size_t>(current->val->len(), 8U);
      char const bit_chars[2] = { '0', '1' };
      for(std::size_t i = 0; i < bits; ++i)
      {
        std::cout << bit_chars[current->val->bit(i)];
      }
      std::cout << " ]";
    }
    std::cout << std::endl;
    nodes.pop();

    if(NULL != current->child[0]) { nodes.push(current->child[0]); }
    if(NULL != current->child[1]) { nodes.push(current->child[1]); }
  }
}

