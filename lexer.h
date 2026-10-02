#ifndef LEXER_H
#define LEXER_H

#include<stdio.h>

int is_keyword(char word[]);
int is_operator(char ch);
int is_specialsymbol(char ch);
int isnumber(char word[]);
int isidentifier(char word[]);
void lexicalAnalyzer(FILE *fp);

#endif