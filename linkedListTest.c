#include "linkedLists.h"
#include <stdlib.h>
#include <stdio.h>

#define to_list_item(item) (struct list_node **)&item
#define to_list_node_item(item) (struct list_node *)item
#define to_string_item(item) (struct string_item *)item
#define string_list_append(list, string) list_append(to_list_item(list), (struct list_node *)string_item_new(string))
#define string_list_remove(list, item) list_remove(to_list_item(list), to_list_node_item(item))
#define string_list_find(list, item) list_find(to_list_item(list), to_list_node_item(item))
#define string_list_reverse(list) list_reverse(to_list_item(list))
#define string_list_pop(list) list_pop(to_list_item(list))

struct string_item
{
    struct list_node node;
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
    struct string_item *my_linked_list = NULL;
    string_list_append(my_linked_list, "1");
    string_list_append(my_linked_list, "2");
    string_list_append(my_linked_list, "3");
    string_list_append(my_linked_list, "4");
    struct string_item *item_to_remove = to_string_item(string_list_append(my_linked_list, "5"));
    string_list_append(my_linked_list, "6");

    string_list_pop(my_linked_list);                    //2 -> 3 -> 4 -> 5 -> 6
    string_list_reverse(my_linked_list);                //6 -> 5 -> 4 -> 3 -> 2
    if (string_list_find(my_linked_list, item_to_remove))
    {
        printf("I've found the item\n");
    }
    else
    {
        printf("Item not found\n");
    }
    string_list_pop(my_linked_list);                    //5 -> 4 -> 3 -> 2
    string_list_remove(my_linked_list, item_to_remove); //4 -> 3 -> 2
    string_list_append(my_linked_list, "6");            //4 -> 3 -> 2 -> 6
    string_list_reverse(my_linked_list);                //6 -> 2 -> 3 -> 4
    if (string_list_find(my_linked_list, item_to_remove))
    {
        printf("I've found the item\n");
    }
    else
    {
        printf("Item not found\n");
    }

    struct string_item *string_item = my_linked_list;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = to_string_item(string_item->node.next);
    }
    return 0;
}