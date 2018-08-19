/*
 * src/tutorial/complex.c
 *
 ******************************************************************************
  This file contains routines that can be bound to a Postgres backend and
  called by the backend in the process of processing queries.  The calling
  format for these routines is dictated by Postgres architecture.
******************************************************************************/

#include "postgres.h"
#include "string.h"
#include "fmgr.h"
#include "libpq/pqformat.h"		/* needed for send/recv functions */

PG_MODULE_MAGIC;

typedef struct intSet
{
  // char             vl_len[4];
	int		data[3];
}			intSet;


/*****************************************************************************
 * Input/Output functions
 *****************************************************************************/

PG_FUNCTION_INFO_V1(intset_in);

Datum
intset_in(PG_FUNCTION_ARGS)
{
  char   *str = PG_GETARG_CSTRING(0);
  intSet    *result;
  int i=0;
  int j=0;
  int k=0;
  char number;
  char temp[50]; //arbitrarily large
  
  result  = (intSet *) palloc(sizeof(intSet));
  
  for ( i = 0; str[i] != '\0'; i++ ) /* 'i' moves through all of original 's' */
    {
      if (( str[i] != '{') && (str[i] != '}') && (str[i] != ' ') )
	{
	  str[j++] = str[i]; /* 'j' only moves after we write a non-'chr' */
	}
    }
  str[j] = '\0'; /* re-null-terminate */

  i = 0;
  j=0;
  k=0;

  while (str[i] != '\0') {
    number = str[i];
    i++;
    if (number == ',') 
      {
	sscanf(temp, "%d", &result->data[k]);
	k++;
    
	j = 0;
	for(j=0; j<50; j++){
	  temp[j] = '\0';
	}
	j = 0;
      }
    else 
      {
	temp[j] = number;
	j++;
      }
   
    
  } 
  sscanf(temp, "%d", &result->data[k]);
 
  
PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(intset_out);

Datum
intset_out(PG_FUNCTION_ARGS)
{
  /*Intset    *intset = (Intset *) PG_GETARG_POINTER(0);
	char	   *result;

	result = psprintf("(%d)", intset->len);
	PG_RETURN_CSTRING(result);*/
  

  intSet    *intset = (intSet *) PG_GETARG_POINTER(0);
  char   *result;
  // test[(sizeof(intset->data) / sizeof(int))];
  int i = 0;
  char *result1;
  char array;   
  //char str[(2*(sizeof(intset->data) / sizeof(int))+2)];
  
    
    strcat( array, " " );

  result = psprintf( "%s",(char *) intset->data);
 
PG_RETURN_CSTRING(result);
}

