# EAPC Cheatsheet Generator
This code was made to generate a cheatsheet for the EAPC/BAPC. It takes in a codebase of useful algorithms and puts them into a .tex document. It also supports LaTeX files for formulas.
This was inspired by [this repository](https://github.com/pin3da/notebook-generator), but since I do not know how to set up JavaScript, I decided to remake it in C.

### Usage
First, you compile the project, which can be done by either calling ```make``` or by using:

```g++ -o bin/cheatsheet src/cheatsheet.c -O3 -g -Wall -Wextra -Werror -Wpedantic -Wstrict-aliasing -static -static-libgcc -static-libstdc++ -lshlwapi```

To run the project, go to the bin directory and call ```cheatsheet.exe [title] [team name] [code folder] [(optional) output name]```. There is an example in the bin folder where I used the command ```cheatsheet.exe Cheatsheet Jan templates```. After that you can upload the .tex file to overleaf and download the pdf.
