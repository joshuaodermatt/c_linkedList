#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

typedef struct {
	char name[50];
	double price;
}content;


struct elem {
	elem* nextElem;
	content* data;
};

int generateRandomNumber() {
	return (int)((rand() % 100) * 10);
}


char generateRandomChar() {
	int num = (int)(rand() % 25) + 65;
	char res = num;
	return res;
}

content* createDataPackage() {
	content* newContent = NULL;
	newContent = (content*)malloc(sizeof(content));

	double randomNum = (double) generateRandomNumber();
	newContent->price = randomNum;
	for (int i = 0; i < 3; i++) {
		char randomChar = generateRandomChar();
		newContent->name[i] = randomChar;
	}
	newContent->name[3] = (char)0;
	return newContent;
}

elem* createList(int count) {
	elem* pFirst = NULL;
	elem* pLast = NULL;
	elem* pNew = NULL;

	for (int i = 0; i < count; i++) {
		pNew = (elem*)malloc(sizeof(elem));
		if (pNew == NULL) exit(-1);
		pNew->nextElem = NULL;

		pNew->data = createDataPackage();

		if (pFirst == NULL) pFirst = pNew;
		if (pLast == NULL) pLast = pNew;
		else {
			pLast->nextElem = pNew;
			pLast = pNew;
		}

	}
	return pFirst;
}


void printList(elem* pFirst) {
	int i = 0;
	printf("\nnumber\tname\tvalue\n-----------------------\n");
	for (elem* element = pFirst; element != NULL; element = element->nextElem) {
		printf("%i\t%s\t%f\n", i, element->data->name, element->data->price);
		i++;
	}
}

void delList(elem* pCurrent) {
	elem* pTemp;
	while (pCurrent != NULL) {
		pTemp = pCurrent;
		pCurrent = pCurrent->nextElem;
		free(pTemp);
	}
}

void flipPos(elem* element) {
	content* dataPrevious = element->data;
	content* dataNext = element->nextElem->data;

	element->data = dataNext;
	element->nextElem->data = dataPrevious;

}

void bubleSort(elem *pFirst) {
	int changedDataElemnts = 0;
	while (changedDataElemnts > 0) {
		changedDataElemnts = 0;
		for (elem* currentElement = pFirst; currentElement->nextElem != NULL; currentElement = currentElement->nextElem) {
			if (currentElement->data->price > currentElement->data->price) {
				flipPos(currentElement);
				changedDataElemnts++;
			}
		}
	}
	
}


elem* sort(elem *pFirst) {
	printf("type the name of the desired alorithm. (type help to list all algorithms");
	char input[50];
	scanf_s("%s", input, sizeof(input));
	if (strcmp(input, "buble") == 0) {
		bubleSort(pFirst);
	}
	if (strcmp(input, "selection") == 0) {
	
	}
	if (strcmp(input, "quick") == 0) {

	}
	return NULL;
}


int main() {
	elem* pFirst = NULL;
	while (true) {
		printf("Please enter command. (enter \"help\" to see all commands)\n");
		char input[50];
		scanf_s("%s", input, sizeof(input));
		if (strcmp(input, "help") == 0) {
			printf("---------------\nq\t -> will quit the application\ncreate\t -> to create a list\nsort\t -> to sort the crated list\ndel\t -> to delete the created List\nlist\t -> list the created List\n---------------\n");
		}
		if (strcmp(input, "q") == 0) {
			break;
		}
		if (strcmp(input, "create") == 0) {
			while (true) {
				printf("Please enter the desired length of the List.\n");
				char sizeOfListInput[50];
				scanf_s("%s", sizeOfListInput, sizeof(sizeOfListInput));
				int sizeOfList;
				if (atoi(sizeOfListInput) == 0) {
					printf("input must be numeric.\n");
				}
				else {
					sizeOfList = atoi(sizeOfListInput);
					if (sizeOfList > 1) {
						clock_t startTime = clock();
						try {
							pFirst = createList(sizeOfList);
							clock_t endTime = clock();
							double resTime = ((double)endTime - (double)startTime) / (double)CLOCKS_PER_SEC;
							printf("List consisting of %i elements was created in %lf seconds\n", sizeOfList, resTime);
						}
						catch (...) {
							printf("Something went wrong! Please try again\n");
						}
						break;
					}
					else {
						printf("list has to consist of at least 2 elements.\n");
					}
				}
			}
			printf("Would you like to print your list? (Y/n)\n");
			char printListInput[50];
			scanf_s("%s", printListInput, sizeof(printListInput));
			if (printListInput[0] == 89 || printListInput[0] == 121 || print) {
				printList(pFirst);
			}
		}
		if (strcmp(input, "sort") == 0) {
			if (pFirst != NULL) {
				pFirst = sort(pFirst);
			}
		}
		if (strcmp(input, "del") == 0) {
			delList(pFirst);
			pFirst = NULL;
		}
		if (strcmp(input, "list") == 0) {
			if (pFirst != NULL) {
				printList(pFirst);
			}
		}
	}
	system("pause");
	return 0;
}



