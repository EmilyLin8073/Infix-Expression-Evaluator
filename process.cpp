/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 10/21/17
 *
 * Author: Pat Troy
 *
 */

/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

#include "proj5.h"
// Enumarated Type specifying all of the Tokens
enum TokenType{
   ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};
bool debugMode;

void printCommands()
{
   printf ("The commands for this program are:\n\n");
   printf ("q - to quit the program\n");
   printf ("? - to list the accepted commands\n");
   printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}


// Class to hold the Token information
class Token
{
private:
   TokenType type;
   char      op;       // using '$' as undefined/error
   int       val;      // using -999 as undefined/error

public:

   // Default to initialize to the ERROR TokenType
   Token()
   {
      type = ERROR;
      op = '$';
      val = -999;
   }

   // Initialize to a specific TokenType
   Token (TokenType t)
   {
      type = t;
      op = '$';
      val = -999;
   }

   // Set to a specific TokenType
   void setToType(TokenType t)
   {
      type = t;
      op = '$';
      val = -999;
   }

   // Set to a OPERATOR TokenType with specific operator value
   void setToOperator(char c)
   {
      type = OPERATOR;
      op = c;
      val = -999;
   }

   // Set to a VALUE TokenType with a specific numeric value
   void setToValue(int v)
   {
      type = VALUE;
      op = '$';
      val = v;
   }

   // return true if the Current Token is of the given TokenType
   bool equalsType(TokenType t)
   {
      if (type == t)
         return true;
      else
         return false;
   }

   // return true if the Current Token is of the OPERATOR TokenType
   //     and contains the given operator character
   bool equalsOperator(char c)
   {
      if (type == OPERATOR && op == c)
         return true;
      else
         return false;
   }

   // Return the Operator for the current Token
   //   verify the current Token is of the OPERATOR TokenType
   char getOperator ()
   {
      if (type == OPERATOR)
         return op;
      else
         return '$';   // using $ to indicate an error value
   }

   // Return the Value for the current Token
   //   verify the current token is of the value TokenType
   int getValue()
   {
      if (type == VALUE)
         return val;
      else
         return -999;  // using -999 to indicate an error value
   }
};


class TokenReader
{
private:
   char inputline[300];  // this assumes that all input lines are 300 characters or less in length
   bool needline;
   int pos;


public:

   // initialize the TokenReader class to read from Standard Input
   TokenReader()
   {
      // set to read from Standard Input
      inputline[0] = '\0';
      pos = 0;
      needline = true;
   }

   // Force the next getNextToken to read in a line of input
   void clearToEoln()
   {
      needline = true;
   }

   // Return the next Token from the input line
   Token getNextToken()
   {
      char* endCheck;

      //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

      // get a new line of input from user
      if (needline)
      {
         endCheck = fgets ( inputline, 300, stdin);

         if (endCheck == NULL )
         {
            printf ("Error in reading");
            Token t(EOFILE);
            return t;
         }

         for (int i = 0 ; i < strlen(inputline) ; i++)
            if ('\n' == inputline[i])
               inputline[i] = ' ';
         strcat (inputline , " ");    // add a space at end to help deal with digit calculation
         needline = false;
         pos = 0;
      }

      // skip over any white space characters in the beginning of the input
      while ( pos < strlen(inputline) && isspace(inputline[pos]) )
      {
         pos++;
      }

      // check for the end of the current line of input
      if (pos >= strlen(inputline))
      { // at end of line
         needline = true;
         Token t(EOLN);
         return t;
      }

      // Get the next character from the input line
      char ch = inputline[pos]; pos++;

      // check if 'q' or 'Q' was entered ==> QUIT Token
      if ( 'q' == ch || 'Q' == ch )
      {
         return Token (QUIT);
      }

      // check if "?" was entered ==> HELP Token
      if ( '?' == ch )
      {
         return Token (HELP);
      }

      // check for Operator values of: + - * / ( )  ==> OPERATOR Token
      if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
          ('/' == ch) || ('(' == ch) || (')' == ch) )
      {
         Token t;
         t.setToOperator( ch );
         return t;
      }

      // check for a number  ==> VALUE Token
      if (isdigit(ch))
      {
         int number = int (ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
         ch = inputline[pos]; pos++;
         while (isdigit(ch))
         {
            number = number * 10 + int (ch) - int('0');
            ch = inputline[pos]; pos++;
         }
         pos--; // since number calcuation check one character after the last digit
         Token t;
         t.setToValue( number );
         return t;
      }
      
      // Input in not valid if code get to this part ==> ERROR Token
      return Token (ERROR);
   }
   
};




