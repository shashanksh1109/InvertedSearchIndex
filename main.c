#include "inverted_index.h"

int main(int argc,char *argv[])
{
	Flist_t *f_head = NULL;
	Wlist_t *arr[27] = {NULL};

	//check argument count
	if(argc == 1)
	{
		printf("Error : please pass 2 or more argument !\nUSAGE : ./a.out f1.txt f2.txt\n");
		return FAILURE;
	}

	if(validate_n_store_filenames(&f_head ,argc ,argv) == SUCCESS)
	{
		printf("validate_n_store_filenames success\n\n");

		while(1)
		{
			int choice;
			printf("select an option :\n1.Create database\n2.Display database\n3.Search database\n4.Save database\n5.Update database\n6.Exit\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:printf("selected create database\n");
					   if(create_DB(f_head ,arr) == SUCCESS)
						   printf("\n-----Create_DB successfully done-----\n\n");
					   break;
				case 2:printf("selected Display database\n");
					   if(display_DB(arr) == SUCCESS)
						   printf("\n-----display_DB successfully done-----\n\n");
					   break;
				case 3:printf("selected Search database\n");
					   if(search_DB(arr) == SUCCESS)
						   printf("\n-----Search_DB successfully done-----\n\n");
					   else
						   printf("\nERROR : Data not found!\n\n");
					   break;
				case 4:printf("selected Save database\n");
					   if(save_DB(arr) == SUCCESS)
						   printf("\n-----Save_DB successfully done-----\n\n");
					   break;
				case 5:printf("selected Update database\n");
					   if(update_DB(arr) == SUCCESS)
						   printf("\n-----Update_DB successfully done-----\n\n");
					   break;
				case 6:return 0;

				default:printf("\nError : please enter valid option\n");
						break;
			}
		}
	}
	else
		printf("validate_n_store_filenames failed !\n");
}

/* validating and storing filenames fun */
int validate_n_store_filenames(Flist_t  **node ,int argc ,char *argv[])
{
	int i,j,flag = 0;
	//check for duplicate files in CLA
	for(i=1;i<argc;i++)
	{
		//open file in read mode
		FILE *fptr = fopen(argv[i],"r");

		//validation
		if(fptr == NULL)
		{
			printf("Error : %s file is not opening!\n",argv[i]);
		}
		else
		{
			//check is it empty file or not
			fseek(fptr ,0L ,SEEK_END);

			if(ftell(fptr) == 0)
			{
				printf("Error : please pass non-empty file\n");
			}
			else
			{
				for(j=1;j<i;j++)
				{
					if(strcmp(argv[i],argv[j]) == 0)
					{
						flag = 1;
						break;
					}
				}
				if(flag != 1)
				{
					store_filenames_to_list(argv[i] ,node);
				}
				flag = 0;
			}
		}
	}
	return SUCCESS;
}

/* storing filenames to the list fun */
int store_filenames_to_list(char *fname ,Flist_t **head)
{
	Flist_t *new = malloc(sizeof(Flist_t));

	if(new == NULL)
		return FAILURE;

	strcpy(new->f_name ,fname);
	new->link = NULL;

	if(*head == NULL)
	{
		*head = new;
		return SUCCESS;
	}
	Flist_t *temp = *head;
	while(temp->link != NULL)
		temp = temp->link;

	temp->link = new;
	return SUCCESS;
}
