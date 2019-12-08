#include <stdio.h>
#include <stdlib.h>
#include "../1/data_structs.h"
#include <string.h>
#include <errno.h>
#include <limits.h>

#define READ_SIZE 1
#define TOTAL_DIFF_PARAM "-t"
#define PARTIAL_DIFF_PARAM "-k"
#define OUTPUT_PARAM "-o"
#define RESTORE_PARAM "-r"


enum RESTORE_PARSE{
	RESTORE_ALL = 1,
	RESTORE_NUMERIC = 2,
	NUM_OF_PARAMS
};
extern void print_list_amount(node *diff_list,FILE* output);
extern void p_list_print(node *diff_list,FILE* output, int amount);
extern node* reg_list_append(node* diff_list, diff* data);

extern void list_print(node *diff_list,FILE* output); 
     /* Print the nodes in diff_list in the following format: byte POSITION ORIG_VALUE NEW_VALUE. 
Each item followed by a newline character. */
 
extern node* list_append(node* diff_list, diff* data); 
     /* Add a new node with the given data to the list,
        and return a pointer to the list (i.e., the first node in the list).
        If the list is null - create a new entry and return a pointer to the entry.*/
 
extern void list_free(node *diff_list); /* Free the memory allocated by and for the list. */


void restore_file(node *diff_list,FILE* r_file, unsigned int number_of_changes)
{
	int fputc_r = 0;
    while ((diff_list != NULL ) && (number_of_changes > 0))
     {

        fprintf(stdout, "byte %lu %02X %02X \n",
                diff_list->diff_data->offset,
                diff_list->diff_data->orig_value,
                diff_list->diff_data->new_value);
		
		/* Setting the offset in file.*/
		fseek(r_file, diff_list->diff_data->offset, SEEK_SET);
		/*Edit the file*/
        fputc_r = fputc(diff_list->diff_data->new_value, r_file);
		if (fputc_r == EOF)
			{
				printf("error on putc\n");
			}
		diff_list = diff_list->next;
		number_of_changes--;
    }
}


int main(int argc, char** argv)
{
	FILE* first_file 	= NULL;
	FILE* second_file 	= NULL;

	FILE* output = stdout;

	unsigned char input_first_file = 0;
	unsigned char input_second_file = 0;

	unsigned int length_first_input = 0;
	unsigned int length_second_input = 0;
	diff* new_diff = NULL;
	node* my_list = NULL;

	unsigned int file_index = 0;
	unsigned int argv_index = 0;

	unsigned int total_diff 		= 0;
	unsigned int n_diff_param_cond 	= 0;
	unsigned int n_diff_param_amnt  = 0;
	unsigned int n_restore_param_cond = 0;
	unsigned int n_restore_param_amnt = INT_MAX;

	long lnum;
	char *end;

	errno = 0;


	/* Avoiding underflow for the for in a bit.*/ 
	if (argc < 2)
	{
		printf("Wrong number of arguments, should be at least 2\n");
		printf("Usage is:\n");
		printf("%s [OPTIONS] <first filename>  <second file name> \n", argv[0] );
		return 1;
	}

	/* Parse input */
	for (argv_index = 0; argv_index < argc - 2; argv_index++)
	{
		if (strcmp(TOTAL_DIFF_PARAM, argv[argv_index]) == 0)
		{
			total_diff = 1;
		}
		else if (strcmp(PARTIAL_DIFF_PARAM, argv[argv_index]) == 0)
		{
			n_diff_param_cond = 1;
			n_diff_param_amnt = atoi(argv[++argv_index]);
		}
		else if (strcmp(OUTPUT_PARAM, argv[argv_index]) == 0)
		{
			if (output != stdout)
				fclose(output);

			output = fopen(argv[++argv_index], "w");
		}
		else if (strcmp(RESTORE_PARAM, argv[argv_index]) == 0)
		{
			n_restore_param_cond = RESTORE_ALL;
/*			int_checker = sscanf(argv[argv_index + 1], "%d%c", &value, &ch);*/
			lnum = strtol(argv[argv_index + 1], &end, 10);        /* 10 specifies base-10 */
			
			
			/*
			//if (int_checker != 1)
			//{
			//	n_restore_param_cond = RESTORE_NUMERIC;
			//	n_restore_param_amnt = value;
			//}*/

			if (end == argv[argv_index + 1])     /*if no characters were converted these pointers are equal*/
			{
					fprintf(stderr, "ERROR: can't convert string to number\n");
			}
			/*If sizeof(int) == sizeof(long), we have to explicitly check for overflows*/
			else if ((lnum == LONG_MAX || lnum == LONG_MIN) && errno == ERANGE)  
			{
					fprintf(stderr, "ERROR: number out of range for LONG\n");
			}
			/*Because strtol produces a long, check for overflow*/
			else if ( (lnum > INT_MAX) || (lnum < INT_MIN) )
			{
					fprintf(stderr, "ERROR: number out of range for INT\n");
			}
			/*Finally convert the result to a plain int (if that's what you want)*/
			else
			{
				argv_index++;
				n_restore_param_amnt = (int) lnum;
			}

		}
	}

	first_file 	= fopen(argv[argc - 2], "rwb+");
	second_file = fopen(argv[argc - 1], "rwb+");

	do
	{
		if(input_second_file != input_first_file)
		{
			new_diff = (diff*)malloc(sizeof(diff));
			new_diff->offset = file_index;
			new_diff->orig_value = input_first_file;
			new_diff->new_value  = input_second_file;

			my_list = reg_list_append(my_list, new_diff);
		}

		length_first_input = fread(&input_first_file, sizeof(unsigned char), 1, first_file);
		length_second_input = fread(&input_second_file, sizeof(unsigned char), 1, second_file);

		file_index++;

	} while((length_first_input == READ_SIZE) && (length_second_input == READ_SIZE));
	if (n_restore_param_cond == 0)
	{
		if (total_diff)
			print_list_amount(my_list, output);
		else if (n_diff_param_cond)
			p_list_print(my_list, output, n_diff_param_amnt);
		else
			list_print(my_list, output);
		
		if (output != stdout)
		{
			fclose(output);
		}
	}
	else
	{
		restore_file(my_list ,second_file, n_restore_param_amnt);
	}

	if (first_file != NULL)
			fclose(first_file);

	if (second_file != NULL)
		fclose(second_file);

	list_free(my_list);

	return 0;
}