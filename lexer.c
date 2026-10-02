#include "lexer.h"
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"

char *keywords[]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if",
"inline","int","long", "register","restrict","return","short","signed","sizeof","static","struct","switch","typedef","union",
"unsigned","void","volatile","while"};

int keyword_count = 34;

char operators[] = "+-*/%=!<>^&|~?:.";

char special[] = "();{}[],'\"";

int is_keyword(char word[])
{
    for(int i=0;i<keyword_count;i++)
    {
        if(strcmp(word,keywords[i])==0)
            return 1;
    }

    return 0;
}

int is_operator(char ch)
{
    for(int i=0;operators[i]!='\0';i++)
    {
        if(ch==operators[i])
            return 1;
    }

    return 0;
}

int is_specialsymbol(char ch)
{
    for(int i=0;special[i]!='\0';i++)
    {
        if(ch==special[i])
            return 1;
    }

    return 0;
}

int isnumber(char word[])
{
    for(int i=0;word[i]!='\0';i++)
    {
        if(!isdigit((unsigned char)word[i]))
            return 0;
    }

    return 1;
}

int isidentifier(char word[])
{
    if(!isalpha((unsigned char)word[0]) && word[0]!='_')
        return 0;

    for(int i=1;word[i]!='\0';i++)
    {
        if(!isalnum((unsigned char)word[i]) && word[i]!='_')
            return 0;
    }

    return 1;
}

void lexicalAnalyzer(FILE *fp)
{
    char ch;
    char buffer[100];
    int i = 0, line = 1;

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '#')
        {
            buffer[0] = ch;
            i = 1;

            while((ch = fgetc(fp)) != EOF && ch != '\n')
            {
                buffer[i++] = ch;
            }

            buffer[i] = '\0';

            printf(BLUE "Preprocessor directive       " RESET ": "YELLOW "%s\n" RESET, buffer);

            line++;
            i = 0;
            continue;
        }

        if(ch == '\n')
        {
            line++;
        }

        // handle string literal
        if(ch == '"')
        {
            printf(GREEN "String literal   " RESET ": "YELLOW "\"\n" RESET);

            while((ch = fgetc(fp)) != EOF && ch != '"')
            {
                // skip inside string
            }

            printf(GREEN "String literal   " RESET ": "YELLOW "\"\n" RESET);

            continue;
        }

        if(isalnum((unsigned char)ch) || ch=='_')
        {
            buffer[i++] = ch;
        }
        else
        {
            if(i > 0)
            {
                buffer[i] = '\0';

                if(is_keyword(buffer))
                    printf(GREEN "keyword         " RESET ": "YELLOW "%s\n" RESET, buffer);

                else if(isnumber(buffer))
                    printf(GREEN "Number          " RESET ": "YELLOW "%s\n" RESET, buffer);

                else if(strcmp(buffer, "printf") == 0)
                    printf(GREEN "Standard I/O    " RESET ": "YELLOW "%s\n" RESET, buffer);

                else if(isidentifier(buffer))
                    printf(GREEN "Identifier      " RESET ": "YELLOW "%s\n" RESET, buffer);

                i = 0;
            }

            if(ch == '/')
            {
                char next = fgetc(fp);

                if(next == '/')
                {
                    printf(MAGENTA "Comment         " RESET ": "YELLOW "//\n" RESET);

                    while((ch = fgetc(fp)) != '\n' && ch != EOF)
                    {
                    }

                    line++;
                }
            }
            else if(is_operator(ch))
            {
                printf(MAGENTA"Operator        " RESET ": "YELLOW "%c\n" RESET, ch);
            }
            else if(is_specialsymbol(ch))
            {
                printf(BLUE "Special symbol  " RESET ": "YELLOW "%c\n" RESET, ch);
            }
        }
    }
}