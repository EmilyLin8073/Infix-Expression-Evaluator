//
//  stack.cpp
//  Proj5
//
//  Created by EmilyLin on 6/11/18.
//  Copyright © 2018 Emily Lin. All rights reserved.
//

#include "proj5.h"

//In this function, we are going to initialized the value stack
void ValueStack::init()
{
   this->size = 2;                //Set the original size to 2
   this->topElement = -1;         //Make the top element to -1
   this->number = new int[size];  //Make the number array into dynamic allocate array
}


//In this function, we are going to check whether the value stack is empty or not
bool ValueStack::isEmpty()
{
   if(this->topElement == -1)
      return true;

   return false;
}


//In this function, we are going to push the value onto stack
void ValueStack::push(int num)
{
   //If the array is full, we grow the array by size 2
   if(this->topElement + 1 == this->size)
   {
      int *newLargerArray = new int[this->size + 2];

      for(int i = 0; i < size; i++)
      {
         newLargerArray[i] = this->number[i];
      }

      delete[] this->number;

      this->number = newLargerArray;
      this->size = this->size + 2;
   }

   this->topElement = this->topElement + 1;    //We grow the top element by 1
   this->number[topElement] = num;             //Put the value into the stack
}


//In this function, we are poping the top element on the stack
void ValueStack::pop()
{
   this->topElement = this->topElement - 1;
}


//In this function, we return the top element on the stack
int ValueStack::top()
{
   return this->number[this->topElement];
}


//In this function, we are resetting the value stack so that it can be reuse later
void ValueStack::reset()
{
   while(topElement != -1)
   {
      delete[] this->number;
   }

   init();
}




//In this function, we are going to initialized the operator stack
void OperatorStack::init2()
{
   this->size2 = 2;                        //Make the size of the operator array into 2
   this->topElement2 = -1;                 //Make the top element of operator array into -1
   this->inputOperator = new char[size2];  //Make the operator array into dynamic allocate array
}


//In this function, we are going to check whether the operator stack is empty or not
bool OperatorStack::isEmpty2()
{
   if(this->topElement2 == -1)
      return true;

   return false;
}


//In this function, we are pushing the operator onto the stack
void OperatorStack::push2(char symbol)
{
   //If the stack is full, we grwo the array by size 2
   if(this->topElement2 + 1 == this->size2)
   {
      char *newLargerArray = new char[this->size2 + 2];

      for(int i = 0; i < size2; i++)
      {
         newLargerArray[i] = this->inputOperator[i];
      }


      delete[] this->inputOperator;

      this->inputOperator = newLargerArray;
      this->size2 = this->size2 + 2;
   }

   this->topElement2 = this->topElement2 + 1;          //Add 1 to the top element
   this->inputOperator[this->topElement2] = symbol;    //Put the operator into the stack
}


//In this function, we are going to pop the top element out of the operator stack
void OperatorStack::pop2()
{
   this->topElement2 = this->topElement2 - 1;
}


//In this function, we are going the reutn the top element on the operator stack
char OperatorStack::top2()
{
   return this->inputOperator[this->topElement2];
}


//In thie function, we are going to reset the operator stack for later use
void OperatorStack::reset2()
{
   while(topElement2 != -1)
   {
      delete[] this->inputOperator;
   }
   
   init2();
}
