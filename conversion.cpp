#include <iostream>
using namespace std;

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 100

typedef int SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	SElemType stacksize;
}SqStack;

void InitStack(SqStack &s)
{
	s.base = (SElemType *)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
	if (NULL == s.base)
		return;

	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
}

void Push(SqStack &s, SElemType e)
{
	if (s.top - s.base >= s.stacksize)
	{
		s.base = (SElemType *)realloc(s.base, s.stacksize+STACK_INCREMENT);
		if (NULL == s.base)
			return;

		s.top = s.base + s.stacksize;
		s.stacksize += STACK_INCREMENT;
	}

	*s.top++ = e;
}

void Pop(SqStack &s, SElemType &e)
{
	e = *--s.top;
}

bool StackEmpty(SqStack &s)
{
	if (s.top == s.base)
		return true;
	else
		return false;
}

void conversion()
{
	cout << "(1348)10 ==> (2504)8" << endl;

	SqStack s;
	InitStack(s);
	SElemType N;

	cin >> N;

	while (N) 
	{
		Push(s, N % 8);
		N = N / 8;
	}

	while (!StackEmpty(s))
	{
		SElemType n;
		Pop(s, n);
		cout << n << endl;
	}

	/*
	for (SElemType i = 0; i < 4; i++)
		cout << s.base[i] << endl;
	*/
}

int main(void)
{
	conversion();
	return 0;
}


