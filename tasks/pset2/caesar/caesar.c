#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int get_sign_length(char const *argv[]);
void encrypt(char * str, int key, int length);
int get_alpha_number(char letter);
char get_asci(int number, int cond);


int main(int argc, char const *argv[])
{
  int key = get_sign_length(argv);

  if (key < 1) {
    return 1;
  }

  printf("Enter text:\n");
  char * str = GetString();
  encrypt(str, key, strlen(str));

  printf("ciphertext: %s\n", str);

  return 0;
}

int get_sign_length(char const *argv[])
{
  if (argv[1] == NULL) {
    return 0;
  }

  return atoi(argv[1]);
}

void encrypt(char * str, int key, int length)
{
  for (int i = 0; i < length; ++i)
  {
    if (!isalpha(str[i])) {
      continue;
    }

    int number = (get_alpha_number(str[i]) + key) % 26;
    char letter = get_asci(number, isupper(str[i]));

    str[i] = letter;
  }
}

int get_alpha_number(char letter)
{
  int start = isupper(letter) ? 65 : 97;

  return (int)letter - start;
}

char get_asci(int number, int cond)
{
  int start = cond > 0 ? 65 : 97;
  int letter = start + number;

  return (char)letter;
}
