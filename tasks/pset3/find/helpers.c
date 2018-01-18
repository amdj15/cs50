/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 1) {
        return false;
    }

    if (n == 1) {
        return values[0] == value ? true : false;
    }

    int middle = floor(n / 2);
    int left = n - middle;

    if (values[middle] > value) {
        int new_vals[middle];
        for (int i = 0; i < middle; ++i)
        {
            new_vals[i] = values[i];
        }

        return search(value, new_vals, middle);
    } else if (values[middle] < value) {
        int new_vals[left];
        for (int i = 0; i < left; ++i)
        {
            new_vals[i] = values[middle + i];
        }

        return search(value, new_vals, left);
    }

    return values[middle] == value ? true : false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int next_tick = 0;

    do {
        int swapped = 0;

        for (int i = 0; i < n; ++i)
        {
            if (values[i] > values[i + 1] && i + 1 < n) {
                swapped = swap(values, i);
            }
        }

       next_tick = swapped ? 1 : 0;
    } while(next_tick);

    return;
}

int swap(int values[], int i)
{
    int swapped = values[i];

    values[i] = values[i + 1];
    values[i + 1] = swapped;

    return 1;
}
