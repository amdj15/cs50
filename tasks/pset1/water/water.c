#include <stdio.h>
#include <cs50.h>

int main(int argc, char const *argv[])
{
  printf("minutes:\n");
  printf("bottles: %i\n", GetInt() * 12);

  return 0;
}
