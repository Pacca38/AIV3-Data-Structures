#include <stddef.h>
#include <stdlib.h>

struct doubly_list_node
{
    struct doubly_list_node *prev;
    struct doubly_list_node *next;
};

int dlist_get_length(struct doubly_list_node **head)
{
    struct doubly_list_node *current_node = *head;
    int c = 0;
    while (current_node)
    {
        c++;
        current_node = current_node->next;
    }
    return c;
}

struct doubly_list_node *dlist_get_item(struct doubly_list_node **head, const int index)
{
    struct doubly_list_node *current_node = *head;

    for (int i = 0; i < index; i++)
    {
        if (!current_node)
        {
            return NULL;
        }
        current_node = current_node->next;
    }
    return current_node;
}

struct doubly_list_node *dlist_get_tail(struct doubly_list_node **head)
{
    struct doubly_list_node *current_node = *head;
    struct doubly_list_node *last_node = NULL;

    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
}

struct doubly_list_node *dlist_append(struct doubly_list_node **head, struct doubly_list_node *item)
{
    struct doubly_list_node *tail = dlist_get_tail(head);
    if (!tail)
    {
        *head = item;
        item->prev = NULL;
    }
    else
    {
        tail->next = item;
        item->prev = tail;
    }

    item->next = NULL;
    return item;
}

struct doubly_list_node *dlist_pop(struct doubly_list_node **head)
{
    struct doubly_list_node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }

    *head = (*head)->next;
    (*head)->prev = NULL;
    current_head->next = NULL;

    return current_head;
}

struct doubly_list_node *dlist_insert_after(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *new_item)
{
    struct doubly_list_node *current_node = *head;
    if (!head)
    {
        return NULL;
    }

    while (current_node)
    {
        if (current_node == item)
        {
            //Check if we are at the tail
            if (!current_node->next)
            {
                new_item->next = NULL;
            }
            else
            {
                current_node->next->prev = new_item;
                new_item->next = current_node->next;
            }
            current_node->next = new_item;
            new_item->prev = current_node;
            return new_item;
        }
        current_node = current_node->next;
    }

    return NULL;
}

struct doubly_list_node *dlist_insert_before(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *new_item)
{
    struct doubly_list_node *current_node = *head;
    if (!head)
    {
        return NULL;
    }

    while (current_node)
    {
        if (current_node == item)
        {
            //Check if we are at the head
            if (!current_node->prev)
            {
                new_item->prev = NULL;
                *head = new_item;
            }
            else
            {
                current_node->prev->next = new_item;
                new_item->prev = current_node->prev;
            }
            current_node->prev = new_item;
            new_item->next = current_node;
            return new_item;
        }
        current_node = current_node->next;
    }

    return NULL;
}

struct doubly_list_node *dlist_remove_item(struct doubly_list_node **head, struct doubly_list_node *item)
{
    struct doubly_list_node *current_node = *head;
    if (!current_node)
    {
        return NULL;
    }

    //Check if head is the item to remove
    if (*head == item)
    {
        return dlist_pop(head);
    }

    while (current_node)
    {
        if (current_node == item)
        {
            //Check if it's not the tail
            if (current_node->next)
            {
                current_node->next->prev = current_node->prev;
            }
            current_node->prev->next = current_node->next;
            current_node->prev = NULL;
            current_node->next = NULL;
            return current_node;
        }
        current_node = current_node->next;
    }

    return current_node;
}

struct doubly_list_node *dlist_remove_at(struct doubly_list_node **head, const int index)
{
    struct doubly_list_node *current_node = *head;
    if (!current_node)
    {
        return NULL;
    }

    //Check if head is the item to remove
    if (index == 0)
    {
        return dlist_pop(head);
    }

    int c = 0;
    while (current_node)
    {
        if (c == index)
        {
            //Check if it's not the tail
            if (current_node->next)
            {
                current_node->next->prev = current_node->prev;
            }
            current_node->prev->next = current_node->next;
            current_node->prev = NULL;
            current_node->next = NULL;
            return current_node;
        }
        current_node = current_node->next;
        c++;
    }

    return current_node;
}

void dlist_swap(struct doubly_list_node **A, struct doubly_list_node **B)
{
    struct doubly_list_node *swap_matrix[4];
    struct doubly_list_node *item1 = *A;
    struct doubly_list_node *item2 = *B;

    if (item2->next == item1)
    {
        swap_matrix[0] = item2->prev;
        swap_matrix[1] = item1->prev;
        swap_matrix[2] = item2->next;
        swap_matrix[3] = item1->next;
        if ((item1->next == item2 && item2->prev == item1) || (item1->prev == item2 && item2->next == item1))
        {
            item2->prev = swap_matrix[2];
            item1->prev = swap_matrix[0];
            item2->next = swap_matrix[3];
            item1->next = swap_matrix[1];
        }
        else
        {
            item2->prev = swap_matrix[1];
            item1->prev = swap_matrix[0];
            item2->next = swap_matrix[3];
            item1->next = swap_matrix[2];
        }
    }
    else
    {
        swap_matrix[0] = item1->prev;
        swap_matrix[1] = item2->prev;
        swap_matrix[2] = item1->next;
        swap_matrix[3] = item2->next;
        if ((item1->next == item2 && item2->prev == item1) || (item1->prev == item2 && item2->next == item1))
        {
            item1->prev = swap_matrix[2];
            item2->prev = swap_matrix[0];
            item1->next = swap_matrix[3];
            item2->next = swap_matrix[1];
        }
        else
        {
            item1->prev = swap_matrix[1];
            item2->prev = swap_matrix[0];
            item1->next = swap_matrix[3];
            item2->next = swap_matrix[2];
        }
    }
}

struct doubly_list_node *dlist_shuffle(struct doubly_list_node **head)
{
    int l = dlist_get_length(head);
    if (l <= 0)
    {
        return NULL;
    }
    if (l <= 1)
    {
        return *head;
    }

    struct doubly_list_node *new_head = *head;
    struct doubly_list_node *item1;
    struct doubly_list_node *item2;
    int n1 = 0;
    int n2 = 0;
    //Switch 2 random cells each for cycle
    for (int i = 0; i < 16; i++)
    {
        //Get 2 random indexes of the list
        n1 = rand() % l;
        n2 = rand() % l;
        while (n2 == n1)
        {
            n2 = rand() % l;
        }
        item1 = dlist_get_item(head, n1);
        item2 = dlist_get_item(head, n2);

        dlist_swap(&item1, &item2);

        if (item1->next)
            item1->next->prev = item1;
        if (item1->prev)
            item1->prev->next = item1;
        else
            new_head = item1;

        if (item2->next)
            item2->next->prev = item2;
        if (item2->prev)
            item2->prev->next = item2;
        else
            new_head = item2;
        
        *head = new_head;
    }

    return new_head;
}
