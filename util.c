/*
 * util.c - (C) 2024 David Riesz
 *
 * This software is licensed under the terms of the MIT License.  Please
 * read the included LICENSE file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "csv2json.h"

int isnumber(const char *str)
{
  char *cp;

  if(str == NULL) { return 0; }
  if(*str == '\0') { return 0; }

  strtoll(str, &cp, 10);
  if(*cp == '\0' ) { return 1; }
  
  strtod(str, &cp);
  if(*cp == '\0') { return 1; }
  
  return 0;
}

int isboolean(const char *str)
{
  if(!strcasecmp(str, "true")) { return 1; }
  if(!strcasecmp(str, "false")) { return 1; }
  return 0;
}

void lowercase(char *str)
{
  char *cp;
  if(!str) { return; }
  for(cp=str ; cp && ((*cp)!='\0') ; cp++)
  {
    *cp = tolower(*cp);
  }
}
