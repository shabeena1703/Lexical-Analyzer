#include<stdio.h>
#include "parser.h"
#include<string.h>
#include<ctype.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

int hasSemicolon(char *line)
{
    int i=strlen(line) - 1;
    while(i>=0 && isspace((unsigned char)line[i]))
    {
        i--;
    }
    if(i >= 0 && line[i] == ';')
    {
        return 1;
    }
    return 0;
}

/* Ignore comments */
void removeComments(char line[], int *comment)
{
    char *single = strstr(line, "//");
    if(single != NULL)
    {
        *single = '\0';
    }

    if(strstr(line, "/*"))
    {
        *comment = 1;
    }

    if(*comment)
    {
        if(strstr(line, "*/"))
        {
            *comment = 0;
        }

        line[0] = '\0';
    }
}


void syntaxAnalyzer(FILE *fp)
{
    char line[300];
    int line_no = 1;
    int brace = 0;
    int has_main = 0;
    int comment = 0;

    //store declared variables
    char declared[100][50];
    int declared_count = 0;
    

    rewind(fp);

    while(fgets(line, sizeof(line), fp))
    {
        removeComments(line,&comment);
        if(line[0] == '\0')
        {
            continue;
        }
        if(strstr(line, "int main()"))
        {
            has_main = 1;
            break;
        }
        else if(strstr(line, "int main("))
        {
            has_main = -1;
            break;
        }
    }

    if(has_main == 0)
    {
        printf(RED "Error " RESET ": " YELLOW "Missing main() function in program\n"RESET);
    }
    else if(has_main == -1)
    {
        printf(RED "Error " RESET ": "YELLOW "Invalid main() declaration\n"RESET);
    }  
    
        //printf check

    int has_printf = 0;
    comment = 0;
    rewind(fp);

    while(fgets(line, sizeof(line), fp))
    {
        removeComments(line, &comment);

        if(line[0] == '\0')
        {
            continue;
        }

        if(strstr(line, "printf("))
        {
            has_printf = 1;
            break;
        }
    }

    if(!has_printf)
    {
        printf(RED "Error" RESET ": " YELLOW "Missing / invalid printf() statement inside main()\n"RESET);
    }

    /* Header check */

    int has_header = 0;
    comment = 0;
    rewind(fp);

    while(fgets(line, sizeof(line), fp))
    {
        removeComments(line, &comment);
        if(line[0] == '\0')
        {
            continue;
        }
        if(strstr(line, "#include"))
        {
            has_header = 1;
            break;
        }
    }

    if(!has_header)
    {
        printf(RED "Error" RESET ": " YELLOW "Missing header file\n"RESET);
    }

    comment = 0;
    rewind(fp);
    line_no = 1;

    while(fgets(line, sizeof(line), fp))
    {
        removeComments(line, &comment);
        if(line[0] == '\0')
        {
            continue;
        }

        //header check
        if(strstr(line, "#include"))
        {
            int i = strlen(line) - 1;

            while(i >= 0 && isspace((unsigned char)line[i]))
            {
                line[i] = '\0';
                i--;
            }

            if(strcmp(line, "#include<stdio.h>") != 0)
            {
                printf(RED "Error " RESET "(line %d): " YELLOW "Invalid header format\n"RESET, line_no);
            }
        }

    
        //brace check
        for(int i = 0; line[i]; i++)
        {
            if(line[i] == '{')
            {
                brace++;
            }
            if(line[i] == '}')
            {
                brace--;
            }
        }

        /* Parentheses check */
        int open = 0, close = 0;

        for(int i = 0; line[i]; i++)
        {
            if(line[i] == '(')
                open++;

            if(line[i] == ')')
                close++;
        }

        if(open != close)
        {
            printf(RED "Error " RESET "(line %d): " YELLOW "Unmatched parentheses\n" RESET,line_no);
        }

        //datatype check
        if((strstr(line, "int ") || strstr(line, "char ") || strstr(line, "float ") || strstr(line, "double ")) && strstr(line,"(") == NULL)
        {
            if(!hasSemicolon(line))
            {
                printf(RED "Error " RESET "(line %d): " YELLOW "Missing semicolon in declaration\n"RESET,line_no);
            }
            
            int i = 0;

            /* Skip leading spaces */
            while(isspace((unsigned char)line[i]))
            {
                i++;
            }

            /* Skip datatype */
            while(isalpha((unsigned char)line[i]))
            {
                i++;
            }

            /* Skip spaces after datatype */
            while(isspace((unsigned char)line[i]))
            {
                i++;
            }
            

            //check variable name
            if(!isalpha((unsigned char)line[i]) && line[i]!='_')
            {
                printf(RED "Error " RESET "(line %d): " YELLOW "Missing variable name in declaration\n"RESET,line_no);
            }
            else
            {
                //store variable name
                int j=0;
                while(isalnum((unsigned char)line[i]) || line[i]=='_')
                {
                    declared[declared_count][j++] = line[i++];
                }
                declared[declared_count][j] = '\0';
                declared_count++;


                /* Skip initialization part if present */
                while(line[i] && line[i] != ';')
                {
                    i++;
                }
            }
        
        }

        //assignment check    
        if(strchr(line, '=') && strstr(line, "for") == NULL && strstr(line, "int ") == NULL && strstr(line, "char ") == NULL && strstr(line, "float ") == NULL && strstr(line, "double ") == NULL)
        {
            char *eq = strchr(line, '=');

            //extract lhs
            int i = 0;
            while(isspace((unsigned char)line[i]))
            {
                i++;
            } 

            char lhs[50];
            int j = 0;

            while(isalnum((unsigned char)line[i]) || line[i]=='_')
            {
                lhs[j++] = line[i++];
            }
            lhs[j] = '\0';


            if(strlen(lhs) == 0)
            {
                printf(RED "Error " RESET "(line %d): " YELLOW "Invalid LHS in assignment\n"RESET,line_no);
            }
            else
            {
                int found = 0;
                for(int k = 0; k < declared_count; k++)
                {
                    if(strcmp(lhs, declared[k]) == 0)
                    {
                        found = 1;
                        break;
                    }
                }

                if(!found)
                {
                    printf(RED "Error " RESET "(line %d): " YELLOW "Undefined variable '%s'\n"RESET,line_no,lhs);
                }
            }

            //RHS check
            char *q = eq + 1;
            while(*q && isspace((unsigned char)*q))
            {
                q++;
            }

            if(*q == ';' || *q == '\n')
            {
                printf(RED "Error " RESET "(line %d): " YELLOW "Missing RHS in assignment\n" RESET,line_no);
            }

            if(!hasSemicolon(line))
            {
                printf(RED "Error " RESET "(line %d): " YELLOW "Missing semicolon in assignment\n"RESET ,line_no);
            }
        }

        for(int i = 0; line[i]; i++)
        {
            if(!isalnum((unsigned char)line[i]) && !isspace((unsigned char)line[i]) && line[i] != '_' && line[i] != '+' && line[i] != '-' && line[i] != '*' 
                && line[i] != '/' &&line[i] != '=' && line[i] != ';' && line[i] != '(' && line[i] != ')' && line[i] != '{' && line[i] != '}' 
                && line[i] != ',' && line[i] != '.' && line[i] != '#' && line[i] != '<' && line[i] != '>' && line[i] != '%' && line[i] != '"' && line[i] != '\'')
            {
                printf(RED "Error " RESET "(line %d): " YELLOW "Invalid symbol '%c'\n"RESET,line_no, line[i]);
            }
        }

        line_no++;
    }

    if(brace != 0)
    {
        printf(RED "Error : Unmatched braces in program\n");
    }
}
