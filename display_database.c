#include "inverted_index.h"

int display_DB(Wlist_t **head)
{
	if(Is_check_database_empty(head) == SUCCESS)
	{
		printf("\nERROR : DATABASE is EMPTY !\n\n");
		return FAILURE;
	}

	for(int i=0;i<27;i++)
	{
		if(head[i] == NULL)
			continue;

		Wlist_t *temp = head[i];
		while(temp)
		{
			printf("[%d] %*c  %-10s  %-5d ",i,5,' ',temp->word ,temp->f_count);
			sublist_t *stemp = temp->sub_link;
			while(stemp)
			{
				printf("%-10s : %5d  %*c ",stemp->f_name ,stemp->w_count,5,' ');
				stemp = stemp->link;
			}
			putchar('\n');
			temp = temp->link;
		}
	}
	return SUCCESS;
}
