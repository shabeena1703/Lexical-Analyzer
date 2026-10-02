# 🔍 Lexical Analyzer 

---

## 📝 Brief Summary

This project is a **C-based Lexical Analyzer and Syntax Analyzer** designed to analyze C source code and identify lexical elements and basic syntax errors.

The program performs two major stages:

**Lexical Analysis** → Identifies tokens such as keywords, identifiers, numbers, operators, special symbols, comments, strings, and preprocessor directives.

**Syntax Analysis** → Checks the source code for common syntax errors such as missing semicolons, unmatched braces and parentheses, invalid declarations, undefined variables, invalid assignments, and missing header files.

---

## 📌 Overview

A compiler processes source code in multiple stages before converting it into machine-level instructions.

This project focuses on two important stages:

**🔹 Lexical Analysis**

The lexical analyzer reads the C source file character by character and identifies different types of tokens.

It recognizes:

-> Keywords

-> Identifiers

-> Numbers

-> Operators

-> Special symbols

-> String literals

-> Comments

-> Preprocessor directives

-> Standard I/O functions such as `printf`

**🔹 Syntax Analysis**

The syntax analyzer checks whether the source code follows basic C syntax rules.

It checks for:

-> Missing `main()` function

-> Invalid `main()` declaration

-> Missing header files

-> Invalid header format

-> Missing `printf()` statement

-> Missing semicolons

-> Missing variable names

-> Undefined variables

-> Invalid assignment statements

-> Missing RHS in assignments

-> Unmatched parentheses

-> Unmatched braces

-> Invalid symbols

This project helped me understand:

-> How a compiler analyzes source code

-> How lexical tokens are identified

-> How syntax errors can be detected

-> File handling in C

-> String and character processing

-> Modular programming

-> Use of C library functions such as `fgets()`, `fgetc()`, `strstr()`, `strcmp()`, `isalnum()`, and `isspace()`

---

## 🎯 Problem Statement

When a C program is compiled, the compiler first needs to understand the source code and verify whether it follows the language rules.

The objective of this project is to develop a simple analyzer that can:

-> Read a C source file

-> Identify different lexical tokens

-> Detect common syntax errors

-> Display meaningful error messages along with line numbers

This provides a basic understanding of how lexical and syntax analysis work internally in a compiler.

---

## 📂 Input

The project takes a **C source file** as input.

Example:

```text
sample.c
```

The input file may contain:

-> C keywords

-> Variables and identifiers

-> Numbers

-> Operators

-> Special symbols

-> Comments

-> String literals

-> Preprocessor directives

-> C statements and declarations

---

## 📁 Project Structure

```text
├── main.c
├── lexer.c
├── lexer.h
├── parser.c
├── parser.h
├── sample.c
└── README.md
```

### 📄 File Description

**main.c**

-> Controls the overall program execution

-> Opens the input C source file

-> Calls the lexical analyzer

-> Calls the syntax analyzer

**lexer.c**

-> Performs lexical analysis

-> Identifies keywords, identifiers, numbers, operators, special symbols, comments, strings, and preprocessor directives

**lexer.h**

-> Contains lexical analyzer function declarations

**parser.c**

-> Performs basic syntax analysis

-> Detects common syntax errors in the C source file

**parser.h**

-> Contains syntax analyzer function declarations

**sample.c**

-> Sample C source file used for testing the analyzer

---

## 🛠️ Tools and Technologies Used

**Programming Language**

```text
C
```

**Operating System**

```text
Linux (Ubuntu)
```

**Compiler**

```text
GCC
```

**Development Tools**

```text
VS Code
Git & GitHub
```

**Concepts Used**

```text
Lexical Analysis

Syntax Analysis

File Handling

String Handling

Character Handling

Pointers

Arrays

Functions

Modular Programming

C Library Functions

Error Detection
```

---

## 🔧 Methods

**🔍 Lexical Analysis Process**

The lexical analyzer reads the input file character by character.

The basic process is:

-> Read each character from the source file

-> Identify preprocessor directives

-> Identify string literals

-> Collect alphanumeric characters into a buffer

-> Check whether the collected word is a keyword

-> Check whether it is a number

-> Check whether it is an identifier

-> Identify operators

-> Identify special symbols

-> Detect comments

-> Display the identified token and its type

Example output:

```text
keyword          : int
Identifier       : main
Special symbol   : (
Special symbol   : )
Special symbol   : {
keyword          : int
Identifier       : a
Operator         : =
Number            : 10
Special symbol   : ;
```

---

**🧠 Syntax Analysis Process**

The syntax analyzer reads the C source file line by line and performs different checks.

It verifies:

```text
        C Source File
              ↓
        Read line by line
              ↓
       Remove comments
              ↓
       Check main() function
              ↓
       Check header files
              ↓
       Check printf()
              ↓
     Check declarations
              ↓
     Check assignments
              ↓
   Check parentheses & braces
              ↓
      Check invalid symbols
              ↓
       Display errors
```

