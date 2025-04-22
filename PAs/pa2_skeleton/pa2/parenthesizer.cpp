#ifndef PARENTHESIZER_CPP
#define PARENTHESIZER_CPP

#include <cstring>

#include "string_utils.cpp"

/*
You can use for or while loop to complete TASK 4, but it is highly recommended to use recursion.
*/

void parenthesize(const char raw_expression[], char destination[])
{
  char expression[MAX_LEN];
  trim(raw_expression, expression);

  // TODO Task 4 BEGIN

char lhs[MAX_LEN], rhs[MAX_LEN];
int index = -1;

// case of addition and subtraction operators: Use last_index_of to find the last " + " or " - " (excluding unary minus),
// then, try top use recursively call parenthesize separatlly on the left and right  two subexpressions.
int plus_index  = last_index_of(expression, " + ");
int minus_index = last_index_of(expression, " - ");
index = max(plus_index, minus_index);
if (index > 0)
{
  if (plus_index == index)
  {
    substring(expression, 0, index, lhs);
    substring(expression, index + 3, strlen(expression), rhs);
    
    char paren_lhs[MAX_LEN], paren_rhs[MAX_LEN];
    parenthesize(lhs, paren_lhs);
    parenthesize(rhs, paren_rhs);
    
    strcpy(destination, "(");
    strcat(destination, paren_lhs);
    strcat(destination, " + ");
    strcat(destination, paren_rhs);
    strcat(destination, ")");
    return;
  }
  else
  {
    substring(expression, 0, index, lhs);
    substring(expression, index + 3, strlen(expression), rhs);
    
    char paren_lhs[MAX_LEN], paren_rhs[MAX_LEN];
    parenthesize(lhs, paren_lhs);
    parenthesize(rhs, paren_rhs);
    
    strcpy(destination, "(");
    strcat(destination, paren_lhs);
    strcat(destination, " - ");
    strcat(destination, paren_rhs);
    strcat(destination, ")");
    return;
  }
}

//case of multiplication and division operators
int mult_index = last_index_of(expression, " * ");
if (mult_index == -1)
  mult_index = last_index_of(expression, "*");
int div_index = last_index_of(expression, " / ");
if (div_index == -1)
  div_index = last_index_of(expression, "/");
index = max(mult_index, div_index);
if (index > 0)
{
  int op_length = 0;
  char op_symbol[4];
  if (mult_index == index)
  {
    op_length = (last_index_of(expression, " * ") == index) ? 3 : 1;
    strcpy(op_symbol, " * ");
  }
  else
  {
    op_length = (last_index_of(expression, " / ") == index) ? 3 : 1;
    strcpy(op_symbol, " / ");
  }
  substring(expression, 0, index, lhs);
  substring(expression, index + op_length, strlen(expression), rhs);
  
  char paren_lhs[MAX_LEN], paren_rhs[MAX_LEN];
  parenthesize(lhs, paren_lhs);
  parenthesize(rhs, paren_rhs);
  
  strcpy(destination, "(");
  strcat(destination, paren_lhs);
  strcat(destination, op_symbol);
  strcat(destination, paren_rhs);
  strcat(destination, ")");
  return;
}

// case of power, try to use index_of to find the first occurrence of '^'.
int exp_index = index_of(expression, "^");
if (exp_index > 0)
{
  substring(expression, 0, exp_index, lhs);
  substring(expression, exp_index + 1, strlen(expression), rhs);
  
  char paren_lhs[MAX_LEN], paren_rhs[MAX_LEN];
  parenthesize(lhs, paren_lhs);
  parenthesize(rhs, paren_rhs);
  
  strcpy(destination, "(");
  strcat(destination, paren_lhs);
  strcat(destination, " ^ ");
  strcat(destination, paren_rhs);
  strcat(destination, ")");
  return;
}

// case of negation: When the expression starts with '-' and the next character is not a space,
if (expression[0] == '-' && expression[1] != ' ')
{
  substring(expression, 1, strlen(expression), rhs);
  
  char paren_rhs[MAX_LEN];
  parenthesize(rhs, paren_rhs);
  
  strcpy(destination, "(-");
  strcat(destination, paren_rhs);
  strcat(destination, ")");
  return;
}

{
  // check if expression starts with "sqrt" using substring and are_equal
  char prefix[5]; // to store the first 4 characters plus the null terminator
  substring(expression, 0, 4, prefix);
  if (are_equal(prefix, "sqrt"))
  {
    char remainder[MAX_LEN];
    substring(expression, 4, strlen(expression), remainder);
    char trimmedRemainder[MAX_LEN];
    trim(remainder, trimmedRemainder);
    
    char paren_rhs[MAX_LEN];
    parenthesize(trimmedRemainder, paren_rhs);
    
    strcpy(destination, "(sqrt ");
    strcat(destination, paren_rhs);
    strcat(destination, ")");
    return;
  }
}

{
  // check if expression starts with "abs" using substring and are_equal
  char prefix[4]; // to store the first 3 characters plus the null terminator
  substring(expression, 0, 3, prefix);
  if (are_equal(prefix, "abs"))
  {
    char remainder[MAX_LEN];
    substring(expression, 3, strlen(expression), remainder);
    char trimmedRemainder[MAX_LEN];
    trim(remainder, trimmedRemainder);
    
    char paren_rhs[MAX_LEN];
    parenthesize(trimmedRemainder, paren_rhs);
    
    strcpy(destination, "(abs ");
    strcat(destination, paren_rhs);
    strcat(destination, ")");
    return;
  }
}

// final factorial operator: Detect the '!' suffix and process the left-hand side recursively.
int fact_index = index_of(expression, "!");
if (fact_index > 0)
{
  substring(expression, 0, fact_index, lhs);
  
  char paren_lhs[MAX_LEN];
  parenthesize(lhs, paren_lhs);
  
  strcpy(destination, "(");
  strcat(destination, paren_lhs);
  strcat(destination, "!)");
  return;
}

// Default case: Treat the expression as an atomic expression (number or variable or constantI) and return it directly.
strcpy(destination, expression);
  // TODO Task 4 END

  // Only invalid expressions should reach this point
  // because your code should have parenthesized and returned all valid expression forms.
  // If this point is reached, it means the expression
  // is invalid OR there is a bug in your code.
  // This is only for debugging purposes, and we won't test the behavior
  // of your code for invalid expressions.
  std::cerr << "Invalid expression: '" << expression << "'" << std::endl;
}

#endif // PARENTHESIZER_CPP
