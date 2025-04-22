#include "Arduino.h"
#include "Stack.h"

Stack::Stack(){
  _top = -1;
  _stack[_capacity];   // to be confirmed
}

void Stack::push(float operand){
  _stack[++_top] = operand;
}

float Stack::pop(){
  return _stack[_top--];
}

float Stack::peek(){
  return _stack[_top];
}

boolean Stack::isFull(){
 return _top == _capacity-1;
}

boolean Stack::isEmpty(){
  return _top == -1;
}
