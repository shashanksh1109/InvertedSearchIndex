#include"inverted_index.h"

int search_DB(Wlist_t **head)
{
	char word[50];
	printf("Enter word to be search:");
	scanf("%s",word);

	for(int i=0;i<27;i++)
	{
		if(head[i] == NULL)
			continue;

		Wlist_t *temp = head[i];

		while(temp != NULL)
		{
			if(strcmp(temp->word ,word) == 0)          //compare given word with word in the database
			{
				sublist_t *stemp = temp->sub_link;
				printf("\n[%d] %*c  %-10s %-5d ",i,5,' ',temp->word ,temp->f_count);

				while(stemp != NULL)
				{
					printf("%-10s : %5d  %*c",stemp->f_name ,stemp->w_count,5,' ');
					stemp = stemp->link;
				}
				printf("\n\n");
				return SUCCESS;
			}
			temp = temp->link;
		}
	}
	return FAILURE;
}
