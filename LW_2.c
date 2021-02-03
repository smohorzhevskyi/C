#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Для двозв’язного списку імен (поля: name, surname) реалізувати
//
// функції:
// а) додавання елемента у порядку спадання surname, для однакових
// прізвищ сортувати у порядку спадання name;
// б) видалення елемента з хвоста списку;
// в) вивести попередній та наступний елементи для k-го (введення з
//	клавіатури);
// г) надрукувати весь список, формат: “Name Surname”;
// д) видалити весь список.

typedef struct s_list {
    char *name;
    char *surname;

    struct s_list *next;
    struct s_list *previous;
}				d_list;


// допоміжна функція для створення елементу двухзвязного списку
d_list *create_list_element(char *name, char *surname) {
    d_list *new_element = (d_list*) (malloc(sizeof(d_list))); // алоціюємо память під новий елемент

    new_element->name = strdup(name); // функція strdup аллокує память під строку
    new_element->surname = strdup(surname);

    new_element->next = NULL;
    new_element->previous = NULL;

    return new_element;
}

// допоміжна функція для створення елементу двухзвязного списку
void create_and_append_element_to_list(d_list **head, char *newName, char *newSurname) {
    d_list *new_element = create_list_element(newName, newSurname);

    if (*head == NULL) {
        *head = new_element;
        return;
    }

    d_list *temp = *head;

    while (temp->next)
        temp = temp->next;

    temp->next = new_element;
    new_element->previous = temp;
}

// а) додавання елемента у порядку спадання surname, для однакових
// прізвищ сортувати у порядку спадання name;

void create_and_append_element_to_list_ordered(d_list **head, char *newName, char *newSurname) {
    d_list *new_element = create_list_element(newName, newSurname);

    if (*head == NULL) {
        *head = new_element;
        return;
    }

    d_list *current = *head;
    d_list *previous = *head;

    while (current) {

        // порівняння імен та прізвищ
        int name_compare_result = strcasecmp(newName, current->name);
        int surname_compare_result = strcasecmp(newSurname, current->surname);

        // умови для прізвищ
        int is_surname_equals = surname_compare_result == 0;
        int is_surname_initial_element_and_fits = surname_compare_result < 0 && current == previous;
        int is_surname_noninitial_element_and_fits = surname_compare_result < 0 && current != previous;

        // якщо в нас однакові прізвища, то це умови для імен
        int is_name_initial_element_and_fits = is_surname_equals && name_compare_result < 0 && current == previous;
        int is_name_noninitial_element_and_fits = is_surname_equals && name_compare_result < 0 && current != previous;

        if (is_surname_initial_element_and_fits || is_name_initial_element_and_fits) {

            new_element->next = current;
            current->previous = new_element;
            *head = new_element;
            return;

        } else if (is_surname_noninitial_element_and_fits || is_name_noninitial_element_and_fits) {

            new_element->next = current;
            new_element->previous = current->previous;
            current->previous->next = new_element;
            current->previous = new_element;
            return;
        }
        previous = current;
        current = current->next;
    }

    previous->next = new_element;
    new_element->previous = previous;
}


// б) видалення елемента з хвоста списку;
void pop_tail_element(d_list **list) {
    d_list *head = *list;

    if (head->next == NULL) {
        free(head);
        *list = NULL;
        return;
    }

    while (head->next)
        head = head->next;

    free(head->previous->next);
//    free(head->previous->name);
//    free(head->previous->surname);
    head->previous->next = NULL;
}

// в) вивести попередній та наступний елементи для k-го (введення з
//	клавіатури);
void print_next_and_previous_element(d_list *head, int index) {
    d_list *curr_element = head;
    for(int i = 0; curr_element && i < index; i++) {
        curr_element = curr_element->next;
    }
    if (curr_element) {
        if (curr_element->previous)
            printf("Previous element: %s %s\n", curr_element->previous->name, curr_element->previous->surname);
        else
            printf("Previous element is absent\n");
        if (curr_element->next)
            printf("Next element: %s %s\n", curr_element->next->name, curr_element->next->surname);
        else
            printf("Next element is absent\n");
    } else {
        printf("There are few elements in list than K\n");
    }

}

// г) надрукувати весь список, формат: “Name Surname”;
void print_linked_list(d_list *list) {
    d_list *head = list;

    while (head) {
        printf("%s %s\n", head->name, head->surname);
        head = head->next;
    }
}

// д) видалити весь список.
void delete_whole_list(d_list **list) {
    d_list *head = *list;

    while (head) {
        d_list *element_to_remove = head;
        head = head->next;
        free(element_to_remove->name);
        free(element_to_remove->surname);
        free(element_to_remove);
    }

    *list = NULL;

    printf("\nList is empty now!");
}


int main(int argc, char *argv[]) {

    d_list *head = NULL;

    create_and_append_element_to_list_ordered(&head, "First", "Person");
    create_and_append_element_to_list_ordered(&head, "Second", "Person");
    create_and_append_element_to_list_ordered(&head, "Abconda", "Person");
    create_and_append_element_to_list_ordered(&head, "Abcond", "Person");
    create_and_append_element_to_list_ordered(&head, "Abcona", "Person");
    create_and_append_element_to_list_ordered(&head, "Third", "Persont");
    create_and_append_element_to_list_ordered(&head, "Lol", "Persoan");
    create_and_append_element_to_list_ordered(&head, "Man", "Woman");
    create_and_append_element_to_list_ordered(&head, "Equal", "Lol");

    print_linked_list(head);

    int k;
    printf("Please enter index of element: ");
    scanf("%d", &k);

    printf("\n");
    print_next_and_previous_element(head, k);
    printf("\n");
    pop_tail_element(&head);
    printf("\n");
    print_linked_list(head);
    printf("\n");
    delete_whole_list(&head);
    printf("\n");
    print_linked_list(head);

    return 0;
}
