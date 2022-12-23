#include <math.h>
#include <stdio.h>
#include <string.h>

int TaskNumber = 0;

typedef struct {
  char description[30];
  int number;
  double time_to_finish;
} Task_info;

int construct_heap(FILE *, Task_info *);
void heapify(Task_info *, int, int);
int add_new_task_heap(Task_info *, int *, Task_info);
void delete_task_heap(Task_info *, int *, Task_info *);
void menu(void);
int find_smallest_element_index(Task_info *, int, int);
void swap(Task_info *, Task_info *);
void print_heap_content(Task_info *, int);
void heap_sort(Task_info *, int);
void save(FILE *, Task_info *, int);
int update_time(Task_info *, int, int, double);
int get_level(Task_info *, int);

int main() {
  Task_info min_heap[10], new_task, To_serve;
  FILE *infp;
  int i, choice, flag = 0, returned_value, index, task_to_Update, exists = 0;
  double time_to_Update;

  infp = fopen("ToDoToday.txt", "r");
  if (infp == NULL) {
    printf("\n\n\t Could not open the file! \n");
  } else {
    do {
      menu();
      scanf("%d", &choice);
      switch (choice) {
      case 1:
        TaskNumber = construct_heap(infp, min_heap);
        printf("\n\n\t Heap constructed successfully \n");
        flag = 1;
        break;
      case 2:
        if (flag == 0) {
          printf("\n\n\t Heap is not constructed yet! \n");
        } else {
          printf("\n\t Enter the number of the task to update:");
          scanf("%d", &task_to_Update);
          printf("\n\t Enter the time to add (enter a positive value) or "
                 "deduct(enter a negative value):");
          scanf("%lf", &time_to_Update);
          index =
              update_time(min_heap, TaskNumber, task_to_Update, time_to_Update);
          if (index != -1) {
            if (min_heap[index].time_to_finish < 1) {
              printf("\n\t Task %s with number %d has time to finish %lf "
                     "minute(s) \n\t This task was found in level %d of the "
                     "heap\n",
                     min_heap[index].description, task_to_Update,
                     60 * (min_heap[index].time_to_finish), get_level(min_heap, index));
            } else {
              printf(
                  "\n\t Task %s with number %d has time to finish %.2lf "
                  "hour(s) \n\t This task was found in level %d of the heap\n",
                  min_heap[index].description, task_to_Update,
                  min_heap[index].time_to_finish, get_level(min_heap, index));
            }
          } else {
            printf("\n\t Task %d not found! \n", task_to_Update);
          }
        }
        break;
      case 3:
        if (flag == 0) {
          printf("\n\n\t Heap is not constructed yet! \n");
        } else {
          printf("\n\n\t Please input: \n\n\t Description:");
          scanf("%s", new_task.description);
          printf("\n\n\t Task number:");
          scanf("%d", &new_task.number);
          printf("\n\n\t Time to finish:");
          scanf("%lf", &new_task.time_to_finish);
          returned_value =
              add_new_task_heap(min_heap, &TaskNumber, new_task);
          if (returned_value == 0) {
            printf("\n\n\t Sorry could not add %s! Heap is FULL!\n",
                   new_task.description);
          } else {
            printf("\n\n\t %s was added successfully!\n", new_task.description);
          }
        }
        break;
      case 4:
        if (flag == 0) {
          printf("\n\n\t Heap is not constructed yet! \n");
        } else { 
        delete_task_heap(min_heap, &TaskNumber, &To_serve);
        if (strcmp(To_serve.description, "EMPTY") == 0) {
          printf("\n\n\t Sorry but the heap is EMPTY!\n");
        } else {
          printf("Task, %s , was released from the heap, you will need %lf hour(s) to finish the task.", To_serve.description, To_serve.time_to_finish);
        }
        }
        break;
      case 5:
        if (flag == 0) {
          printf("\n\n\t Heap is not constructed yet!\n");
        } else {
          heap_sort(min_heap, TaskNumber);
        }
        break;
      case 6:
        if (flag == 0) {
          printf("\n\n\t Heap is not constructed yet!\n");
        
        } else if(TaskNumber == 0) {
          printf("\n\n\t Heap is empty!\n");
          
        } else {
          infp = fopen("ToDoNext.txt", "w");
          save(infp, min_heap, TaskNumber);
          fclose(infp);
        }
        printf("\n\n\tDone!\n\n\t");
        break;
      default:
        printf("\n\n\tSorry that was an invalid choice!\n");
      }
    } while (choice != 6);
  }
}

void menu(void) {
  printf("\n\n\t--------- Task management --------\n");
  printf("\n\n\t Please choose an option: ");
  printf("\n\n\t1. Start the program \n");
  printf("\n\n\t2. Update a task time \n");
  printf("\n\n\t3. Add a new task \n");
  printf("\n\n\t4. Act on a task in my queue \n");
  printf("\n\n\t5. View tasks sorted \n");
  printf("\n\n\t6. QUIT \n");
  printf("\n\n\t Your choice please: ");
}

int get_level(Task_info *min_heap, int index)
{
  int counter = 0;
  for(int i=index; i!=0; i=(i-1)/2)
    {
      counter++;
    }
  return counter;
}

