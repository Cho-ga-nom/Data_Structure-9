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
	Node* head = NULL;                      // 루트 노드를 가리킬 헤드 포인터
	Node* ptr = NULL;	/* temp */          // 이진 탐색으로 찾은 값을 저장할 포인터 변수

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
			if(ptr != NULL)                            // 값을 찾았다면 출력. 그러지 못했다면 찾지 못했다는 메시지 출력
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



void inorderTraversal(Node* ptr)           // 중위순회
{
	if(ptr)
	{
		inorderTraversal(ptr->left);            // ptr->left를 인자로 재귀 호출하여 왼쪽 리프노드까지 내려감. 리프 노드의 left가 NULL이므로 호출을 멈추고 리턴.
		printf(" %d ", ptr->key);              // 리턴 받았으므로 노드의 key 출력.
		inorderTraversal(ptr->right);          // NULL을 만날 때까지 right로 내려감. right 노드가 없으면 리턴하여 한칸 위의 노드로 올라감. 이후 key 값을 출력하고
		return;                                // 다시 right 노드를 찾아 내려감. 이걸 반복하여 트리 전체 노드의 key를 출력.
	}
}

void preorderTraversal(Node* ptr)        // 전위순회
{
	if(ptr)
	{
		printf(" %d ", ptr->key);       // 루트 노드에서부터 key값을 먼저 출력. 그리고 left로 끝까지 내려가면서 차레로 key값 출력.
		preorderTraversal(ptr->left);      // left가 리프 노드에 도달하면 NULL이 리턴되고, 한칸 위의 노드에 올라가서 right를 찾아 내려감.
		preorderTraversal(ptr->right);      // right는 밑에서부터 올라가면서 key값을 출력.
		return;
	}
}

void postorderTraversal(Node* ptr)        // 후위순회
{
	if(ptr)
	{
		postorderTraversal(ptr->left);     // left를 따라 리프 노드까지 내려감. 왼쪽 리프 노드의 key가 출력.
		postorderTraversal(ptr->right);    // right 노드를 찾아서 key값 출력. 그리고 한 칸 위로 올라가서 부모 노드의 key 출력.
		printf(" %d ", ptr->key);
		return;
	}
}


int insert(Node* head, int key)
{
	Node* temp = head->left;                       // 임시 포인터 temp에 루트 노드의 주소 저장
	Node* parent;                                  // 부모 노드의 주소를 저장할 포인터
	Node *newnode = (Node*)malloc(sizeof(Node));    // 새로 삽입할 노드.
	newnode->key = key;
	newnode->left = NULL; 
	newnode->right = NULL;

	if(head->left == NULL)                    // 루트 노드가 없다면 
	{
		head->left = newnode;                 // 새로 삽입한 노드를 루트 노드로 지정.
		return 1;
	}

	while(temp != NULL)                     // temp가 리프 노드에 도달할 때까지
	{
		if(newnode->key > temp->key)        // 새로 삽입할 노드의 key가 현재 노드의 key보다 크다면
		{
			parent = temp;                  // 현재 노드의 주소를 부모 노드의 주소로서 저장
			temp = temp->right;             // temp가 오른쪽 노드로 이동
		}
		else if(newnode->key < temp->key)    // 현재 노드의 key보다 작다면
		{
			parent = temp;
			temp = temp->left;            // temp가 왼쪽 노드로 이동
		}
	}

	if(newnode->key < parent->key)        // 새로 삽입할 노드의 key가 바로 위에 있는 부모 노드의 key보다 작다면
	{
		parent->left = newnode;          // 부모 노드의 왼쪽에 연결
		return 1;
	}
	else                                 // 부모 노드의 key보다 크다면
	{
		parent->right = newnode;        // 부모 노드의 오른쪽에 연결
		return 1;
	}
}

int deleteLeafNode(Node* head, int key)
{
	Node *temp = head->left;                     // 루트 노드의 주소 저장
	Node *parent;                                // 부모 노드의 주소를 저장할 포인터 변수

	if(head->left == NULL)                            // 루트 노드가 없다면
	{
		printf("삭제할 노드가 없습니다.\n\n");         // 삭제를 수행하지 않고 리턴.
		return 1;
	}

	while((temp != NULL) && (temp->key != key))       // temp가 리프 노드에 도달하거나, 삭제할 key를 찾아내면 반복문 탈출.
	{
		if(key < temp->key)                    // 현재 노드의 key보다 작으면
		{
			parent = temp;              // 부모 노드의 주소 저장
			temp = temp->left;         // 왼쪽으로 이동
		}
		else if(key > temp->key)     // 현재 노드의 key보다 크면
		{
			parent = temp;          // 부모 노드의 주소 저장
			temp = temp->right;      // 오른쪽으로 이동
		}
	}

	if((temp->left != NULL) || (temp->right != NULL))          // left, right중 하나라도 NULL이 아니라면
	{
		printf("리프 노드가 아닙니다.\n\n");               // 리프 노드가 아닌 것이므로 삭제하지 않고 리턴.
		return 1;
	}
	else if(temp == NULL)                                  // temp가 NULL이라면 리프 노드까지 내려갔는데도 일치하는 key를 찾지 못했다는 뜻이므로 
	{
		printf("해당 리프 노드가 존재하지 않습니다.\n\n");   // 삭제하지 않고 리턴.
		return 1;
	}
	else
	{
		if(parent->left == temp)             // 삭제할 temp가 부모 노드의 왼쪽 자식이라면
		{
			free(temp);
			parent->left = NULL;          // 부모 노드의 left를 NULL로 초기화
			return 1;
		}
		else if(parent->right == temp)      // 오른쪽 자식이라면
		{
			free(temp);
			parent->right = NULL;         // right를 NULL로 초기화
			return 1;
		}
	}
}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr)                                       // ptr이 NULL 이면 NULL을 리턴
	{
		return NULL;
	}
	if(key == ptr->key)             // key를 찾으면 해당 노드의 주소 리턴
	{
		return ptr;
	}
	if(key < ptr->key)              // 찾으려는 key가 현재 노드의 key보다 작으면
	{
		return searchRecursive(ptr->left, key);    // ptr의 왼쪽 자식을 인자로 하여 재귀호출
	}
	return searchRecursive(ptr->right, key);     // 찾으려는 key가 현재 노드의 key보다 크다면 오른쪽 자식을 인자로 하여 재귀호출
}

Node* searchIterative(Node* head, int key)
{
	Node *temp = head->left;               // 루트 노드의 주소 저장

	while(temp)                      // temp가 NULL에 도달할 때까지
	{
		if(key == temp->key)      // key를 찾아내면 해당 노드의 주소 리턴
		{
			return temp;
		}
		if(key < temp->key)        // 작으면 왼쪽 자식으로 이동
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;     // 크면 오른쪽 자식으로 이동
		}
	}
	return NULL;
}


int freeBST(Node* head)
{
	Node* temp = head->left;       // 루트 노드의 주소 저장
	Node* prev = NULL;              // 부모 노드의 주소를 저장할 포인터

	while(temp->left != NULL)                 // 왼쪽 자식의 리프 노드까지 내려가면서
	{
		while(temp->right != NULL)            // 오른쪽 자식의 리프 노드까지 내려가면서
		{
			prev = temp;                 // 부모 노드의 주소 저장
		    temp = temp->right;        // 오른쪽 자식으로 이동
		    free(temp);	            // 메모리 해제
		}

		prev = temp;             // 부모 노드의 주소 저장
		temp = temp->left;       // 왼쪽 자식으로 이동
		free(temp);             // 메모리 해제
	}

	free(head);          // 헤드 노드의 메모리도 해제
}