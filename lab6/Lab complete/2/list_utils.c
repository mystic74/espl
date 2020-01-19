#include "data_structs.h"
#include <stdlib.h>
#include <stdio.h>


static int max_size = 0;

static int current_size = 0;
void remove_last_node(node* list);


void list_print(node *diff_list,FILE* output)
{
    while (diff_list != NULL)
    {
        fprintf(output, "%d .  %s \n",
                diff_list->curr_command->n_command_index,
                diff_list->curr_command->str);
        diff_list = diff_list->next;

    }
}

char* get_string_for_index(node* listy, int index)
{
	while(listy != NULL)
	{
		if (listy->curr_command->n_command_index == index)
		{
			return listy->curr_command->str;
		}
		listy = listy->next;
	}

	fprintf(stderr, "No value for index %d in history list\n", index);
	return NULL;
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

	while(diff_list->next != NULL)
	{
		diff_list = diff_list->next;
	}

	diff_list->next = n_node;

	return head_node;
}


/**
* This function allocates a new node, and appends it to the end of the list.
* remember to free it at the end.
* if the list is full, remove the last node.
*/
node* list_append(node* diff_list, command* data)
{
	node* n_node = (node*)malloc(sizeof(node));

	n_node->curr_command = data;
	n_node->next = diff_list;

	if (current_size < max_size)
		current_size++;
	else
	{
		remove_last_node(diff_list);
	}
	
	return n_node;
}

/* Remove the last node, O(n). */
void remove_last_node(node* list)
{
	node* curr_node = NULL;

	while ((list != NULL) && (list->next != NULL))
	{
		curr_node = list;
		list= list->next;
	}
	free(list->curr_command);
	free(list);
	curr_node->next = NULL;

}

node* remove_node_at_index(node* list, int index)
{
	node* tmpNode = NULL;
	node* orgList = list;

	if (list == NULL)
		return NULL;

	if (list->curr_command->n_command_index == index)
	{
		tmpNode = list->next;
		free(list->curr_command);
		free(list);
		current_size--;
		return tmpNode;
	}

	while ((list != NULL) && (list->next != NULL))
	{
		if (list->next->curr_command->n_command_index == index)
		{
			tmpNode = list->next;
			list->next = tmpNode->next;
			free(tmpNode->curr_command);
			free(tmpNode);
			current_size--;
			return orgList;
		}
		list = list->next;
	}

	return orgList;
}

node* alloc_list_size(int size_of_list)
{
	max_size = size_of_list;
	return NULL;
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

	current_size = 0;
}
