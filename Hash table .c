void initializeHT(student* HT){
    for(int i=0; i<11; i++){
        HT[i].id = 0;
        strcpy(HT[i].name, "Empty");
        HT[i].status = 0;
    }
}

int add(student* HT, student toAdd, int location, int* n){
    int i = 1, h1_location = location;
    if(*n == MAX){
        return -1;
    }
    while(HT[location].status == 1){
        // linear probing
        location = (location + 1)%SIZE;

        // or double hashing
        location = (h1_location + i * hash2(toAdd.id))%SIZE;
        i++;
    }
    strcpy(HT[location].name, toAdd.name);
    HT[location].id = toAdd.id;
    HT[location].status = 1;
    (*n)++;
    return 1;
}

int hash1(int id){
    return id % SIZE;
}

int hash2(int id){
    return 7 - id % 7;
}

int delete(student* HT, int id, int location, int* n){
    int n_tries = 0, flag = 0, i = 1, h1.location = location;
    if(*n == 0){
        return -1;
    }
    while(HT[location].status != 0 && n_tries <= SIZE){
        if(HT[location].id == id){
            HT[location].id = 0;
            strcpy(HT[location].name, "Empty");
            HT[location].status = -1;
            flag = 1;
            (*n)--;
            break;
        }
        else{
            // linear probing
            location = (location + 1)%SIZE;

            // or double hashing
            location = (h1.location + i * hash2(id))%SIZE;
            i++; 
            n_tries++; 
        }
    }
    return flag;
}

int search(student* HT, int id, int location, int n, int* position){
    int n_tries = 0, flag = 0, i = 1, h1.location = location;
    if(n == 0){
        return -1;
    }
    while(HT[location].status != 0 && n_tries <= SIZE){
        if(HT[location].id == id){
            *position = location; 
            flag = 1;
            break;
        }
        else{
            // linear probing
            location = (location + 1)%SIZE;

            // or double hashing
            location = (h1.location + i * hash2(id))%SIZE;
            i++; 
            n_tries++; 
        }
    }
    return flag;
}

void printing(student* HT){
    for(int i=0; i<SIZE, i++){
        if(HT[i].status == 1){
            printf("%d",HT[i].id);
        }   
    }
}

// chaining

student_node* create_initialize_node(){
    
    student_node* new_node;
    char temp;
    new_node = (student_node*)malloc(sizeof(student_node));
    scanf("%c",&temp);
    printf("\n\t Input the student name:");
    gets(new_node->student_name);
    printf("\n\t Input the student ID:");
    scanf("%d",&new_node->student_id);
    new_node->next = NULL;

    return new_node;
}

void initialize_hash_table(student_node** HT, int size){
    for(int i = 0; i<size; i++){
        HT[i] = NULL;
    }
}

int hash_function(int id, int size){
    return (id%size);
}

void add_student(student_node** HT, student_node* ToAdd, int index){
    if(HT[index] == NULL){
        HT[index] = ToAdd;
    }else{
        ToAdd->next = HT[index];
        HT[index] = ToAdd;
    }
}

student_node* delete_student(student_node** HT, int id, int index){
    student_node *walker, *temp;

    if(HT[index] == NULL){
        return NULL;
    }else{
        walker = HT[index];
        if(walker->student_id == id){
            HT[index] = walker->next;
            return walker;
        }else{
            while(walker->next != NULL){
                if(walker->next->student_id == id){
                    temp = walker->next;
                    walker->next = walker->next->next;
                    return temp;
                }else{
                    walker = walker->next;
                }
            } 
            return NULL; 
        }
    }
}