---

## 🚨 Error Detection

The syntax analyzer generates error messages when common syntax problems are found.

** Example 1 — Missing semicolon**

```c
int b = 10 + 5
```

Output:

```text
Error (line 8): Missing semicolon in declaration
```

**Example 2 — Undefined variable**

```c
b = 10 + 5;
```

when `b` has not been declared.

Output:

```text
Error (line 8): Undefined variable 'b'
```

**Example 3 — Missing variable name**

```c
int;
```

Output:

```text
Error (line 9): Missing variable name in declaration
```

**Example 4 — Unmatched parentheses**

```c
for(i=0;i<5;i++
```

Output:

```text
Error (line 12): Unmatched parentheses
```

**Example 5 — Missing `main()` function**

If the input program does not contain a valid `main()` function:

```text
Error: Missing main() function in program
```

---

## 🔄 Program Flow

```text
                  START
                    ↓
          Read command-line argument
                    ↓
            Open C source file
                    ↓
          ┌─────────┴─────────┐
          ↓                   ↓
   Lexical Analysis     Syntax Analysis
          ↓                   ↓
   Identify Tokens       Check Syntax
          ↓                   ↓
   Display Tokens        Display Errors
          └─────────┬─────────┘
                    ↓
                  END
```

---

## 💡 Key Insights

-> Understood the basic phases of a compiler

-> Learned how lexical tokens are identified

-> Learned how syntax errors can be detected

-> Improved understanding of file handling in C

-> Practiced character-by-character file processing

-> Improved string handling using standard C library functions

-> Learned how to maintain and check declared variables

-> Practiced modular programming using `.c` and `.h` files

-> Improved debugging and error-handling skills

---

## 📦 Output

The program displays the results of both lexical and syntax analysis.

**🔍 Lexical Analysis**

Example:

```text
LEXICAL ANALYSIS....

Preprocessor directive : #include<stdio.h>
keyword                : int
Identifier             : main
Special symbol         : (
Special symbol         : )
Special symbol         : {
keyword                : int
Identifier             : a
Special symbol         : ;
Identifier             : printf
Special symbol         : (
String literal         : "
Special symbol         : )
Special symbol         : ;
```

**🧠 Syntax Analysis**

For an invalid C program, errors are displayed with their corresponding line numbers:

```text
SYNTAX ANALYSIS....

Error (line 8): Missing semicolon in declaration
Error (line 9): Missing variable name in declaration
Error (line 12): Unmatched parentheses
Error (line 8): Undefined variable 'b'
```

---

## 🚀 How to Run This Project

**Clone Repository**

```bash
git clone https://github.com/shabeena1703/Lexical-Analyzer.git
```

**Navigate to Project Folder**

```bash
cd Lexical-Analyzer
```

**Compile**

```bash
gcc main.c lexer.c parser.c -o lexical_analyzer
```

**Run**

```bash
./lexical_analyzer sample.c
```

---

## 🧪 Sample Input

Example `sample.c`:

```c
#include<stdio.h>

int main()
{
    int a;
    char d;

    d = 's';
    a = 5;

    b = 10 + 5;

    int;

    int i;

    for(i=0;i<5;i++
    {
        printf("%d",i);
    }

    printf("%d %d",a,b);
}
```

The analyzer processes this program and reports the detected lexical tokens and syntax errors.

---

## ⚠️ Challenges Faced

-> Identifying different types of tokens correctly

-> Handling comments and string literals

-> Processing the input file character by character

-> Detecting missing semicolons

-> Checking unmatched braces and parentheses

-> Tracking declared variables

-> Detecting undefined variables

-> Validating C declarations and assignments

-> Handling different types of syntax errors

-> Maintaining separate modules for lexical and syntax analysis

---

## 🧪 Result and Conclusion

This project successfully implements a basic **Lexical Analyzer and Syntax Analyzer for C source code**.

The lexical analyzer identifies different tokens from the input source file, while the syntax analyzer detects common syntax errors and displays meaningful error messages with line numbers.

The project provided practical understanding of how source code is processed during the early stages of compilation.

---

## 🔮 Future Work

-> Support more C syntax rules

-> Improve detection of multi-character operators such as `==`, `!=`, `<=`, and `>=`

-> Improve handling of nested and multi-line comments

-> Support more complex variable declarations

-> Add better expression validation

-> Improve syntax error recovery

-> Add support for more C data types

-> Build a graphical user interface

-> Extend the analyzer into a complete mini compiler

---

## 👤 Author & Contact

**Shaik Shabeena**

Electronics and Communication Engineering

📧 Email: [skshabeena33@gmail.com](mailto:skshabeena33@gmail.com)

🔗 LinkedIn: https://www.linkedin.com/in/shaik-shabeena-36a7b9332/
