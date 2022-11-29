#include "linkedLists.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct dictionary_node
{
    struct list_node node;
    const char *key;
    size_t key_len;
    void *value;
};

struct dictionary
{
    struct dictionary_node **nodes;
    size_t hashmap_size;
};

struct dictionary *dict_increase_hashmap_size(struct dictionary *dict, const size_t new_hashmap_size);

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

void dict_print(struct dictionary *dict)
{
    for (size_t i = 0; i < dict->hashmap_size; i++)
    {
        printf("Node %zu:\n", i);
        struct dictionary_node *current = dict->nodes[i];
        while (current)
        {
            printf("\"%s\": %p\n", current->key, current->value);
            current = (struct dictionary_node *)current->node.next;
        }
    }
}

struct dictionary *dict_new(const size_t hashmap_size)
{
    struct dictionary *table = (struct dictionary *)malloc(sizeof(struct dictionary));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size ;
    table->nodes = (struct dictionary_node **)calloc(table->hashmap_size , sizeof(struct dictionary_node *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }

    return table;
}

struct dictionary_node *dict_search(struct dictionary *table, const char *key, const size_t key_len)
{
    size_t index = get_index_from_key(key, key_len, table->hashmap_size);

    struct dictionary_node *current_node = table->nodes[index];
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
        current_node = (struct dictionary_node *)current_node->node.next;
    }

    return current_node;
}

struct dictionary_node *dict_insert(struct dictionary **table, const char *key, const size_t key_len, void *value)
{
    size_t index = get_index_from_key(key, key_len, (*table)->hashmap_size);

    struct dictionary_node *head = (*table)->nodes[index];
    if (!head)
    {
        (*table)->nodes[index] = (struct dictionary_node *)malloc(sizeof(struct dictionary_node));
        if (!(*table)->nodes[index])
        {
            return NULL;
        }
        (*table)->nodes[index]->key = key;
        (*table)->nodes[index]->key_len = key_len;
        (*table)->nodes[index]->value = value;
        (*table)->nodes[index]->node.next = NULL;

        return (*table)->nodes[index];
    }

    struct dictionary_node *new_item = (struct dictionary_node *)malloc(sizeof(struct dictionary_node));
    if (!new_item)
    {
        return NULL;
    }
    //Unique keys
    if (dict_search((*table), key, key_len))
    {
        return NULL;
    }
    new_item->key = key;
    new_item->key_len = key_len;
    new_item->value = value;

    struct dictionary_node *ret =  (struct dictionary_node *)list_append((struct list_node **)&head, (struct list_node *)new_item);

    //If collision in a given hashmap is greater than 5, then increase hashmap_size
    if (list_get_length((struct list_node **)&head) > 5)
    {
        struct dictionary *new_dict = dict_increase_hashmap_size((*table), (*table)->hashmap_size * 5);
        if (new_dict)
        {
            (*table) = new_dict;
        }
    }

    return ret;
}

struct dictionary_node *dict_remove(struct dictionary *table, const char *key, const size_t key_len)
{
    size_t index = get_index_from_key(key, key_len, table->hashmap_size);

    struct dictionary_node *current_node = table->nodes[index];
    if (!current_node)
    {
        return NULL;
    }

    while (current_node)
    {
        if (strcmp(key, current_node->key) == 0)
        {
            return (struct dictionary_node *)list_remove((struct list_node **)&table->nodes[index], (struct list_node *)current_node);
        }
        current_node = (struct dictionary_node *)current_node->node.next;
    }

    return current_node;
}

struct dictionary *dict_increase_hashmap_size(struct dictionary *dict, const size_t new_hashmap_size)
{
    struct dictionary *new_dict = dict_new(new_hashmap_size);
    if (!new_dict)
    {
        return NULL;
    }

    for (size_t i = 0; i < dict->hashmap_size; i++)
    {
        struct dictionary_node *current = dict->nodes[i];
        while (current)
        {
            dict_insert(&new_dict, current->key, current->key_len, current->value);
            current = (struct dictionary_node *)current->node.next;
        }
    }

    return new_dict;
}