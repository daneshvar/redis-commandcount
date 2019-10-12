#include "utils.h"

/*
Copyright (c) 2001 Mike Barcroft <mike@FreeBSD.org>
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 * strnstr.c from FreeBSD
 */
/*
 * Find the first occurrence of find in s, where the search is limited to the
 * first slen characters of s.
 */
const char* StrFind(const char* s, const char* find, size_t slen) {
  if (!slen) {
    return NULL;
  }

  char c, sc;
  size_t len;

  if ((c = *find++) != '\0') {
    len = strlen(find);
    do {
      do {
        if ((sc = *s++) == '\0' || slen-- < 1) {
          return (NULL);
        }
      } while (sc != c);
      if (len > slen) {
        return (NULL);
      }
    } while (strncmp(s, find, len) != 0);
    s--;
  }
  return s;
}

/* convert character array to integer */
int StrInt(const char* array, size_t n) {
  int number = 0;
  int mult = 1;

  n = (int)n < 0 ? -n : n; /* quick absolute value check  */

  /* for each character in array */
  while (n--) {
    /* if not digit or '-', check if number > 0, break or continue */
    if ((array[n] < '0' || array[n] > '9') && array[n] != '-') {
      if (number)
        break;
      else
        continue;
    }

    if (array[n] == '-') { /* if '-' if number, negate, break */
      if (number) {
        number = -number;
        break;
      }
    } else { /* convert digit to numeric value   */
      number += (array[n] - '0') * mult;
      mult *= 10;
    }
  }
  return number;
}
