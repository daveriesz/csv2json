#
# Makefile - (C) 2024 David Riesz
#
# This software is licensed under the terms of the MIT License.  Please
# read the included LICENSE file.
#

PROGRAM  = csv2json

CSOURCES = main.c util.c csv.c json.c
COBJECTS = $(CSOURCES:.c=.o)

CFLAGS   = $(COPT) $(CINC) $(CDEF)
COPT     = -g
CINC     = 
CDEF     = 

LDFLAGS  = $(LDOPT) $(LDDIR) $(LDLIB)
LDOPT    = 
LDDIR    = 
LDLIB    = -lcsv

CSV1     = testfiles/test1.csv
JSON1    = testfiles/test1.json
CSV2     = testfiles/test2.csv
JSON2    = testfiles/test2.json
CSV3     = testfiles/test3.csv
JSON3    = testfiles/test3.json
CSV4     = testfiles/test4.csv
JSON4    = testfiles/test4.json

GDBCMDS  = gdb-commands.txt

all: $(PROGRAM)

$(PROGRAM): $(COBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

run1: $(PROGRAM)
	cat "$(CSV1)" | ./$< > $(JSON1)
	cat "$(JSON1)"

run2: $(PROGRAM)
	cat "$(CSV2)" | ./$< > $(JSON2)
	cat "$(JSON2)"

run3: $(PROGRAM)
	cat "$(CSV3)" | ./$< > $(JSON3)
	cat "$(JSON3)"

run4: $(PROGRAM)
	cat "$(CSV4)" | ./$< > $(JSON4)
	cat "$(JSON4)"

clean:
	$(RM) $(PROGRAM)
	$(RM) $(COBJECTS)

%.o: %.c csv2json.h
	$(CC) -c $< -o $@ $(CFLAGS)

gdb1: $(PROGRAM)
	printf "break main\nrun <%s\n" "$(CSV1)" > "$(GDBCMDS)"
	gdb $< -x $(GDBCMDS)

gdb2: $(PROGRAM)
	printf "break main\nrun <%s\n" "$(CSV2)" > "$(GDBCMDS)"
	gdb $< -x $(GDBCMDS)
