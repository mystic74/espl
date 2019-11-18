#include "data_structs.h"
#include <stdio.h>
#include <stdlib.h>

void list_print(node *diff_list, FILE* output)
{
	do
	{
		fprintf(output, "byte %lu %02X %02X \n",
						 diff_list->diff_data->offset,
						 diff_list->diff_data->orig_value,
						 diff_list->diff_data->new_value);
		diff_list = diff_list->next;
	}while (diff_list != NULL);
}

node* list_append(node* diff_list, diff* data)
{
	node* new_node = (node*)malloc(sizeof(node));
	if (new_node == NULL)
	{
		printf("Warning : Out of memory \n");
		return NULL;
	}
	new_node->diff_data = data;
	new_node->next = diff_list;

	return new_node;
}

void list_free(node *diff_list, int do_free)
{
	node* temp_node;
	while(diff_list != NULL)
	{
		temp_node = diff_list;
		diff_list = diff_list->next;
		if (do_free)
			free(temp_node->diff_data);
		free(temp_node);
	}
}

