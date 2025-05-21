#include "inverted_index.h"

int create_DB(Flist_t *file_head ,Wlist_t *arr[])
{
	/* check data base is empty or not */
	if(Is_check_database_empty( arr ) == FAILURE)
	{   
		printf("\nERROR : DATA-BASE is not empty!\ncannot create the data-base\n\n");
		return FAILURE;
	}

	while(file_head != NULL)
	{
		char *fname = file_head->f_name;
		file_head = file_head->link;

		FILE *fptr = fopen(fname ,"r");

		while(1)
		{
			char *str;

			fscanf(fptr ,"%s" ,str);         //get word from file
			if(feof(fptr))
			{
				break;
			}
			else
			{
				create_hash_table(arr ,fname ,str);
			}
		}
	}
	return SUCCESS;
}

/* creating main-node */
int create_hash_table(Wlist_t *arr[] ,char *file_name ,char *word_name)
{

	/* generate key */
	char ch = *word_name;
	int index;
	if(ch >= 65 && ch <= 90)    //if character is uppercase convert to lowercase
	{
		ch = ch+32;
	}

	if(ch >= 97 && ch <= 122)   
		index = ch % 97;       //generate key for lower case character
	else
		index = 26;            //for special characters & numbers index=26

	if(arr[index] == NULL)
	{
		arr[index] = create_main_node(word_name ,file_name);
		(arr[index])->sub_link = create_sub_node(file_name);

		return SUCCESS;
	}
	Wlist_t *temp = arr[index],*prev = NULL;

	while(temp != NULL)
	{
		if(strcmp(temp->word ,word_name) == 0)
		{
			sublist_t *stemp = temp->sub_link, *sprev = NULL;
			while(stemp != NULL)
			{
				if(strcmp(stemp->f_name ,file_name) == 0)
				{
					stemp->w_count ++;
					return SUCCESS;
				}
				sprev = stemp;
				stemp = stemp->link;
			}
			temp->f_count ++;
			sprev->link = create_sub_node(file_name);
			return SUCCESS;
		}
		prev = temp;
		temp = temp->link;
	}

	prev->link = create_main_node(word_name ,file_name);
	prev->link->sub_link = create_sub_node(file_name);

	return SUCCESS;
}

/* create main node */
Wlist_t *create_main_node(char *word_name ,char *file_name)
{

	Wlist_t *new = malloc(sizeof(Wlist_t));

	if(new == NULL)
		return NULL;

	new->f_count = 1;
	strcpy(new->word ,word_name);
	new->link = NULL;

	return new;
}

/* create a sub-node */
sublist_t *create_sub_node(char *file_name)
{
	sublist_t *subnew = malloc(sizeof(sublist_t));

	if(subnew == NULL)
		return NULL;

	subnew->w_count = 1;
	strcpy(subnew->f_name ,file_name);
	subnew->link = NULL;

	return subnew;
}
