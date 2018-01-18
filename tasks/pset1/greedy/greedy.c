#include <stdio.h>
#include <cs50.h>
#include <math.h>

int how_mach(int dimension, int *sum, int counter);

int main(int argc, char const *argv[])
{
  float change;

  do {
    printf("How much? ");
    change = GetFloat();
  } while (change < 0.0);

  int sum = round(change * 100);

  int quaters = how_mach(25, &sum, 1);
  int tens = how_mach(10, &sum, 1);
  int fives = how_mach(5, &sum, 1);
  int cents = how_mach(1, &sum, 1);

  printf("%i\n", quaters + tens + fives + cents);

  return 0;
}

int how_mach(int dimension, int *sum, int counter)
{
  int current = dimension * counter;

  if (current < *sum) {
    return how_mach(dimension, sum, ++counter);
  }

  int coins_number;

  if (current == *sum) {
    coins_number = counter;
    *sum = 0;
  } else {
    coins_number = counter - 1;
    *sum = *sum - coins_number * dimension;
  }

  return coins_number;
}
