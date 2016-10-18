#include <stdbool.h>
#include "interface.h"

bool change_state( struct _node* n, int state )
{
  n->state = state+1;
}
