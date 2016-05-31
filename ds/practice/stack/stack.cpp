#include <iostream>
#include <cstdio>
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
    //TODO:
}

// Issue 2: convert Dec to Oct
// >> 1348 ==> 2504
void Conversion()
{
	cout << "(1348)10 ==> (2504)8" << endl;
    //TODO:
}

int main(void)
{
    cout << "Choose one: \n"
         << "1. LineEdit\n"
         << "2. Conversion\n"
         << ">> ";

    char c = getchar();

    switch (c)
    {
    case '1':
        LineEdit();
        break;
    case '2':
        Conversion();
        break;
    default:
        cout << "Invalid choice (" << c << ")." << endl;
        break;
    }

	return 0;
}


