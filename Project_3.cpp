#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct makanan{
	char nama[100];
	int price;
	
	makanan *next;
	makanan *prev;
}*head[15], *tail[15];

int hash_function(char* str){
	int value = 0;
	for(int i = 0; i < strlen(str); i++){
		value += str[i];
	}
	
	return value % 15;
}

makanan* createData(char* name, int price){
	makanan* data = (makanan*)malloc(sizeof(makanan));
	strcpy(data -> nama, name);
	data -> price = price;
	data -> next = data -> prev = NULL;
	return data;
}

void insert(char* name, int price){
	int index = hash_function(name);
	makanan* newData = createData(name, price);
	if(head[index] == NULL){
		head[index] = tail[index] = newData;
	} else {
		tail[index] -> next = newData;
		newData -> prev = tail[index];
		tail[index] = newData;
	}
}

void validation(){
	int harga = 0;
	char nama[100] = "";
	while(strlen(nama) < 1){
		printf("Input product name : ");
		scanf("%[^\n]", nama); getchar();
	} while(harga < 1000){
		printf("Input produk price [min 1000] : ");
		scanf("%d", &harga); getchar();
	}
	
	insert(nama, harga);
}

void removeData(char* name){
	int index = hash_function(name);
	if(head[index] == NULL){
		printf("%s not found\n", name);
		return;
	} else if(head[index] == tail[index]){
		int price = head[index] -> price;
		free(head[index]);
		head[index] = tail[index] = NULL;
		printf("sucessfully deleted %s (%d)", name, price);
		return;
	} else {
		makanan* temp = tail[index];
		while(temp != NULL){
			if(strcmp(temp -> nama, name) == 0){
				int price = temp -> price;
				tail[index] = temp -> prev;
				tail[index] -> next = NULL;
				free(temp);
				temp = NULL;
				printf("sucessfully deleted %s (%d)", name, price);
				return;
			}
			
			temp = temp -> next;
		}
		
		printf("%s not found\n", name);
	}
}

void validationR(){
	char name[100] = "";
	while(strlen(name) < 1){
		printf("Input product name to be deleted : ");
		scanf("%[^\n]", name); getchar();
	} 
	removeData(name);
}

void print_All(){
	for(int i = 0; i < 15; i++){
		printf("%d. ", i);
		if(head[i] != NULL){
			makanan* temp = head[i];
			while(temp != NULL){
				printf("%s (%d)", temp -> nama, temp -> price);
				if(temp -> next = NULL){
					printf("-->");
				}
				
				temp = temp -> next;
			}
		}
		
		printf("\n");
	}
	
	printf("\n");
}

int main(){

	bool exit;
	while(!exit){
		system("cls");
		print_All();
		printf("Pungus Resto\n");
		printf("========\n");
		printf("1. Add Menu\n");
		printf("2. Delete Menu\n");
		printf("3. Exit\n");
		int choose = -1;
		while(choose < 1 || choose > 3){
			printf(">> ");
			scanf("%d", &choose); getchar();
		} switch(choose){
			case 1:
				validation();
				break;
			case 2:
				validationR();
				break;
			case 3:
				exit = true;
				break;
		}
	}

	return 0;
}

