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

int getLength(elem *pFirst) {
	int length = 0;
	for (elem* currentElement = pFirst; currentElement != NULL; currentElement = currentElement->nextElem) {
		length++;
	}
	return length;
}

void selectionSort(elem *pFirst) {
	int lenght = getLength(pFirst);
	for(int listPos = 0; listPos < lenght; listPos++) {
		double smallestValue = 10000000;
		elem* smallestValueElem = NULL;
		double i = 0;
		for (elem* currentElement = pFirst; currentElement != NULL; currentElement = currentElement->nextElem) {
			if (currentElement->data->price < smallestValue && i >= listPos) {
				smallestValueElem = currentElement;
				smallestValue = currentElement->data->price;
			}
			i++;
		}
		i = 0;
		if (smallestValueElem != NULL) {
			for (elem* currentElement = pFirst; currentElement != NULL; currentElement = currentElement->nextElem) {
				if (i == listPos) {
					if (smallestValue == currentElement->data->price) {
						break;
					}
					content* listPosData = currentElement->data;
					content* smallestValueElementData = smallestValueElem->data;
					currentElement->data = smallestValueElementData;
					smallestValueElem->data = listPosData;
				}
			i++;
			}
		}
	}
}

void bubbleSort(elem *pFirst, char *option) {
	int changedDataElemnts;
	do {
		changedDataElemnts = 0;
		for (elem* currentElement = pFirst; currentElement->nextElem != NULL; currentElement = currentElement->nextElem) {
			if (strcmp(option, "asc") == 0 && currentElement->data->price > currentElement->nextElem->data->price) {
				content* dataPrevious = currentElement->data;
				content* dataNext = currentElement->nextElem->data;

				currentElement->data = dataNext;
				currentElement->nextElem->data = dataPrevious;
				changedDataElemnts++;
			}
			else if (strcmp(option, "desc") == 0 && currentElement->data->price < currentElement->nextElem->data->price) {
				content* dataPrevious = currentElement->data;
				content* dataNext = currentElement->nextElem->data;

				currentElement->data = dataNext;
				currentElement->nextElem->data = dataPrevious;
				changedDataElemnts++;
			}
		}
	} while (changedDataElemnts > 0);
}





void sort(elem *pFirst) {
	while (true) {

		printf("type the name of the desired alorithm. (type \"help\" to list all algorithms. Type \"q\" to cancel sorting)\n");
		char input[50];
		scanf_s("%s", input, sizeof(input));

		printf("type \"asc\" to sort ascending, type \"desc\" to sort descending\n");
		char sortOption[50];
		scanf_s("%s", sortOption, sizeof(sortOption));

		clock_t startTime = NULL;
		bool sorted = false;
		
		if (strcmp(input, "bubble") == 0 && (strcmp(sortOption, "asc") == 0 || strcmp(sortOption, "desc") == 0)) {
			startTime = clock();
			bubbleSort(pFirst, sortOption);
			sorted = true;
			
		}else if (strcmp(input, "selection") == 0 && (strcmp(sortOption, "asc") == 0 || strcmp(sortOption, "desc") == 0)) {
			startTime = clock();
			selectionSort(pFirst);
			sorted = true;
			
		}else if (strcmp(input, "quick") == 0 && (strcmp(sortOption, "asc") == 0 || strcmp(sortOption, "desc") == 0)) {
			startTime = clock();
			sorted = true;
			
		}else if ((input[0] == 89 || input[0] == 121)) {
			break;
		}
		if (sorted) {
			clock_t endTime = clock();
			double resTime = ((double)endTime - (double)startTime) / (double)CLOCKS_PER_SEC;
			printf("sorted your list successfully in %lf seconds.\n", resTime);
			break;
		}
		else {
			printf("your input is invalid, please try again.\n");
		}
	}
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
			printf("Would you like to print your list? (y/n)\n");
			char printListInput[50];
			scanf_s("%s", printListInput, sizeof(printListInput));
			if (printListInput[0] == 89 || printListInput[0] == 121) {
				printList(pFirst);
			}
		}
		if (strcmp(input, "sort") == 0) {
			if (pFirst != NULL) {
				sort(pFirst);
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



