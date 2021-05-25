//BINOMIALHEAP

#include<stdio.h>
#include<stdlib.h>


struct node{
	struct node* left;
	struct node* sib;
	int data;
	struct node* p;
	int degree;
};

struct lnode{
	struct node* lnod;
	struct lnode* next;
};
struct queue{
	struct lnode* head;
	struct lnode* tail;
};
struct node* CreateNode(int key){
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->data = key;
	temp->degree = 0;
	temp->left = NULL;
	temp->sib = NULL;
	temp->p = NULL;
	return temp;
}


struct node* LINK(struct node* y,struct node* z){
	y->p = z;
	y->sib = z->left;
	z->left = y;
	z->degree++;
	return z;
}
struct node* MERGE(struct node* H1,struct node* H2){
	if(H1 == NULL)return H2;
	if(H2 == NULL)return H1;
	struct node* head;
	struct node* temp1=H1;
	struct node* temp2=H2;
	struct node* tail;
	if(H1->degree <= H2->degree){
		head = H1;
		temp1 = H1->sib;
	}
	else{
		head = H2;
		temp2 = H2->sib;
	}
	
	tail = head;
	while(temp1 != NULL && temp2 != NULL){
		if(temp1->degree <= temp2->degree){
			tail->sib = temp1;
			temp1 = temp1->sib;
		}
		else{
			tail->sib = temp2;
			temp2 = temp2->sib;
		}
		tail = tail->sib;
	}
	if(temp1 != NULL)tail->sib = temp1;
	else tail->sib = temp2;
	
	return head;
}
struct node* UNION(struct node* H1,struct node* H2){
	if(H1 == NULL)return H2;
	if(H2 == NULL)return H1;
	
	struct node* H = MERGE(H1,H2);
	if(H== NULL)return NULL;
	struct node* prev = NULL;
	struct node* x = H;
	struct node* next = x->sib;
	
	while(next != NULL){
		if(x->degree != next->degree || (next->sib != NULL) && (next->sib->degree == x->degree) ){
			prev = x;
			x = next;
		}
		else if(x->data <= next->data){
			x->sib = next->sib;
			LINK(next,x);
		}
		else{
			if(prev == NULL)H = next;
			else prev->sib = next;
			
			LINK(x,next);
			x=next;
		}
		
		next = x->sib;	
	
	}
	return H;
	

}
struct node* INSERT(struct node* H,int data){
	struct node* H1 = CreateNode(data);
	H = UNION(H,H1);
	return H;

}

struct node* FINDMIN(struct node* H){
	if(H == NULL)return NULL;
	struct node* temp = H;
	struct node* min = H;
	while(temp!= NULL){
		if(temp->data < min->data)min = temp;
		temp = temp->sib;
	}
	return min;

}
struct node* MAKEHEAP(struct node* x){
	if(x->sib == NULL)return x;
	struct node* y = MAKEHEAP(x->sib);
	x->sib->sib = x;
	return y;
}
struct node* EXTRACTMIN(struct node* H){
	if(H== NULL){
	printf("-1");
	return H;
	}
	struct node* min = FINDMIN(H);
	printf("%d",min->data);
	struct node* H1 = NULL;
	struct node* temp= H;
	if(H->data == min->data)temp = NULL;
	else{
		while(temp->sib != NULL){
			if(temp->sib->data == min->data )break;
			temp = temp->sib;
		}
	}
	
	if(temp==NULL && min->sib == NULL)H = NULL;
	else if(temp == NULL)H = min->sib;
	else if(temp->sib == NULL)temp = NULL;
	else temp->sib = min->sib;
	
	if(min->left != NULL){
		H1 = MAKEHEAP(min->left);
		min->left->sib = NULL;
	}
	H = UNION(H1,H);
	
	free(min);
	return H;
	
}
struct node* FIND(struct node* H,int data){
	struct node* temp = H;
	struct node* ptr = NULL;
	if(temp->data == data){
	ptr = temp;
	return ptr;
	}
	if(temp->left != NULL && ptr == NULL)ptr = FIND(temp->left,data);
	if(temp->sib != NULL && ptr == NULL)ptr = FIND(temp->sib,data);
	return ptr;


}
struct node* DECREASEKEY(struct node* H,int x,int y){
	if(H == NULL || x < y)return H;
	struct node* temp = FIND(H,x);
	if(temp == NULL )return H;
	
	temp->data = x-y;
	
