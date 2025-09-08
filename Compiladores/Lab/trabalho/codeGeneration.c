/*
 *
 * UFMT - Universidade Federal de Mato Grosso
 * Laboratório de Compiladores
 * Author: Wesley Antonio Junior dos Santos
 * RGA:202011722024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "symbolTable.h"
#include "codeGeneration.h"
#include "errorHandler.h"

// ===============================================
// INTEGRATED OPTIMIZER SYSTEM
// ===============================================

typedef enum
{
    OPT_CONSTANT_FOLDING,
    OPT_DEAD_CODE_ELIMINATION,
    OPT_STRENGTH_REDUCTION,
    OPT_COMMON_SUBEXPRESSION
} OptimizationType;

typedef struct
{
    int enabled;
    int level;
    int constant_folding;
    int strength_reduction;
    int dead_code_elimination;
} OptimizerConfig;

static OptimizerConfig optimizer_config = {1, 1, 1, 1, 0};

// String literal management
#define MAX_STRINGS 100
typedef struct
{
    char label[64];
    char content[256];
} StringLiteral;

static StringLiteral string_literals[MAX_STRINGS];
static int string_count = 0;

// Global variables
extern SymTable table;
extern FILE *out_file;
static int label_counter = 0;

// Optimization tracking - store last two loaded values
static char last_left_operand[64] = "";
static char last_right_operand[64] = "";
static int has_literal_operands = 0;

// Function to add a string literal and return its label
static char *addStringLiteral(const char *str)
{
    if (string_count >= MAX_STRINGS)
    {
        fprintf(stderr, "Error: Too many string literals\n");
        return NULL;
    }

    // Generate label for this string
    sprintf(string_literals[string_count].label, "str_%d", string_count);

    // Copy the string content without quotes
    int len = strlen(str);
    if (str[0] == '"' && str[len - 1] == '"')
    {
        strncpy(string_literals[string_count].content, str + 1, len - 2);
        string_literals[string_count].content[len - 2] = '\0';
    }
    else
    {
        strcpy(string_literals[string_count].content, str);
    }

    return string_literals[string_count++].label;
}

static int isLiteralInteger(const char *str)
{
    if (!str || *str == '\0')
        return 0;

    char *endptr;
    strtol(str, &endptr, 10);
    return (*endptr == '\0' && strchr(str, '.') == NULL);
}

static int isLiteralFloat(const char *str)
{
    if (!str || *str == '\0')
        return 0;

    char *endptr;
    strtod(str, &endptr);
    return (*endptr == '\0' && strchr(str, '.') != NULL);
}

static int isPowerOfTwo(long value)
{
    return value > 0 && (value & (value - 1)) == 0;
}

static int log2Int(long value)
{
    int log = 0;
    while (value > 1)
    {
        value >>= 1;
        log++;
    }
    return log;
}

static long evaluateConstantInteger(const char *expr)
{
    // Simple constant evaluation (could be expanded)
    return strtol(expr, NULL, 10);
}

static double evaluateConstantFloat(const char *expr)
{
    // Simple constant evaluation (could be expanded)
    return strtod(expr, NULL);
}

static void optimizeConstantFolding(char *dest, const char *op, const char *left, const char *right, Type type)
{
    if (!optimizer_config.enabled || !optimizer_config.constant_folding)
    {
        dest[0] = '\0';
        return;
    }

    dest[0] = '\0';

    if (type == INTEGER && isLiteralInteger(left) && isLiteralInteger(right))
    {
        long left_val = evaluateConstantInteger(left);
        long right_val = evaluateConstantInteger(right);
        long result = 0;

        if (strcmp(op, "+") == 0)
        {
            result = left_val + right_val;
        }
        else if (strcmp(op, "-") == 0)
        {
            result = left_val - right_val;
        }
        else if (strcmp(op, "*") == 0)
        {
            result = left_val * right_val;
        }
        else if (strcmp(op, "/") == 0 && right_val != 0)
        {
            result = left_val / right_val;
        }
        else
        {
            return; // Can't optimize
        }

        sprintf(dest, "    ; Constant folding optimization: %s %s %s = %ld\n", left, op, right, result);
        sprintf(dest + strlen(dest), "    mov rbx, %ld                ; Optimized constant\n", result);
        sprintf(dest + strlen(dest), "    push rbx\n");
    }
    else if (type == FLOAT && isLiteralFloat(left) && isLiteralFloat(right))
    {
        double left_val = evaluateConstantFloat(left);
        double right_val = evaluateConstantFloat(right);
        double result = 0.0;

        if (strcmp(op, "+") == 0)
        {
            result = left_val + right_val;
        }
        else if (strcmp(op, "-") == 0)
        {
            result = left_val - right_val;
        }
        else if (strcmp(op, "*") == 0)
        {
            result = left_val * right_val;
        }
        else if (strcmp(op, "/") == 0 && right_val != 0.0)
        {
            result = left_val / right_val;
        }
        else
        {
            return; // Can't optimize
        }

        long *bits = (long *)&result;
        sprintf(dest, "    ; Constant folding optimization: %s %s %s = %f\n", left, op, right, result);
        sprintf(dest + strlen(dest), "    mov rbx, %ld                ; Optimized float constant\n", *bits);
        sprintf(dest + strlen(dest), "    push rbx\n");
    }
}

static void optimizeStrengthReduction(char *dest, const char *op, const char *left, const char *right, Type type)
{
    if (!optimizer_config.enabled || !optimizer_config.strength_reduction)
    {
        dest[0] = '\0';
        return;
    }

    dest[0] = '\0';

    // Optimize multiplication by powers of 2
    if (strcmp(op, "*") == 0 && type == INTEGER)
    {
        if (isLiteralInteger(right))
        {
            long right_val = evaluateConstantInteger(right);
            if (isPowerOfTwo(right_val))
            {
                int shift_amount = log2Int(right_val);
                sprintf(dest, "    ; Strength reduction optimization: multiply by %ld = shift left %d\n", right_val, shift_amount);
                sprintf(dest + strlen(dest), "    pop rcx                     ; Get multiplier (ignored)\n");
                sprintf(dest + strlen(dest), "    pop rbx                     ; Get multiplicand\n");
                sprintf(dest + strlen(dest), "    shl rbx, %d                 ; Shift left instead of multiply\n", shift_amount);
                sprintf(dest + strlen(dest), "    push rbx\n");
                return;
            }
        }
        if (isLiteralInteger(left))
        {
            long left_val = evaluateConstantInteger(left);
            if (isPowerOfTwo(left_val))
            {
                int shift_amount = log2Int(left_val);
                sprintf(dest, "    ; Strength reduction optimization: multiply by %ld = shift left %d\n", left_val, shift_amount);
                sprintf(dest + strlen(dest), "    pop rbx                     ; Get second operand\n");
                sprintf(dest + strlen(dest), "    pop rax                     ; Get first operand\n");
                sprintf(dest + strlen(dest), "    shl rax, %d                 ; Shift left instead of multiply\n", shift_amount);
                sprintf(dest + strlen(dest), "    push rax\n");
                return;
            }
        }
    }

    if (strcmp(op, "/") == 0 && type == INTEGER && isLiteralInteger(right))
    {
        long right_val = evaluateConstantInteger(right);
        if (isPowerOfTwo(right_val))
        {
            int shift_amount = log2Int(right_val);
            sprintf(dest, "    ; Strength reduction optimization: divide by %ld = shift right %d\n", right_val, shift_amount);
            sprintf(dest + strlen(dest), "    pop rcx                     ; Get divisor (ignored)\n");
            sprintf(dest + strlen(dest), "    pop rax                     ; Get dividend\n");
            sprintf(dest + strlen(dest), "    sar rax, %d                 ; Arithmetic shift right\n", shift_amount);
            sprintf(dest + strlen(dest), "    push rax\n");
            return;
        }
    }

    if (strcmp(op, "*") == 0 && type == INTEGER)
    {
        if (isLiteralInteger(right))
        {
            long right_val = evaluateConstantInteger(right);
            if (right_val == 0)
            {
                sprintf(dest, "    ; Optimization: multiply by 0\n");
                sprintf(dest + strlen(dest), "    pop rbx                     ; Remove operands\n");
                sprintf(dest + strlen(dest), "    pop rbx\n");
                sprintf(dest + strlen(dest), "    mov rbx, 0                  ; Result is 0\n");
                sprintf(dest + strlen(dest), "    push rbx\n");
                return;
            }
            else if (right_val == 1)
            {
                sprintf(dest, "    ; Optimization: multiply by 1 (identity)\n");
                sprintf(dest + strlen(dest), "    pop rbx                     ; Remove multiplier\n");
                sprintf(dest + strlen(dest), "    ; First operand already on stack\n");
                return;
            }
        }
        if (isLiteralInteger(left))
        {
            long left_val = evaluateConstantInteger(left);
            if (left_val == 0)
            {
                sprintf(dest, "    ; Optimization: multiply by 0 (left operand)\n");
                sprintf(dest + strlen(dest), "    pop rbx                     ; Remove operands\n");
                sprintf(dest + strlen(dest), "    pop rbx\n");
                sprintf(dest + strlen(dest), "    mov rbx, 0                  ; Result is 0\n");
                sprintf(dest + strlen(dest), "    push rbx\n");
                return;
            }
            else if (left_val == 1)
            {
                sprintf(dest, "    ; Optimization: multiply by 1 (left operand - identity)\n");
                sprintf(dest + strlen(dest), "    pop rbx                     ; Keep second operand\n");
                sprintf(dest + strlen(dest), "    pop rax                     ; Remove first operand (1)\n");
                sprintf(dest + strlen(dest), "    push rbx                    ; Push second operand as result\n");
                return;
            }
        }
    }

    if ((strcmp(op, "+") == 0 || strcmp(op, "-") == 0) && type == INTEGER)
    {
        if (isLiteralInteger(right))
        {
            long right_val = evaluateConstantInteger(right);
            if (right_val == 0)
            {
                sprintf(dest, "    ; Optimization: %s by 0 (identity)\n",
                        strcmp(op, "+") == 0 ? "addition" : "subtraction");
                sprintf(dest + strlen(dest), "    pop rbx                     ; Remove zero\n");
                sprintf(dest + strlen(dest), "    ; First operand already on stack\n");
                return;
            }
        }
    }
}

void resetLabelCounter()
{
    label_counter = 0;
    last_left_operand[0] = '\0';
    last_right_operand[0] = '\0';
    has_literal_operands = 0;
}

// Function to create assembly file preamble
void makePreambule(const char *filename)
{
    // Assembly format header with detailed comments
    fprintf(out_file, "; ===============================================\n");
    fprintf(out_file, "; Assembly code generated from: %s\n", filename);
    fprintf(out_file, "; Generated by UFMT Compiler Lab Project\n");
    fprintf(out_file, "; Author: Wesley Antonio Junior dos Santos\n");
    fprintf(out_file, "; ===============================================\n");
    fprintf(out_file, "\n");

    // External function declarations
    fprintf(out_file, "; ===============================================\n");
    fprintf(out_file, "; External function declarations\n");
    fprintf(out_file, "; ===============================================\n");
    fprintf(out_file, "extern printf                   ; C standard library printf\n");
    fprintf(out_file, "extern scanf                    ; C standard library scanf\n");
    fprintf(out_file, "extern exit                     ; C standard library exit\n");
    fprintf(out_file, "\n");

    // Data section with format strings and variables
    fprintf(out_file, "; ===============================================\n");
    fprintf(out_file, "; Data section - Constants and Variables\n");
    fprintf(out_file, "; ===============================================\n");
    fprintf(out_file, "section .data\n");
    fprintf(out_file, "    ; Format strings for I/O operations\n");
    fprintf(out_file, "    fmt_d:       db \"%%ld\", 0          ; Integer format (no newline)\n");
    fprintf(out_file, "    fmt_f:       db \"%%lf\", 0          ; Float format (no newline)\n");
    fprintf(out_file, "    fmt_s:       db \"%%s\", 0          ; String format (no newline)\n");
    fprintf(out_file, "    fmt_c:       db \"%%c\", 0          ; Char format (no newline)\n");
    fprintf(out_file, "    fmt_dln:     db \"%%ld\", 10, 0     ; Integer format (with newline)\n");
    fprintf(out_file, "    fmt_fln:     db \"%%lf\", 10, 0     ; Float format (with newline)\n");
    fprintf(out_file, "    fmt_sln:     db \"%%s\", 10, 0      ; String format (with newline)\n");
    fprintf(out_file, "    fmt_cln:     db \"%%c\", 10, 0      ; Char format (with newline)\n");
    fprintf(out_file, "\n");
    fprintf(out_file, "    ; Boolean literals\n");
    fprintf(out_file, "    str_true:    db \"true\", 0         ; Boolean true string\n");
    fprintf(out_file, "    str_false:   db \"false\", 0        ; Boolean false string\n");
    fprintf(out_file, "    newline:     db 10, 0              ; Newline character\n");
    fprintf(out_file, "\n");
    fprintf(out_file, "    ; Temporary variables\n");
    fprintf(out_file, "    temp_float:  dq 0.0              ; Temporary for float conversions\n");
    fprintf(out_file, "\n");
    fprintf(out_file, "    ; Program variables\n");
}

// End of data section and beginning of code section
void dumpCodeDeclarationEnd()
{
    // Add all declared variables to the data section
    for (int i = 0; i < table.max_size; i++)
    {
        if (table.array[i].data.identifier[0] != '\0')
        {
            SymTableNode *node = &table.array[i];
            while (node != NULL)
            {
                if (node->data.type == STRING)
                {
                    if (node->data.value != NULL)
                    {
                        // Create string literal and initialize variable with its address
                        char *label = addStringLiteral(node->data.value);
                        if (label != NULL)
                        {
                            fprintf(out_file, "    %s:          dq %s              ; String variable = %s\n",
                                    node->data.identifier, label, node->data.value);
                        }
                        else
                        {
                            fprintf(out_file, "    %s:          dq 0              ; String variable (error)\n", node->data.identifier);
                        }
                    }
                    else
                    {
                        fprintf(out_file, "    %s:          dq 0              ; String variable\n", node->data.identifier);
                    }
                }
                else if (node->data.type == CHAR)
                {
                    if (node->data.value != NULL)
                    {
                        // Extract character from 'x' format
                        char c = node->data.value[1]; // Get character between quotes
                        fprintf(out_file, "    %s:          db %d              ; Char variable = %s\n",
                                node->data.identifier, (int)c, node->data.value);
                    }
                    else
                    {
                        fprintf(out_file, "    %s:          db 0              ; Char variable\n", node->data.identifier);
                    }
                }
                else if (node->data.type == BOOL)
                {
                    if (node->data.value != NULL)
                    {
                        int val = (strcmp(node->data.value, "true") == 0) ? 1 : 0;
                        fprintf(out_file, "    %s:          db %d              ; Bool variable = %s\n",
                                node->data.identifier, val, node->data.value);
                    }
                    else
                    {
                        fprintf(out_file, "    %s:          db 0              ; Bool variable\n", node->data.identifier);
                    }
                }
                else
                {
                    if (node->data.value != NULL)
                    {
                        if (node->data.type == INTEGER)
                        {
                            fprintf(out_file, "    %s:          dq %s              ; Integer variable = %s\n",
                                    node->data.identifier, node->data.value, node->data.value);
                        }
                        else if (node->data.type == FLOAT)
                        {
                            fprintf(out_file, "    %s:          dq %s              ; Float variable = %s\n",
                                    node->data.identifier, node->data.value, node->data.value);
                        }
                    }
                    else
                    {
                        fprintf(out_file, "    %s:          dq 0", node->data.identifier);
                        if (node->data.type == FLOAT)
                        {
                            fprintf(out_file, ".0");
                        }
                        fprintf(out_file, "              ; %s variable\n",
                                node->data.type == INTEGER ? "Integer" : "Float");
                    }
                }
                node = node->next;
            }
        }
    }

    // Add string literals to the data section
    if (string_count > 0)
    {
        fprintf(out_file, "\n    ; String literals\n");
        for (int i = 0; i < string_count; i++)
        {
            fprintf(out_file, "    %s:     db \"%s\", 0\n", string_literals[i].label, string_literals[i].content);
        }
    }

    fprintf(out_file, "\nsection .text\n");
    fprintf(out_file, "global main\n");
    fprintf(out_file, "\n");
}

// Function to create assembly file epilogue
void makeCodeEpilogue(void)
{
    // Add final cleanup code to the existing main function
    fprintf(out_file, "\n");
    fprintf(out_file, "    ; Program cleanup and exit\n");
    fprintf(out_file, "    mov rsp, rbp                ; Restore stack pointer\n");
    fprintf(out_file, "    pop rbp                     ; Restore base pointer\n");
    fprintf(out_file, "    mov rdi, 0                  ; Exit status\n");
    fprintf(out_file, "    call exit                   ; Exit program\n");
    fprintf(out_file, "\n");
}
void makeCodeDeclaration(char *dest, char *identifier, Type type, char *value)
{
    // Don't generate code here - variables will be declared in dumpCodeDeclarationEnd
    // Suppress unused parameter warnings
    (void)identifier;
    (void)type;
    (void)value;

    dest[0] = '\0'; // Empty string
}

int makeCodeAssignment(char *dest, char *id, char *expr)
{
    SymTableEntry *ret = findSymTable(&table, id);
    dest[0] = '\0';

    // Validation already done in the syntactic analyzer
    if (ret->type == INTEGER || ret->type == FLOAT)
    {
        sprintf(dest + strlen(dest), "%s", expr);
        sprintf(dest + strlen(dest), "    pop rbx\n");
        sprintf(dest + strlen(dest), "    mov [%s], rbx\n", ret->identifier);
    }
    else if (ret->type == CHAR || ret->type == BOOL)
    {
        sprintf(dest + strlen(dest), "%s", expr);
        sprintf(dest + strlen(dest), "    pop rbx\n");
        sprintf(dest + strlen(dest), "    mov [%s], bl\n", ret->identifier);
    }
    else if (ret->type == STRING)
    {
        sprintf(dest + strlen(dest), "%s", expr);
        sprintf(dest + strlen(dest), "    pop rbx\n");
        sprintf(dest + strlen(dest), "    mov [%s], rbx\n", ret->identifier);
    }
    else
    {
        fprintf(stderr, "Unsupported type for assignment at line %d\n",
                cont_lines);
        return 0;
    }
    return 1;
}

int checkTypeCompatibility(Type type1, Type type2)
{
    return (type1 == type2);
}

// Function to print type mismatch error
void printTypeMismatchError(int line, const char *operation, Type type1, Type type2)
{
    const char *type1_str;
    const char *type2_str;

    switch (type1)
    {
    case INTEGER:
        type1_str = "int";
        break;
    case FLOAT:
        type1_str = "float";
        break;
    case STRING:
        type1_str = "string";
        break;
    case CHAR:
        type1_str = "char";
        break;
    case BOOL:
        type1_str = "bool";
        break;
    default:
        type1_str = "unknown";
        break;
    }

    switch (type2)
    {
    case INTEGER:
        type2_str = "int";
        break;
    case FLOAT:
        type2_str = "float";
        break;
    case STRING:
        type2_str = "string";
        break;
    case CHAR:
        type2_str = "char";
        break;
    case BOOL:
        type2_str = "bool";
        break;
    default:
        type2_str = "unknown";
        break;
    }

    fprintf(stderr, "Error at line %d: Type mismatch in %s operation. Cannot operate %s with %s.\n",
            line, operation, type1_str, type2_str);
}

int makeCodeLoad(char *dest, char *id, int ref)
{
    dest[0] = '\0';

    if (ref == 0)
    {
        // Check if it's a string literal
        if (id[0] == '"')
        {
            // It's a string literal
            sprintf(dest + strlen(dest), "    ; Load string literal: %s\n", id);
            // For string literals, we store the address of the string
            char *label = addStringLiteral(id);
            if (label == NULL)
                return 0;
            sprintf(dest + strlen(dest), "    mov rbx, %s               ; Load string address\n", label);
            sprintf(dest + strlen(dest), "    push rbx\n");
            return 1;
        }
        // Check if it's a char literal
        else if (id[0] == '\'')
        {
            // It's a char literal
            char char_val = id[1]; // Get the character inside quotes
            sprintf(dest + strlen(dest), "    ; Load char literal: %s\n", id);
            sprintf(dest + strlen(dest), "    mov rbx, %d                ; Load char value\n", (int)char_val);
            sprintf(dest + strlen(dest), "    push rbx\n");
            return 1;
        }
        // Check if it's a boolean literal
        else if (strcmp(id, "1") == 0) // true represented as 1
        {
            sprintf(dest + strlen(dest), "    ; Load boolean literal: true\n");
            sprintf(dest + strlen(dest), "    mov rbx, 1                ; Load true value\n");
            sprintf(dest + strlen(dest), "    push rbx\n");
            return 1;
        }
        else if (strcmp(id, "0") == 0) // false represented as 0
        {
            sprintf(dest + strlen(dest), "    ; Load boolean literal: false\n");
            sprintf(dest + strlen(dest), "    mov rbx, 0                ; Load false value\n");
            sprintf(dest + strlen(dest), "    push rbx\n");
            return 1;
        }
        // It's a numeric literal (integer or float)
        else if (strchr(id, '.') != NULL)
        {
            // It's a float number
            double val = atof(id);
            long *bits = (long *)&val;
            sprintf(dest + strlen(dest), "    ; Load float literal: %s\n", id);
            sprintf(dest + strlen(dest), "    mov rbx, %ld                ; Load float bits\n", *bits);
        }
        else
        {
            // It's an integer number - load as integer
            int val = atoi(id);
            sprintf(dest + strlen(dest), "    ; Load integer literal: %s\n", id);
            sprintf(dest + strlen(dest), "    mov rbx, %d                ; Load integer value\n", val);
        }
        sprintf(dest + strlen(dest), "    push rbx\n");

        // Track literal operands for optimization
        if (strlen(last_left_operand) == 0)
        {
            strcpy(last_left_operand, id);
        }
        else
        {
            strcpy(last_right_operand, id);
            has_literal_operands = 1; // We have both operands as literals
        }

        return 1;
    }

    SymTableEntry *ret = findSymTable(&table, id);
    // Validation already done in the syntactic analyzer

    if (ret->type == CHAR || ret->type == BOOL)
    {
        sprintf(dest + strlen(dest), "    movzx rbx, byte [%s]\n", ret->identifier);
    }
    else
    {
        sprintf(dest + strlen(dest), "    mov rbx, [%s]\n", ret->identifier);
    }
    sprintf(dest + strlen(dest), "    push rbx\n");

    // Track variable operands (not literals)
    if (strlen(last_left_operand) == 0)
    {
        strcpy(last_left_operand, id);
    }
    else
    {
        strcpy(last_right_operand, id);
        has_literal_operands = 0; // At least one is not a literal
    }

    return 1;
}

void makeCodeAdd(char *dest, Type type)
{
    char temp[256];
    char optimized[512];

    // Try optimization if we have literal operands
    if (has_literal_operands && strlen(last_left_operand) > 0 && strlen(last_right_operand) > 0)
    {
        optimized[0] = '\0';
        optimizeConstantFolding(optimized, "+", last_left_operand, last_right_operand, type);
        if (strlen(optimized) > 0)
        {
            // Clear dest and use only optimized code (no loads needed)
            dest[0] = '\0';
            strcat(dest, optimized);
            // Reset tracking
            has_literal_operands = 0;
            last_left_operand[0] = '\0';
            last_right_operand[0] = '\0';
            return;
        }
    }

    // Check for strength reduction patterns
    if (strlen(last_right_operand) > 0)
    {
        optimized[0] = '\0';
        optimizeStrengthReduction(optimized, "+", last_left_operand, last_right_operand, type);
        if (strlen(optimized) > 0)
        {
            strcat(dest, optimized);
            // Reset tracking
            has_literal_operands = 0;
            last_left_operand[0] = '\0';
            last_right_operand[0] = '\0';
            return;
        }
    }

    // Standard addition code
    if (type == INTEGER)
    {
        sprintf(temp, "    ; Integer addition operation\n");
        strcat(dest, temp);
        strcat(dest, "    pop rcx                     ; Get second operand\n");
        strcat(dest, "    pop rbx                     ; Get first operand\n");
        strcat(dest, "    add rbx, rcx                ; Add: rbx = rbx + rcx\n");
        strcat(dest, "    push rbx                    ; Push result\n");
    }
    else if (type == FLOAT)
    {
        sprintf(temp, "    ; Float addition operation\n");
        strcat(dest, temp);
        strcat(dest, "    pop rcx                     ; Get second operand\n");
        strcat(dest, "    pop rbx                     ; Get first operand\n");
        strcat(dest, "    ; Convert to float for addition\n");
        strcat(dest, "    mov [temp_float], rbx       ; Store first operand\n");
        strcat(dest, "    movsd xmm0, [temp_float]    ; Load as double\n");
        strcat(dest, "    mov [temp_float], rcx       ; Store second operand\n");
        strcat(dest, "    movsd xmm1, [temp_float]    ; Load as double\n");
        strcat(dest, "    addsd xmm0, xmm1            ; Add: xmm0 = xmm0 + xmm1\n");
        strcat(dest, "    movsd [temp_float], xmm0    ; Store result\n");
        strcat(dest, "    mov rbx, [temp_float]       ; Load result back\n");
        strcat(dest, "    push rbx                    ; Push result\n");
    }

    // Reset tracking after operation
    has_literal_operands = 0;
    last_left_operand[0] = '\0';
    last_right_operand[0] = '\0';
}

void makeCodeSub(char *dest, Type type)
{
    char optimized[512];

    // Try optimization if we have literal operands
    if (has_literal_operands && strlen(last_left_operand) > 0 && strlen(last_right_operand) > 0)
    {
        optimized[0] = '\0';
        optimizeConstantFolding(optimized, "-", last_left_operand, last_right_operand, type);
        if (strlen(optimized) > 0)
        {
            strcat(dest, optimized);
            // Reset tracking
            has_literal_operands = 0;
            last_left_operand[0] = '\0';
            last_right_operand[0] = '\0';
            return;
        }
    }

    // Check for strength reduction patterns
    if (strlen(last_right_operand) > 0)
    {
        optimized[0] = '\0';
        optimizeStrengthReduction(optimized, "-", last_left_operand, last_right_operand, type);
        if (strlen(optimized) > 0)
        {
            strcat(dest, optimized);
            // Reset tracking
            has_literal_operands = 0;
            last_left_operand[0] = '\0';
            last_right_operand[0] = '\0';
            return;
        }
    }

    // Standard subtraction code
    if (type == INTEGER)
    {
        sprintf(dest + strlen(dest), "    ; Integer subtraction operation\n");
        sprintf(dest + strlen(dest), "    pop rcx                     ; Get second operand\n");
        sprintf(dest + strlen(dest), "    pop rbx                     ; Get first operand\n");
        sprintf(dest + strlen(dest), "    sub rbx, rcx                ; Subtract: rbx = rbx - rcx\n");
        sprintf(dest + strlen(dest), "    push rbx                    ; Push result\n");
    }
    else if (type == FLOAT)
    {
        sprintf(dest + strlen(dest), "    ; Float subtraction operation\n");
        sprintf(dest + strlen(dest), "    pop rcx                     ; Get second operand\n");
        sprintf(dest + strlen(dest), "    pop rbx                     ; Get first operand\n");
        sprintf(dest + strlen(dest), "    ; Convert to float for subtraction\n");
        sprintf(dest + strlen(dest), "    mov [temp_float], rbx       ; Store first operand\n");
        sprintf(dest + strlen(dest), "    movsd xmm0, [temp_float]    ; Load as double\n");
        sprintf(dest + strlen(dest), "    mov [temp_float], rcx       ; Store second operand\n");
        sprintf(dest + strlen(dest), "    movsd xmm1, [temp_float]    ; Load as double\n");
        sprintf(dest + strlen(dest), "    subsd xmm0, xmm1            ; Subtract: xmm0 = xmm0 - xmm1\n");
        sprintf(dest + strlen(dest), "    movsd [temp_float], xmm0    ; Store result\n");
        sprintf(dest + strlen(dest), "    mov rbx, [temp_float]       ; Load result back\n");
        sprintf(dest + strlen(dest), "    push rbx                    ; Push result\n");
    }

    // Reset tracking after operation
    has_literal_operands = 0;
    last_left_operand[0] = '\0';
    last_right_operand[0] = '\0';
}

void makeCodeMul(char *dest, Type type)
{
    char optimized[512];

    // Try optimization if we have literal operands
    if (has_literal_operands && strlen(last_left_operand) > 0 && strlen(last_right_operand) > 0)
    {
        optimized[0] = '\0';
        optimizeConstantFolding(optimized, "*", last_left_operand, last_right_operand, type);
        if (strlen(optimized) > 0)
        {
            // Clear dest and use only optimized code
            dest[0] = '\0';
            strcat(dest, optimized);
            // Reset tracking
            has_literal_operands = 0;
            last_left_operand[0] = '\0';
            last_right_operand[0] = '\0';
            return;
        }
    }

    // Check for strength reduction patterns (multiplication by powers of 2)
    if (strlen(last_right_operand) > 0)
    {
        optimized[0] = '\0';
        optimizeStrengthReduction(optimized, "*", last_left_operand, last_right_operand, type);
        if (strlen(optimized) > 0)
        {
            strcat(dest, optimized);
            // Reset tracking
            has_literal_operands = 0;
            last_left_operand[0] = '\0';
            last_right_operand[0] = '\0';
            return;
        }
    }

    // Standard multiplication code
    if (type == INTEGER)
    {
        sprintf(dest + strlen(dest), "    ; Integer multiplication operation\n");
        sprintf(dest + strlen(dest), "    pop rcx                     ; Get second operand\n");
        sprintf(dest + strlen(dest), "    pop rax                     ; Get first operand\n");
        sprintf(dest + strlen(dest), "    imul rax, rcx               ; Multiply: rax = rax * rcx\n");
        sprintf(dest + strlen(dest), "    mov rbx, rax                ; Move result to rbx\n");
        sprintf(dest + strlen(dest), "    push rbx                    ; Push result\n");
    }
    else if (type == FLOAT)
    {
        sprintf(dest + strlen(dest), "    ; Float multiplication operation\n");
        sprintf(dest + strlen(dest), "    pop rcx                     ; Get second operand\n");
        sprintf(dest + strlen(dest), "    pop rbx                     ; Get first operand\n");
        sprintf(dest + strlen(dest), "    ; Convert to float for multiplication\n");
        sprintf(dest + strlen(dest), "    mov [temp_float], rbx       ; Store first operand\n");
        sprintf(dest + strlen(dest), "    movsd xmm0, [temp_float]    ; Load as double\n");
        sprintf(dest + strlen(dest), "    mov [temp_float], rcx       ; Store second operand\n");
        sprintf(dest + strlen(dest), "    movsd xmm1, [temp_float]    ; Load as double\n");
        sprintf(dest + strlen(dest), "    mulsd xmm0, xmm1            ; Multiply: xmm0 = xmm0 * xmm1\n");
        sprintf(dest + strlen(dest), "    movsd [temp_float], xmm0    ; Store result\n");
        sprintf(dest + strlen(dest), "    mov rbx, [temp_float]       ; Load result back\n");
        sprintf(dest + strlen(dest), "    push rbx                    ; Push result\n");
    }

    // Reset tracking after operation
    has_literal_operands = 0;
    last_left_operand[0] = '\0';
    last_right_operand[0] = '\0';
}

void makeCodeDiv(char *dest, Type type)
{
    char optimized[512];

    // Try optimization if we have literal operands
    if (has_literal_operands && strlen(last_left_operand) > 0 && strlen(last_right_operand) > 0)
    {
        optimized[0] = '\0';
        optimizeConstantFolding(optimized, "/", last_left_operand, last_right_operand, type);
        if (strlen(optimized) > 0)
        {
            strcat(dest, optimized);
            // Reset tracking
            has_literal_operands = 0;
            last_left_operand[0] = '\0';
            last_right_operand[0] = '\0';
            return;
        }
    }

    // Check for strength reduction patterns (division by powers of 2)
    if (strlen(last_right_operand) > 0)
    {
        optimized[0] = '\0';
        optimizeStrengthReduction(optimized, "/", last_left_operand, last_right_operand, type);
        if (strlen(optimized) > 0)
        {
            strcat(dest, optimized);
            // Reset tracking
            has_literal_operands = 0;
            last_left_operand[0] = '\0';
            last_right_operand[0] = '\0';
            return;
        }
    }

    // Standard division code
    if (type == INTEGER)
    {
        sprintf(dest + strlen(dest), "    ; Integer division operation with zero check\n");
        sprintf(dest + strlen(dest), "    pop rcx                     ; Get second operand (divisor)\n");
        sprintf(dest + strlen(dest), "    pop rax                     ; Get first operand (dividend)\n");
        sprintf(dest + strlen(dest), "    ; Check for division by zero\n");
        sprintf(dest + strlen(dest), "    cmp rcx, 0                  ; Compare divisor with zero\n");
        sprintf(dest + strlen(dest), "    je division_by_zero         ; Jump if divisor is zero\n");
        sprintf(dest + strlen(dest), "    ; Perform integer division\n");
        sprintf(dest + strlen(dest), "    xor rdx, rdx                ; Clear remainder register\n");
        sprintf(dest + strlen(dest), "    idiv rcx                    ; Divide: rax = rax / rcx\n");
        sprintf(dest + strlen(dest), "    mov rbx, rax                ; Move quotient to rbx\n");
        sprintf(dest + strlen(dest), "    push rbx                    ; Push quotient\n");
        sprintf(dest + strlen(dest), "    jmp division_end            ; Skip error handling\n");
        sprintf(dest + strlen(dest), "\ndivision_by_zero:\n");
        sprintf(dest + strlen(dest), "    mov rdi, 1                  ; Exit code 1\n");
        sprintf(dest + strlen(dest), "    call exit                   ; Exit with error\n");
        sprintf(dest + strlen(dest), "\ndivision_end:\n");
    }
    else if (type == FLOAT)
    {
        sprintf(dest + strlen(dest), "    ; Float division operation with zero check\n");
        sprintf(dest + strlen(dest), "    pop rcx                     ; Get second operand (divisor)\n");
        sprintf(dest + strlen(dest), "    pop rbx                     ; Get first operand (dividend)\n");
        sprintf(dest + strlen(dest), "    ; Check for division by zero\n");
        sprintf(dest + strlen(dest), "    mov [temp_float], rcx       ; Store divisor\n");
        sprintf(dest + strlen(dest), "    movsd xmm1, [temp_float]    ; Load divisor as double\n");
        sprintf(dest + strlen(dest), "    xorpd xmm2, xmm2            ; Clear xmm2 (zero)\n");
        sprintf(dest + strlen(dest), "    comisd xmm1, xmm2           ; Compare with zero\n");
        sprintf(dest + strlen(dest), "    je division_by_zero         ; Jump if divisor is zero\n");
        sprintf(dest + strlen(dest), "    ; Convert to float for division\n");
        sprintf(dest + strlen(dest), "    mov [temp_float], rbx       ; Store dividend\n");
        sprintf(dest + strlen(dest), "    movsd xmm0, [temp_float]    ; Load as double\n");
        sprintf(dest + strlen(dest), "    divsd xmm0, xmm1            ; Divide: xmm0 = xmm0 / xmm1\n");
        sprintf(dest + strlen(dest), "    movsd [temp_float], xmm0    ; Store result\n");
        sprintf(dest + strlen(dest), "    mov rbx, [temp_float]       ; Load result back\n");
        sprintf(dest + strlen(dest), "    push rbx                    ; Push quotient\n");
        sprintf(dest + strlen(dest), "    jmp division_end            ; Skip error handling\n");
        sprintf(dest + strlen(dest), "\ndivision_by_zero:\n");
        sprintf(dest + strlen(dest), "    mov rdi, 1                  ; Exit code 1\n");
        sprintf(dest + strlen(dest), "    call exit                   ; Exit with error\n");
        sprintf(dest + strlen(dest), "\ndivision_end:\n");
    }

    // Reset tracking after operation
    has_literal_operands = 0;
    last_left_operand[0] = '\0';
    last_right_operand[0] = '\0';
}

void makeCodeMod(char *dest)
{
    sprintf(dest + strlen(dest), "    pop r8                      ; Get divisor\n");
    sprintf(dest + strlen(dest), "    pop rax                     ; Get dividend\n");
    sprintf(dest + strlen(dest), "    xor rdx, rdx                ; Clear remainder\n");
    sprintf(dest + strlen(dest), "    idiv r8                     ; rax = rax / r8\n");
    sprintf(dest + strlen(dest), "    push rdx                    ; Push remainder\n");
}

void makeCodeNeg(char *dest, Type type)
{
    if (type == INTEGER)
    {
        sprintf(dest + strlen(dest), "    ; Integer negation\n");
        sprintf(dest + strlen(dest), "    pop rbx\n");
        sprintf(dest + strlen(dest), "    neg rbx\n");
        sprintf(dest + strlen(dest), "    push rbx\n");
    }
    else if (type == FLOAT)
    {
        sprintf(dest + strlen(dest), "    ; Float negation\n");
        sprintf(dest + strlen(dest), "    pop rbx\n");
        sprintf(dest + strlen(dest), "    mov [temp_float], rbx       ; Store float bits\n");
        sprintf(dest + strlen(dest), "    movsd xmm0, [temp_float]    ; Load as double\n");
        sprintf(dest + strlen(dest), "    xorpd xmm1, xmm1            ; Clear xmm1\n");
        sprintf(dest + strlen(dest), "    subsd xmm1, xmm0            ; Negate: xmm1 = 0 - xmm0\n");
        sprintf(dest + strlen(dest), "    movsd [temp_float], xmm1    ; Store result\n");
        sprintf(dest + strlen(dest), "    mov rbx, [temp_float]       ; Load result back\n");
        sprintf(dest + strlen(dest), "    push rbx\n");
    }
}

// Implementation of new functions for I/O
void makeCodeRead(char *dest, char *varname, Type type)
{
    // Initialize dest string
    dest[0] = '\0';

    if (type == INTEGER)
    {
        strcat(dest, "    lea rdi, [fmt_d]            ; Integer format\n");
        sprintf(dest + strlen(dest), "    lea rsi, [%s]               ; Variable address\n", varname);
        strcat(dest, "    mov rax, 0                  ; Clear rax for scanf\n");
        strcat(dest, "    call scanf                  ; Call scanf\n");
    }
    else if (type == FLOAT)
    {
        strcat(dest, "    lea rdi, [fmt_f]            ; Float format\n");
        sprintf(dest + strlen(dest), "    lea rsi, [%s]               ; Variable address\n", varname);
        strcat(dest, "    mov rax, 0                  ; Clear rax for scanf\n");
        strcat(dest, "    call scanf                  ; Call scanf\n");
    }
    else if (type == CHAR)
    {
        strcat(dest, "    lea rdi, [fmt_c]            ; Char format\n");
        sprintf(dest + strlen(dest), "    lea rsi, [%s]               ; Variable address\n", varname);
        strcat(dest, "    mov rax, 0                  ; Clear rax for scanf\n");
        strcat(dest, "    call scanf                  ; Call scanf\n");
    }
    else if (type == STRING)
    {
        strcat(dest, "    lea rdi, [fmt_s]            ; String format\n");
        sprintf(dest + strlen(dest), "    lea rsi, [%s]               ; Variable address\n", varname);
        strcat(dest, "    mov rax, 0                  ; Clear rax for scanf\n");
        strcat(dest, "    call scanf                  ; Call scanf\n");
    }
}

void makeCodeWrite(char *dest, Type type)
{
    if (type == INTEGER)
    {
        // Write operation for integer
        strcat(dest, "    ; Write operation for integer\n");
        strcat(dest, "    pop rbx                     ; Get value to write\n");
        strcat(dest, "    mov rsi, rbx                ; Move to printf argument\n");
        strcat(dest, "    lea rdi, [fmt_dln]          ; Load format string\n");
        strcat(dest, "    mov rax, 0                  ; Clear rax for printf\n");
        strcat(dest, "    call printf                 ; Call printf\n");
    }
    else if (type == FLOAT)
    {
        // Write operation for float
        strcat(dest, "    ; Write operation for float\n");
        strcat(dest, "    pop rbx                     ; Get value to write\n");
        strcat(dest, "    mov [temp_float], rbx       ; Store float bits\n");
        strcat(dest, "    movsd xmm0, [temp_float]    ; Load as double\n");
        strcat(dest, "    lea rdi, [fmt_fln]          ; Load float format string\n");
        strcat(dest, "    mov rax, 1                  ; One XMM register used\n");
        strcat(dest, "    call printf                 ; Call printf\n");
    }
    else if (type == CHAR)
    {
        // Write operation for char
        strcat(dest, "    ; Write operation for char\n");
        strcat(dest, "    pop rbx                     ; Get value to write\n");
        strcat(dest, "    mov rsi, rbx                ; Move to printf argument\n");
        strcat(dest, "    lea rdi, [fmt_cln]          ; Load char format string\n");
        strcat(dest, "    mov rax, 0                  ; Clear rax for printf\n");
        strcat(dest, "    call printf                 ; Call printf\n");
    }
    else if (type == BOOL)
    {
        // Write operation for bool (true/false)
        int label = label_counter++;
        strcat(dest, "    ; Write operation for bool\n");
        strcat(dest, "    pop rbx                     ; Get value to write\n");
        strcat(dest, "    cmp rbx, 0                  ; Compare with 0\n");
        sprintf(dest + strlen(dest), "    je .print_false_%d\n", label);
        strcat(dest, "    lea rdi, [str_true]         ; Load 'true' string\n");
        sprintf(dest + strlen(dest), "    jmp .print_bool_%d\n", label);
        sprintf(dest + strlen(dest), ".print_false_%d:\n", label);
        strcat(dest, "    lea rdi, [str_false]        ; Load 'false' string\n");
        sprintf(dest + strlen(dest), ".print_bool_%d:\n", label);
        strcat(dest, "    mov rax, 0                  ; Clear rax for printf\n");
        strcat(dest, "    call printf                 ; Call printf\n");
        strcat(dest, "    lea rdi, [newline]          ; Print newline\n");
        strcat(dest, "    call printf\n");
    }
    else if (type == STRING)
    {
        // Write operation for string
        strcat(dest, "    ; Write operation for string\n");
        strcat(dest, "    pop rbx                     ; Get string address\n");
        strcat(dest, "    mov rsi, rbx                ; Move to printf argument\n");
        strcat(dest, "    lea rdi, [fmt_sln]          ; Load string format\n");
        strcat(dest, "    mov rax, 0                  ; Clear rax for printf\n");
        strcat(dest, "    call printf                 ; Call printf\n");
    }
}
void makeCodeWriteString(char *dest, char *str)
{
    dest[0] = '\0';

    // Add string to data section and get its label
    char *label = addStringLiteral(str);
    if (label == NULL)
    {
        return; // Error handled in addStringLiteral
    }

    // Generate assembly code to print the string
    sprintf(dest + strlen(dest), "    lea rdi, [fmt_sln]          ; Load string format\n");
    sprintf(dest + strlen(dest), "    lea rsi, [%s]               ; Load string address\n", label);
    sprintf(dest + strlen(dest), "    mov rax, 0                  ; Clear rax for printf\n");
    sprintf(dest + strlen(dest), "    call printf                 ; Call printf\n");
}

// Implementation of functions for control structures
void makeCodeIf(char *dest, char *condition, char *body)
{
    int label = label_counter++;
    dest[0] = '\0';

    sprintf(dest + strlen(dest), "%s", condition);
    sprintf(dest + strlen(dest), "    pop rbx\n");
    sprintf(dest + strlen(dest), "    cmp rbx, 0\n");
    sprintf(dest + strlen(dest), "    je .L%d\n", label);
    sprintf(dest + strlen(dest), "%s", body);
    sprintf(dest + strlen(dest), "\n.L%d:\n", label);
}

void makeCodeIfElse(char *dest, char *condition, char *ifBody, char *elseBody)
{
    int label1 = label_counter++;
    int label2 = label_counter++;
    dest[0] = '\0';

    sprintf(dest + strlen(dest), "%s", condition);
    sprintf(dest + strlen(dest), "    pop rbx\n");
    sprintf(dest + strlen(dest), "    cmp rbx, 0\n");
    sprintf(dest + strlen(dest), "    je .L%d\n", label1);
    sprintf(dest + strlen(dest), "%s", ifBody);
    sprintf(dest + strlen(dest), "    jmp .L%d\n", label2);
    sprintf(dest + strlen(dest), "\n.L%d:\n", label1);
    sprintf(dest + strlen(dest), "%s", elseBody);
    sprintf(dest + strlen(dest), "\n.L%d:\n", label2);
}

void makeCodeWhile(char *dest, char *condition, char *body)
{
    int label1 = label_counter++;
    int label2 = label_counter++;
    dest[0] = '\0';

    sprintf(dest + strlen(dest), "\n.L%d:\n", label1);
    sprintf(dest + strlen(dest), "%s", condition);
    sprintf(dest + strlen(dest), "    pop rbx\n");
    sprintf(dest + strlen(dest), "    cmp rbx, 0\n");
    sprintf(dest + strlen(dest), "    je .L%d\n", label2);
    sprintf(dest + strlen(dest), "%s", body);
    sprintf(dest + strlen(dest), "    jmp .L%d\n", label1);
    sprintf(dest + strlen(dest), "\n.L%d:\n", label2);
}

// Implementation of functions for comparisons
void makeCodeComparison(char *dest, char *op, Type type)
{
    if (type == INTEGER)
    {
        sprintf(dest + strlen(dest), "    ; Integer comparison operation: %s\n", op);
        sprintf(dest + strlen(dest), "    pop rcx                     ; Get second operand\n");
        sprintf(dest + strlen(dest), "    pop rbx                     ; Get first operand\n");
        sprintf(dest + strlen(dest), "    cmp rbx, rcx                ; Compare integers\n");

        if (strcmp(op, "<") == 0)
        {
            sprintf(dest + strlen(dest), "    setl al                     ; Set if less than\n");
        }
        else if (strcmp(op, ">") == 0)
        {
            sprintf(dest + strlen(dest), "    setg al                     ; Set if greater than\n");
        }
        else if (strcmp(op, "<=") == 0)
        {
            sprintf(dest + strlen(dest), "    setle al                    ; Set if less or equal\n");
        }
        else if (strcmp(op, ">=") == 0)
        {
            sprintf(dest + strlen(dest), "    setge al                    ; Set if greater or equal\n");
        }
        else if (strcmp(op, "==") == 0)
        {
            sprintf(dest + strlen(dest), "    sete al                     ; Set if equal\n");
        }
        else if (strcmp(op, "!=") == 0)
        {
            sprintf(dest + strlen(dest), "    setne al                    ; Set if not equal\n");
        }
    }
    else if (type == FLOAT)
    {
        sprintf(dest + strlen(dest), "    ; Float comparison operation: %s\n", op);
        sprintf(dest + strlen(dest), "    pop rcx                     ; Get second operand\n");
        sprintf(dest + strlen(dest), "    pop rbx                     ; Get first operand\n");
        sprintf(dest + strlen(dest), "    ; Convert to float for comparison\n");
        sprintf(dest + strlen(dest), "    mov [temp_float], rbx       ; Store first operand\n");
        sprintf(dest + strlen(dest), "    movsd xmm0, [temp_float]    ; Load as double\n");
        sprintf(dest + strlen(dest), "    mov [temp_float], rcx       ; Store second operand\n");
        sprintf(dest + strlen(dest), "    movsd xmm1, [temp_float]    ; Load as double\n");
        sprintf(dest + strlen(dest), "    comisd xmm0, xmm1           ; Compare floats\n");

        if (strcmp(op, "<") == 0)
        {
            sprintf(dest + strlen(dest), "    setb al                     ; Set if less than\n");
        }
        else if (strcmp(op, ">") == 0)
        {
            sprintf(dest + strlen(dest), "    seta al                     ; Set if greater than\n");
        }
        else if (strcmp(op, "<=") == 0)
        {
            sprintf(dest + strlen(dest), "    setbe al                    ; Set if less or equal\n");
        }
        else if (strcmp(op, ">=") == 0)
        {
            sprintf(dest + strlen(dest), "    setae al                    ; Set if greater or equal\n");
        }
        else if (strcmp(op, "==") == 0)
        {
            sprintf(dest + strlen(dest), "    sete al                     ; Set if equal\n");
        }
        else if (strcmp(op, "!=") == 0)
        {
            sprintf(dest + strlen(dest), "    setne al                    ; Set if not equal\n");
        }
    }

    sprintf(dest + strlen(dest), "    movzx rbx, al               ; Zero-extend result\n");
    sprintf(dest + strlen(dest), "    push rbx                    ; Push result\n");
}

void makeCodeNot(char *dest)
{
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "cmp rbx, 0\n");
    sprintf(dest + strlen(dest), "sete al\n");
    sprintf(dest + strlen(dest), "movzx rbx, al\n");
    sprintf(dest + strlen(dest), "push rbx\n");
}

// ===============================================
// FUNCTION CODE GENERATION
// ===============================================

void makeCodeFunction(char *dest, char *funcName, Type returnType, char *body)
{
    sprintf(dest, "; ===============================================\n");
    sprintf(dest + strlen(dest), "; Function: %s\n", funcName);
    sprintf(dest + strlen(dest), "; ===============================================\n");
    sprintf(dest + strlen(dest), "%s:\n", funcName);
    sprintf(dest + strlen(dest), "    ; Function prologue\n");
    sprintf(dest + strlen(dest), "    push rbp                    ; Save old base pointer\n");
    sprintf(dest + strlen(dest), "    mov rbp, rsp                ; Set new base pointer\n");
    sprintf(dest + strlen(dest), "\n");
    sprintf(dest + strlen(dest), "    ; Function body\n");
    sprintf(dest + strlen(dest), "%s", body);
    sprintf(dest + strlen(dest), "\n");
    sprintf(dest + strlen(dest), "    ; Function epilogue (if no explicit return)\n");
    sprintf(dest + strlen(dest), "    mov eax, 0                  ; Default return value\n");
    sprintf(dest + strlen(dest), "    mov rsp, rbp                ; Restore stack pointer\n");
    sprintf(dest + strlen(dest), "    pop rbp                     ; Restore base pointer\n");
    sprintf(dest + strlen(dest), "    ret                         ; Return to caller\n\n");
}

void makeCodeMain(char *dest, char *body)
{
    sprintf(dest, "; ===============================================\n");
    sprintf(dest + strlen(dest), "; Main program entry point\n");
    sprintf(dest + strlen(dest), "; ===============================================\n");
    sprintf(dest + strlen(dest), "main:\n");
    sprintf(dest + strlen(dest), "    ; Initialize stack frame\n");
    sprintf(dest + strlen(dest), "    push rbp                    ; Save base pointer\n");
    sprintf(dest + strlen(dest), "    mov rbp, rsp                ; Set new base pointer\n");
    sprintf(dest + strlen(dest), "\n");
    sprintf(dest + strlen(dest), "    ; Program execution starts here\n");
    sprintf(dest + strlen(dest), "%s", body);
    sprintf(dest + strlen(dest), "\n");
    sprintf(dest + strlen(dest), "    ; Program cleanup and exit\n");
    sprintf(dest + strlen(dest), "    mov rsp, rbp                ; Restore stack pointer\n");
    sprintf(dest + strlen(dest), "    pop rbp                     ; Restore base pointer\n");
    sprintf(dest + strlen(dest), "    mov rdi, 0                  ; Exit status\n");
    sprintf(dest + strlen(dest), "    call exit                   ; Exit program\n\n");
}

void makeCodeReturn(char *dest, char *expr, Type type)
{
    sprintf(dest, "    ; Return statement\n");
    sprintf(dest + strlen(dest), "%s", expr);
    sprintf(dest + strlen(dest), "    pop rax                     ; Get return value\n");
    sprintf(dest + strlen(dest), "    mov rsp, rbp                ; Restore stack pointer\n");
    sprintf(dest + strlen(dest), "    pop rbp                     ; Restore base pointer\n");
    sprintf(dest + strlen(dest), "    ret                         ; Return to caller\n");
}

void makeCodeFunctionCall(char *dest, char *funcName, char *args, Type returnType)
{
    sprintf(dest, "    ; Function call: %s\n", funcName);
    sprintf(dest + strlen(dest), "%s", args); // Push arguments (in reverse order)
    sprintf(dest + strlen(dest), "    call %s                     ; Call function\n", funcName);
    sprintf(dest + strlen(dest), "    ; Clean up stack (simplified - should calculate actual size)\n");
    sprintf(dest + strlen(dest), "    ; Return value is in eax\n");
}

void makeCodeFunctionCallExpression(char *dest, char *funcName, char *args, Type returnType)
{
    sprintf(dest, "    ; Function call in expression: %s\n", funcName);
    sprintf(dest + strlen(dest), "%s", args); // Push arguments (in reverse order)
    sprintf(dest + strlen(dest), "    call %s                     ; Call function\n", funcName);
    sprintf(dest + strlen(dest), "    ; Clean up stack (simplified - should calculate actual size)\n");
    sprintf(dest + strlen(dest), "    push rax                    ; Push return value on stack\n");
}