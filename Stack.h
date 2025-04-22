#ifndef Stack_h
#define Stack_h

#include "Arduino.h"

class Stack {
  public:
    Stack();            
    void push(float n);  // Push a float onto the stack
    float pop();         // Pop a float from the stack
    float peek();        // View top of the stack
    boolean isFull();    // Check if full
    boolean isEmpty();   // Check if empty

  private:
    int8_t _top;
    static const uint8_t _capacity = 20;
    float _stack[_capacity];
};

#endif
