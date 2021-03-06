#define MY_MAX_INPUT 2048 

typedef struct command {
    int n_command_index;
    char str[MY_MAX_INPUT]; /* The command were saving */
} command;

typedef struct node node;
 
struct node {
    command *curr_command; /* pointer to a struct containing the offset and the value of the bytes in each of the files*/
    node* next;
    node* prev;
};
