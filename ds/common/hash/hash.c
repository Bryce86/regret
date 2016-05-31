#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct nlist { /* table entry: */
	struct nlist *next; /* next entry in chain */
	char *name; /* defined name */
	char *defn; /* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table*/

/* hash: form hash value for string s */
unsigned int hash(char *s)
{
	unsigned int hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np; /* found */

	return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned int hashval;

	if ((np = lookup(name)) == NULL) { /* not found */
		np = (struct nlist *)malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else /* already there */
		free((void *)np->defn); /* free previous defn */
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;

	return np;
}

/* run it */
int main(int argc, char *argv[])
{
	struct nlist *p;
	install("MAX", "max");	
	install("MIN", "min");	
	install("PRINT", "printf");	

	p = install("MAX", "hello");	
	printf("%s, %s\n", p->name, p->defn);

	p = lookup("MIN");
	printf("%s, %s\n", p->name, p->defn);

	/* To-Do: free hashtab */

	return 0;	
}
