/*
 * json.c - (C) 2024 David Riesz
 *
 * This software is licensed under the terms of the MIT License.  Please
 * read the included LICENSE file.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "csv2json.h"

void write_json(c2j_info *info)
{
  int ii, jj, rr, cc, dupidx;
  c2j_heading *hh = info->headings;
  char ***ee = info->entries;
  int debug = 0;
  char *val;

  rr = (info->rows)-1;
  cc = (info->cols);
 
  for(ii=0 ; ii<rr ; ii++)
  {
    printf("{\n");
    for(jj=0 ; jj<cc ; jj++)
    {
      if(hh[jj].isdup) { continue; }
      printf("  \"%s\":", hh[jj].name);
      if(debug) { fprintf(stderr, "%s:", hh[jj].name); }
      if(hh[jj].dupidx >= 0) { printf("["); }
      for(dupidx=jj ; dupidx>=0 ; dupidx = hh[dupidx].dupidx)
      {
        val = NULL;
        if(ee[ii][dupidx]) { val = strdup(ee[ii][dupidx]); }
        if(debug)
        {
          if(dupidx != jj) { fprintf(stderr, ","); }
          fprintf(stderr, "%s", val?val:"null");
        }
        if(dupidx != jj) { printf(","); }
        if(val == NULL)
        {
          printf("null");
        }
        else if(isboolean(val))
        {
          lowercase(val);
          printf("%s", val);
        }
        else if(isnumber(val))
        {
          printf("%s", val);
        }
        else
        {
          printf("\"%s\"", val);
        }
        if(val) { free(val); }
      }
      if(hh[jj].dupidx >= 0) { printf("]"); }
      if(debug) { fprintf(stderr, "\n"); }
      if(jj < (cc-1)) { printf(",\n"); }
    }
    printf("\n}");
//    if(ii < (rr-1)) { printf(","); }
    printf("\n");
    fprintf(stderr, "wrote %'d/%'d records to JSON output\r", ii+1, (info->rows)-1);
    fflush(stderr);
  }
  fprintf(stderr, "\n"); fflush(stderr);
}

