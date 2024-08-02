#include <stdio.h>
#include <stdlib.h>

// Dimension of Arrays
#define DIM 30

// Constants for colors
#define WHITE 0 
#define GRAY 1
#define BLACK 2
#define RED 3

// Type Definition for Pointer on Node Struct
typedef struct node *pp;

// Node Struct Definition
struct node {
  int i,j;
  int distance;
  int color;
  pp predecessor;
  pp next;
  pp previous;
  pp up;
  pp down;
};

const char* color(int color);
void printList(pp head);
void Print(pp H[]);
void Insert(pp *head1, pp* head2, int i, int j);
void Delete(pp *head1, pp* head2, int i, int j);
void InsertHorizontal(pp *head, int i, int j);
void InsertVertical(pp *head, int i, int j);
void DeleteHorizontal(pp *head, int i, int j);
void DeleteVertical(pp *head, int i, int j);
void BFS(pp H[], int i);
void Enqueue(pp Queue[], int *head, int *tail, pp x);
pp Dequeue(pp Queue[], int *head, int *tail);
void CreateCircle(pp Tree[]);

int main(void) {
  
  int i, j; 
  pp H[DIM];
  pp V[DIM];
  int q;
  for(q = 0; q < DIM; q++){
  	H[q] = NULL;
	V[q] = NULL;
  }
  
  char answer = '_';

  while(answer != 'Q' && answer != 'q') {
  	printf("\nA Program to represent a Sparse Array\n");
    printf(" Options:\n");
    printf(" I: Insert node\n");
    printf(" P: Print the Sparse Array\n");
	printf(" D: Delete node\n");
    printf(" B: Breadth-First-Search\n");
    printf(" Q: Quit Program\n");
    printf("\n--------------------------------------------------------------\n");
    printf("\nSelect a proper option: (I/P/D/B/Q): ", answer);

    fflush(stdin);
    answer = getchar();
    getchar();

    printf("Your choice was: %c", answer);
    printf("\n--------------------------------------------------------------\n");

    if(answer != 'I' && answer != 'i' && answer != 'P' && answer != 'p' && answer != 'D' && answer != 'd' && answer != 'Q' &&
       answer != 'q' && answer != 'B' && answer != 'b') {
      printf("\n\nInvalid input, please try again.\n");
    }

    if(answer == 'I' || answer == 'i') {
     printf("\n\nInsert a node (i,j), with i,j integers between 1 and %d: ", DIM);
     printf("\nProvide the node: ");
	 scanf("%d%d", &i, &j);
      
     while((i<1 || i>DIM) || (j<1 || j>DIM) || (getchar() != '\n')){
	  	printf("\nWrong node please insert again: ");
	  	while (getchar() != '\n'); // Clear the input buffer
	  	scanf("%d%d", &i, &j);
	  }
	 if(i == j){
	  	Insert(&H[i-1], &V[j-1],i, j);
	  } else {
        Insert(&H[i-1], &V[j-1], i, j);
		Insert(&H[j-1], &V[i-1], j, i);
	  }
    }
      

    if(answer == 'P' || answer == 'p') {
      printf("\n\nPrint the node array\n"); 
	  int Empty = 1; // Assume all elements are NULL initially
      for (q = 0; q < DIM; q++) {
        if ((H[q] != NULL) && (V[q] != NULL)) {
        Empty = 0; // An array is not NULL, so set the flag to 0 and break
        break;
       }
      }
      if (Empty == 1) {
        printf("The Sparse Array is empty, there is nothing to print\n");
	  } else {
      for(int n = 0; n < 23; n++){
	    printf("-");
	  }
	  printf("\n");
	  Print(H);
      printf("\n");
    }
}

    if(answer == 'D' || answer == 'd') {
      printf("\n\nDelete Node\n");
      int Empty = 1; // Assume all elements are NULL initially
      for (q = 0; q < DIM; q++) {
        if ((H[q] != NULL) && (V[q] != NULL)) {
        Empty = 0; // An array is not NULL, so set the flag to 0 and break
        break;
       }
      }
      if (Empty == 1) {
        printf("The Sparse Array is empty, there is nothing to delete\n");
	  } else {
      printf("\nThe node to delete is: ");
      scanf("%d%d", &i, &j);
    
	while((i<1 || i>DIM) || (j<1 || j>DIM) || (getchar() != '\n')){
	  	printf("\nWrong node please choose again: ");
	  	while (getchar() != '\n'); // Clear the input buffer
	    scanf("%d%d", &i, &j);
	}
	if(i == j){
	    Delete(&H[i-1], &V[j-1], i, j );
	} else {
	  	Delete(&H[i-1], &V[j-1], i, j );
	    Delete(&H[j-1], &V[i-1], j, i );
	  }
    }
  }
  
  if(answer == 'B' || answer == 'b') {
  	printf("\nBreadth-First-Search\n");
  	int Empty = 1; // Assume all elements are NULL initially
      for (q = 0; q < DIM; q++) {
        if ((H[q] != NULL) && (V[q] != NULL)) {
        Empty = 0; // An array is not NULL, so set the flag to 0 and break
        break;
       }
      }
      if (Empty == 1) {
        printf("The Sparse Array is empty, can't do BFS\n");
    } else {
      	printf("Enter the array H[i] to be the root:");
        scanf("%d", &i);
        
        while(i<1 || i>DIM || getchar() != '\n') {
	    	printf("\nWrong array, please insert the array H[i] again: ");
	    	while (getchar() != '\n'); // Clear the input buffer
	    	scanf("%d", &i);
	    }
        BFS(H, i);
	  }
    }
  }
    
  printf("\n\nThe program has halted.");
  
  // Free Memory
  for (int n = 0; n < DIM; n++) {
        pp current = H[n];
        while (current != NULL) {
            pp temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    for (int o = 0; o < DIM; o++) {
        pp current = V[o];
        while (current != NULL) {
            pp temp = current;
            current = current->down;
            free(temp);
        }
    }
    
  return 0;
}      

const char* color(int color) {
    switch (color) {
        case WHITE:
            return "White";
        case GRAY:
            return "Gray";
        case BLACK:
            return "Black";
        case RED:
            return "Red"; //Unused Vertices
        default:
            return "Error"; // Handle invalid color values
    }
}

// Breadth-First-Search
void BFS(pp H[], int i) {
    pp s; // Starting vertex
    s = H[i - 1];

    // Empty List, can't do BFS
    if (s == NULL) {
        printf("Array H[%d] is empty, can't run BFS\n", i - 1);
        return;
    }

     //Set all vertices White except the starting vertex
    pp u;
    int q;
    for (q = 0; q < DIM; q++) {
        if ((q != i - 1) && (H[q] != NULL)) {
            u = H[q];
            u->color = WHITE;
            u->distance = -1;
            u->predecessor = NULL;
        }
    }

     //Set the starting vertex Gray
    s->color = GRAY;
    s->distance = 0;
    s->predecessor = NULL;

     //Initiate Queue
    pp Queue[DIM];
    pp Tree[DIM];
    for (q = 0; q < DIM; q++) {
        Queue[q] = NULL;
        Tree[q] = NULL;
    }
    int head = 1;
    int tail = 1;
    Enqueue(Queue, &head, &tail, s);
    int m = 0;
    Tree[m] = s;
    
    while(head != tail){
        u = Dequeue(Queue, &head, &tail);
        pp v;
        v = u;
        while(v != NULL){
        	int col = v->j - 1;
        	pp h = H[col];
        	if(h->color == WHITE){
        		h->color = GRAY;
        		h->distance = u->distance +1;
        		h->predecessor = u;
        		m++;
        		Tree[m] = h;
                Enqueue(Queue, &head, &tail, h);
			}
			v = v->next;		
		 }
		u->color = BLACK;
    }

    // Make all unused vertices red
    for (q = 0; q < DIM; q++) {
        pp h = H[q];
        if ((h != NULL) && (h->color != BLACK)) {
        	h->color = RED;
        }
    }

	printf("\nBFS Tree\n");   
    for (q = 0; q < DIM; q++) {
        pp h = Tree[q];
        if(h != NULL){
        	if(h->distance == 0){
        		printf("\nRoot is %d with color %s and distance %d\n", h->i, color(h->color), h->distance);
			} else {
				printf("Child %d from parent %d, with color %s and distance %d from root\n",h->i, h->predecessor->i, color(h->color), h->distance);
			}
        }
    }
    
    char answer = '_';
    while(answer != 'N' && answer != 'n'){
    	printf("\n\nDo you want to create a circle\n");
    	printf(" Options:\n");
    	printf(" Y: Yes, let's create a circle'\n");
    	printf(" N: No, return to main menu\n");
    	printf("\n--------------------------------------------------------------\n");
    	printf("\nSelect a proper option: (Y/N): ", answer);

   	 	fflush(stdin);
    	answer = getchar();
    	getchar();

    	printf("Your choice was: %c", answer);
    	printf("\n--------------------------------------------------------------\n");
    
    	if(answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n') {
      		printf("\n\nInvalid input, please try again.\n");
    	}
    	if(answer == 'Y' || answer == 'y'){
			int Empty = 1; // Assume all elements are NULL initially
			int n = 0; // Counts how many vertices exist in the tree
    		for (q = 0; q < DIM; q++) {
        		if (Tree[q] != NULL) {
        			Empty = 0; // An array is not NULL, so set the flag to 0 and break
        			n++; // Found a vertex
      		 	}
      		}
			// Empty Tree Check
    		if (Empty == 1) {
        		printf("\nERROR, The Tree is empty, can't create a circle\n");
        		printf("Return to main menu\n");
        		return;
			}			
			// Single vertex tree check
			if (n < 2) {
				printf("\nYour tree consists of only the root\n");
				printf("The tree needs at least 3 vertices in order to create a circle\n");
				printf("Return to main menu\n");
				return;
			}
			// Double vertex tree check
			if (n < 3) {
				printf("\nYour tree consists of only 2 vertices\n");
				printf("The tree needs at least 3 vertices in order to create a circle\n");
				printf("Return to main menu\n");
				return;
			}
			// Create a Circle from BFS Tree
			printf("\nLet's create a circle\n");
    		CreateCircle(Tree);
		}
	}
	printf("\nReturn to main menu\n");
}

// Function to create a circle
void CreateCircle(pp Tree[]){
	int q;
	pp h;
	int i, j;
    pp a = NULL;
	pp b = NULL;
	while((a == NULL) || (b == NULL)){
        printf("\nEnter 2 different vertices from the BFS tree that will create a circle:\n");
        scanf("%d%d", &i, &j);
        
        while((i == j) || (getchar() != '\n')){
        	if(i == j){
             	printf("Wrong, you entered the same vertex twice\n");
			}
        	printf("Enter again 2 different vertices from the BFS tree that will create a circle:\n");
        	while (getchar() != '\n'); // Clear the input buffer
        	scanf("%d%d", &i, &j);
		}
		a = NULL;
		b = NULL;
        for(q = 0; q < DIM; q++){
        	h = Tree[q];
        	if(h != NULL) {
        		if(i == h->i)
        		{
        			a = Tree[q]; 
				} 
				if (j == h->i){
					b = Tree[q]; 
        		}
			}
		}			
		if(a == NULL){
			printf("Vertex i = %d you entered doesn't exist in the tree\n", i);
		} 
		if(b == NULL){
			printf("Vertex j = %d you entered doesn't exist in the tree\n", j);
		}
	}
				
	pp SetA[DIM], SetB[DIM], SetAB[DIM], Circle[DIM];
    for(q = 0; q < DIM; q++) {
        SetA[q] = NULL;
        SetB[q] = NULL;
        SetAB[q] = NULL;
        Circle[q] = NULL;
    }   
    // Create SetA
    int p = 0;
    while(a->predecessor != NULL) {
    	pp aux1 = (pp)malloc(sizeof(struct node)); 
    	aux1->i = a->i;
    	aux1->j = a->predecessor->i;
    	SetA[p++] = aux1;
    	a = a->predecessor;
	}
	// Create SetB
	int k = 0;
    while(b->predecessor != NULL) {
    	pp aux2 = (pp)malloc(sizeof(struct node)); 
    	aux2->i = b->i;
    	aux2->j = b->predecessor->i;
    	SetB[k++] =  aux2;
    	b = b->predecessor;
	}
	// Find non-common edges in SetB with SetA and store them in SetAB
	int z = 0;
	for (int d = 0; d < k; d++) {
    	pp tempB = SetB[d];
    	int Common = 0;
    	for (q = 0; q < p; q++) {
        	pp tempA = SetA[q];
        	if (tempA != NULL && tempB != NULL && tempA->i == tempB->i && tempA->j == tempB->j) {
            	Common = 1;
            	break;
        	}
    	}
    	if (Common == 0) {
        	SetAB[z++] = tempB;
    	}
	}
	//  Create Circle with the sets above
	int counter = 0;
	for(q=0; q < p; q++){
		if(SetA[q] != NULL){
			Circle[counter++] = SetA[q];
		}
	}
	for(q = 0; q < z; q++){
		if(SetAB[q] != NULL){
			Circle[counter++] = SetAB[q];
		}
	}
	// Add edge (i,j)
	pp ab = (pp)malloc(sizeof(struct node)); // Allocate memory for the new edge
	ab->i = i;
	ab->j = j;
	// Check if edge (i,j) already exists
	int Edge = 0;
	for(q = 0; q < counter; q++){
		h = Circle[q];
		if(h != NULL){
			if(((ab->i == h->i) && (ab->j == h->j)) || ((ab->i == h->j) && (ab->j == h->i))) {
				Edge = 1;
			}
		}
	}
	if(Edge == 0){
		Circle[counter++] = ab;
	}
	// Print SetA
	int Empty = 0;
	printf("\nSet%d : ", i);
	for(q=0; q < DIM; q++){
		h = SetA[q];
		if(h != NULL){
			printf("(%d,%d) ", h->i, h->j);
			Empty = 1;
		}
	}
	if(Empty == 0){
		printf("Empty");
	}
	// Print SetB
	Empty = 0;	
	printf("\nSet%d : ", j);
	for(q=0; q < DIM; q++){
		h = SetB[q];
		if(h != NULL){
			printf("(%d,%d) ", h->i, h->j);
			Empty = 1;
		}
	}
	if(Empty == 0){
		printf("Empty");
	}
	if(counter > 2){	
	// Print Circle
	printf("\nCircle : ");
	} else {
		printf("\nCan't create a circle with this combination of vertices\n");
		printf("In order to create a circle you need at least 3 edges\n");
		printf("Your combination of vertices consists of edges: ");
	} 
	for(q=0; q < counter; q++){
		h = Circle[q];
		if(h != NULL){
			printf("(%d,%d) ", h->i, h->j);
		}
	}
	free(ab);	
}

// Enqueue function for BFS
void Enqueue(pp Queue[], int *head, int *tail, pp x){
	// Overflow Check
	if((*head) == ((*tail) + 1)){
		printf("Queue is full (Overflow)\n");
		return;
	}
	
	Queue[*tail-1] = x;
	if((*tail) == DIM){
		*tail = 1;
	} else {
		*tail = *tail + 1;
	}
}

 // Dequeue function for BFS
pp Dequeue(pp Queue[], int *head, int *tail){
	// Undeflow Check
	if((*head) == (*tail)){
		printf("The Queue is empty (Underflow)\n");
		return NULL;
	}
	
	pp x;
	x = Queue[*head-1];
	if((*head) == DIM){
		*head = 1;
	} else {
		*head = *head +1;
	}
	return x;
}

// PRINT
void Print(pp H[]) {
  int i;
  for(i = 0; i < DIM; i++) {
    printf("H[%d]: ", i);
    printList(H[i]);
    printf("NULL\n");
    printf("\n");
  }
}

void printList(pp head) {
  if(head == NULL) return;
  printf("(%d,%d)-> ", head->i, head->j);
  printList(head->next);
}

//Insert Node
void Insert(pp* head1, pp* head2, int i, int j){
	InsertHorizontal(head1, i, j);
	InsertVertical(head2, i, j);
}

//Delete Node
void Delete(pp* head1, pp* head2, int i, int j){
	DeleteHorizontal(head1, i, j);
	DeleteVertical(head2, i, j);
}

// Insert Vertical Element in Sorted Order Considering i
void InsertVertical(pp *head, int i, int j) {
  // Create Element
  pp curr = (pp)malloc(sizeof(struct node));
  curr->i = i;
  curr->j = j;
  // Temporary Node Pointer
  pp tmp;

  // Conditions
  int con1 = (*head == NULL);
  int Check = (*head != NULL);
  int con2 = ((*head != NULL) && (*head)->i > i);
  int con3 = ((*head != NULL) && (*head)->i < i);
	
  // List is empty
  if(con1) {
	*head= curr;
    curr->down = NULL;
    curr->up = NULL;
    printf("Node (%d,%d) was inserted in V[%d]\n", i, j, j-1);
  }
  
  // Check for duplicates
  if(Check){
 	tmp = *head;
    while(tmp->down != NULL){
    	if(tmp->i == i){
    		printf("Node (%d,%d) was inserted before in V[%d]\n", i, j, j-1);
    		return;
		}
		tmp = tmp->down;
	}
	if(tmp->i == i){
		printf("Node (%d,%d) was inserted before in V[%d]\n", i, j, j-1);
		return;
	}
 }
 
  // Insert at the start of the list
  if(con2) {
    curr->down= *head;
    curr->up = NULL;
	(*head)->up = curr;
    *head = curr;
    printf("Node (%d,%d) was inserted in V[%d]\n", i, j, j-1);
  }

  if(con3) {
    tmp = *head;
    while(tmp->down != NULL && tmp->down->i < i) {
      tmp = tmp->down;
    }
	
   // Insert at the end of the list
   if(tmp->down == NULL) {
      tmp->down = curr;
      curr->up = tmp;
      curr->down = NULL;
      printf("Node (%d,%d) was inserted in V[%d]\n", i, j, j-1);
    } 
    
	// Insert in between nodes
	else {
      curr->down = tmp->down;
      tmp->down = curr;
      curr->up = tmp;
      curr->down->up = curr;
      printf("Node (%d,%d) was inserted in V[%d]\n", i, j, j-1);
    }
  }
}

// Insert Horizontal Element in Sorted Order Considering j
void InsertHorizontal(pp *head, int i, int j) {
  // Create Element
  pp curr = (pp)malloc(sizeof(struct node));
  curr->i = i;
  curr->j = j;
  // Temporary Node Pointer
  pp tmp;

  // Conditions
  int con1 = (*head == NULL);
  int Check = (*head != NULL);
  int con2 = ((*head != NULL) && (*head)->j > j);
  int con3 = ((*head != NULL) && (*head)->j < j);
	
  // List is empty
  if(con1) {
	*head = curr;
    curr->next = NULL;
    curr->previous = NULL;
    printf("Node (%d,%d) was inserted in H[%d]\n", i, j, i-1);
  }
  
  // Check for duplicates
  if(Check){
 	tmp = *head;
    while(tmp->next != NULL){
    	if(tmp->j == j){
    		printf("Node (%d,%d) was inserted before in H[%d]\n", i, j, i-1);
    		return;
		}
		tmp = tmp->next;
	}
	if(tmp->j == j){
		printf("Node (%d,%d) was inserted before in H[%d]\n", i, j, i-1);
		return;
	}
 }
 
  // Insert at the start of the list
  if(con2) {
    curr->next = *head;
    curr->previous = NULL;
	(*head)->previous = curr;
    *head = curr;
    printf("Node (%d,%d) was inserted in H[%d]\n", i, j, i-1);
  }

  if(con3) {
    tmp = *head;
    while(tmp->next != NULL && tmp->next->j < j) {
      tmp = tmp->next;
    }
	
   // Insert at the end of the list
   if(tmp->next == NULL) {
      tmp->next = curr;
      curr->previous = tmp;
      curr->next = NULL;
      printf("Node (%d,%d) was inserted in H[%d]\n", i, j, i-1);
    } 
    
	// Insert in between nodes
	else {
      curr->next = tmp->next;
      tmp->next = curr;
      curr->previous = tmp;
      curr->next->previous = curr;
      printf("Node (%d,%d) was inserted in H[%d]\n", i, j, i-1);
    }
  }
}

// Delete Vertical Element
void DeleteVertical(pp *head, int i, int j) {
  pp tmp, aux;

  // Conditions
  int con1 = (*head == NULL);
  int con2 = ((*head != NULL) && ((*head)->i != i));
  int con3 = ((*head != NULL) && ((*head)->i == i));

  // Empty List, nothing to delete
  if(con1) {
   printf("Node (%d,%d) does not exist in V[%d]\n", i, j, j-1);
  }

  if(con2) {
    tmp = *head;

    while(tmp->down != NULL && tmp->down->i != i) {
      tmp = tmp->down;
    }

	// Delete not the head of the list
    if(tmp->down == NULL) {
      printf("Node (%d,%d) does not exist in V[%d]\n", i, j, j-1);
    } else if(tmp->down->i == i) {
      aux = tmp->down;
      tmp->next = tmp->down->down;
      
	  // Delete a node in between
      if(aux->down != NULL){
      	aux->down->up = aux->up;
		free(aux);    
		printf("Node (%d,%d) was deleted from V[%d]\n", i, j, j-1);	
	  }
	  
	  // Delete the last node
      if(aux->down == NULL){
		free(aux);  	
		printf("Node (%d,%d) was deleted from V[%d]\n", i, j, j-1);
	  }
    }
  }

	// Delete the head of the list
  if(con3) {
    aux = *head;
    *head = (*head)->down;
    free(aux);    	
    printf("Node (%d,%d) was deleted from V[%d]\n", i, j, j-1);
  }
}

// Delete Horizontal Element
void DeleteHorizontal(pp *head, int i, int j) {
  pp tmp, aux;

  // Conditions
  int con1 = (*head == NULL);
  int con2 = ((*head != NULL) && ((*head)->j != j));
  int con3 = ((*head != NULL) && ((*head)->j == j));

  // Empty List, nothing to delete
  if(con1) {
  	printf("Node (%d,%d) does not exist in H[%d]\n", i, j, i-1);
  }

  if(con2) {
    tmp = *head;

    while(tmp->next != NULL && tmp->next->j != j) {
      tmp = tmp->next;
    }

	// Delete not the head of the list
    if(tmp->next == NULL) {
      printf("Node (%d,%d) does not exist in H[%d]\n", i, j, i-1);
    } else if(tmp->next->j == j) {
      aux = tmp->next;
      tmp->next = tmp->next->next;
      
	  // Delete a node in between
      if(aux->next != NULL){
      	aux->next->previous = aux->previous;
		free(aux); 
		printf("Node (%d,%d) was deleted from H[%d]\n", i, j, i-1);   	
	  }
	  
	  // Delete the last node
      if(aux->next == NULL){
		free(aux);  
		printf("Node (%d,%d) was deleted from H[%d]\n", i, j, i-1);	
	  }
    }
  }

	// Delete the head of the list
  if(con3) {
    aux = *head;
    *head = (*head)->next;
    free(aux);   
	printf("Node (%d,%d) was deleted from H[%d]\n", i, j, i-1); 	
  }
}
