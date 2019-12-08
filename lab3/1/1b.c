#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "data_structs.h"

#define READ_SIZE 1

extern void list_print(node *diff_list,FILE* output); 
     /* Print the nodes in diff_list in the following format: byte POSITION ORIG_VALUE NEW_VALUE. 
Each item followed by a newline character. */

extern node* list_append(node* diff_list, diff* data); 
     /* Add a new node with the given data to the list,
        and return a pointer to the list (i.e., the first node in the list).
        If the list is null - create a new entry and return a pointer to the entry.*/
 
extern void list_free(node *diff_list); /* Free the memory allocated by and for the list. */

int main(int argc, char** argv)
{
	FILE* first_file 	= NULL;
	FILE* second_file 	= NULL;
	unsigned char input_first_file = 0;
	unsigned char input_second_file = 0;

	unsigned int length_first_input = 0;
	unsigned int length_second_input = 0;

	diff* new_diff = NULL;
	node* my_list = NULL;

	unsigned int file_index = 0;


	if (argc != 3)
	{
		printf("Wrong number of arguments, should be 2\n");
		printf("Usage is:\n");
		printf("%s <first filename>  <second file name> \n", argv[0] );
		return 1;
	}

	first_file 	= fopen(argv[1], "r");
	second_file = fopen(argv[2], "r");

	do
	{
		if(input_second_file != input_first_file)
		{
			new_diff = (diff*)malloc(sizeof(diff));
			new_diff->offset = file_index;
			new_diff->orig_value = input_first_file;
			new_diff->new_value  = input_second_file;

			my_list = list_append(my_list, new_diff);
		}

		length_first_input = fread(&input_first_file, sizeof(unsigned char), READ_SIZE, first_file);
		length_second_input = fread(&input_second_file, sizeof(unsigned char), READ_SIZE, second_file);

		file_index++;
	} while((length_first_input == READ_SIZE) && (length_second_input == READ_SIZE));

	list_print(my_list, stdout);

	list_free(my_list);

	if (first_file != NULL)
		fclose(first_file);
	if (second_file != NULL)
		fclose(second_file);

	return 0;
}