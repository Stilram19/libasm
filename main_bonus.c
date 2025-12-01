# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libasm_bonus.h"

int cmp_str(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

void free_dummy(void *data)
{
    // For string literals, we do nothing
    (void)data;
}

// print function for debugging
void print_list(t_list *head)
{
    printf("[");
    while (head)
    {
        printf("%s", (char *)head->data);
        if (head->next)
            printf(" -> ");
        head = head->next;
    }
    printf("]\n");
}

void ft_list_push_front_test(t_list **list) {
    if (list == NULL) {
        return ;
    }

    printf("Initial list: ");
    print_list(*list);

    // test 1: push front on empty list
    ft_list_push_front(list, "OMAR");
    printf("After push_front(\"OMAR\"): ");
    print_list(*list);

    // test 2: push another on non-empty list
    ft_list_push_front(list, "IS");
    printf("After push_front(\"IS\"): ");
    print_list(*list);

    // test 3: passing NULL as parameter
    ft_list_push_front(NULL, NULL);
    printf("After push_front(NULL): ");
    print_list(*list);

    // test 4: push another on non-empty list
    ft_list_push_front(list, "NAME");
    printf("After push_front(\"NAME\"): ");
    print_list(*list);

    // test 5: push another on non-empty list
    ft_list_push_front(list, "MY");
    printf("After push_front(\"MY\"): ");
    print_list(*list);

    // final expected order: MY -> NAME -> IS -> OMAR
}

void ft_list_size_test(t_list **list) {
    if (list == NULL) {
        return ;
    }

    ft_list_push_front(list, "world");
    ft_list_push_front(list, "hello");

    print_list(*list); // [hello -> world]

    int size = ft_list_size(*list);
    printf("List size: %d\n", size); // Expected: 2

    // Test empty list
    t_list *empty = NULL;
    printf("Empty list size: %d\n", ft_list_size(empty)); // Expected: 0

}

void ft_list_remove_if_test(t_list **list)
{
    if (list == NULL) {
        return ;
    }

    printf("Initial list: ");
    print_list(*list);

    // prepare list: MY -> NAME -> IS -> OMAR
    ft_list_push_front(list, "OMAR");
    ft_list_push_front(list, "IS");
    ft_list_push_front(list, "NAME");
    ft_list_push_front(list, "MY");

    printf("Before remove_if: ");
    print_list(*list);

    // test 1: remove "IS"
    ft_list_remove_if(list, "IS", cmp_str, free_dummy);
    printf("After remove_if(\"IS\"): ");
    print_list(*list); // expected: MY -> NAME -> OMAR

    // test 2: remove head "MY"
    ft_list_remove_if(list, "MY", cmp_str, free_dummy);
    printf("After remove_if(\"MY\"): ");
    print_list(*list); // Expected: NAME -> OMAR

    // test 3: remove tail "OMAR"
    ft_list_remove_if(list, "OMAR", cmp_str, free_dummy);
    printf("After remove_if(\"OMAR\"): ");
    print_list(*list); // Expected: NAME

    // test 4: remove non-existing "NOTHING"
    ft_list_remove_if(list, "NOTHING", cmp_str, free_dummy);
    printf("After remove_if(\"NOTHING\"): ");
    print_list(*list); // expected: NAME

    // test 5: passing NULL -> nothing happens
    ft_list_remove_if(list, NULL, cmp_str, free_dummy);
    printf("Passing NULL: ");
    print_list(*list); // expected: NAME

    // test 6: remove remaining "NAME" -> list becomes empty
    ft_list_remove_if(list, "NAME", cmp_str, free_dummy);
    printf("After remove_if(\"NAME\"): ");
    print_list(*list); // expected: []
}

void ft_list_sort_test(t_list **list)
{
    if (list == NULL) {
        return ;
    }

    printf("Initial list: ");
    print_list(*list);

    // prepare unsorted list: Z -> A -> M -> B
    ft_list_push_front(list, "B");
    ft_list_push_front(list, "M");
    ft_list_push_front(list, "A");
    ft_list_push_front(list, "Z");

    printf("Before sort: ");
    print_list(*list); // expected: Z -> A -> M -> B

    // sort the list
    ft_list_sort(list, cmp_str);

    printf("After sort: ");
    print_list(*list); //expected: A -> B -> M -> Z

    // Test empty list
    t_list *empty = NULL;
    ft_list_sort(&empty, cmp_str);
    printf("Empty list after sort: ");
    print_list(empty); // expected: []

    // Test single element list
    t_list *single = NULL;
    ft_list_push_front(&single, "ONLY");
    ft_list_sort(&single, cmp_str);
    printf("Single-element list after sort: ");
    print_list(single); // expected: ONLY
}

void ft_atoi_base_test(void)
{
    printf("\n=== ft_atoi_base TEST ===\n");

    // 1. simple decimal
    printf("ft_atoi_base(\"42\", \"0123456789\") = %d\n",
        ft_atoi_base("42", "0123456789"));  // expected 42

    // 2. negative number
    printf("ft_atoi_base(\"   -123\", \"0123456789\") = %d\n",
        ft_atoi_base("   -123", "0123456789"));  // expected -123

    // 3. binary
    printf("ft_atoi_base(\"1011\", \"01\") = %d\n",
        ft_atoi_base("1011", "01"));  // expected 11

    // 4. hexadecimal lowercase
    printf("ft_atoi_base(\"7f\", \"0123456789abcdef\") = %d\n",
        ft_atoi_base("7f", "0123456789abcdef"));  // expected 127

    // 5. base with signs, (invalid) expected 0
    printf("ft_atoi_base(\"123\", \"0123+\") = %d\n",
        ft_atoi_base("123", "0123+"));  // expected 0

    // 6. base with duplicates, (invalid) expected 0
    printf("ft_atoi_base(\"12\", \"00123456789\") = %d\n",
        ft_atoi_base("12", "00123456789"));  // expected 0

    // 7. base size < 2, (invalid) expected 0
    printf("ft_atoi_base(\"1\", \"0\") = %d\n",
        ft_atoi_base("1", "0"));  // expected 0

    // 8. number with + and whitespace
    printf("ft_atoi_base(\" \\t +42\", \"0123456789\") = %d\n",
        ft_atoi_base(" \t +42", "0123456789"));  // expected 42
}


int main(void)
{
    // t_list *list = NULL;

    // ft_list_push_front_test(&list);
    // ft_list_size_test(&list);
    // ft_list_remove_if_test(&list);
    // ft_list_sort_test(&list);
    // ft_atoi_base_test();
    return 0;
}
