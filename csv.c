/*
 * csv.c - (C) 2024 David Riesz
 *
 * This software is licensed under the terms of the MIT License.  Please
 * read the included LICENSE file.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <csv.h>

#include "csv2json.h"

void cb1(void *s, size_t len, void *data)
{
  int ii, mod, datarow;
  char *value = strndup((char *)s, len);
  c2j_info *info = (c2j_info *)data;
  int dupmatch;

  if(info->rows == 0) { mod = info->cells; }
  else                { mod = info->cells % ((info->rows)*(info->cols)); }

  if(info->rows == 0) { info->cols++; }

  if(info->rows == 0) // headings
  {
    info->headings = (c2j_heading *)realloc(info->headings, sizeof(c2j_heading)*((info->cols)));
    memset(&(info->headings[mod]), 0, sizeof(c2j_heading));
    info->headings[mod].name = strdup(value);
    info->headings[mod].idx = mod;
    info->headings[mod].dupidx = -1;
    for(ii=(mod-1), dupmatch=0 ; ii>=0 && !dupmatch ; ii--)
    {
      if(!strcmp(info->headings[mod].name, info->headings[ii].name))
      {
        info->headings[ii].dupidx = info->headings[mod].idx;
        info->headings[mod].isdup = 1;
        dupmatch = 1;
//        fprintf(stderr, "duplicate heading: %s, idx=%d\n", info->headings[mod].name, info->headings[mod].idx);
      }
    }
  }
  else // entries
  {
    datarow = (info->rows)-1;
    if(mod == 0)
    {
      info->entries = (char ***)realloc(info->entries, sizeof(char **)*(info->rows));
      info->entries[datarow] = (char **)malloc(sizeof(char *)*(info->cols));
    }
    if((value==NULL) || (strlen(value)==0))
    {
      info->entries[datarow][mod] = NULL;
    }
    else
    {
      info->entries[datarow][mod] = strdup(value);
    }
//    fprintf(stderr, "added value: r/c=%2d/%2d - %s\n", datarow, mod, info->entries[datarow][mod]);
  }
  info->cells++;
  if(value) { free(value); }

  return;
}

void cb2(int c, void *data)
{
  c2j_info *info = (c2j_info *)data;
  info->rows++;
  fprintf(stderr, "read %'d rows from the CSV input\r", info->rows); fflush(stderr);
}

void read_csv(c2j_info *info)
{
  struct csv_parser csvp;
  int fd;
  size_t bytes_read, parse_read;
  char buf[1024];
  
  memset(info, 0, sizeof(c2j_info));
  
  fd = STDIN_FILENO;

  if(csv_init(&csvp, 0) != 0) { exit(EXIT_FAILURE); }
  
  while((bytes_read = read(fd, buf, 1024)) > 0)
  {
    parse_read = csv_parse(&csvp, buf, bytes_read, cb1, cb2, info);
    if(parse_read != bytes_read)
    {
      csv_strerror(csv_error(&csvp));
      exit(EXIT_FAILURE);
    }
  }
  fprintf(stderr, "\n"); fflush(stderr);
  csv_fini(&csvp, cb1, cb2, info);
  fprintf(stderr, "cols: %d\n", info->cols);
  fprintf(stderr, "rows: %d\n", info->rows);
}
