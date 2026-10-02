/* NAME : SHAIK SHABEENA
REGISTRATION NO: 25048_004

DESCRIPTION:

* This project provides a basic implementation of the lexical and syntax analysis stages of a compiler.
* It takes a C source file as input and analyzes the program in two stages:
    -> Lexical Analysis – identifies and classifies the different tokens present in the C program.
    ->Syntax Analysis – checks the program for common syntax errors.

* The project is divided into separate files so that lexical analysis, syntax analysis, function declarations, and program execution are 
  handled independently.

                                //main.c//
* main.c is the main controlling file of the project.
  It:
    -> Accepts the C source-file name through the command line.
    -> Opens the input file.
    -> Checks whether the file was opened successfully.
    -> Calls the lexical analyzer to perform lexical analysis.
    -> Rewinds the file so that it can be read again.
    -> Calls the syntax analyzer to perform syntax analysis.
    -> Closes the file after both analyses are completed.
    -> Displays the headings for lexical and syntax analysis using colors.
* So, main.c connects and controls the complete project.


                            //lexer.h//
* It is is the header file for the lexical analyzer.
* It contains the declarations of the functions implemented in lexer.c.
* This file allows main.c and other required files to access the lexical-analysis functions without writing their declarations again.


                                //lexer.c//
* It is responsible for Lexical Analysis.
* It reads the input C program character by character and identifies different types of tokens.
* It performs:
    -> Keyword identification.
    -> Identifier identification.
    -> Number identification.
    -> Operator identification.
    -> Special-symbol identification.
    -> String-literal handling.
    -> Comment identification.
    -> Preprocessor-directive identification.
    -> Standard I/O identification, such as printf().
* It also displays the identified tokens using different colors so that the lexical analysis output is easier to understand.


                                //parser.h//
* It is the header file for the syntax analyzer.
* It contains the declaration of the syntax-analysis function implemented in parser.c.
* This allows main.c to access the syntax analyzer properly.


                                //parser.c//
* It is responsible for Syntax Analysis.
* It reads the source program line by line and checks whether the program follows the syntax rules implemented in our project.
* It performs checks for:
    -> Presence and declaration of main().
    -> Presence of printf().
    -> Header-file availability and format.
    -> Matching braces.
    -> Matching parentheses.
    -> Valid variable declarations.
    -> Missing variable names.
    -> Missing semicolons.
    -> Valid assignment statements.
    -> Undefined variables.
    -> Missing right-hand side in assignments.
    -> Invalid symbols.
* It also stores the names of declared variables and uses them later to check whether variables used in assignments have already been declared.
* Syntax errors are displayed with their line numbers.


                            //sample.c//
* It is the input C source file for our project.
* This is the file that is given to the analyzer for testing.
* The lexer reads this file to identify its tokens, and then the parser reads the same file again to perform syntax checking.

* Overall, the project demonstrates how a C program can be analyzed step by step before the later stages of compilation.


*/
#include "lexer.h"
#include "parser.h"
#include<stdio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"

int main(int argc, char *argv[])
{
    FILE *fp;
     if(argc != 2)
    {
        printf(RED "ERROR: Usage should be ./a.out <filename>\n"RESET);
        return 0;
    }

    fp = fopen(argv[1],"r");
    if(fp==NULL)
    {
        printf(RED"Error: File not found\n"RESET);
        return 0;
    }
    printf(MAGENTA "LEXICAL ANALYSIS....\n\n"RESET);
    lexicalAnalyzer(fp);
    rewind(fp);

    printf(MAGENTA"\nSYNTAX ANALYSIS....\n\n"RESET);
    syntaxAnalyzer(fp);

    fclose(fp);
    return 0;
}