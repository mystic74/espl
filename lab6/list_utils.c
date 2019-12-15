#include "data_structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int list_size = 0;
static int max_size = 0;
static node* last_node = NULL;
static node* first_node = NULL;
node* list_append(node* diff_list, command* data);
int get_list_size();
void list_print(node *diff_list,FILE* output);
node* reg_list_append(node* diff_list, command* data);
node* reg_list_edit(node* diff_list, command* data, int loc);
node* reg_list_edit_at_loc_allocatec(node* diff_list,char* stringy_string, int loc);
node* list_edit_at_loc_allocatec(node* diff_list,char* stringy_string, int loc);
node* list_edit_at_loc(node* diff_list, command* data, int loc);
node* node_removal(node* listy, int index);
char* get_string_for_index(node* listy, int index);

char* get_string_for_index(node* listy, int index)
{
	while(listy != NULL)
	{
		if (listy->curr_command->n_command_index == index)
		{
			return listy->curr_command->str;
		}
	}
	return NULL;
}
node* node_removal(node* listy, int index)
{
	node* tempNode;
/* Should not get here though.*/
	if (list_size == 0)
		return NULL;
	
	if (list_size == 1)
	{
		if (listy->curr_command != NULL)
		{
			free(listy->curr_command);
			free(listy);
			last_node = NULL;
			first_node = NULL;
			list_size--;
			return NULL;
		}
	}

	/* Check for last node */
	if (first_node->curr_command->n_command_index == index)
	{
		first_node = first_node->next;
		free(listy->curr_command);
		free(listy);
		list_size--;
		return first_node;
	}

	/* Check for last node */
	if (last_node->curr_command->n_command_index == index)
	{
		tempNode = last_node;
		last_node = last_node->prev;
		free(tempNode->curr_command);
		free(tempNode);
		list_size--;
		return first_node;
	}
	while (listy != NULL)
	{
		/* Delete this! */
		if (listy->curr_command->n_command_index == index)
		{
			/* Handle some middle node. */		
			tempNode = listy;

			((node*)(listy->prev))->next = listy->next;

			free(listy->curr_command);
			free(listy);
			list_size--;

			return first_node;
		}
		
		listy = listy->next;
	}
	return first_node;	
}
int get_list_size()
{
	return list_size;
}

void list_print(node *diff_list,FILE* output)
{
    while (diff_list != NULL)
    {
        fprintf(output, "%d .  %s",
                diff_list->curr_command->n_command_index,
                diff_list->curr_command->str);
        diff_list = diff_list->next;

    }
}
/**
* This function allocates a new node, and appends it to the end of the list.
* remember to free it at the end.
*/
node* reg_list_append(node* diff_list, command* data)
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
	n_node-> prev = diff_list;

	list_size ++;

	return head_node;
}

/**
* This function allocates a new node, and appends it to the location specified.
* remember to free it at the end.
*/
node* reg_list_edit(node* diff_list, command* data, int loc)
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
	n_node-> prev = diff_list;
	last_node = n_node;

	list_size++;

	return head_node;
}


node* reg_list_edit_at_loc_allocatec(node* diff_list,char* stringy_string, int loc)
{
	command* first_diff = (command*) malloc(sizeof(command));
	memcpy(first_diff->str, stringy_string, strlen(stringy_string));
	first_diff->n_command_index = loc;
	return reg_list_edit(diff_list, first_diff, loc % max_size);
	
}

node* list_edit_at_loc_allocatec(node* diff_list,char* stringy_string, int loc)
{
	command* first_diff = (command*) malloc(sizeof(command));
	memcpy(first_diff->str, stringy_string, strlen(stringy_string));
	first_diff->str[strlen(stringy_string)] = 0;
	first_diff->n_command_index = loc;
	return list_edit_at_loc(diff_list, first_diff, loc % max_size);
	
}


node* list_edit_at_loc(node* diff_list, command* data, int loc)
{
	node* n_node = (node*)malloc(sizeof(node));
	node* tempNode = NULL;

	/* Set me as head.*/
	first_node = n_node;
	n_node->curr_command = data;
	n_node->next = diff_list;
	n_node->prev = NULL;

	if (diff_list != NULL)
		diff_list->prev = n_node;
	else
	{
		last_node = first_node;
	}
	
	if (list_size < max_size)
		list_size++;
	else
	{
		tempNode = last_node->prev;
		/* Remove the last node*/
		if(last_node->curr_command != NULL)
			free(last_node->curr_command);
		if (last_node != NULL)
			free(last_node);
		
		last_node = tempNode;
		tempNode->next = NULL;
	}
	
	return n_node;
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
	n_node->prev = NULL;

	diff_list->prev = n_node;
	
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


node* alloc_list_size(int size_of_list)
{
	max_size = size_of_list;
	return NULL;
}