/**************************************************************/
/*                                                            */
/*  The Code above this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

void processExpression (Token inputToken, TokenReader *tr);

int main(int argc, char *argv[])
{
   /***************************************************************/
   /* Add code for checking command line arguments for debug mode */

   ValueStack v1;      //Create the object for value class
   OperatorStack o1;   //Create the object for operator class

   debugMode = false;

   //Sets debug mode
   for(int i = 0; i < argc; i++)
   {
      if(strcmp(argv[i], "-d") == 0)
      {
         printf("\nDEBUG MODE ON\n");
         debugMode = true;
      }
   }


   Token inputToken;
   TokenReader tr;

   printf ("Starting Expression Evaluation Program\n\n");
   printf ("Enter Expression: ");


   inputToken = tr.getNextToken ();

   while (inputToken.equalsType(QUIT) == false)
   {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
         printCommands();
         tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
         printf ("Invalid Input - For a list of valid commands, type ?\n");
         tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
         printf ("Blank Line - Do Nothing\n");
         /* blank line - do nothing */
      }
      else
      {
        processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
   }

   printf ("Quitting Program\n");

   v1.reset();  //Reset the value stack
   o1.reset2(); //Reset the operator stack
   return 1;
}


void processExpression (Token inputToken, TokenReader *tr)
{
   /**********************************************/
   /* Declare both stack head pointers here      */

   //First Step
   ValueStack numStack;      //Creat the object for value stack
   OperatorStack operStack;  //Creat the object for operator stack

   numStack.init();          //Initialized the value stack
   operStack.init2();        //Initialized the operator stack


   //Second Step
   /* Loop until the expression reaches its End */
   while (inputToken.equalsType(EOLN) == false)
   {
      /* The expression contain a VALUE */
      if (inputToken.equalsType(VALUE))
      {
         /* make this a debugMode statement */
         if(debugMode == true)
            printf ("Val: %d, ", inputToken.getValue() );

         // add code to perform this operation here
         numStack.push(inputToken.getValue());
      }
      
      /* The expression contains an OPERATOR */
      if (inputToken.equalsType(OPERATOR))
      {
         /* make this a debugMode statement */
         if(debugMode == true)
            printf ("OP: %c, ", inputToken.getOperator() );
         
         // add code to perform this operation here
         if(inputToken.getOperator() == '(')
         {
            operStack.push2(inputToken.getOperator());
         }

         if(inputToken.getOperator() == '+' || inputToken.getOperator() == '-')
         {
            while(operStack.isEmpty2() != true && (operStack.top2() == '+' ||
                                                   operStack.top2() == '-' ||
                                                   operStack.top2() == '*' ||
                                                   operStack.top2() == '/'))
            {
               //popAndEval();

               if(inputToken.getOperator() != '+' && inputToken.getOperator() != '-' &&
                  inputToken.getOperator() != '*' && inputToken.getOperator() != '/')
               {
                  cout << "Error, the top of the operator stack is not +, -, *, /" << endl;
                  return;
               }

               operStack.pop2();         //Pop the top element out of the operator stack

               int v2 = numStack.top();  //Assign the top element on the value stack to v2
               numStack.pop();           //Pop the top element

               int v1 = numStack.top();  //Assign the top element on the value stack to v2
               numStack.pop();           //Pop the top element

               Token v3 = *new Token;

               int result;

               //Add
               if(inputToken.getOperator() == '+')
                  result = v1 + v2;

               //Subtraction
               if(inputToken.getOperator() == '-')
                  result = v1 - v2;

               //Mulitplication
               if(inputToken.getOperator() == '*')
                  result = v1 * v2;

               //Division
               if(inputToken.getOperator() == '/')
               {
                  //Check for 0 case
                  if(v2 == 0)
                     cout << "Error, cannot divide by 0" << endl;
                  else
                     result = v1 / v2;
               }

               v3.setToValue(result);
               numStack.push(result);
            }

            operStack.push2(inputToken.getOperator());

           // cout <<  "The top element of operStack is: " << operStack.top2() << endl << endl;
         }

         if(inputToken.getOperator() == '*' || inputToken.getOperator() == '/')
         {
            while(operStack.isEmpty2() != true && (operStack.top2() == '*' ||
                                                   operStack.top2() == '/'))
            {
               //popAndEval();

               if(inputToken.getOperator() != '+' && inputToken.getOperator() != '-' &&
                  inputToken.getOperator() != '*' && inputToken.getOperator() != '/')
               {
                  cout << "Error, the top of the operator stack is not +, -, *, /" << endl;
                  return;
               }

               operStack.pop2();         //Pop the top element out of the operator stack

               int v2 = numStack.top();  //Assign the top element on the value stack to v2
               numStack.pop();           //Pop the top element

               int v1 = numStack.top();  //Assign the top element on the value stack to v2
               numStack.pop();           //Pop the top element

               Token v3 = *new Token;

               int result;

               //Add
               if(inputToken.getOperator() == '+')
                  result = v1 + v2;

               //Subtraction
               if(inputToken.getOperator() == '-')
                  result = v1 - v2;

               //Mulitplication
               if(inputToken.getOperator() == '*')
                  result = v1 * v2;

               //Division
               if(inputToken.getOperator() == '/')
               {
                  //Check for 0 case
                  if(v2 == 0)
                     cout << "Error, cannot divide by 0" << endl;
                  else
                     result = v1 / v2;
               }
               
               v3.setToValue(result);
               numStack.push(result);
            }
            operStack.push2(inputToken.getOperator());
         }

         if(inputToken.getOperator() == ')')
         {
            while((operStack.isEmpty2() != true) && (operStack.top2() != '('))
            {
               //popAndEval();

               if(operStack.top2() != '+' && operStack.top2() != '-' &&
                  operStack.top2() != '*' && operStack.top2() != '/')
               {
                  cout << "Error, the top of the operator stack is not +, -, *, /" << endl;
                  return;
               }

               operStack.pop2();         //Pop the top element out of the operator stack

               int v2 = numStack.top();  //Assign the top element on the value stack to v2
               numStack.pop();           //Pop the top element

               int v1 = numStack.top();  //Assign the top element on the value stack to v2
               numStack.pop();           //Pop the top element

               Token v3 = *new Token;

               int result;

               //Add
               if(operStack.top2() == '+')
                  result = v1 + v2;

               //Subtraction
               if(operStack.top2() == '-')
                  result = v1 - v2;

               //Mulitplication
               if(operStack.top2() == '*')
                  result = v1 * v2;

               //Division
               if(operStack.top2() == '/')
               {
                  //Check for 0 case
                  if(v2 == 0)
                     cout << "Error, cannot divide by 0" << endl;
                  else
                     result = v1 / v2;
               }
               
               v3.setToValue(result);
               numStack.push(result);
            }

            if(operStack.isEmpty2() == true)
               cout << "Error, the operator stack is empty" << endl;

            else
            {
               operStack.pop2();
            }
         }
      }

      //Third Step
      /* get next token from input */
      inputToken = tr->getNextToken ();

      while(operStack.isEmpty2() != true)
      {
         //popAndEval();

         if(operStack.top2() != '+' && operStack.top2() != '-' &&
            operStack.top2() != '*' && operStack.top2() != '/')
         {
            cout << "Error, the top of the operator stack is not +, -, *, /" << endl;
            return;
         }

         operStack.pop2();         //Pop the top element out of the operator stack

         int v2 = numStack.top();  //Assign the top element on the value stack to v2
         numStack.pop();           //Pop the top element

         int v1 = numStack.top();  //Assign the top element on the value stack to v2
         numStack.pop();           //Pop the top element

         Token v3 = *new Token;

         int result;

         //Add
         if(operStack.top2() == '+')
            result = v1 + v2;

         //Subtraction
         if(operStack.top2() == '-')
            result = v1 - v2;

         //Mulitplication
         if(operStack.top2() == '*')
            result = v1 * v2;

         //Division
         if(operStack.top2() == '/')
         {
            //Check for 0 case
            if(v2 == 0)
               cout << "Error, cannot divide by 0" << endl;
            else
               result = v1 / v2;
         }

         v3.setToValue(result);
         numStack.push(result);
      }
   }
   
   /* The expression has reached its end */
   
   // add code to perform this operation here

   //If the value stack is empty, print the error message
   if(numStack.isEmpty() == true)
      cout << "Error, the value stack is empty" << endl;
   else   //Else, we print out the result
      cout << "The value on top of the stack: " << numStack.top() << endl;

   numStack.pop();  //Pop the result out of the stack, after this, stack should be empty

   //If the value stack is not empty, print the error message
   if(numStack.isEmpty() != true)
      cout << "Error, the value stack is not empty" << endl << endl;

   printf ("\n");
}

