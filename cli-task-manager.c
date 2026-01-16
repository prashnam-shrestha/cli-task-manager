#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct task
{
    int number;
    char description[100];
    bool done;
    struct task *prev;
    struct task *next;
}
task;

task *add_task(task *ptr, int task_number);
void list_task(task *list, int total_task);
task *delete_task(task *list, int *task_ptr);
void update_number(task *list, int total_task);
void update_mark(task *list);
void free_memory(task *list);

int main(void)
{
    // Add task in linked lists
    // Mark as done: Show tasks - Enter task number - Task not found || Set task(Done): done || Set task(Incomplete): done
    // Delete: Show tasks - Enter task number - Task not found || Delete the task from the linked list - Update number
    int total_task = 0;

    task *list = NULL;

    while (true)
    {
        printf("--- Task manager --- \n");
        printf("1. Add task\n");
        printf("2. List all tasks\n");
        printf("3. Update completion\n");
        printf("4. Delete task\n");
        printf("5. Exit\n");

        int choice;
        printf("Enter choice:");
        scanf("%i", &choice);
        getchar();

        if (choice == 1)
        {
            // Add task
            total_task ++;
            list = add_task(list, total_task);
        }
        else if (choice == 2)
        {
            list_task(list, total_task);
        }
        else if (choice == 3)
        {
            update_mark(list);
        }
        else if (choice == 4)
        {
            list_task(list, total_task);
            list = delete_task(list, &total_task);
            update_number(list, total_task);
        }
        else if (choice == 5)
        {
            printf("Thank you!\n");
            free_memory(list);
            break;
        }
        else 
        {
            printf("Choice not found!\n");
        }
        printf("\n");
    } 
    return 0;

}


task *add_task(task *ptr, int task_number)
{
    char description[100];
    printf("Description: ");
    scanf("%[^\n]s", description);
    getchar();

    task *n = malloc(sizeof(task));
    if (n == NULL)
    {
        printf("Memory not alloted\n");
        return ptr;
    }
    n->number = task_number;
    strcpy(n->description, description);
    n->done = false;
    n->prev = NULL;
    n->next = ptr;
    if (n->next != NULL)
    {
    n->next->prev = n;
    };

    printf("Task added!✅\n");
    return n;
}

void list_task(task *list, int total_task)
{
    task *ptr = list;
    if (ptr == NULL)
    {
        printf("No tasks in the list\n");
        return;
    }

    printf("--- Tasks ---\n");
    char mark[15];

    // Move pointer to the tail
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    // Print from tail
    while (ptr != NULL)
    {
        
        if (ptr->done == true)
        {
            strcpy(mark, "Completed");
        }
        else
        {
            strcpy(mark, "Incomplete");
        }
        printf("%i: %s | %s\n",ptr->number, mark , ptr->description);
        ptr = ptr->prev;
    }
}

task *delete_task(task *list, int *task_ptr)
{
    if (list == NULL)
    {
        printf("No task in the list!\n");
        return list;
    }
    int task_number = *task_ptr;
    int number;
    printf("Enter task no to delete:");
    scanf("%i", &number);

    task *ptr = list;
    while (ptr != NULL)
    {
        if (ptr->number == number)
        {
            *task_ptr = *task_ptr - 1;
            printf("Task no.%i deleted!✅\n",number);
            if (ptr->prev == NULL && ptr->next == NULL)
            {
                free(ptr);
                return NULL;
            }
            else if (ptr->prev == NULL)
            {
                task *temp = ptr->next;
                ptr->next->prev = NULL;
                free(ptr);
                return temp;
            }
            else if (ptr->next == NULL)
            {
                ptr->prev->next = NULL;
                free(ptr);
                return list;
                
            }
            else 
            {
                ptr->next->prev = ptr->prev;
                ptr->prev->next = ptr->next;
                free(ptr);
                return list;
            }
        }
        ptr = ptr->next;
    }
    printf("Task number not found!\n");
    return list;
}

void update_number(task *list, int total_task)
{
    int task_number = total_task;
    task *ptr = list;
    while (ptr != NULL)
    {
        ptr->number = task_number;
        task_number--;
        ptr = ptr->next;
    }
}

void update_mark(task *list)
{
    if (list == NULL)
    {
        printf("No task in the list!\n");
        return;
    }
    int number;
    printf("Enter task no to update: ");
    scanf("%i", &number);


    while(list != NULL)
    {
        if (list->number == number)
        {
            list->done = !(list->done);
            printf("Task updated✅\n");
            return;
        }
        list = list->next;
    }
    printf("Task number not found!\n");
    
}

void free_memory(task *list)
{
    while(list != NULL)
    {
        task *temp = list->next;
        free(list);
        list = temp;
    }
}