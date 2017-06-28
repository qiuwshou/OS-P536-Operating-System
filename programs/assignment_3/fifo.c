//queue manipulation
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int num_process = 102;// 100 + 2(head,tail) used for key value 
#define NUM_PROCESS 100
struct node{
  int pid;
  int key_value;
  int priority;
  struct node *prev;
  struct node *next;
};

struct node *head;
struct node *tail;



struct node *newNode(int pid, int priority){
  struct node *new_node = (struct node *)malloc(sizeof(struct node));
  new_node->pid  = pid;
  new_node->priority = priority;
  num_process = num_process -1 ;
  new_node->key_value = num_process;
  return new_node;
} 

void initial(){
  head = newNode(-1,0);
  tail = newNode(-2,0);
  head->prev = NULL;
  tail->next = NULL;
  head->next = tail;
  tail->prev = head;
}

int find_pid(int pid){
  struct node *temp = head->next;
  while(is_empty() != 1){
    if(temp->pid == pid){
      printf("process_id:%d,key_value:%d,priority:%d\n",temp->pid,temp->key_value,temp->priority);
      return 1;
    }
    else{
      temp = temp->next;
    }
  }
  return 0;
}

int find_key_value(int key_value){
  struct node *temp = head->next;
  while(is_empty() != 1){
    if(temp->key_value == key_value){
      printf("process_id:%d,key_value:%d,priority:%d\n",temp->pid,temp->key_value,temp->priority);
      return 1;
    }
    else{
      temp = temp->next;
    }
  }
  return 0;
}

//insert before the tail
void enque(int pid, int priority){
  struct node *curr = newNode(pid, priority);
  struct node *temp = tail->prev;
  if(is_empty() == 1 ){ // check if the queue is empty
    head->next = curr;
    tail->prev = curr;
    curr->next = tail;
    curr->prev = head;
  }
  else{
    curr->prev = temp;
    curr->next = tail;
    tail->prev = curr;
    temp->next = curr;
  }
  return;
}

//extract after the head - equals to deletion
void deque(){
  struct node *curr = head->next;
  struct node *next = curr->next;
  if(is_empty() == 1 ){ // check if the queue is empty
    return;
  }
  else{
    head->next = next;
    next->prev = head;
  }
}

//insert  by the priority 
void insert(int pid,int priority){
  struct node *curr = newNode(pid, priority);
  if(is_empty() == 1) { //insert the process if queue is empty
    head->next = curr;
    tail->prev = curr;
    curr->prev = head;
    curr->next = tail;
   
  }
  else{ // insert after the process wih higher prioriy
    struct node *temp = head->next;
    while(temp->key_value < NUM_PROCESS){
      if(temp->priority <= priority){
        struct node *temp_prev = temp->prev;
	temp_prev->next = curr;
        temp->prev = curr;
	curr->next = temp;
	curr->prev = temp_prev;
	return;
      }
      else{
	temp = temp->next;
	if(temp->key_value >= NUM_PROCESS){
          struct node * temp_prev = temp->prev;
	  temp->prev = curr;
          temp_prev->next = curr;
	  curr->next = temp;
	  curr->prev = temp_prev;
	}
      }
    } 
  }
}


int is_empty(){
  struct node *temp = head->next;
  if(temp->key_value >= NUM_PROCESS){
    return 1;
  }
  else{
    return 0;
  }
}

void print_all(){
  struct node *temp = head->next;
  while(temp->key_value < NUM_PROCESS){
    printf("process_id:%d,key_value:%d,priority:%d\n",temp->pid,temp->key_value,temp->priority);
    temp = temp->next;
  }
  return;
}





int main(){
  initial();
  printf("here is my queue\n");
  enque(1,10);
  enque(2,10);
  enque(3,10);
  print_all();
  printf("deque one process.\n");
  deque();
  print_all();
  printf("insert with different priority.\n");
  insert(4,20);
  insert(5,5);
  print_all();
}
