#ifndef EVALUATOR_CPP
#define EVALUATOR_CPP

#include <cstring>
#include <iostream>

#include "string_utils.cpp"

/*
You can use for or while loop to complete TASK 3, but it is highly recommended to use recursion.
*/

double evaluate(const char raw_expression[])
{  
  char expression[MAX_LEN];
  trim(raw_expression, expression);

  // Print debug information.
  // Note that this only prints the information in the interactive mode.
  if (DEBUG)
  {
    std::cerr << "DEBUG: evaluating: " << expression << std::endl;
  }

  // Evaluate numbers.
  if (is_number(expression))
    return parse_number(expression);

  //a converter that converts a specific string("E", "e", "PI", "pi") to a set value
  if (are_equal(expression, "E") || are_equal(expression, "e"))
  return E;
  if (are_equal(expression, "PI") || are_equal(expression, "pi"))
  return PI;

  char lhs[MAX_LEN];
  char rhs[MAX_LEN];
  int index;

  // Evaluate Binary Operators
  // +, -, * /, power
  if ((index = max(last_index_of(expression, " + "),
                   last_index_of(expression, " - "))) > 0)
  {
    // Addition and subtraction are provided as examples.
    if (index == last_index_of(expression, " + "))
    {
      substring(expression, 0, index, lhs);
      substring(expression, index + 3, strlen(expression), rhs);
      return evaluate(lhs) + evaluate(rhs);
    }

    if (index == last_index_of(expression, " - "))
    {
      substring(expression, 0, index, lhs);
      substring(expression, index + 3, strlen(expression), rhs);
      return evaluate(lhs) - evaluate(rhs);
    }
  }
  // TODO Task 3 BEGIN
  //  multiplication (*) and division (/), 5th precedence
  if ((index = max(last_index_of(expression, "*"), last_index_of(expression, "/"))) > 0)
  {
    if (index == last_index_of(expression, "*"))
    {
      // split into lhs and rhs
      substring(expression, 0, index, lhs);
      substring(expression, index + 1, strlen(expression), rhs);
      return evaluate(lhs) * evaluate(rhs);
    }
    else // division
    {
      substring(expression, 0, index, lhs);
      substring(expression, index + 1, strlen(expression), rhs);
      return evaluate(lhs) / evaluate(rhs);
    }
  }

  //  power operator (^), 4th precedence
  if ((index = index_of(expression, "^")) > 0)
  {
      // split into base and exponent
      substring(expression, 0, index, lhs);
      substring(expression, index + 1, strlen(expression), rhs);
      double base = evaluate(lhs);
      double exponent = evaluate(rhs);
      return power(base, (int)exponent);
  }


  // square root (sqrt) and absolute value (abs), 3rd precedence
 // handle sqrt and abs functions (third precedence)
 int sqrt_index = index_of(expression, "sqrt");
 int abs_index  = index_of(expression, "abs");
 if (sqrt_index >= 0 || abs_index >= 0)// any of one exists
 {
     if (abs_index >= 0 && (abs_index < sqrt_index || sqrt_index < 0))//If `abs` exists and is before `sqrt`, or if `sqrt` does not exist, `abs` takes precedence.
     {
         substring(expression, abs_index + 3, strlen(expression), rhs);
         return absolute(evaluate(rhs));
     }
     if (sqrt_index >= 0)// only sqrt, or sqrt before abs
     {
         substring(expression, sqrt_index + 4, strlen(expression), rhs);
         return square_root(evaluate(rhs));
     }
 }


   // negation (-), 2nd precedence
   if (expression[0] == '-' && expression[1] != ' ')// diff from the MINUS case
   {
       substring(expression, 1, strlen(expression), rhs);//extract the pure digital part only
       return -evaluate(rhs);
   }


  //  factorial (!), highest precedence
  if ((index = index_of(expression, "!")) > 0)
  {
      // extract the number before the factorial operator
      substring(expression, 0, index, lhs);
      return factorial((int)evaluate(lhs));
  }

  // Only invalid expressions should reach this point
  // because your code should have evaluated all valid expression forms.
  // If this point is reached, it means the expression
  // is invalid OR there is a bug in your code.
  // This is only for debugging purposes, and we won't test the behavior
  // of your code for invalid expressions.
  std::cerr << "Invalid expression: '" << expression << "'" << std::endl;
  return 0.0 / 0.0; // NaN
}

#endif // EVALUATOR_CPP
