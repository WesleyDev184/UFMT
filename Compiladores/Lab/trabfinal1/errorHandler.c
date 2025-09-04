/*
 * UFMT - Universidade Federal de Mato Grosso
 * Laboratório de Compiladores
 * Author: Wesley Antonio Junior dos Santos
 * RGA:202011722024
 *
 * Error Handling System Implementation
 */

#include <string.h>
#include "errorHandler.h"

// Global variables
ErrorList *error_list = NULL;
int error_count = 0;
int warning_count = 0;
int show_warnings = 1;
const char *current_filename = "input";

void initErrorHandler(void)
{
  error_list = NULL;
  error_count = 0;
  warning_count = 0;
}

void addError(ErrorType type, int line, int column, const char *message, const char *filename)
{
  ErrorList *new_error = malloc(sizeof(ErrorList));
  if (!new_error)
  {
    fprintf(stderr, "Fatal: Out of memory while reporting error\n");
    exit(1);
  }

  new_error->error.type = type;
  new_error->error.line = line;
  new_error->error.column = column;
  new_error->error.message = malloc(strlen(message) + 1);
  strcpy(new_error->error.message, message);
  new_error->error.filename = malloc(strlen(filename) + 1);
  strcpy(new_error->error.filename, filename);
  new_error->next = error_list;

  error_list = new_error;
  error_count++;
}

void addWarning(ErrorType type, int line, int column, const char *message, const char *filename)
{
  if (!show_warnings)
    return;

  ErrorList *new_warning = malloc(sizeof(ErrorList));
  if (!new_warning)
  {
    fprintf(stderr, "Fatal: Out of memory while reporting warning\n");
    exit(1);
  }

  new_warning->error.type = type;
  new_warning->error.line = line;
  new_warning->error.column = column;
  new_warning->error.message = malloc(strlen(message) + 1);
  strcpy(new_warning->error.message, message);
  new_warning->error.filename = malloc(strlen(filename) + 1);
  strcpy(new_warning->error.filename, filename);
  new_warning->next = error_list;

  error_list = new_warning;
  warning_count++;
}

const char *getErrorTypeName(ErrorType type)
{
  switch (type)
  {
  case ERROR_SYNTAX:
    return "Syntax Error";
  case ERROR_SEMANTIC:
    return "Semantic Error";
  case ERROR_TYPE_MISMATCH:
    return "Type Error";
  case ERROR_UNDECLARED_VAR:
    return "Undeclared Variable";
  case ERROR_REDECLARED_VAR:
    return "Redeclared Variable";
  case ERROR_UNINITIALIZED_VAR:
    return "Uninitialized Variable";
  case ERROR_DIVISION_BY_ZERO:
    return "Division by Zero";
  case ERROR_UNREACHABLE_CODE:
    return "Unreachable Code";
  case WARNING_UNUSED_VAR:
    return "Warning: Unused Variable";
  case WARNING_UNINITIALIZED_VAR:
    return "Warning: Possibly Uninitialized Variable";
  default:
    return "Unknown Error";
  }
}

void printErrors(void)
{
  ErrorList *current = error_list;
  int printed_errors = 0;
  int printed_warnings = 0;

  // Print errors first
  while (current)
  {
    if (current->error.type < WARNING_UNUSED_VAR)
    { // It's an error
      fprintf(stderr, "%s:%d: %s: %s\n",
              current->error.filename,
              current->error.line,
              getErrorTypeName(current->error.type),
              current->error.message);
      printed_errors++;
    }
    current = current->next;
  }

  // Then print warnings
  if (show_warnings)
  {
    current = error_list;
    while (current)
    {
      if (current->error.type >= WARNING_UNUSED_VAR)
      { // It's a warning
        fprintf(stderr, "%s:%d: %s: %s\n",
                current->error.filename,
                current->error.line,
                getErrorTypeName(current->error.type),
                current->error.message);
        printed_warnings++;
      }
      current = current->next;
    }
  }

  if (printed_errors > 0)
  {
    fprintf(stderr, "\nCompilation failed with %d error(s)", printed_errors);
    if (printed_warnings > 0)
    {
      fprintf(stderr, " and %d warning(s)", printed_warnings);
    }
    fprintf(stderr, ".\n");
  }
  else if (printed_warnings > 0)
  {
    fprintf(stderr, "\nCompilation succeeded with %d warning(s).\n", printed_warnings);
  }
}

void printWarnings(void)
{
  ErrorList *current = error_list;
  int printed_warnings = 0;

  // Print only warnings
  while (current)
  {
    if (current->error.type >= WARNING_UNUSED_VAR)
    { // It's a warning
      fprintf(stderr, "%s:%d: %s: %s\n",
              current->error.filename,
              current->error.line,
              getErrorTypeName(current->error.type),
              current->error.message);
      printed_warnings++;
    }
    current = current->next;
  }

  if (printed_warnings > 0)
  {
    fprintf(stderr, "\n%d warning(s) generated.\n", printed_warnings);
  }
}

void freeErrorList(void)
{
  ErrorList *current = error_list;
  while (current)
  {
    ErrorList *next = current->next;
    free(current->error.message);
    free(current->error.filename);
    free(current);
    current = next;
  }
  error_list = NULL;
  error_count = 0;
  warning_count = 0;
}

int hasErrors(void)
{
  return error_count > 0;
}

void printErrorSummary(void)
{
  if (error_count > 0 || warning_count > 0)
  {
    printf("\n=== COMPILATION STATISTICS ===\n");
    printf("Errors: %d\n", error_count);
    printf("Warnings: %d\n", warning_count);

    if (error_count > 0)
    {
      printf("\nErrors found during compilation:\n");
      printErrors();
    }

    if (warning_count > 0 && show_warnings)
    {
      printf("\nWarnings found during compilation:\n");
      printWarnings();
    }
  }
  else
  {
    printf("\n=== COMPILATION STATISTICS ===\n");
    printf("No errors or warnings found.\n");
  }
}

void freeErrorHandler(void)
{
  freeErrorList();
}
