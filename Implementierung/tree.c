struct node {
    char character;
    int frequency;
    struct node* left;
    struct node* right;
};

struct *node add(char character, int frequency, *node two) {
    struct node one = malloc(sizeof(struct node));
    if (!one) {
        return NULL;
    }
    one->character = character;
    one->frequency = frequency;
    one->left = one->right = NULL;

    struct node *new_node = malloc(sizeof(struct node));
    if (!new_node) {
        return NULL;
    }
    new_node->character = NULL;
    new_node->frequency = one->frequency + two->frequency;
    new_node->left = one;
    new_node->right = two;
    return new_node;
}