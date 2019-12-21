#include "data_structs.h"
#include "env_var_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Create a new pair for a given enviroment variable.*/
pair* generate_pair(char* var_name, char* var_value)
{
    pair* curr_pair = (pair*) malloc(sizeof(pair));
    curr_pair->name = (char*) malloc(strlen(var_name) + 1);
    curr_pair->value = (char*) malloc(strlen(var_value) + 1);

	strcpy(curr_pair->name, var_name);
	strcpy(curr_pair->value, var_value);
    return curr_pair;

}

void print_env_for_val(pair_node* env_list, char* value)
{
    /* Go over the list, and compare to the value given.
        if equals, print.*/
    while(env_list != NULL)
	{
		if (strcmp(env_list->curr_var->value, value) == 0)
		{
			printf("%s : %s \n", env_list->curr_var->name, env_list->curr_var->value);
		}
		env_list = env_list->next;
	}
	
}

pair_node* env_list_append(pair_node* env_list, pair* data)
{
	pair_node* n_node = (pair_node*)malloc(sizeof(pair_node));

	n_node->curr_var = data;
	n_node->next = env_list;
	
	return n_node;
}
char* get_value_from_name(pair_node* env_list, char* name)
{    
	while(env_list != NULL)
	{
		if (strcmp(env_list->curr_var->name, name) == 0)
		{
			return env_list->curr_var->value;
		}
		env_list = env_list->next;
	}
	return NULL;
}

pair* get_node_from_name(pair_node* env_list, char* name)
{
   
	while(env_list != NULL)
	{
		if (strcmp(env_list->curr_var->name, name) == 0)
		{
			return env_list->curr_var;
		}
		env_list = env_list->next;
	}
	return NULL;
}


pair_node* remove_env_name(pair_node* list, char* name)
{
	pair_node* tmpNode = NULL;
	pair_node* orgList = list;

	if (list == NULL)
    {   
        fprintf(stderr, "No such env variable\n");
		return NULL;
    }
    if (strcmp(list->curr_var->name, name) == 0)
	{
		tmpNode = list->next;
        /* TODO Free strings!*/
		free(list->curr_var->name);
		free(list->curr_var->value);
		free(list->curr_var);
		free(list);
		return tmpNode;
	}

	while ((list != NULL) && (list->next != NULL))
	{
        if (strcmp(list->next->curr_var->name, name) == 0)
		{
			tmpNode = list->next;
			list->next = tmpNode->next;
			/* TODO Free strings!*/
		    free(list->curr_var);
		    free(list);
	    	return orgList;
		}
		list = list->next;
	}

	return NULL;
}

void env_list_free(pair_node *diff_list)
{
	pair_node* curr_node = NULL;

	while (diff_list != NULL)
	{
		curr_node = diff_list;		
		diff_list = diff_list->next;
		if(curr_node->curr_var != NULL)
		{
			free(curr_node->curr_var->name);
			free(curr_node->curr_var->value);
			free(curr_node->curr_var);
		}
		if (curr_node != NULL)
			free(curr_node);
	}

}
