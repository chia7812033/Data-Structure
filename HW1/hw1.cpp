#include <stdio.h>
#include <stdlib.h>
struct node *create_node(FILE **fp);
void display(struct node *p);
int count_length(struct node *p);
void display_order(struct node *p);
void sort(struct node **p);
struct student
{
    int id;
    double avg;
};
struct node
{
    struct student st;
    struct node *link;
};

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    FILE *fp;
    fp = fopen("input.txt", "r");
    head = create_node(&fp);
    sort(&head);
    display(head);

    return 0;
}

struct node *create_node(FILE **fp)
{
    struct student t;
    struct node *head, *tail, *p;
    head = tail = (struct node *)malloc(sizeof(struct node));
    while (fscanf(*fp, "%d %lf", &t.id, &t.avg) != EOF)
    {
        p = (struct node *)malloc(sizeof(struct node));
        p->link = NULL;
        p->st = t;
        tail->link = p;
        tail = p;
    }
    p = head;
    head = head->link;
    free(p);
    p = head;
    return head;
}

void display(struct node *p)
{
    while (p != NULL)
    {
        printf("0%d %lf\n", p->st.id, p->st.avg);
        p = p->link;
    }
    printf("\n\n");
}

int count_length(struct node *p)
{
    int len = 0;
    while (p != NULL)
    {
        len++;
        p = p->link;
    }

    return len;
}

void display_order(struct node *p)
{
    int len = count_length(p);
    struct node *tmp = p, *max = (struct node *)malloc(sizeof(struct node));
    max->st.avg = 0;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (tmp->st.avg > max->st.avg)
            {
                max = tmp;
            }
            tmp = tmp->link;
        }
        printf("%08d %lf\n", max->st.id, max->st.avg);
        max->st.avg = -1;
        tmp = p;
    } 
}

void sort(struct node **p)
{
    int len = count_length(*p);
    struct node **current = &(*p), **tmp;
    struct student t;
    for (int i = 0; i < len - 1; i++)
    {
        tmp = &((*current)->link);
        for (int j = i+1; j < len; j++)
        {
            if ((*current)->st.avg < (*tmp)->st.avg)
            {
                t = (*current)->st;
                (*current)->st = (*tmp)->st;
                (*tmp)->st = t;
            }
            tmp = &((*tmp)->link);
        }
        current = &((*current)->link);
    } 
}