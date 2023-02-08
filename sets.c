#include "sets.h"

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

size_t get_index_from_key(const char *key, size_t key_len, size_t hashmap_size)
{
    return djb33x_hash(key, key_len) % hashmap_size;
}

void set_print(struct set_table *table)
{
    for (size_t i = 0; i < table->hashmap_size; i++)
    {
        printf("Node %zu:\n", i);
        struct set_node *current = table->nodes[i];
        while (current)
        {
            printf("%s\n", current->key);
            current = (struct set_node *)current->node.next;
        }
    }
}

struct set_table *set_table_new(const size_t hashmap_size)
{
    struct set_table *table = (struct set_table *)malloc(sizeof(struct set_table));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size ;
    table->nodes = (struct set_node **)calloc(table->hashmap_size , sizeof(struct set_node *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }

    return table;
}

struct set_node *set_search(struct set_table *table, const char *key, const size_t key_len)
{
    size_t index = get_index_from_key(key, key_len, table->hashmap_size);

    struct set_node *current_node = table->nodes[index];
    if (!current_node)
    {
        return NULL;
    }

    while (current_node)
    {
        if (strcmp(key, current_node->key) == 0)
        {
            return current_node;
        }
        current_node = (struct set_node *)current_node->node.next;
    }

    return current_node;
}

struct set_node *set_insert(struct set_table **table, const char *key, const size_t key_len)
{
    size_t index = get_index_from_key(key, key_len, (*table)->hashmap_size);

    struct set_node *head = (*table)->nodes[index];
    if (!head)
    {
        (*table)->nodes[index] = (struct set_node *)malloc(sizeof(struct set_node));
        if (!(*table)->nodes[index])
        {
            return NULL;
        }
        (*table)->nodes[index]->key = key;
        (*table)->nodes[index]->key_len = key_len;
        (*table)->nodes[index]->node.next = NULL;

        return (*table)->nodes[index];
    }

    struct set_node *new_item = (struct set_node *)malloc(sizeof(struct set_node));
    if (!new_item)
    {
        return NULL;
    }
    //Unique keys
    if (set_search((*table), key, key_len))
    {
        return NULL;
    }
    new_item->key = key;
    new_item->key_len = key_len;

    struct set_node *ret = (struct set_node *)list_append((struct list_node **)&head, (struct list_node *)new_item);

    //If collision in a given hashmap is greater than 5, then increase hashmap_size
    if (list_get_length((struct list_node **)&head) > 5)
    {
        struct set_table *new_table = set_increase_hashmap_size((*table), (*table)->hashmap_size * 5);
        if (new_table)
        {
            (*table) = new_table;
        }
    }

    return ret;
}

struct set_node *set_remove(struct set_table *table, const char *key, const size_t key_len)
{
    size_t index = get_index_from_key(key, key_len, table->hashmap_size);

    struct set_node *current_node = table->nodes[index];
    if (!current_node)
    {
        return NULL;
    }

    while (current_node)
    {
        if (strcmp(key, current_node->key) == 0)
        {
            return (struct set_node *)list_remove((struct list_node **)&table->nodes[index], (struct list_node *)current_node);
        }
        current_node = (struct set_node *)current_node->node.next;
    }

    return current_node;
}

struct set_table *set_increase_hashmap_size(struct set_table *table, const size_t new_hashmap_size)
{
    struct set_table *new_table = set_table_new(new_hashmap_size);
    if (!new_table)
    {
        return NULL;
    }

    for (size_t i = 0; i < table->hashmap_size; i++)
    {
        struct set_node *current = table->nodes[i];
        while (current)
        {
            set_insert(&new_table, current->key, current->key_len);
            current = (struct set_node *)current->node.next;
        }
    }

    return new_table;
}