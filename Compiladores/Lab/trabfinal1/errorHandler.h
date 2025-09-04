/*
 * UFMT - Universidade Federal de Mato Grosso
 * Laboratório de Compiladores
 * Author: Wesley Antonio Junior dos Santos
 * RGA:202011722024
 *
 * Error Handling System
 */

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  ERROR_SYNTAX,
  ERROR_SEMANTIC,
  ERROR_TYPE_MISMATCH,
  ERROR_UNDECLARED_VAR,
  ERROR_REDECLARED_VAR,
  ERROR_UNINITIALIZED_VAR,
  ERROR_DIVISION_BY_ZERO,
  ERROR_UNREACHABLE_CODE,
  WARNING_UNUSED_VAR,
  WARNING_UNINITIALIZED_VAR
} ErrorType;

typedef struct
{
  int line;
  int column;
  char *message;
  ErrorType type;
  char *filename;
} CompilerError;

typedef struct ErrorList
{
  CompilerError error;
  struct ErrorList *next;
} ErrorList;

// Global error handling
extern ErrorList *error_list;
extern int error_count;
extern int warning_count;
extern int show_warnings;

// Function declarations
void initErrorHandler(void);
void addError(ErrorType type, int line, int column, const char *message, const char *filename);
void addWarning(ErrorType type, int line, int column, const char *message, const char *filename);
void printErrors(void);
void printWarnings(void);
void printErrorSummary(void);
void freeErrorList(void);
void freeErrorHandler(void);
int hasErrors(void);
const char *getErrorTypeName(ErrorType type);

// Enhanced error reporting macros
#define REPORT_ERROR(type, line, msg) addError(type, line, 0, msg, current_filename)
#define REPORT_WARNING(type, line, msg) addWarning(type, line, 0, msg, current_filename)
#define REPORT_TYPE_ERROR(line, op, t1, t2)                                                                                                                                    \
  do                                                                                                                                                                           \
  {                                                                                                                                                                            \
    char buffer[256];                                                                                                                                                          \
    const char *type1_str = (t1 == INTEGER) ? "int" : ((t1 == FLOAT_TYPE) ? "float" : "string");                                                                               \
    const char *type2_str = (t2 == INTEGER) ? "int" : ((t2 == FLOAT_TYPE) ? "float" : "string");                                                                               \
    snprintf(buffer, sizeof(buffer), "Type mismatch in %s operation: cannot operate '%s' with '%s'. Consider using same type or explicit casting.", op, type1_str, type2_str); \
    addError(ERROR_TYPE_MISMATCH, line, 0, buffer, current_filename);                                                                                                          \
  } while (0)

#endif // ERROR_HANDLER_H
