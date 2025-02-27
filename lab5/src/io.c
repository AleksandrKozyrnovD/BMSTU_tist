#include "io.h"
#include "app.h"

void print_hello(void)
{
    printf("%s%s",
           "\n\n================\n\n",
           " 1) Моделирование и характеристика для очереди в виде массива.\n"
           " 2) Моделирование и характеристика для очереди в виде списка.\n"
           " 3) Изменить время обработки заявки.\n"
           " 4) Вывод сравнения времени при выполнении операций.\n"
           " 0) Выход из программы.\n\n"
           );
}

void clean_my(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

int check_float(double *const number)
{
    char num[4];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return DONT_INT_NUM_CHOICE;
    num[strlen(num) - 1] = '\0';
    *number = (double)atof(num);

    return OK;
}

int check_number(int *number, const int l, const int r)
{
    printf("Ввод пункта меню: ");
    char num[126];
    if (scanf("%125s", num) != 1)
        return INV_NUM_CHOICE;
    *number = num[0] - '0';

    if (*number < l || *number > r)
        return INV_NUM_CHOICE;

    return OK;
}

void len_swow(queue_t *queue)
{
    printf("Текущая длина очереди '%s': %d\n", queue->name, queue->tmp_len);
    if (queue->count_req > 0)
    {
        printf("Средняя длина очереди '%s': %lf\n", queue->name,
                (double)queue->sum_len / (double)queue->count_req);
    }
}

