/*
 * csv2json.h - (C) 2024 David Riesz
 *
 * This software is licensed under the terms of the MIT License.  Please
 * read the included LICENSE file.
 */

#ifndef __CSV2JSON__CSV2JSON_H__
#define __CSV2JSON__CSV2JSON_H__

typedef struct c2j_heading
{
  char *name;
  int idx;
  int isdup;
  int dupidx;
} c2j_heading;

typedef struct c2j_info
{
  int rows, cols, cells;
  c2j_heading *headings;
  int headings_finished;
  char ***entries;
} c2j_info;

int isnumber(const char *str);
int isboolean(const char *str);
void lowercase(char *str);

void read_csv(c2j_info *info);
void write_json(c2j_info *info);

#endif /* __CSV2JSON__CSV2JSON_H__ */
