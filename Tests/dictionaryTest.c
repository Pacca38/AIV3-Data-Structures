#include "dictionaries.h"

#define dict_add(dict, key, value) dict_insert(&dict, key, strlen(key), value)
#define dict_remove(dict, key) dict_remove(dict, key, strlen(key))
#define dict_search(dict, key) dict_search(dict, key, strlen(key))
#define dict_change_value(dict, key, new_value) dict_search(dict, key)->value = new_value

void search_test(struct dictionary *dict, char *string)
{
    struct dictionary_node *node = dict_search(dict, string);
    if (node)
    {
        printf("Found key %s with value=%p\n", string, node->value);
    }
    else
    {
        printf("Key %s not found\n", string);
    }
}

int main(int argc, char **argv)
{
    struct dictionary *my_dict = dict_new(1);

    int a = 25;
    dict_add(my_dict, "Pippo", &a);
    dict_add(my_dict, "Pluto", "ciao");
    dict_add(my_dict, "Ciao", &a);
    dict_add(my_dict, "Key", "pluto");
    dict_add(my_dict, "Null", "string");
    dict_add(my_dict, "Freffa", &a);

    search_test(my_dict, "Pluto");
    search_test(my_dict, "Freffa");

    dict_remove(my_dict, "Pluto");
    search_test(my_dict, "Pluto");

    dict_print(my_dict);
    dict_change_value(my_dict, "Null", "new_string");
    dict_print(my_dict);
    
    return 0;
}