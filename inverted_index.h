#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1
#define NOELEMENT -2
#define EMPTYLIST -3
#define REPEATED -4
#define FILE_EMPTY -5
#define NOT_PRESENT -6

#define SIZE 26
#define BUFF_SIZE 255
#define NAMELENGTH 50

//inverted table
typedef struct sub_node
{
	char f_name[NAMELENGTH];
	int w_count;
	struct sub_node *link;
}sublist_t;

typedef struct node
{
	char word[NAMELENGTH];
	struct node *link;
	struct sub_node *sub_link;
	int f_count;
}Wlist_t;

typedef struct file_node
{
	char f_name[NAMELENGTH];
	struct file_node *link;
}Flist_t;


/* File validation */
int validate_n_store_filenames(Flist_t ** ,int argc ,char *filenames[]);
int store_filenames_to_list(char *fname ,Flist_t **head);

/*Create DB*/
int create_DB(Flist_t *file_head, Wlist_t **head);

int create_hash_table(Wlist_t *arr[] ,char *file_name ,char *word_name);
Wlist_t *create_main_node(char *word_name ,char *file_name);
sublist_t *create_sub_node(char *);

/*Display*/
int display_DB(Wlist_t **head);
int Is_check_database_empty(Wlist_t **head);

/*Save*/
int save_DB(Wlist_t **head);

/*search */
int search_DB(Wlist_t **head);

/*Update */
int update_DB(Wlist_t **);
Wlist_t *create_main_node_in_update_DB(Wlist_t ** ,int) ;

#endif
