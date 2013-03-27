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

void ClearStack(SqStack &s)
{		
	s.top = s.base;	
}

void DestroyStack(SqStack &s)
{
	if (NULL != s.base)
		free(s.base);

	s.top = s.base = NULL;
}

void GetTop(SqStack &s, SElemType &e)
{
	if (s.top == s.base)
		return;
	
	e = *(s.top - 1);
}

void StackTraverse(SqStack &s /*Status (* visit)() */)
{
	/*
	while (!StackEmpty(s))
		cout << *--s.top;
		*/

	SElemType *p = s.base;

	while (p != s.top)
		cout << *p++;
}

void LineEdit()
{
	SqStack s;
	InitStack(s);

	SElemType ch = getchar();

	while (ch != EOF)
	{
		while (ch != EOF && ch != '\n')	
		{
			switch (ch) {
				SElemType c;
				case '#' : Pop(s, c); break;
				case '@' : ClearStack(s); break;
				default : Push(s, ch);
			}	
			ch = getchar();
		}
		
		// stack traverse
		StackTraverse(s);

		ClearStack(s);	
		if (ch != EOF)
			ch = getchar();
	}
	DestroyStack(s);
}

int main(void)
{
	LineEdit();
	return 0;
}


