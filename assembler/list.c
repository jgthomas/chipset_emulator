#include <stdlib.h>
#include <assert.h>
#include "list.h"


Node *create_node()
{
        Node *node = malloc(sizeof(*node));
        assert(node != NULL);
        return node;
}
