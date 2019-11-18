#include "data_structs.h"
#include <stdio.h>
#include <stdlib.h>

extern void list_print(node *diff_list,FILE* output); 
     /* Print the nodes in diff_list in the following format: byte POSITION ORIG_VALUE NEW_VALUE. 
Each item followed by a newline character. */
 
extern node* list_append(node* diff_list, diff* data); 
     /* Add a new node with the given data to the list,
        and return a pointer to the list (i.e., the first node in the list).
        If the list is null - create a new entry and return a pointer to the entry.*/
 
extern void list_free(node *diff_list, int do_free); /* Free the memory allocated by and for the list. */


int main (int argc, char** argv)
{
	diff* diff1 = (diff*)malloc(sizeof(diff));
	diff* diff2 = (diff*)malloc(sizeof(diff));
	node* my_list = NULL;


	diff1->offset = 10;
	diff1->orig_value = 'C';
	diff1->new_value = 'Y';

	diff2->offset = 22;
	diff2->orig_value = 'R';
	diff2->new_value = 'Z';


	my_list = list_append(my_list, diff1);
	my_list = list_append(my_list, diff2);


	list_print(my_list, stdout);

	list_free(my_list, 1);

}