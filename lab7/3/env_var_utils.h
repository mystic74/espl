#ifndef _ENV_VAR_UTILS_H
#define _ENV_VAR_UTILS_H

pair* generate_pair(char* var_name, char* var_value);
pair_node* env_list_append(pair_node* env_list, pair* data);
void print_env_for_val(pair_node* env_list, char* value);
char* get_value_from_name(pair_node* env_list, char* name);
pair* get_node_from_name(pair_node* env_list, char* name);
void env_list_free(pair_node *diff_list);
pair_node* remove_env_name(pair_node* list, char* name);

#endif