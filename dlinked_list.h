#include <stddef.h>
#include <stdlib.h>

struct doubly_list_node
{
    struct doubly_list_node *prev;
    struct doubly_list_node *next;
};

int dlist_get_length(struct doubly_list_node **head);

struct doubly_list_node *dlist_get_item(struct doubly_list_node **head, const int index);

struct doubly_list_node *dlist_get_tail(struct doubly_list_node **head);

struct doubly_list_node *dlist_append(struct doubly_list_node **head, struct doubly_list_node *item);

struct doubly_list_node *dlist_pop(struct doubly_list_node **head);

struct doubly_list_node *dlist_insert_after(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *new_item);

struct doubly_list_node *dlist_insert_before(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *new_item);

struct doubly_list_node *dlist_remove_item(struct doubly_list_node **head, struct doubly_list_node *item);

struct doubly_list_node *dlist_remove_at(struct doubly_list_node **head, const int index);

void dlist_swap(struct doubly_list_node **A, struct doubly_list_node **B);

struct doubly_list_node *dlist_shuffle(struct doubly_list_node **head);
