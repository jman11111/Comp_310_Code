/*linked list interface*/

struct link_list {
        char* word;
        int counter;
        struct link_list *next;
};

typedef struct link_list *node;

node createNode();

void printlist(node head);

void delete_node(node head);

node addNode(node head,char* value, int count);

void insertAfter(node prev_node,char* str,int count);

void push(node* head, char* str,int count);
