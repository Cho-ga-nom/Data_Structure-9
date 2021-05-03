/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("[----- [조수현]  [2018038084] -----]\n\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr)
	{
		inorderTraversal(ptr->left);
		printf(" %d ", ptr->key);
		inorderTraversal(ptr->right);
		return;
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr)
	{
		printf(" %d ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
		return;
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr)
	{
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" %d ", ptr->key);
		return;
	}
}


int insert(Node* head, int key)
{
	Node* temp = head->left;
	Node* parent;
	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->key = key;
	newnode->left = NULL;
	newnode->right = NULL;

	if(head->left == NULL)
	{
		head->left = newnode;
		return 1;
	}

	while(temp != NULL)
	{
		if(newnode->key > temp->key)
		{
			parent = temp;
			temp = temp->right;
		}
		else if(newnode->key < temp->key)
		{
			parent = temp;
			temp = temp->left;
		}
	}

	if(newnode->key < parent->key)
	{
		parent->left = newnode;
		return 1;
	}
	else
	{
		parent->right = newnode;
		return 1;
	}
}

int deleteLeafNode(Node* head, int key)
{
	Node *temp = head->left;
	Node *parent;

	if(head->left == NULL)
	{
		printf("삭제할 리프 노드가 없습니다.\n\n");
		return 1;
	}

	while((temp != NULL) && (temp->key != key))
	{
		if(key < temp->key)
		{
			parent = temp;
			temp = temp->left;
		}
		else if(key > temp->key)
		{
			parent = temp;
			temp = temp->right;
		}
	}

	if((temp->left != NULL) || (temp->right != NULL))
	{
		printf("리프 노드가 아닙니다.\n\n");
		return 1;
	}
	else
	{
		if(parent->left == temp)
		{
			parent->left = NULL;
			return 1;
		}
		else if(parent->right == temp)
		{
			parent->right = NULL;
			return 1;
		}
	}
}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr)
	{
		return NULL;
	}
	if(key == ptr->key)
	{
		return ptr;
	}
	if(key < ptr->key)
	{
		return searchRecursive(ptr->left, key);
	}
	return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)
{
	Node *temp = head->left;

	while(temp)
	{
		if(key == temp->key)
		{
			return temp;
		}
		if(key < temp->key)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	return NULL;
}


int freeBST(Node* head)
{
	Node* temp = head->left;
	Node* prev = NULL;

	while(temp->left != NULL)
	{
		while(temp->right != NULL)
		{
			prev = temp;
		    temp = temp->right;
		    free(temp);	
		}

		prev = temp;
		temp = temp->left;
		free(temp);
	}

	free(head);
}