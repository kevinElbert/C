#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue{
	char name[100];
	char status[100];
	int priority;
	
	queue* next;
	queue* prev;
}*head, *tail;

queue* queueCustomer(char *name, char *status, int priority){
	queue* p = (queue*) malloc(sizeof(queue));
	strcpy(p->status, status);
	strcpy(p->name, name);
	p->priority = priority;
	p->next = p->prev = NULL;
	return p;
}

void push(queue *p){
	if(head == NULL){
		head = tail = p;
	} else{
		if(p->priority < head->priority){
			if(head == NULL){
				head = tail = p;
			} else{
				p->next = head;
				head->prev = p;
				head = p;
			}
		} else if(p->priority >= tail->priority){
			if(head == NULL){
				head = tail = p;
			} else{
				tail->next = p;
				p->prev = tail;
				tail = p;
			}
		} else{
			queue *temp = head;
			while(temp->next->priority <= p->priority){
				temp = temp->next;
			}
			p->next = temp->next;
			temp->next->prev = p;
			temp->next = p;
			p->prev = temp;
			
		}
	}
}

void addCustomer(){
	
	char status[100];
	char name[100];
	int priority;
	
	do{
		scanf("%s %[^\n]",status,name); getchar();
	} while(strcmp(status, "VVIP") != 0 && strcmp(status, "VIP") != 0 && strcmp(status, "Member") != 0 && strcmp(status, "Guest") != 0);
	
	if(strcmp(status, "VVIP") == 0){
		priority = 1;
	} else if(strcmp(status, "VIP") == 0){
		priority = 2;
	} else if(strcmp(status, "Member") == 0){
		priority = 3;
	} else{
		priority = 4;
	}
	push(queueCustomer(status, name, priority));
}

int main(){
	bool exit;
	while(!exit){
		system("cls");
		printf("============================\n");
		printf("SUNIB Restaurant Reservation\n");
		printf("============================\n\n");
		
		printf("Waiting Line:\n");
		if(head == NULL){
			printf("Queue is empty\n");
		} else{
			queue* temp = head;
			while(temp != NULL){
				printf("%s %s\n", temp->status, temp->name);
				temp = temp->next;
			}
		}
		
		printf("\n1. Add Customer to Queue\n");
		printf("2. Serve One\n");
		printf("3. Serve All\n");
		printf("4. Dismiss Queue\n");
		printf("0. Exit\n");
		int choose;
		do{
			printf("Input Menu Number: ");
			scanf("%d", &choose); getchar();
		} while(choose < 0 || choose > 4);
		
		switch(choose){
			case 1:
				addCustomer();
				break;
			case 2:
				printf("Attention! %s is being server at %s table", head->name, head->status); getchar();
				if (head == tail){
					free(head);
					head = tail = NULL;
				} else {
					queue *next = head->next;
					next->prev = NULL;
					head->next = NULL;
					head = next;
				}
				break;
			case 3:
				while(head != NULL){
					printf("Attention! %s is being server at %s table\n", head->name, head->status);
					if (head == tail){
						free(head);
						head = tail = NULL;
					} else {
						queue *next = head->next;
						next->prev = NULL;
						head->next = NULL;
						head = next;
					}
				}
				getchar();
				break;
			case 4:
				while(head != NULL){
					if (head == tail){
						free(head);
						head = tail = NULL;
					} else {
						queue *next = head->next;
						next->prev = NULL;
						head->next = NULL;
						head = next;
					}
				}
				printf("End of the day!\n"); getchar();
				break;
			case 0:
				exit = true;
				break;
		}
		
	}

	return 0;
}

