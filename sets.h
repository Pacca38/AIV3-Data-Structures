#include "linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct set_node
{
    struct list_node node;
    const char *key;
    size_t key_len;
};

struct set_table
{
    struct set_node **nodes;
    size_t hashmap_size;
};

struct set_table *set_increase_hashmap_size(struct set_table *table, const size_t new_hashmap_size);

size_t djb33x_hash(const char *key, const size_t keylen);

size_t get_index_from_key(const char *key, size_t key_len, size_t hashmap_size);

void set_print(struct set_table *table);

struct set_table *set_table_new(const size_t hashmap_size);

struct set_node *set_search(struct set_table *table, const char *key, const size_t key_len);

struct set_node *set_insert(struct set_table **table, const char *key, const size_t key_len);

struct set_node *set_remove(struct set_table *table, const char *key, const size_t key_len);

struct set_table *set_increase_hashmap_size(struct set_table *table, const size_t new_hashmap_size);