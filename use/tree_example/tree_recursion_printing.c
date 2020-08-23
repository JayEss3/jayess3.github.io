#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode{
	int data;
	struct treeNode *left;
	struct treeNode *right;
}treeNode;

treeNode *headNode=NULL;

treeNode *addNode(treeNode *tempPtr, int newInt);
void printTree(treeNode *tempPtr);
void preOrderPrint(treeNode*tempPtr);
void postOrderPrint(treeNode*tempPtr);

int main(void){
	
	int root, leaves, input;
	treeNode *tempPtr=headNode;
	
	printf("What root do you want?   ");
	scanf("%d", &root);
	printf("How many leaves?   ");
	scanf("%d", &leaves);
	
	treeNode *headNode=(treeNode *) malloc(sizeof(treeNode));
	headNode->data=root;
	headNode->left=NULL;
	headNode->right=NULL;
	
	for(int i=0;i<leaves;i++){
		printf("Input number: ");
		scanf("%d", &input);
		addNode(headNode, input);
	}
	
	printf("\n\nPrinting Tree In Order\n");
	printTree(headNode);
	printf("\n\nPrinting Tree Pre Order\n");
	preOrderPrint(headNode);
	printf("\n\nPrinting Tree Post Order\n");
	postOrderPrint(headNode);
	printf("\n");
}

treeNode *addNode(treeNode *tempPtr, int newInt){
	treeNode *newNode;
	if(tempPtr==NULL){
		newNode=(treeNode*) malloc(sizeof(treeNode));
		newNode->data=newInt;
		newNode->left=NULL;
		newNode->right=NULL;
		
		return newNode;
	}
	else{
		if(newInt<tempPtr->data){
			tempPtr->left=addNode(tempPtr->left, newInt);
		}
		else if(newInt>tempPtr->data){
			tempPtr->right=addNode(tempPtr->right, newInt);
		}
	}
	return tempPtr;
}

void printTree(treeNode *tempPtr){
	if(tempPtr!=NULL){
		printTree(tempPtr->left);
		printf("\t%d", tempPtr->data);
		printTree(tempPtr->right);
	}
	return;
}

void preOrderPrint(treeNode*tempPtr){
	if(tempPtr!= NULL){
		printf("\t%d", tempPtr->data);
		preOrderPrint(tempPtr->left);
		preOrderPrint(tempPtr->right);
	}
	return;
}

void postOrderPrint(treeNode*tempPtr){
	if(tempPtr!= NULL){
		postOrderPrint(tempPtr->left);
		postOrderPrint(tempPtr->right);
		printf("\t%d", tempPtr->data);
	}
	return;
}