#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include for memset

typedef struct node
{
    int ipAdd;
    int dataPacket;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

typedef struct splay_tree
{
    struct node *root;
} splay_tree;

node *new_node(int ipAdd)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        fprintf(stderr, "Memory allocation failed for node.\n");
        exit(EXIT_FAILURE);
    }
    n->ipAdd = ipAdd;
    n->dataPacket = 0; // Initialize dataPacket to 0
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    return n;
}

splay_tree *new_splay_tree()
{
    splay_tree *t = malloc(sizeof(splay_tree));
    if (t == NULL)
    {
        fprintf(stderr, "Memory allocation failed for splay tree.\n");
        exit(EXIT_FAILURE);
    }
    t->root = NULL;
    return t;
}

node *maximum(splay_tree *t, node *x)
{
    while (x->right != NULL)
        x = x->right;
    return x;
}

void left_rotate(splay_tree *t, node *x)
{
    node *y = x->right;
    if (y == NULL)
        return;

    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        t->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(splay_tree *t, node *x)
{
    node *y = x->left;
    if (y == NULL)
        return;

    x->left = y->right;
    if (y->right != NULL)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        t->root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void splay(splay_tree *t, node *n)
{
    while (n->parent != NULL)
    {
        if (n->parent == t->root)
        {
            if (n == n->parent->left)
            {
                right_rotate(t, n->parent);
            }
            else
            {
                left_rotate(t, n->parent);
            }
        }
        else
        {
            node *p = n->parent;
            node *g = p->parent;
            if (n->parent->left == n && p->parent->left == p)
            {
                right_rotate(t, g);
                right_rotate(t, p);
            }
            else if (n->parent->right == n && p->parent->right == p)
            {
                left_rotate(t, g);
                left_rotate(t, p);
            }
            else if (n->parent->right == n && p->parent->left == p)
            {
                left_rotate(t, p);
                right_rotate(t, g);
            }
            else if (n->parent->left == n && p->parent->right == p)
            {
                right_rotate(t, p);
                left_rotate(t, g);
            }
        }
    }
}

void insert(splay_tree *t, node *n)
{
    node *y = NULL;
    node *temp = t->root;
    while (temp != NULL)
    {
        y = temp;
        if (n->ipAdd < temp->ipAdd)
            temp = temp->left;
        else
            temp = temp->right;
    }
    n->parent = y;
    if (y == NULL)
        t->root = n;
    else if (n->ipAdd < y->ipAdd)
        y->left = n;
    else
        y->right = n;
    splay(t, n);
}

node *search(splay_tree *t, node *n, int x)
{
    if (n == NULL)
        return NULL;
    if (x == n->ipAdd)
    {
        splay(t, n);
        return n;
    }
    else if (x < n->ipAdd)
        return search(t, n->left, x);
    else
        return search(t, n->right, x);
}

void inorder(splay_tree *t, node *n, char *cmn)
{
    if (n != NULL)
    {
        inorder(t, n->left, cmn);
        printf("%s%d -> %d\n", cmn, n->ipAdd, n->dataPacket);
        inorder(t, n->right, cmn);
    }
}

int main()
{
    char *cmn = "192.168.3.";
    splay_tree *t = new_splay_tree();

    // Define and initialize nodes
    node *add[] = {
        new_node(104), new_node(112), new_node(117),
        new_node(124), new_node(121), new_node(108),
        new_node(109), new_node(111), new_node(122),
        new_node(125), new_node(129)};
    int size = sizeof(add) / sizeof(add[0]);

    // Insert nodes into the splay tree
    for (int idx = 0; idx < size; idx++)
    {
        insert(t, add[idx]);
    }

    // Search for nodes
    int find[] = {104, 112, 117, 124, 121, 108, 109, 111, 122, 125, 129};
    int find_size = sizeof(find) / sizeof(find[0]);
    for (int idx = 0; idx < find_size; idx++)
    {
        node *res = search(t, t->root, find[idx]);
        if (res)
            printf("Found: %s%d\n", cmn, res->ipAdd);
        else
            printf("Not Found: %s%d\n", cmn, find[idx]);
    }

    // Inorder traversal
    printf("\nInorder traversal:\n");
    inorder(t, t->root, cmn);

    return 0;
}
