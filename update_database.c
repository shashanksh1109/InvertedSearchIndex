#include"inverted_index.h"

int update_DB(Wlist_t **head)
{
	char filename[50] ,str[50];
	int i,index,f_count;

	printf("Enter filename :");
	scanf("%s",filename);

	FILE *fptr = fopen(filename ,"r");

	/* file validation */
	if(fptr == NULL)
	{
		printf("\nERROR : file open failed!\nPlease pass valid file\n\n");
		return FAILURE;
	}
	fseek(fptr ,0L ,SEEK_END);

	if(ftell(fptr) == 0)
	{
		printf("\nERROR : file is empty!\nPlease pass valid file.\n\n");
		return FAILURE;
	}
	/* check data base is empty or not */
	if(Is_check_database_empty(head) == FAILURE)
	{
		printf("\nERROR : DATA-BASE is not empty!\ncannot update the data-base\n\n");
		return FAILURE;
	}

	/* call create data-base function */
	rewind(fptr);
	while(fscanf(fptr ,"%s" ,str) != EOF)
	{

		if(*str != '#')
		{
			printf("\nERROR : Pass valid file !\n\n");
			return FAILURE;
		}
		char *token = strtok(str ,"#;");
		index = atoi(token);

		/* create main-node */
		Wlist_t *new = create_main_node_in_update_DB(head ,index);

		token = strtok(NULL ,"#;");  //get the wordname from file
		strcpy(new->word ,token);    //store word to data base

		token = strtok(NULL ,"#;");  //get filecount from file
		f_count = atoi(token);
		new->f_count = f_count;      //store the filecount to data base 

		for(i=0;i<f_count;i++)       //run file count times
		{
			/* create sub-node */
			sublist_t *snew = malloc(sizeof(sublist_t));

			if(snew == NULL)
				return FAILURE;

			token = strtok(NULL ,"#;");
			strcpy(snew->f_name ,token);     //store filename to database

			token = strtok(NULL ,"#;");
			int w_count = atoi(token);        
			snew->w_count = w_count;         //store word count to data base

			if(new->sub_link == NULL)
			{
				new->sub_link = snew;
			}
			else
			{
				sublist_t *temp = new->sub_link;
				while(temp->link)
					temp = temp->link;

				temp->link = snew;           //establish the subnode link
			}
		}
	}
	return SUCCESS;
}

/* create_main_node_in_update_DB fun */
Wlist_t *create_main_node_in_update_DB(Wlist_t **head ,int index)
{
	Wlist_t *new = malloc(sizeof(Wlist_t));

	if(new == NULL)
		return NULL;

	new->link = NULL;
	new->sub_link = NULL;

	if(head[index] == NULL)
	{
		head[index] = new;
		return new;
	}
	Wlist_t *temp = head[index];
	while(temp->link != NULL)
	{
		temp = temp->link;
	}
	temp->link = new;

	return new;
}

