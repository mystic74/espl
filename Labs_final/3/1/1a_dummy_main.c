#include <stdio.h>
#include <stdlib.h>
#include "data_structs.h"


extern void list_print(node *diff_list,FILE* output); 
     /* Print the nodes in diff_list in the following format: byte POSITION ORIG_VALUE NEW_VALUE. 
Each item followed by a newline character. */
 
extern node* list_append(node* diff_list, diff* data); 
     /* Add a new node with the given data to the list,
        and return a pointer to the list (i.e., the first node in the list).
        If the list is null - create a new entry and return a pointer to the entry.*/
 
extern void list_free(node *diff_list); /* Free the memory allocated by and for the list. */

int main()
{
	diff* first_diff = (diff*) malloc(sizeof(diff));
	diff* second_diff = (diff*) malloc(sizeof(diff));
	node* my_list = NULL;


	first_diff->offset = 16;
	first_diff->orig_value = 'T';
	first_diff->new_value = 'O';

	second_diff->offset = 11;
	second_diff->orig_value = 'M';
	second_diff->new_value = 'R';



	my_list = list_append(my_list, first_diff);
	my_list = list_append(my_list, second_diff);


	list_print(my_list, stdout);

	list_free(my_list);

	return 0;

}