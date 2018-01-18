#include <stdio.h>
#include <cs50.h>
#include <string.h>

void get_first_letters(char name[], char *initials);
int get_words_number(char name[]);
void to_upper_case(char *initials, int length);

int main(int argc, char const *argv[])
{
  char *name = GetString();

  int length = get_words_number(name);
  char *initials = malloc(length * sizeof(char));

  if (initials != NULL) {
    get_first_letters(name, initials);
    to_upper_case(initials, length);

    printf("%s\n", initials);

    free(initials);
  }

  return 0;
}

void to_upper_case(char *initials, int length)
{
  for (int i = 0; i < length; ++i)
  {
    initials[i] = initials[i] - 32;
  }
}

void get_first_letters(char name[], char *initials)
{
  int new_word = 1;
  int counter = 0;

  for (int i = 0, n = strlen(name); i < n; ++i)
  {
    if (new_word == 1) {
      new_word = 0;
      initials[counter++] = name[i];
      continue;
    }

    if (name[i] == ' ') {
      new_word = 1;
    }
  }
}

int get_words_number(char name[])
{
  int words_len = 1;

  for (int i = 0, n = strlen(name); i < n; ++i)
  {
    if (name[i] == ' ') {
      words_len++;
    }
  }

  return words_len;
}
