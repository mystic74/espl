#include "data_structs.h"
#include <stdlib.h>
#include <stdio.h>

void list_print(node *diff_list,FILE* output)
{
    while (diff_list != NULL)
    {
        fprintf(output, "byte %lu %02X %02X \n",
                diff_list->diff_data->offset,
                diff_list->diff_data->orig_value,
                diff_list->diff_data->new_value);

        diff_list = diff_list->next;

    }
}

void print_list_amount(node *diff_list,FILE* output)
{
	unsigned int diff_amount = 0;
    while (diff_list != NULL)
    {
        diff_amount++;
        diff_list = diff_list->next;
    }

    fprintf(output, "%u", diff_amount);
}

void p_list_print(node *diff_list,FILE* output, int amount)
{
    while ((diff_list != NULL) && (amount > 0))
    {
        fprintf(output, "byte %lu %02X %02X \n",
                diff_list->diff_data->offset,
                diff_list->diff_data->orig_value,
                diff_list->diff_data->new_value);

        diff_list = diff_list->next;
        amount--;
    }
}

/**
* This function allocates a new node, and appends it to the end of the list.
* remember to free it at the end.
*/
node* reg_list_append(node* diff_list, diff* data)
{
	node* n_node = (node*)malloc(sizeof(node));
	node* head_node = diff_list;
	n_node->diff_data = data;
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
*/
node* list_append(node* diff_list, diff* data)
{
	node* n_node = (node*)malloc(sizeof(node));


	n_node->diff_data = data;
	n_node->next = diff_list;

	return n_node;
}

void list_free(node *diff_list)
{
	node* curr_node = NULL;

	while (diff_list != NULL)
	{
		curr_node = diff_list;		
		diff_list = diff_list->next;
		if(curr_node->diff_data != NULL)
			free(curr_node->diff_data);
		if (curr_node != NULL)
			free(curr_node);
	}
}