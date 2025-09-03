# Simplified C Compiler - Version 1

## Overview

This is a compiler for a simplified version of the C programming language that generates x86-64 assembly code. The compiler is implemented using Flex (lexical analyzer) and Bison (parser) and includes a complete symbol table implementation and code generation for assembly output.

## Features

### Supported Language Constructs

1. **Variable Declarations**

   - Global scope variables only
   - Supported types: `int` and `float`
   - Syntax: `<type> <identifier> ;` or `<type> <identifier> = <value> ;`
   - Examples:
     ```c
     int total;
     float average = 3.14;
     ```

2. **Scope Management**

   - Code blocks delimited by `{` and `}`
   - Single main block execution

3. **Conditional Statements**

   - `if` statements
   - `if-else` statements
   - Examples:

     ```c
     if (x > 0) {
         // statements
     }

     if (condition) {
         // if body
     } else {
         // else body
     }
     ```

4. **Loop Constructs**

   - `while` loops
   - Example:
     ```c
     while (counter < 10) {
         // loop body
     }
     ```

5. **Input/Output Operations**

   - `read(variable)` - reads input into a variable
   - `write(expression)` - outputs an expression value
   - `write("string")` - outputs a string literal
   - Examples:
     ```c
     read(age);
     write(total);
     write("Hello World");
     ```

6. **Operators**
   - **Arithmetic**: `+`, `-`, `*`, `/`, `%`
   - **Relational**: `<`, `<=`, `>`, `>=`, `==`, `!=`
   - **Logical**: `!` (negation)
   - **Assignment**: `=`

### Improvements Made

1. **Language Translation**

   - Translated all Portuguese comments and messages to English
   - Maintained original header comments as requested

2. **Enhanced Error Handling**

   - Improved error messages with line numbers
   - Better semantic error detection
   - Comprehensive variable declaration checking

3. **Code Generation Improvements**

   - Fixed assembly code generation for x86-64
   - Proper stack management for expressions
   - Optimized register usage

4. **Symbol Table Enhancements**

   - Robust hash table implementation
   - Proper memory management
   - Detailed symbol information display

5. **Build System**
   - Fixed Makefile to include all necessary source files
   - Proper dependency management
   - Clean build targets

## Usage

### Compilation

```bash
make clean
make
```

### Running the Compiler

```bash
./compiler <input_file> [-o <output_file>]
```

- `<input_file>`: Source code file in simplified C
- `[-o <output_file>]`: Optional output assembly file name

### Examples

1. **Basic compilation**:

   ```bash
   ./compiler program.txt
   ```

   Generates `program.asm`

2. **Custom output file**:
   ```bash
   ./compiler program.txt -o my_program.asm
   ```
   Generates `my_program.asm`

## Sample Program

```c
float var_x;
float var_y;
float total;
float media;
int impar;

{
    read(var_x);
    read(var_y);
    total = var_x + var_y;
    media = total / 2;
    write(media);
    impar = 0;
    while (total > 0) {
        if (impar == 0) {
            impar = 1;
        } else {
            impar = 0;
        }
        total = total - 1;
    }
    write(impar);
}
```

## Output

Upon successful compilation, the compiler will:

1. Generate assembly code in the specified output file
2. Display a success message
3. Show the complete symbol table with variable information

Example output:

```
=== COMPILATION SUCCESSFUL ===
Assembly code generated in: program.asm

=== SYMBOL TABLE ===
[0]: EMPTY
[1]: {media} {1} {(null)}
[2]: {impar} {0} {(null)}
...
```

## Error Handling

The compiler provides detailed error messages for:

- **Lexical errors**: Invalid characters or tokens
- **Syntax errors**: Incorrect grammar usage
- **Semantic errors**:
  - Undeclared variables
  - Duplicate variable declarations
  - Type mismatches

Error messages include line numbers for easy debugging.

## Architecture

### Components

1. **Lexical Analyzer (lex.l)**

   - Tokenizes input source code
   - Recognizes keywords, identifiers, operators, and literals

2. **Parser (parser.y)**

   - Implements grammar rules for the simplified C language
   - Builds abstract syntax tree
   - Performs semantic analysis

3. **Symbol Table (symbolTable.c/h)**

   - Hash table implementation for variable storage
   - Manages variable types and values
   - Supports collision resolution via chaining

4. **Code Generation (codeGeneration.c/h)**

   - Generates x86-64 assembly code
   - Manages expression evaluation and control flow
   - Handles I/O operations

5. **Main Driver (main.c)**
   - Command-line interface
   - File handling
   - Compilation orchestration

## Technical Details

- **Target Architecture**: x86-64
- **Assembly Format**: NASM-compatible
- **Symbol Table**: Hash table with chaining
- **Memory Management**: Proper allocation and deallocation
- **Register Usage**: Optimized for expression evaluation

## Limitations

- Global variables only (no local scope)
- Limited to `int` and `float` types
- No function definitions (single main block)
- No arrays or complex data structures
- String literals for output only

## Dependencies

- GCC compiler
- Flex (lexical analyzer generator)
- Bison (parser generator)
- Make build system

## Author

Wesley Antonio Junior dos Santos  
RGA: 202011722024  
UFMT - Universidade Federal de Mato Grosso  
Laboratório de Compiladores
