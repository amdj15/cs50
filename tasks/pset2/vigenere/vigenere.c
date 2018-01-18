#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include "vigenere.h"

int main(int argc, char const *argv[])
{
  const char *key = argv[1];

  if (key == NULL || !validate_key(key))
  {
    return 1;
  }

  printf("Enter text:\n");

  char *text = GetString();
  char *encrypted = encrypt(text, key);

  printf("ciphertext: %s\n");
  free(encrypted);

  return 0;
}

int validate_key(const char *str)
{

  for (int i = 0, n = strlen(str); i < n; ++i)
  {
    if (!isalpha(str[i]))
    {
      return 0;
    }
  }

  return 1;
}

char * encrypt(char *str, const char *key)
{
  int length = strlen(str);
  int keylen = strlen(key);
  char *out = malloc(length * sizeof(char));
  int alpha_cnt = 0;

  for (int i = 0; i < length; ++i)
  {
    if (!isalpha(str[i])) {
      out[i] = str[i];
      continue;
    }

    int index = alpha_cnt++ % keylen;
    int shift = get_alpha_number(key[index]);
    int number = (get_alpha_number(str[i]) + shift) % 26;
    out[i] = get_asci(number, isupper(str[i]));
  }

  return out;
}

int get_alpha_number(char letter)
{
  return (int)letter - get_start_asci_number(letter);
}

int get_start_asci_number(char letter)
{
  return isupper(letter) ? SUPER_START_LETTER : LOWER_START_LETTER;
}

char get_asci(int shift, int super)
{
  int start = super ? SUPER_START_LETTER : LOWER_START_LETTER;
  return start + shift;
}
