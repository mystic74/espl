#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_structs.h"


extern void list_print(node *diff_list,FILE* output); 
     /* Print the nodes in diff_list in the following format: byte POSITION ORIG_VALUE NEW_VALUE. 
Each item followed by a newline character. */
 
extern node* list_append(node* diff_list, diff* data); 
     /* Add a new node with the given data to the list,
        and return a pointer to the list (i.e., the first node in the list).
        If the list is null - create a new entry and return a pointer to the entry.*/
 
extern void list_free(node *diff_list, int do_free); /* Free the memory allocated by and for the list. */


int main(int argc, char** argv)
{
	FILE* first_input_file = NULL;
	FILE* second_input_file = NULL;
	unsigned char first_input = 0;
	unsigned char second_input = 0;
	unsigned int first_input_length = 0;
	unsigned int second_input_length = 0;
	diff* curr_diff = NULL;
	node* listy_list = NULL;

	unsigned int file_index = 0;

	if (argc != 3)
	{
		printf("Wrong number of arguments, should be 2\n");
		printf("Usage is:\n");
		printf("%s <filename>\n", argv[0] );
		return 1;
	}

	/* Try to open the file*/
	first_input_file = fopen(argv[1], "r");
	second_input_file = fopen(argv[2], "r");

	do
	{
		if (first_input != second_input)
		{
			curr_diff = (diff*) malloc(sizeof(diff));
			curr_diff->offset = file_index;
			curr_diff->orig_value = first_input;
			curr_diff->new_value = second_input;

			listy_list = list_append(listy_list, curr_diff);
		}
		first_input_length = fread(&first_input, sizeof(unsigned char), 1, first_input_file);
		second_input_length = fread(&second_input, sizeof(unsigned char), 1, second_input_file);
		
		
		file_index++;

	} while((first_input_length == 1) && (second_input_length == 1));

	list_print(listy_list, stdout);


	list_free(listy_list, 1);
	printf("\nDone. \n");
}