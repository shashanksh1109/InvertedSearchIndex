#include"inverted_index.h"

int save_DB(Wlist_t **head)
{
	char fname[50];
	printf("Enter filename:");
	scanf("%s",fname);

	FILE *fptr = fopen(fname ,"w");

	/* file validation */
	if(fptr == NULL)
	{
		printf("Error : %s file is not opened !\n",fname);
		return FAILURE;
	}
	for(int i=0;i<27;i++)
	{
		if(head[i] == NULL)
			continue;
		Wlist_t *temp = head[i];

		while(temp)
		{
			fprintf(fptr ,"%s%d;%s;%d;" ,"#",i,temp->word,temp->f_count);
			sublist_t *stemp = temp->sub_link; 
			while(stemp)
			{
				fprintf(fptr ,"%s;%d;" ,stemp->f_name ,stemp->w_count);
				stemp = stemp->link;
			}
			fprintf(fptr ,"%s\n" ,"#");
			temp = temp->link;
		}
	}
	return SUCCESS;
}
