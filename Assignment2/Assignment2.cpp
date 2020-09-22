/*
*  FILE          : Assignment2.c
*  PROJECT       : Assignment2
*  PROGRAMMER    : Manu Murali Student
*  FIRST VERSION : 2017-11-26
*  DESCRIPTION   :
*    This program will create a binary tree using the elemnts in the inputData
*  and print the elemnts in the binary in order by traversing throughh the tree 
*  using stack concept
*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdint.h"

// structure defining a binary tree node.  Lower sorted values will go the the left, higher to the right.
typedef struct nodeData {
	char name[30];				// character string of the data being stored in the node
	struct nodeData *left;		// pointer to the next node in the tree that is less than current node OR NULL if empty
	struct nodeData *right;		// pointer to the next node in the tree that is greater than current node OR NULL if empty
}BinaryTreeNodeDef;

struct nodeData *head = NULL;	// head of the binary tree

// This pointer is used to create new node in the linked list
BinaryTreeNodeDef *newNode;
// data to be stored in tree.  In this case there is just a character string but this could have contained more

typedef struct nodeInfo{
	BinaryTreeNodeDef *LatestNode;
	struct nodeInfo *nextNode;
}nodeAddress;

// replace inputData used for test put it in here and is created from Prog8130AssignDataCreator.exe 
char *inputData[12] = {
	{ "gyekn" },
	{ "jrqgh" },
	{ "claty" },
	{ "yuets" },
	{ "xqfhl" },
	{ "eybho" },
	{ "kcygb" },
	{ "jtwsb" },
	{ "cohep" },
	{ "bmvmt" },
	{ "eavia" },
	{ "hpycf" }
};

// FUNCTION      : addToBinaryTree
//
// DESCRIPTION   :
//   This function will store the data in newNode into a binary tree according to alphabetical order
//
// PARAMETERS    :
//   newString - the string that is to be stored in the binary tree in alphabetica order
//
// RETURNS       :
//   Nothing
void addToBinaryTree(char *newString) {
	//new node creation
	newNode = (BinaryTreeNodeDef *)malloc(sizeof(BinaryTreeNodeDef));
	BinaryTreeNodeDef *tempNode = NULL;
	BinaryTreeNodeDef *tempRNode = NULL;
	uint8_t posFlag = 0; //posFlag = 0 --> left, posFlag = 1 --> right
	// check memory is allocated or not
	if (newNode == NULL)
	{
		printf("Cannot provide memory to new element\n");
	}
	else
	{
		// copy the given string to the  new node created
		strcpy((newNode->name), newString);
		newNode->left = NULL;
		newNode->right = NULL;
		// check whether there is elements in linked list
		if (head == NULL)
		{
			head = newNode;
		}
		else
		{
			tempNode = head;
			while (tempNode != NULL)
			{
				if (strcmp(newString, tempNode->name) >= 0)
				{
					if (tempNode->right == NULL)
					{
						posFlag = 1;
						break;
					}
					else
					{
						tempNode = tempNode->right;
					}
				}
				else
				{
					if (tempNode->left == NULL)
					{
						posFlag = 0;
						break;
					}
					else
					{
						tempNode = tempNode->left;
					}
				}
			}
			if (posFlag)
			{
				tempNode->right = newNode;
			}
			else
			{
				tempNode->left = newNode;
			}
		}
	}

}

// FUNCTION      : printBinaryTree
//
// DESCRIPTION   :
//   This function will print the entire binary tree out.  
//   It uses stack concept to traverse through the binary tree. For this purpose 
//   the function make use of a structure named nodeInfo, where the address of the
//   accessing binary tree node is saved
//
// PARAMETERS    :
//   None
//
// RETURNS       :
//   Nothing
void printBinaryTree(void) {
	
	//this will points to the first element in the stack  
	nodeAddress *traverseHead = NULL;
	nodeAddress *tempAddress = NULL;
	BinaryTreeNodeDef *tempNode;
	//used to traverse through the binary tree created
	BinaryTreeNodeDef *traverseNode;
	//used to create new entry to the stack
	nodeAddress *newEntry = NULL;

	//flags used to control the loop
	uint8_t leftSignal = 1;
	uint8_t traverse = 1;

	traverseHead = (nodeAddress *)malloc(sizeof(nodeAddress));
	traverseHead->LatestNode = head;
	traverseHead->nextNode = NULL;
	traverseNode = head;
	//loop is used to traverse through the binary tree and print the element
	while (traverse)
	{
		//going to the left most element
		if (traverseNode->left != NULL && leftSignal)
		{
				//allocate memory in stack for the new element
				newEntry = (nodeAddress *)malloc(sizeof(nodeAddress));
				if (newEntry == NULL)
				{
					printf("Stack Full\n");
					break;
				}
				//making the new entry as the header pointer to the stack
				newEntry->nextNode = traverseHead;
				newEntry->LatestNode = traverseNode->left;
				traverseHead = newEntry;
				traverseNode = traverseNode->left;
		}
		else
		{
			leftSignal = 0;
			printf("%s\n", traverseHead->LatestNode->name);
			//after printing the left child and parent traversing to the right child
			if (traverseHead->LatestNode->right != NULL)
			{
				newEntry = (nodeAddress *)malloc(sizeof(nodeAddress));
				if (newEntry == NULL)
				{
					printf("Stack Full\n");
					break;
				}
				newEntry->nextNode = traverseHead->nextNode;
				newEntry->LatestNode = traverseHead->LatestNode->right;
				leftSignal = 1;
				traverseHead = newEntry;
				traverseNode = traverseHead->LatestNode;
			}
			else
			{
				tempAddress = traverseHead;
				traverseHead = traverseHead->nextNode;
				if (traverseHead == NULL)
				{
					//reached the right most element so there is no more element
					//remaining, so exit the loop
					traverse = 0;
					break;
				}
				traverseNode = traverseHead->LatestNode;
			}
			 

		}
	}
}



void main() {
	int i;

	// put all the data into the binary tree
	for (i = 0; i < 12; i++)
		addToBinaryTree(inputData[i]);

	// print the entire tree.  It should come out in alphabetical order because of the way it was stored in the tree
	printBinaryTree();
}
