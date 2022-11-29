#include "sets.h"

#define set_insert(set, key) set_insert(&set, key, strlen(key))
#define set_search(set, key) set_search(set, key, strlen(key))
#define set_remove(set, key) set_remove(set, key, strlen(key))

void find_key_test(struct set_table *set, char *string)
{
    if (set_search(set, string))
    {
        printf("Found key %s\n", string);
    }
    else
    {
        printf("Key %s not found\n", string);
    }
}

int main(int argc, char **argv)
{
    struct set_table *my_set = set_table_new(1);

    set_insert(my_set, "1");
    set_insert(my_set, "2");
    set_insert(my_set, "3");
    set_insert(my_set, "4");
    set_insert(my_set, "5");
    set_insert(my_set, "6");
    set_insert(my_set, "7");
    set_insert(my_set, "8");
    set_insert(my_set, "9");
    set_insert(my_set, "10");
    set_insert(my_set, "11");


    find_key_test(my_set, "2");
    find_key_test(my_set, "Ciao");

    set_remove(my_set, "2");
    find_key_test(my_set, "2");

    set_print(my_set);

    return 0;
}