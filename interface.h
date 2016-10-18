#ifndef INTERFACE_H
#define INTERFACE

struct _node
{
  int state;
};

struct _states
{
  const int STATE_OFF;
  const int STATE_ON;
};

bool change_node( struct _node* n, int state );

#endif
