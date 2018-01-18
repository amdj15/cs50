#include <stdio.h>
#include <cs50.h>

#define MIN_HEIHT 0
#define MAX_HEIGH 23

void draw(int height, int level);
void print_block(char *str, int times);
int get_height(void);

int main(int argc, char const *argv[])
{
  int height = get_height();
  draw(++height, 2);

  return 0;
}

void draw(int height, int level)
{
  if (level <= height) {
    int placeholders_need = height - level;

    print_block(" ", placeholders_need);
    print_block("#", level);
    print_block("\n", 1);

    draw(height, ++level);
  }
}

void print_block(char *str, int times)
{
  for (int i = 0; i < times; ++i)
  {
    printf("%s", str);
  }
}

int get_height(void)
{
  int height;

  do {
    printf("Height: ");
    height = GetInt();
  } while (height < MIN_HEIHT || height > MAX_HEIGH);

  return height;
}

