#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "interface.h"

#ifdef _WIN32
  #include <windows.h>
#endif
#ifdef __linux__
  #include <dlfcn.h>
#endif

typedef struct _node Node;

int main(int argc, char** argv)
{
  typedef bool (*change_node_function)();

  char* key_input = malloc(sizeof(char) * 128);

  unsigned int buffer_size = 10;
  Node nodes[10];
  unsigned int idx = 0;

  do
  {
    scanf("%128s", key_input);
    printf("got input:\t%s\n", key_input);

    if (strcmp(key_input, "p") == 0 || strcmp(key_input, "print") == 0)
    {
      for (unsigned int i = 0; i < buffer_size; ++i)
      {
        printf("state of node #%d is %d\n", i, nodes[i].state);
      }
    }

    if (strcmp(key_input, "c") == 0 || strcmp(key_input, "create") == 0)
    {
      scanf("\n%s", key_input);
      scanf("Specify library to load %128s", key_input);

#ifdef __linux__
      void* handle = dlopen(key_input, RTLD_NOW | RTLD_GLOBAL);
      printf("Going to print under linux\n");
#endif
#ifdef __WIN32
      HINSTANCE handle = LoadLibrary("test.dll");
      printf("Going to print under windows\n");
#endif

      if (handle == NULL)
      {
        fprintf(stderr, "Unable to find library: %s\n", key_input);
        return 1;
      }
      change_node_function func = dlsym(handle, "change_state");
      if (func == NULL)
      {
        printf("Unable to find symbol change_state\n");
        return 1;
      }

      Node n;
      n.state = 0;
      bool ret = func(&n, 1);

      nodes[++idx%buffer_size] = n;
      printf("new state is %d\n", n.state);
    }
  }
  while( strcmp(key_input, "q") != 0 && strcmp(key_input, "quit") != 0 );

  return 0;
}
