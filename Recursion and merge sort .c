void traverse_inOrder(node* root){
    if(root == NULL){
        return;   
    }else{
        traverse_inOrder(root->left);
        printf("\t %d ", root->N);
        traverse_inOrder(root->right);
    }
}

node* find_min(node* root){ 
    if(root->left == NULL){
        return root;
    }else{
        return (find_min(root->left));
    }
}

node* add_node(node* root, node* ToAdd){
    if(root == NULL){
        root = ToAdd;
    }else if(ToAdd->N < root->N){
        root->left = add_node(root->left, ToAdd);
    }else{
        root->right = add_node(root->right, ToAdd);
    }
    return root;
}

int search_element(node* root, int N){
    if(root == NULL){
        return 0;
    }else if(root->N == N){
        return 1;
    }else if(N < root->N){
        return (search_element(root->left, N));
    }else{
        return (search_element(root->right, N));
    }
}

node* delete_node(node* root, int toDelete){
    node* temp;

    if(root == NULL){
        return root;
    }else if(toDelete < root->N){
        root->left = delete_node(root->left, toDelete)
    }else if(toDelete > root->N){
        root->right = delete_node(root->right, toDelete)
    }

    else if(root->left!=NULL && root->right!=NULL){
        temp = find_min(root->right);
        root->N = temp->N;
        root->right = delete_node(root->right, root->N);
    }

    else{
        temp = root;
         if(root->left == NULL){
             root = root->right;
         }else if(root->right == NULL){
             root = root->left;
         }
         free(temp);
    }
    return root;
}


int sum(int* arr, int size){
    if(size == 1){
        return arr[0];
    }else{
        return (arr[size] + sum(arr,size-1));
    }
}

int sum_increasing(int* arr, int size){
    if(size == 0){
        return 0;
    }else{
        return (arr[0] + sum_increasing(arr+1,size-1));
    }
}

int factorial(int n){
    if(n == 1){
        return 1;
    }else{
        return (n*factorial(n-1));
    }
}

int factorial_without_recursion(int N){
   int result = 1;
   for(i=1; i<=N; i++){
     result = result*i;
     }
   return(result);
}

int strlen(char* w){
    if(w[0] == '\o'){
        return 0;
    }else{
        return (1+strlen(w+1));
    }
}

int sum_up_n(int X){
    if(X == 1){
        return 1;
    }else{
        return (X + sum_up_n(X-1));
    }
}

int binary(int N, int*count){
    if(N == 0){
        return 0;
    }else{
        return (N%2 * pow(10,(*count)) + binary(N/2, count++));
    }
}

int sum(int N){
    if(N == 0){
        return 0;
    }else{
        return (N%10 + sum(N/10));
    }
}

void highest(int* arr, int size, int* max){
    if(size==0){
        return;
    }else{
        if(*max < arr[0]){
            *max = arr[0];
        } 
        highest(arr+1, size-1, max);
    }
}

void function(node* walker){
    if(walker == NULL){
        return;
    }
    printf("%d \n", walker->element);
    function(walker->next);
}

void function_opposite(node* walker){
    if(walker == NULL){
        return;
    }
    function(walker->next);
    printf("%d \n", walker->element);
}

void tower_hanoi(int N, char source, char temp, char destination){
    if(N==1){
        printf("(%c, %c) \n", source, destination);
    }else{
        tower_hanoi(N-1, source, destination, temp);
        printf("(%c, %c) \n", source, destination);
        tower_hanoi(N-1, temp, source, destination);
    }
}

void mergeSort(int arr[], int lb, int ub){
    if(lb < ub){
        int mid = (lb + ub)/2;
        mergeSort(arr, lb, mid);
        mergeSort(arr, mid + 1, ub);
        merge(arr, lb, mid, ub);
    }
}

void merge(int arr[], int lb, int mid, int ub){
    int i, j, k;
    int n_1 = mid - lb + 1;
    int n_2 = ub - mid;
    int L[n_1], R[n_2];
    
    for(i = 0; i < n_1; i++){
        L[i] = arr[lb + i]; 
    }
    for(j = 0; j < n_2; j++){    
        R[j] = arr[mid + 1 + j];
    }

    i = 0; 
    j = 0; 
    k = lb; 
    
    while(i < n_1 && j < n_2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while(i < n_1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n_2){
        arr[k] = R[j];
        j++;
        k++;
    }
}
