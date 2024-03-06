# csv2json
**csv2json** is (yet another) utility to convert CSV files to JSON.

## Why
I needed a utility to convert simple CSV files to simple JSON files and was unsatisifed with existing solutions.
They all were too complex, too difficult to build, or had some bizarrely large number of dependencies.
This utility is simple to build and handles exactly one use case:  converting basic ASCII CSV files to basic JSON.

## Building
You need only GNU Make, a C compiler, and libcsv.  To build it, type: ```make```.

## Running
**csv2json** takes a CSV input on STDIN and produces a JSON output on STDOUT.  Usage will go something like:
```
cat input.csv | csv2json > output.json
```
As an example, the following input CSV:
```
H1,H2,H3,H2,H4,H2,H5
horse,1.3,-4,white,book,farenheit,
donkey,truce,F-6,,5,random,dispatch
turtle,true,ectoplasm,clown,usenet,fifteen,6d
albatross,,flywheel,4e+2,risque,FaLse,grease
```
will produce the following output JSON:
```
{
  "H1":"horse",
  "H2":[1.3,"white","farenheit"],
  "H3":-4,
  "H4":"book",
  "H5":null
}
{
  "H1":"donkey",
  "H2":["truce",null,"random"],
  "H3":"F-6",
  "H4":5,
  "H5":"dispatch"
}
{
  "H1":"turtle",
  "H2":[true,"clown","fifteen"],
  "H3":"ectoplasm",
  "H4":"usenet",
  "H5":"6d"
}
{
  "H1":"albatross",
  "H2":[null,4e+2,false],
  "H3":"flywheel",
  "H4":"risque",
  "H5":"grease"
}
```
Note that if multiple columns have the same heading, the corresponding values will be collected in an array.

## Issues

Issue?  Bug?  Feature request?  Please submit an [issue](https://github.com/daveriesz/csv2json/issues).

## Contributing

Feel free to submit a pull request if you want to contribute.
I'm not very good at reading other people's code, so please include a verbose description and/or explanation.

## Licensing

This project and its code are all copyright (C) 2024 by David Riesz and licensed under the terms of the MIT License.  If you don't know what this means you can find out by reading [license file](LICENSE?raw=1).
