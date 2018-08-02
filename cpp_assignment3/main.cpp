//Assignment 3 in C++ 2nd quarter at Foothill, by Jessica Dickinson Goodman
//  main.cpp
//  cpp_assignment3

#include <random>
#include <iostream>
using namespace std;

class Automaton{
private:
   static const int RULES_SIZE = 8;
   bool rule[RULES_SIZE];
   string thisGen;
   string extremeBit; // bit, "*" or " ", implied everywhere "outside"
   int displayWidth;  // an odd number so it can be perfectly centered

   int numDigits(int num);
   int minVal = 0;
   int maxVal = 255;
   int defaultRule[8];

public:
   static const int MAX_DISPLAY_WIDTH = 121;
   Automaton(int rule);
   string toStringCurrentGen();
   bool setRule(int newRule);
   void resetFirstGen();
   bool setDisplayWidth(int width);
   void propagateNewGeneration();
};

Automaton::Automaton(int rule){
   resetFirstGen();
   if(!setRule(rule)){
      for (int i = 0; i < RULES_SIZE; i++){
         this->rule[i] = false;
      }
   }
}

void Automaton::resetFirstGen(){
   thisGen = "*";
   extremeBit = ' ';
}

string Automaton::toStringCurrentGen(){
   string returnString = thisGen;
   while(returnString.length() < displayWidth){
      returnString = extremeBit + returnString + extremeBit;
   }
   if(returnString.length() > displayWidth){
      int deleteThese = (returnString.length() - displayWidth)/2;
      returnString = thisGen.substr(deleteThese, displayWidth);
   }
   return returnString;
}

bool Automaton::setRule(int newRule){
   if(newRule > maxVal || newRule < minVal)
      return false;

   for (int i = 0; i < RULES_SIZE; i++){
      int temp = pow(2, i);
      if ( (newRule & temp) != 0)   rule[i] = true; else rule[i] = false;
   }
   return true;
}

bool Automaton::setDisplayWidth(int width){
   if(width < MAX_DISPLAY_WIDTH && width > 0){
      if (width % 2 == 1)
         displayWidth = width;
      else
         displayWidth = width + 1;
   }
   else
      displayWidth = MAX_DISPLAY_WIDTH;
   return displayWidth;
}

void Automaton::propagateNewGeneration(){
   thisGen = extremeBit + extremeBit + thisGen + extremeBit + extremeBit;
   //covert thisGen to an int array
   int thisGenIntArray[thisGen.length()];
   for(int i = 0; i < thisGen.length(); i++){
      if(thisGen[i] == '*')
         thisGenIntArray[i] = 1;
      if(thisGen[i] == ' ')
         thisGenIntArray[i] = 0;
   }

   int nextGen[thisGen.length()];
   int nextGenLength = 0;

   //In sequential groups of 3, convert the 0s and 1s of thisGenIntArray to a decimal, then find the 0 or 1 at that index in rule[]
   for (int i = 0; i < thisGen.length() - 2; i++){
      int triad = (thisGenIntArray[i]*4)+(thisGenIntArray[i+1]*2)+thisGenIntArray[i+2];
      nextGen[i] = rule[triad];
      nextGenLength++;
   }

   thisGen = "";

   //Convert back to '*'s and ' 's for thisGen.
   for (int i = 0; i < nextGenLength; i++){
      if(nextGen[i] == 0)
         thisGen += ' ';
      else
         thisGen += '*';
   }
}

int main(){

   int userInput = 124;
   for (int i = 0; i < 5; i ++){
      cout << "Enter Rule (0 - 255): " << endl;
      cin >> userInput;

      cout << "start" << endl;
      Automaton auton(userInput);
      auton.setDisplayWidth(79);
      for(int i = 0; i < 100; i++){
         cout << auton.toStringCurrentGen() << endl;
         auton.propagateNewGeneration();
      }
      cout << "end" << endl;
      cout << "Try typing 30, 54, 60, 90, 94, 150 for cool patterns. " << endl;
   }
}


