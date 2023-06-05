#include "postfix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void apply_operator(struct double_stack * this, char expr){
  char c = expr;
  
  double second = double_stack_pop(this);
  double first = double_stack_pop(this);
  double result;

  switch (c) {
    case '+':
      result = first + second;
      break;
    case '-':
      result =  first - second;
      break;
    case 'X':
      result =  first * second;
      break;
    case '/':
      result =  first / second;
      break;
    case '^':
      result = pow(first, second);
      break;
    default:
      break;
  } 
  double_stack_push(this, result);
}

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {
  struct double_stack * stack = double_stack_new(nargs);
  double result;

  for(int i=0; i<nargs; i++) {  
    if(strlen(args[i])==1) {
      switch(args[i][0]) {
        case '+':
        case '-':
        case 'X':
        case '/':
        case '^':
          apply_operator(stack,args[i][0]);
          break;
        default:
          double_stack_push(stack,atof(args[i]));
          break;
      }
    } else { // when the string length is >1
        double_stack_push(stack,atof(args[i]));
    }
  } 
  result = double_stack_pop(stack);
  return result;
}

