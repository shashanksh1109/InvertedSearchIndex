#include"inverted_index.h"

/* check whether data base is empty or not */
int Is_check_database_empty(Wlist_t **head)
{
	for(int i = 0; i < 27; i++)
	{
		if(head[i] == NULL)
			continue;
        return FAILURE;
	}
	return SUCCESS;
}

