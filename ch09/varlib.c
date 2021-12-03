/*
file:	varlib.c
author: 2018117610_moonjunyong
datetime: 2021-11-20 00:34
description:
	a simple storage system to store name=value pairs
	with facility to mark items as part of the environment

	interface:
		VLsote(name, value)		return 1 for OK, 0 for no
		VLlookup(name)			return string or NULL if not there
		VLlist()				prints out current table
	
	envionment-related functions
		VLexport(name)			add name to list of env vars
		VLtable2envion()		copy from table to environ
		VLenviron2table()		copy from environ to table
	
	details:
		the table is stored as an array of structs that
		contain a flag for global and a single string of
		the form name=value. This allow EZ addition to the
		environment. It makes searching pretty easy, as
		long as you search for "name="
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	"varlib.h"			// varlib.h 만들어야 한다.(you make a filename that is "varlib.h")
#include	<string.h>

#define MAXVARS 200				/* a linked list would be nicer */

struct var {
    	char *str;				/* name=val string				*/
		int global;				/* a boolean					*/
};
static struct var tab[MAXVARS];	/* the table					*/

static char *new_string(char *, char *);	/* private method	*/
static struct var *find_item(char *, int);

int VLstore(char *name, char *val)
/*
	traverse list, if found, replace it, else add at end
	since there is no delete, a blank one is free one
	return 1 if trouble, 0 if ok (like a command)
*/
{
	struct var *itemp;
	char *s;
	int rv = 1;
	
	if((itemp=find_item(name,1))!= NULL 
	&& (s=new_string(name,val))!= NULL) 
	{
	    if( itemp->str)				/* has a val?		*/
		    free(itemp->str);		/* y : remove it	*/
		itemp->str = s;				
		rv = 0;						/* ok!				*/
	}
	return rv;
}
static char *new_string(char *name, char *val)
/*
	return new string of form name=value or NULL on error
*/
{
	char *retval;
	
	retval = malloc(strlen(name) + strlen(val) + 2);
	if( retval != NULL)
	    	sprintf(retval, "%s=%s", name, val);
	return retval;
}

char *VLlookup(char *name)
/*
	return value of var or empty string if not there
*/
{
	struct var *itemp;
	if( (itemp = find_item(name, 0)) != NULL)
	    	return itemp->str + 1 + strlen(name);
	return "";
}

int VLexport(char *name)
/*
	marks a var for export, adds it if not there
	return 1 for no, o for ok
*/
{
	struct var *itemp;
	int 	rv = 1;

	if( (itemp = find_item(name, 0)) != NULL) {
	    	itemp->global = 1;
		rv = 0;
	}
	else if( VLstore(name, "") == 1)
	    	rv = VLexport(name);
	return rv;
}

static struct var *find_item(char *name, int first_blank)
/*
	searches table for an item
	return ptr to struct or NULL if not found
	OR if (first_blank) then ptr to first blank one
*/
{
	int i;
	int len = strlen(name);
	char *s;

	for(i = 0; i < MAXVARS && tab[i].str != NULL; i++)
	{
	    s = tab[i].str;
	    if( strncmp(s, name, len) == 0 && s[len] == '=') {
		return &tab[i];	
	    }
	}
	if( i < MAXVARS && first_blank)
	    	return &tab[i];
	return NULL;
}

void VLlist()
/*
	performs the shell's set command
	Lists the contents of the variable table, marking each
	exported variable with the symbol '*'
*/
{
	int i;
	for(i = 0; i < MAXVARS && tab[i].str != NULL; i++)
	{
		if( tab[i].global)
		    	printf("  * %s\n", tab[i].str);
		else
		    	printf("    %s\n", tab[i].str);
	}
}
int VLenviron2table(char *env[])
/*
	initialize the variable table by loading array of strings
	return 1 for ok, 0 for not ok
*/
{
	int i;
	char *newstring;

	for(i=0; env[i] != NULL; i++)
	{
	 	if( i == MAXVARS)
			return 0;
		newstring = malloc(1+strlen(env[i]));
		if(newstring == NULL)
		    	return 0;
		strcpy(newstring, env[i]);
		tab[i].str = newstring;
		tab[i].global = 1;
	}
	while( i < MAXVARS) {			/* I know we don't need this	*/
	    tab[i].str = NULL;			/* static global are nulled		*/
		tab[i++].global = 0;		/* by default					*/
	}
	return 1;
}

char ** VLtable2environ()
/*
	build an array of pointers suitable for making a new environment
	note, you need to free() this when done to avoid a memory leaks
*/
{
	int		i,					/* index			*/
			j,					/* another index	*/
			n = 0;				/* counter			*/
	char	**envtab;			/* array of pointers */

	for(i = 0; i < MAXVARS && tab[i].str != NULL; i++)
	    	if(tab[i].global == 1)
		    	n++;
	envtab = (char **)malloc( (n+1) * sizeof(char *) );
	if( envtab == NULL)
	    	return NULL;
	
	for( i = 0, j = 0; i<MAXVARS && tab[i].str != NULL; i++)
	    	if( tab[i].global == 1)
		    	envtab[j++] = tab[i].str;
	envtab[j] = NULL;
	return envtab;
}
	
