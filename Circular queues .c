#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tag {
  char name[30];
  int id;
  struct tag *next;
} node;

node *create_fill_node(char *name_temp, int id_temp) {
  node *new_node;
  // 1. Create a node
  new_node = (node *)malloc(sizeof(node));
  // 2. Fill the elements in the node
  strcpy(new_node->name, name_temp);
  new_node->id = id_temp;
  new_node->next = NULL;
  return (new_node);
}

void enqueue(node **front, node **rear, node *new_node) {
  if (*front == NULL) {
    *front = new_node;
  } else {
    (*rear)->next = new_node;
  }
  *rear = new_node;
  (*rear)->next = *front;
}

int dequeue(node **front, node **rear) {
  int id_to_return;
  node *temp;
  temp = *front;
  id_to_return = temp->id;
  if ((*front)->next == *front) {
    *front = NULL;
    *rear = NULL;
  } else {
    *front = (*front)->next;
    (*rear)->next = *front;
  }
  free(temp);
  return id_to_return;
}

void printing(node *front) {

  node *walker;
  if (front == NULL)
    printf("\n\t\t The queue is EMPTY!\n");
  else {
    walker = front;
    printf("\n\t\t Your queue contains the following students:\n");

    do {
      printf("\n\t\t %s with id %d \n", walker->name, walker->id);
      walker = walker->next;
    } while (walker != front);
  }
}

void destroy(node **front, node **rear) {
  node *temp;
  while (*front != NULL) {
    if ((*front)->next == *front) {
      free(*front);
      *front = NULL;
      *rear = NULL;
      return;
    }
    temp = *front;
    *front = (*front)->next;
    free(temp);
    (*rear)->next = *front;
  }
}

void save(FILE *fp, node *front) {
  node *walker;
  if (front == NULL)
    return;
  else {
    walker = front;
    do {
      fprintf(fp, "%s %d \n", walker->name, walker->id);
      walker = walker->next;
    } while (walker != front);
  }
}

int leave_queue(node **front, node **rear, int id) {
  node *temp, *walker, *first_node;
  int flag = 0;
  walker = *front;
  if ((*front)->id == id) {
    if (*front == *rear) {
      free(*front);
      *front = NULL;
      *rear = NULL;
    } else {
      temp = *front;
      *front = (*front)->next;
      (*rear)->next = *front;
      free(temp);
    }
    flag = 1;
    return flag;
  }
  do {
    if (walker->next->id == id) {
      temp = walker->next;
      walker->next = walker->next->next;
      free(temp);
      if (walker->next == *front)
        *rear = walker;
      flag = 1;
      break;
    }
    walker = walker->next;
  } while (walker != *front);
  return flag;
}

int time_up(node **front, node **rear, int choice2) {
  int served;
  if (choice2 == 1) {
    served = (dequeue(front, rear));
    return served;
  } else if (choice2 == 2) {
    served = (*front)->id;
    *rear = *front;
    *front = (*front)->next;
    return served;
  }
}

void menu(void) {
  printf("\n\n\t\t--------------- Menu to Use-----------------\n");
  printf("\t\t 1. Add a student to a queue \t\t    \n");
  printf("\t\t 2. Time is up \t\t\t\t    \n");
  printf("\t\t 3. Print the content of the queue \t    \n");
  printf("\t\t 4. Student is no more interested \t    \n");
  printf("\t\t 5. I need my toy back \t\t\t    \n");
  printf("\t\t 6. Exit \t\t\t\t    \n");
  printf("\t\t--------------------------------------------\n");
  printf("\n\t\t Enter your choice: ");
}

int main(void) {

  int choice, flag = 0, choice2, served;
  node *front = NULL, *rear = NULL;
  node *new_node;
  char name_temp[70];
  int id_temp;
  FILE *fp;

  do {
    menu();
    scanf("%d", &choice);

    switch (choice) {

    case 1:
      printf("\n\t\t Enter the student name:");
      getchar();
      gets(name_temp);
      printf("\n\t\t Enter the student id:");
      scanf("%d", &id_temp);
      new_node = create_fill_node(name_temp, id_temp);
      enqueue(&front, &rear, new_node);

      break;
    case 2:

      if (front == NULL) {
        printf("\n\t\t The queue is empty\n");
      } else {

          printf("\n\t\t Enter 1 if the student wants to leave or 2 if the student wants to stay:");
          scanf("%d", &choice2);
          served = time_up(&front, &rear, choice2);
      
          if (choice2 == 1) {
            printf("\n\t\t The student with id %d has been served and left the queue\n", served);
          } else if (choice2 == 2) {
            printf("\n\t\t The student with id %d has been served and remained in the queue\n", served);
          }
      }
      break;
    case 3:
      printing(front);
      break;
    case 4:
      printf("\n\t\t Enter the student id:");
      scanf("%d", &id_temp);
      flag = leave_queue(&front, &rear, id_temp);
      if (flag == 1) {
        printf("\n\t\t Student with id %d was removed from the queue\n",
               id_temp);
      } else {
        printf("\n\t\t Student with id %d is not in the queue\n", id_temp);
      }
      break;
    case 5:
      fp = fopen("record.txt", "w");
      save(fp, front);
      printf("\n\t\t Everybody left the queue!\n");
      destroy(&front, &rear);
      fclose(fp);
      return 0;
    case 6:
      printf("\n\t\t You decided to quit! GOOD BYE!\n");
      return 0;
    default:
      printf("\n\t\t That was a WRONG Choice!\n");
    }
  } while (choice != 5);

  return 0;
}