	struct node* pt = temp->p;
	int z;
	while(pt != NULL && temp->data < pt->data){
		z = temp->data;
		temp->data = pt->data;
		pt->data = z;
		temp = pt;
		pt = pt->p;
		
	}
	return H;

}
struct node* DELETE(struct node* H,int data){
	if(H== NULL){
	printf("-1");
	return NULL;}
	printf("%d",data);
	
	struct node* temp1 = FIND(H,data);
	if(temp1 == NULL )return H;
	
	temp1->data = -1000000;
	
	struct node* pt = temp1->p;
	int z;
	while(pt != NULL && temp1->data < pt->data){
		z = temp1->data;
		temp1->data = pt->data;
		pt->data = z;
		temp1 = pt;
		pt = pt->p;
		
	}
	temp1->data = data;
	struct node* min = temp1;
	struct node* H1 = NULL;
	struct node* temp= H;
	if(H->data == min->data)temp = NULL;
	else{
		while(temp->sib != NULL){
			if(temp->sib->data == min->data )break;
			temp = temp->sib;
		}
	}
	
	if(temp==NULL && min->sib == NULL)H = NULL;
	else if(temp == NULL)H = min->sib;
	else if(temp->sib == NULL)temp = NULL;
	else temp->sib = min->sib;
	
	if(min->left != NULL){
		H1 = MAKEHEAP(min->left);
		min->left->sib = NULL;
	}
	H = UNION(H1,H);
	free(min);
	return H;

}


struct queue* INSERTQ(struct queue* Q,struct node* temp){
	struct lnode* temp1 = (struct lnode*)malloc(sizeof(struct lnode));
	temp1->lnod = temp;
	temp1->next = NULL;
	if(Q->head == NULL && Q->tail == NULL){
		Q->head = temp1;
		Q->tail = temp1;
		return Q;
	}
	Q->tail->next = temp1;
	Q->tail = Q->tail->next;
	return Q;

}
struct node* POP(struct queue* Q){
	if(Q->head == NULL)return NULL;
	if(Q->head == Q->tail){
	Q->head = NULL;
	struct node* temp = Q->tail->lnod;
	Q->tail = NULL;
	return temp;}
	else{
		struct node* temp = Q->head->lnod;
		struct lnode* ptr = Q->head;
		Q->head = Q->head->next;
		ptr->next = NULL;
		free(ptr);
		return temp;
	
	}
}
void PRINTTREE(struct node* temp){
	if(temp == NULL)return;
	struct queue* T = (struct queue*)malloc(sizeof(struct queue));
	T->head = NULL;
	T->tail = NULL;
	T = INSERTQ(T,temp);
	temp = temp->sib;
	while(T->head != NULL && T->tail != NULL){
		while(temp != NULL){
		T = INSERTQ(T,temp);
		temp = temp->sib;
		}
		temp = POP(T);
		printf("%d ",temp->data);
		temp = temp->left;
	
	}
	free(T);
	return;

}
void PRINT(struct node* H){
	struct queue* Q = (struct queue*)malloc(sizeof(struct queue));
	Q->head = NULL;
	Q->tail = NULL;
	struct node* temp = H;
	while(temp!= NULL){
		Q = INSERTQ(Q,temp);
		temp = temp->sib;
	}
	int i = 1;
	while(Q->head != NULL){
		temp = POP(Q);
		printf("%d ",temp->data);
		PRINTTREE(temp->left);
	}
	
	
	
	
}


void main(){
	char x;
	int k,z;
	struct node* H = NULL;
	while(1){
	scanf("%c",&x);
	
	if(x=='i'){
		scanf("%d",&k);
		H = INSERT(H,k);
	}
	if(x=='m'){
		struct node* min = FINDMIN(H);
		if(min == NULL)printf("-1");
		else printf("%d",min->data);
		printf("\n");
	}
	if(x=='x'){
		H = EXTRACTMIN(H);
		printf("\n");
	}
	if(x=='p'){
		if(H == NULL)printf("-1");
		else PRINT(H);
		printf("\n");
	}
	if(x=='r'){
		scanf("%d %d",&k,&z);
		struct node* temp = FIND(H,k);
		H = DECREASEKEY(H,k,z);
		if(temp == NULL )printf("-1");
		else printf("%d",k-z);
		printf("\n");
		
	}
	if(x=='d'){
		scanf("%d",&k);
		H = DELETE(H,k);
		printf("\n");
	}
	if(x=='e'){break;}
	}

}
