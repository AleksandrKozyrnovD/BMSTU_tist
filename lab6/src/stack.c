#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "stack.h"

int l_push(list_stack_t *stack, int type)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return ERR_MEM;
    node->type = type;
    node->prev = stack->top;
    stack->top = node;
    stack->index++;

    return EXIT_SUCCESSFUL;
}

int l_pop(list_stack_t *stack, int *type)
{
    if (stack->top == NULL)
        return ERR_EMPTY;
    node_t *tmp = stack->top;
    if (type)
        *type = tmp->type;
    stack->top = stack->top->prev;
    free(tmp);
    
    stack->index--;
    return EXIT_SUCCESSFUL;
}

int l_peek(list_stack_t *stack, int *type)
{
    if (stack->top == NULL)
        return 0;
    
    l_pop(stack, type);
    if (l_push(stack, *type))
        return ERR_MEM;

    return EXIT_SUCCESSFUL;;
}

void free_l_stack(list_stack_t *stack)
{
    while (stack->top)
        l_pop(stack, NULL);
}

void l_print(FILE *file, list_stack_t *stack, const char *restrict format)
{
    list_stack_t temp = { .top = NULL, .index = 0 };
    int tmp;
    if (stack->top == NULL)
    {
        printf("Пусто\n");
        return;
    }

    printf("=/=/=/=/=/=/\n");
    while (stack->top)
    {
        l_pop(stack, &tmp);
        fprintf(file, format, tmp);
        printf("=/=/=/=/=/=/\n");
        l_push(&temp, tmp);
    }

    while (temp.top)
    {
        l_pop(&temp, &tmp);
        l_push(stack, tmp);
    }
}

int stack_is_empty(const list_stack_t *stack)
{
    return stack->top == NULL;
}

int stack_get_result(int arr[NUMS_COUNT])
{
    list_stack_t _stack = { .top = NULL, .index = 0 };
    list_stack_t _stack_operation = { .top = NULL, .index = 0 };

    list_stack_t *stack = &_stack;
    list_stack_t *stack_operation = &_stack_operation;
    int opt;
    int val;

    if (l_push(stack_operation, '*'))
    {
        free_l_stack(stack);
        free_l_stack(stack_operation);
        return ERR_MEM;
    }
    if (l_push(stack_operation, '+'))
    {
        free_l_stack(stack);
        free_l_stack(stack_operation);
        return ERR_MEM;
    }

    // from 0 to 5
    for (size_t i = 0; i < 6; i++)
    {
        if (l_push(stack, arr[i]))
        {
            free_l_stack(stack);
            free_l_stack(stack_operation);
            return ERR_MEM;
        }
    }
    // int a_opt, b_opt;
    int a_val = 0, b_val = 0;

    while (!stack_is_empty(stack_operation))
    {
        l_pop(stack_operation, &opt);
        l_pop(stack, &a_val);
        l_pop(stack, &b_val);

        if (opt == '+')
            l_push(stack, a_val + b_val);
        else if (opt == '-')
            l_push(stack, b_val - a_val);
        else if (opt == '*')
            l_push(stack, a_val * b_val);
    }

    l_push(stack_operation, '+');
    l_push(stack_operation, '-');
    l_push(stack_operation, '-');
    l_push(stack, arr[6]);
    l_push(stack, arr[7]);

    while (!stack_is_empty(stack_operation))
    {
        l_pop(stack_operation, &opt);
        l_pop(stack, &a_val);
        l_pop(stack, &b_val);

        if (opt == '+')
            l_push(stack, a_val + b_val);
        else if (opt == '-')
            l_push(stack, b_val - a_val);
        else if (opt == '*')
            l_push(stack, a_val * b_val);
    }

    l_push(stack_operation, '+');
    l_push(stack_operation, '*');
    l_push(stack_operation, '+');
    l_push(stack, arr[8]);

    while (!stack_is_empty(stack_operation))
    {
        l_pop(stack_operation, &opt);
        l_pop(stack, &a_val);
        l_pop(stack, &b_val);

        if (opt == '+')
            l_push(stack, a_val + b_val);
        else if (opt == '-')
            l_push(stack, b_val - a_val);
        else if (opt == '*')
            l_push(stack, a_val * b_val);
    }
    
    val = -1;
    l_pop(stack, &val);

    free_l_stack(stack);
    free_l_stack(stack_operation);

    return val;
}

// int stack_res(int arr[NUMS_COUNT])
// {
//     arr_stack_t *stack = malloc(sizeof(arr_stack_t));
//     arr_stack_t *stack_opt = malloc(sizeof(arr_stack_t));
//
//     if (stack == NULL || stack_opt == NULL)
//         printf("Ошибка выделения памяти под стек!\n");
//
//     // 2 + (3 - (4 + (5 * 6)))
//     // 2 3 4 5 6 * + - +
//     // 6 5 4 3 2
//     // * + - +
//     char opt;
//     int val;
//
//     as_push(stack_opt, '*', 0);
//     as_push(stack_opt, '+', 0);
//     as_push(stack, ' ', arr[0]);
//     as_push(stack, ' ', arr[1]);
//     as_push(stack, ' ', arr[2]);
//     as_push(stack, ' ', arr[3]);
//     as_push(stack, ' ', arr[4]);
//     as_push(stack, ' ', arr[5]);
//
//     while (stack_opt->length)
//     {
//         as_pop(stack_opt, &opt, &val);
//         char a_opt, b_opt;
//         int a_val, b_val;
//         as_pop(stack, &a_opt, &a_val);
//         as_pop(stack, &b_opt, &b_val);
//
//         if (opt == '+')
//             as_push(stack, ' ', a_val + b_val);
//         else if (opt == '-')
//             as_push(stack, ' ', b_val - a_val);
//         else if (opt == '*')
//             as_push(stack, ' ', a_val * b_val);
//     }
//
//     as_push(stack_opt, '+', 0);
//     as_push(stack_opt, '-', 0);
//     as_push(stack_opt, '-', 0);
//     as_push(stack, ' ', arr[6]);
//     as_push(stack, ' ', arr[7]);
//
//     while (stack_opt->length)
//     {
//         as_pop(stack_opt, &opt, &val);
//         char a_opt, b_opt;
//         int a_val, b_val;
//         as_pop(stack, &a_opt, &a_val);
//         as_pop(stack, &b_opt, &b_val);
//
//         if (opt == '+')
//             as_push(stack, ' ', a_val + b_val);
//         else if (opt == '-')
//             as_push(stack, ' ', b_val - a_val);
//         else if (opt == '*')
//             as_push(stack, ' ', a_val * b_val);
//     }
//
//     as_push(stack_opt, '+', 0);
//     as_push(stack_opt, '*', 0);
//     as_push(stack_opt, '+', 0);
//     as_push(stack, ' ', arr[8]);
//
//     while (stack_opt->length)
//     {
//         as_pop(stack_opt, &opt, &val);
//         char a_opt, b_opt;
//         int a_val, b_val;
//         as_pop(stack, &a_opt, &a_val);
//         as_pop(stack, &b_opt, &b_val);
//
//         if (opt == '+')
//             as_push(stack, ' ', a_val + b_val);
//         else if (opt == '-')
//             as_push(stack, ' ', b_val - a_val);
//         else if (opt == '*')
//             as_push(stack, ' ', a_val * b_val);
//     }
//
//     as_pop(stack, &opt, &val);
//
//     return val;
// }
