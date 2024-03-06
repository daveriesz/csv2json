/*
 * main.c - (C) 2024 David Riesz
 *
 * This software is licensed under the terms of the MIT License.  Please
 * read the included LICENSE file.
 */

#include <locale.h>

#include "csv2json.h"

int main(int argc, char **argv)
{
  c2j_info info;

  setlocale(LC_NUMERIC, "");

  read_csv(&info);
  write_json(&info);
}