int add_new_task_heap(Task_info *min_heap, int *TaskNumber,
                         Task_info new_task) {
  int index;

  if (*TaskNumber == 10) {
    return 0;
  } else {
    index = (*TaskNumber)++;
    min_heap[index] = new_task;

    while (index >= 1 &&
           min_heap[index].time_to_finish < min_heap[(index - 1) / 2].time_to_finish) {
      swap(&min_heap[index], &min_heap[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
    return 1;
  }
}

void delete_task_heap(Task_info *min_heap, int *TaskNumber,
                         Task_info *ToServe) {
  int root_index = 0, last_index, child_index;

  if (*TaskNumber == 0) {
    strcpy((*ToServe).description, "EMPTY");
  } else {
    *ToServe = min_heap[root_index];
    min_heap[root_index] = min_heap[--(*TaskNumber)];
    last_index = *TaskNumber - 1;
    if (last_index < 0) {
      return;
    } else {
      child_index = (root_index * 2) + 1;
      while (child_index <= last_index) {
        if (child_index + 1 <= last_index &&
            min_heap[child_index].time_to_finish >
                min_heap[child_index + 1].time_to_finish) {
          child_index++;
        }
        if (min_heap[child_index].time_to_finish <
            min_heap[root_index].time_to_finish) {
          swap(&min_heap[child_index], &min_heap[root_index]);
          root_index = child_index;
          child_index = (2 * root_index) + 1;
        } else {
          break;
        }
      }
    }
  }
}

void print_heap_content(Task_info *min_heap, int TaskNumber) {
  int i;

  for (i = 0; i < TaskNumber; i++) {
    printf("%s\n%d\n%.2lf\n", min_heap[i].description, min_heap[i].number,
           min_heap[i].time_to_finish);
  }
}

void heap_sort(Task_info *min_heap, int TaskNumber) {
  Task_info temp[10];
  Task_info testing;
  int n_task_temp = TaskNumber, i;

  for (i = 0; i < TaskNumber; i++) {
    temp[i] = min_heap[i];
  }

  while (n_task_temp != 0) {
    delete_task_heap(temp, &n_task_temp, &testing);
    printf("\n\n\t %s \n", testing.description);
  }
}

int construct_heap(FILE *infp, Task_info *min_heap) {
  int i = 0, last_index, TaskNumber;
  char temp[30];

  while (!feof(infp)) {
    fgets(min_heap[i].description, 30, infp);
    min_heap[i].description[strlen(min_heap[i].description) - 1] = '\0';
    min_heap[i].number = i + 1;
    fscanf(infp, "%lf", &min_heap[i].time_to_finish);
    fgets(temp, 30, infp);
    fgets(temp, 30, infp);
    i++;
  }

  TaskNumber = i;
  last_index = TaskNumber - 1;

  for (i = ((last_index + 1) / 2) - 1; i >= 0; i--) {
    heapify(min_heap, i, last_index);
  }
  return TaskNumber;
}

// last parent who has a child: last_parent_index = ((last_index+1)/2)-1)

void heapify(Task_info *min_heap, int parent_index, int last_index) {
  int right_child_index, left_child_index, smallest_element_index;

  // Base case: we reach a leaf
  if (parent_index > (((last_index + 1) / 2) - 1)) {
    return;
  } else {
    left_child_index = (2 * parent_index) + 1;
    right_child_index = (2 * parent_index) + 2;

    if (right_child_index > last_index) {
      smallest_element_index =
          find_smallest_element_index(min_heap, left_child_index, parent_index);
    } else {
      smallest_element_index =
          find_smallest_element_index(min_heap, left_child_index, parent_index);
      smallest_element_index = find_smallest_element_index(
          min_heap, right_child_index, smallest_element_index);
    }
    if (smallest_element_index != parent_index) {
      swap(&min_heap[smallest_element_index], &min_heap[parent_index]);
      heapify(min_heap, smallest_element_index, last_index);
    }
  }
}

void swap(Task_info *s1, Task_info *s2) {
  Task_info temp;

  temp = *s1;
  *s1 = *s2;
  *s2 = temp;
}

int find_smallest_element_index(Task_info *min_heap, int index1, int index2) {
  if (min_heap[index1].time_to_finish < min_heap[index2].time_to_finish) {
    return index1;
  } else {
    return index2;
  }
}

void save(FILE *infp, Task_info *min_heap, int TaskNumber) {
  int i;
  for (i = 0; i < TaskNumber; i++) {
    fprintf(infp, "%s\n%d\n%.2lf\n---------------------\n", min_heap[i].description,
            min_heap[i].number, min_heap[i].time_to_finish);
  }
}

int update_time(Task_info *min_heap, int TaskNumber, int task_to_update,
                double new_time) {
  int i;
  int index = -1;
  for (i = 0; i < TaskNumber; i++) {
    if (min_heap[i].number == task_to_update) {
      min_heap[i].time_to_finish += new_time;
      index = i;
      break;
    }
  }
  if (index != -1) {
    for (i = ((TaskNumber) / 2) - 1; i >= 0; i--) {
      heapify(min_heap, i, TaskNumber - 1);
    }
  }
  return index;
}
