//
//  proj5.h
//  Proj5
//
//  Created by EmilyLin on 6/11/18.
//  Copyright © 2018 Emily Lin. All rights reserved.
//

#ifndef proj5_h
#define proj5_h
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;


//The value stack
class ValueStack
{
private:
   int *number;       //The value array
   int topElement;    //The top element for value stack
   int size;          //The array size for value stack

public:
   void init();           //The initialized function for value stack
   void push(int num);    //The push function for value stack
   void pop();            //The pop function for value stack
   void reset();          //The reset function for value stack
   bool isEmpty();        //The isEmpty function for value stack
   int top();             //The top function for value stack
};


//The class for the operator stack
class OperatorStack
{
private:
   char *inputOperator;    //The value array
   int topElement2;        //The top element for value stack
   int size2;              //The array size for value stack

public:
   void init2();           //The initialized function for value stack
   void push2(char symbol);//The push function for value stack
   void pop2();            //The pop function for value stack
   void reset2();          //The reset function for value stack
   bool isEmpty2();        //The isEmpty function for value stack
   char top2();            //The top function for value stack

   
};


//void processExpression (Token inputToken, TokenReader *tr);

#endif /* proj5_h */
