#include <iostream>
using namespace std;

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 100

typedef char SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	SElemType stacksize;
}SqStack;

void InitStack(SqStack &s)
{
}


void Push(SqStack &s, SElemType e)
{

}

void Pop(SqStack &s, SElemType &e)
{

}

bool StackEmpty(SqStack &s)
{
	return false;
}

void ClearStack(SqStack &s)
{		

}

void DestroyStack(SqStack &s)
{
	
}

void GetTop(SqStack &s, SElemType &e)
{

}

void StackTraverse(SqStack &s /*Status (* visit)() */)
{

}

// Issue 1: repeat your input.
// >> abcd
// >> abcd
void LineEdit()
{

}

// Issue 2: convert Dec to Oct
// >> 1348 ==> 2504
void conversion()
{
	cout << "(1348)10 ==> (2504)8" << endl;
}

int main(void)
{
	LineEdit();
	return 0;
}


