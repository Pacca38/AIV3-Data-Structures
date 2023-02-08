#include "doublyLinkedLists.h"
#include <stdio.h>
#include <time.h>

#define to_dlist(item) (struct doubly_list_node **)&item
#define to_dlist_node(item) (struct doubly_list_node *)item
#define to_string_item(item) (struct string_item *)item
#define string_dlist_append(list, string) dlist_append(to_dlist(list), to_dlist_node(string_item_new(string)))
#define string_dlist_pop(list) dlist_pop(to_dlist(item))
#define string_dlist_insert_after(list, item, string) dlist_insert_after(to_dlist(list), to_dlist_node(item), to_dlist_node(string_item_new(string)))
#define string_dlist_insert_before(list, item, string) dlist_insert_before(to_dlist(list), to_dlist_node(item), to_dlist_node(string_item_new(string)))
#define string_dlist_remove_item(list, item) dlist_remove_item(to_dlist(list), to_dlist_node(item))
#define string_dlist_shuffle(list) dlist_shuffle(to_dlist(list))

struct string_item
{
    struct doubly_list_node node;
    const char *string;
};

struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}

int main()
{
    srand(time(NULL));

    struct string_item *my_doubly_linked_list = NULL;
    string_dlist_append(my_doubly_linked_list, "1");
    string_dlist_append(my_doubly_linked_list, "2");
    struct string_item *three = to_string_item(string_dlist_append(my_doubly_linked_list, "3"));
    string_dlist_append(my_doubly_linked_list, "4");
    struct string_item *five = to_string_item(string_dlist_append(my_doubly_linked_list, "5"));
    string_dlist_append(my_doubly_linked_list, "6");

    string_dlist_insert_after(my_doubly_linked_list, three, "3.5");
    string_dlist_insert_before(my_doubly_linked_list, five, "4.5");

    string_dlist_remove_item(my_doubly_linked_list, five);

    string_dlist_shuffle(my_doubly_linked_list);

    struct string_item *string_item = my_doubly_linked_list;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = to_string_item(string_item->node.next);
    }
    return 0;
}