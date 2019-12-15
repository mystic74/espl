#include "data_structs.h"
#include <stdlib.h>
#include <stdio.h>

static int list_size = 0;

node* alloc_list_size(int size_of_list)
{
	int i = 0;
	node* my_list = NULL;

	for (i = 0; i < size_of_list, i++)
	{
		command* first_diff = (command*) malloc(sizeof(command));
		my_list = reg_list_append(first_diff);
	}

	return my_list;
}

int get_list_size()
{
	return list_size;
}

/**
* This function allocates a new node, and appends it to the end of the list.
* remember to free it at the end.
*/
node* reg_list_append(node* diff_list, char* data)
{

	node* n_node = (node*)malloc(sizeof(node));
	node* head_node = diff_list;
	n_node->curr_command = data;
	n_node->next = NULL;

	if (diff_list == NULL)
		return n_node;

	/* Go to the end of the list */
	while(diff_list->next != NULL)
	{
		diff_list = diff_list->next;
	}

	/* Add the current node.*/
	diff_list->next = n_node;
	n_node-> perv = diff_list;

	list_size ++;

	return head_node;
}



/**
* This function allocates a new node, and appends it to the location specified.
* remember to free it at the end.
*/
node* reg_list_edit_at_loc(node* diff_list, char* data, int loc)
{


	node* n_node = (node*)malloc(sizeof(node));
	node* head_node = diff_list;
	n_node->curr_command = data;
	n_node->next = NULL;

	if (diff_list == NULL)
		return n_node;

	/* Go to the end of the list */
	while((diff_list->next != NULL) && (loc > 0))
	{
		diff_list = diff_list->next;
		loc--;
	}

	/* Add the current node.*/
	diff_list->next = n_node;
	n_node-> perv = diff_list;

	list_size++;

	return head_node;
}


/**
* This function allocates a new node, and appends it to the end of the list.
* remember to free it at the end.
*/
node* list_append(node* diff_list, command* data)
{
	node* n_node = (node*)malloc(sizeof(node));

	/* Set me as head.*/
	n_node->curr_command = data;
	n_node->next = diff_list;
	n_node->perv = NULL;

	diff_list->perv = n_node;
	
	list_size++;
	return n_node;
}



void list_free(node *diff_list)
{
	node* curr_node = NULL;

	while (diff_list != NULL)
	{
		curr_node = diff_list;		
		diff_list = diff_list->next;
		if(curr_node->curr_command != NULL)
			free(curr_node->curr_command);
		if (curr_node != NULL)
			free(curr_node);
	}

	list_size--;
}