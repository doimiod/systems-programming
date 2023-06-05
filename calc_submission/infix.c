#include "infix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int left_bracket(char expr) {
  if(expr=='(') {
    return 1;
  }
  return 0;
}

int right_bracket(char expr) {
  if(expr==')') {
    return 1;
  }
  return 0;
}

int isOperator (char * ch) {
  int result = 0;
  if(strlen(ch)==1) {
    switch (ch[0]) {
    case '^':
    case 'X':
    case '/':
    case '+':
    case '-':
      result= 1;
      break;
    default:
      result= 0;
      break;
    } 
  }
  printf("result in operator is %d\n", result);
  return result;
}

int int_prec (char ch) {
  int result = -1;
  switch(ch) {
    case '^':
      result = 3;
      break;
    case 'X':
    case '/':
      result = 2;
      break;
    case '+':
    case '-':
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result; 
}

int isEmpty (struct double_stack * this) {
  return this->top<=0;
}

int double_peek (struct double_stack * this) {
  return this->items[this->top -1];
}

int int_op_of_higher_prec(char op1, char op2) {
  int op_value1 = int_prec(op1);
  int op_value2 = int_prec(op2);
  if(op_value1 >= op_value2) {
    return 1;
  } else return 0;
}

double evaluate_infix_expression (char ** args, int nargs) {

  struct double_stack * stack = double_stack_new(nargs);
  char * postfix[nargs];
  int length = 0;
  double result;
  int top = 0;
  int remained_items;

  for(int i=0; i<nargs; i++) {
    printf("%d\n",i);
    if(isOperator(args[i])) { //if token is operator
      //printf("PRINT\n");
      while(!isEmpty(stack)) {
        //printf("check\n");

        top = double_peek(stack);
        //printf("double_peek(stack) is %d\n",double_peek(stack));
        //printf("Something in stack is %d\n",int_prec(args[i][0]));
        printf("something in stack is %d\n",int_op_of_higher_prec(args[double_peek(stack)][0], args[i][0]));
      
        if(isOperator(args[i])&&int_op_of_higher_prec(args[double_peek(stack)][0], args[i][0])) {
          //printf("it goes through if\n");
	   double_stack_pop(stack);
	   postfix[length] = args[top];
	   length++;
        }
	else {
           printf("it goes through else\n");
	   break;	
	}
      } 
      double_stack_push(stack, i);
    }

    else if(left_bracket(args[i][0])) { //if token is left bracket
      double_stack_push(stack, i);
    }

    else if(right_bracket(args[i][0])) { //if token is right bracket
      while(!isEmpty(stack)) {
        top = double_peek(stack);
        if(!left_bracket(args[top][0])) {
          double_stack_pop(stack);
          postfix[length] = args[top];
          length++;
        } else {
          double_stack_pop(stack);
          break;
        }
      }
    }

    else { //if token is operated
      postfix[length] = args[i];
      length++;
    }
  } //end for

  for(int i=0;i<length;i++){
    printf("postfix[%d] is %s\n",i,postfix[i]);
  }
  

  while(!isEmpty(stack)) {
    remained_items = double_stack_pop(stack);
    postfix[length] = args[remained_items];
    length++;
  } 
  result = evaluate_postfix_expression(postfix, length);
  return result;
}
