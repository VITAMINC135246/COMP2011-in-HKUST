#ifndef STRING_UTILS_CPP
#define STRING_UTILS_CPP

#include <cstring>

#include "definitions.cpp"
#include "math_utils.cpp"

/*
You MUST use recursion to complete TASK 2. You are NOT allowed to use any for or while loop.
*/

/**
 * Indicates whether the string 'a' represents the same string value as 'b'.
 * @return true if the values are the same; false otherwise.
 */
bool are_equal(const char a[], const char b[])
{
  // TODO Task 2.1 BEGIN
  // Base case writing
  if (a[0] == '\0' && b[0] == '\0')
  {
    return true;
  }

  // once the chars are diff, then false
  if (a[0] != b[0])
  {
    return false;
  }

  // point to the next element that take a place in the memory
  return are_equal(a + 1, b + 1);
  // TODO Task 2.1 END
}

/**
 * Returns the index of the *first* character of the *first* pattern occurrence in the string.
 *
 * E.g. str = "This is the pattern 1 and pattern 2", pattern = "pattern"
 * index_of should return 12 (... pattern 1 and pattern 2)
 *                                ^
 */

// Assistant function, writing for helping check the resting part of pattern is matched or not
bool matching_checker(const char str[], const char pattern[])
{

  // base case writing
  if (pattern[0] == '\0')
  {
    return true;
  } // finish matching

  if (str[0] == '\0')
  {
    return false;
  } // string ends earlier than pattern

  if (str[0] != pattern[0])
  {
    return false;
  } // not matched

  // recursive case. check the next element
  return matching_checker(str + 1, pattern + 1);
}

int index_of(const char str[], const char pattern[])
{
  // TODO Task 2.2 BEGIN
  // base case writing
  if (str[0] == '\0' || strlen(str) < strlen(pattern))
  {
    return -1;
  } // if string starts from \0 or remaining string is shorter than pattern, return -1.
  if (pattern[0] == '\0')
  {
    return 0;
  } // if the target pattern is starting form \0, it means that needed nothing to be found.

  // main logic
  if (str[0] == pattern[0])
  {
    if (matching_checker(str, pattern))
    {
      return 0;
    }
  }
  // recursive case
  int next_result = index_of(str + 1, pattern); // current index not good, so continue to next
  return (next_result == -1) ? -1 : next_result + 1;
  // TODO Task 2.2 END
}

/**
 * Returns the index of the *first* character of the *last* pattern occurrence in the string.
 *
 * E.g. str = "This is the pattern 1 and pattern 2", pattern = "pattern"
 * index_of should return 26 (... pattern 1 and pattern 2)   ==> different from index_of
 *                                              ^
 */
int last_index_of(const char str[], const char pattern[])
{
  // TODO Task 2.3 BEGIN
  // base case writing
  if (str[0] == '\0')
  {
    return -1;
  } // if string starts from \0, it countains nothing; or researches till the end, still not found, return -1.
  if (pattern[0] == '\0')
  {
    return 0; // if the target pattern is starting form \0, it means that needed nothing to be found.
  }

  int next_result = last_index_of(str + 1, pattern);

  if (str[0] == pattern[0])
  { // potential start
    if (matching_checker(str, pattern))
    {
      if (next_result == -1)
      { // no more matcher
        return 0;
      }

      return (0 > next_result + 1) ? 0 : next_result + 1;
    }
  }

  if (next_result == -1)
  {
    return -1; // before fingding the last match, always return -1
  }
  return next_result + 1;

  // TODO Task 2.3 END
}

/**
 * Indicates if the character 'c' is a digit.
 *
 * If 'c' is one of the characters '0', '1', ..., '9', then it is a digit; and
 * this function returns true; otherwise, it returns false.
 */
bool is_digit(const char c) { return c >= '0' && c <= '9'; }

/**
 * Returns the integer value of the digit character 'c'.
 *
 * If 'c' is one of the characters '0', '1', ..., '9', then it returns the
 * corresponding integer value of the digit, i.e., 0, 1, ..., 9.
 */
int parse_digit(const char c) { return c - '0'; }

/**
 * Indicates if the string 'str' represents a number.
 */
bool is_number(const char str[])
{
  // TODO Task 2.4 BEGIN
  static int index = 0;
  static bool has_decimal = false;
  bool result = false;

  // first place check
  if (index == 0)
  {
    if (str[0] == '\0' || str[0] == '.')
    {
      return false; // empty string or starting with '.' is unvalid
    }
    if (str[0] == '0' && str[1] != '\0' && str[1] != '.')
    {
      return false; // leading zero followed by non-decimal char nonono
    }
  }

  // Base case writing
  if (str[index] == '\0')
  {
    // last character cannot be '.'
    result = (index > 0 && str[index - 1] != '.');
    index = 0; // reset static
    has_decimal = false;
    return result;
  }

  if (str[index] == '.')
  {
    if (has_decimal) // double '.'
    {
      index = 0;
      has_decimal = false;
      return false;
    }
    has_decimal = true;
  }
  else if (!is_digit(str[index])) // unvalid input
  {
    index = 0;
    has_decimal = false;
    return false; //
  }

  index++;
  result = is_number(str); // Recursive call
  return result;
  // TODO Task 2.4 END
}

/**
 * Returns the value of the number represented by the string 'str'.
 */
double parse_number(const char str[])
{
  // TODO Task 2.5 BEGIN
  static int index_in_parse_number = 0;
  static bool passed_decimal_in_parse_number = false;
  static double int_part = 0;
  static double frac_part = 0;
  static double divider = 1;

  if (index_in_parse_number == 0) // reinitialize the value
  {
    passed_decimal_in_parse_number = false;
    int_part = 0;
    frac_part = 0;
    divider = 1;
  }

  char current = str[index_in_parse_number];

  if (current == '\0') // end case
  {
    index_in_parse_number = 0;   // reinitialize the value
    return int_part + frac_part; // add up together
  }

  if (current == '.')
  {
    passed_decimal_in_parse_number = true;
  }

  else if (is_digit(current))
  {
    int digit = parse_digit(current);
    if (!passed_decimal_in_parse_number)
    {
      int_part = int_part * 10 + digit; // add up the int part before the decimal sign'.' is working
    }
    else
    {
      divider *= 10;
      frac_part += digit / divider;
    }
  }

  index_in_parse_number++;
  return parse_number(str);
  // TODO Task 2.5 END
}

/**
 * Remove all leading and trailing whitespaces from the string 'str', and store
 * the result in 'destination'.
 */
void trim(const char str[], char destination[])
{
  // TODO Task 2.6 BEGIN
  static int offset = 0;
  static int start = -1;
  static int last_non_space = -1;

  // base case writing
  if (str[0] == '\0')
  {
    // calculate the starting place of the original string
    const char *original = str - offset;
    if (start != -1 && last_non_space != -1 && start <= last_non_space)
    {
      // the right boundary of substring is exclusive
      substring(original, start, last_non_space + 1, destination);
    }
    else
    {
      destination[0] = '\0';
    }
    // reset static
    offset = 0;
    start = -1;
    last_non_space = -1;
    return;
  }

  // If the current character is not a space, update start and last_non_space
  if (str[0] != ' ')
  {
    if (start == -1)
    {
      start = offset;
    }
    last_non_space = offset;
  }

  offset++;
  trim(str + 1, destination);
  // TODO Task 2.6 END
}

#endif // STRING_UTILS_CPP
