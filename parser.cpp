// Lexi Anderson
// CS4280, Proj 2
// parser.cpp

#include <iostream>

#include "parser.h"
#include "scanner.h"
#include "token.h"

token_t tkn;

void parser() {
  tkn = scanner();
  S();
  if (tkn.id == EOF_TK) // continue
  else error();
  
  return;
}

// Abort program on parsing error
void error() {
  std::cout << "Parsing error at token \'" << tkn << "\'" << std::endl;
  exit(0);
}

// nonterminal functions

void S() {
  if (tkn.id == KEYWD_TK && tkn.str == "Name") {
    tkn = scanner();
    if (tkn.id == ID_TK) {
      tkn = scanner();
      if (tkn.id == KEYWD_TK && tkn.str == "Spot") {
        tkn = scanner();
        if (tkn.id == ID_TK) {
          tkn = scanner();
          R();
          E();
          
          return;
        } else error();
      } else error();
    } else error();
  } else error();
  
  return;
}

void R() {
  if (tkn.id == KEYWD_TK && tkn.str == "Place") {
    tkn = scanner();
    A();
    B();
    if (tkn.id == KEYWD_TK && tkn.str == "Home") {
      tkn = scanner();
      
      return;
    } else error();
  } else error();
}

void E() {
  if (tkn.id == KEYWD_TK && tkn.str == "Show") {
    tkn = scanner();
    if (tkn.id = ID_TK) {
      tkn = scanner();
      
      return;
    } else error();
  } else error();
}

void A() {
  if (tkn.id == KEYWD_TK && tkn.str == "Name") {
    tkn = scanner();
    if (tkn.id = ID_TK) {
      tkn = scanner();
      
      return;
    } else error();
  } else error();
}

void B() {
  if (tkn.id == OP_TK && tkn.str == ".") {
    tkn = scanner();
    C();
    if (tkn.id == OP_TK && tkn.str == ".") {
      tkn = scanner();
      B();
      
      return;
    } else error();
  } else if (tkn.id == OP_TK || tkn.id == KEYWD_TK) { //TODO: test implementation
    D();
    B();
    
    return;
  } else {  // nullable
    return;
  }
}

void C() {
  if (tkn.id == OP_TK && tkn.str == "{") {
    F();
    
    return;
  } else if (tkn.id == KEYWD_TK && tkn.str == "Here") {
    G();
    
    return;
  } else error();
}

void D() {
  if (tkn.id == OP_TK) {
    if (tkn.str == "/") {
      H();
      
      return;
    } else if (tkn.str == "{") {
      F();
      
      return;
    } else error();
  } else if (tkn.id == KEYWD_TK) {
    if (tkn.str == "Assign") {
      J();
      
      return;
    } else if (tkn.str == "Spot" || tkn.str == "Move") {
      K();
      
      return;
    } else if (tkn.str == "Flip") {
      L();
      
      return;
    } else if (tkn.str == "Show") {
      E();
      
      return;
    } else error();
  } else error();
}

void F() {
  if (tkn.id == OP_TK && tkn.str == "{") {
    tkn = scanner();
    if (tkn.id == KEYWD_TK) {
      if (tkn.str == "If") {
        tkn = scanner();
        if (tkn.id == ID_TK) {
          tkn = scanner();
          T();
          W();
          D();
          // finish after if-statement
        } else error();
      } else if (tkn.str == "Do") {
        tkn = scanner();
        if (tkn.id == "KEYWD_TK" && tkn.str == "Again") {
          tkn = scanner();
          D();
          T();
          W();
          // finish after if-statement
        } else error();
      } else error();
    } else error();
  } else error();
  
  // closing brace for both productions
  if (tkn.id == OP_TK && tkn.str == "}") {
    tkn = scanner();
            
    return;
  } else error();
}

void G() {
  if (tkn.id == KEYWD_TK && tkn.str == "Here") {
    tkn = scanner();
    if (tkn.id == NUM_TK) {
      tkn = scanner();
      if (tkn.id == KEYWD_TK && tkn.str == "There") {
        tkn = scanner();
        
        return;
      } else error();
    } else error();
  } else error();
}

void T() {
  if (tkn.id == OP_TK) {
    if (tkn.str == "<<" || tkn.str == "<-") {
      tkn = scanner();
      
      return;
    } else error();
  } else error();
}

void V() {
  if (tkn.id == OP_TK) {
    if (tkn.str == "+" || tkn.str == "%" || tkn.str == "&") {
      tkn = scanner();
      
      return;
    } else error();
  } else error();
}

void H() {
  if (tkn.id == OP_TK && tkn.str == "/") {
    tkn = scanner();
    Z();
    
    return;
  } else error();
}

void J() {
  if (tkn.id == KEYWD_TK && tkn.str == "Assign") {
    tkn = scanner();
    if (tkn.id == ID_TK) {
      tkn = scanner();
      D();
      
      return;
    } else error();
  } else error();
}

void K() {
  if (tkn.id == KEYWD_TK) {
    if (tkn.str == "Spot") {
      tkn = scanner();
      if (tkn.id == NUM_TK) {
        tkn = scanner();
        if (tkn.id == KEYWD_TK && tkn.str == "Show") {
          tkn = scanner();
          if (tkn.id == NUM_TK) {
            tkn = scanner();
            
            return;
          } else error();
        } else error();
      } else error();
    } else if (tkn.str == "Move") {
      tkn = scanner();
      if (tkn.id == ID_TK) {
        tkn = scanner();
        if (tkn.id == KEYWD_TK && tkn.str == "Show") {
          tkn = scanner();
          if (tkn.id == ID_TK) {
            tkn = scanner();
            
            return;
          } else error();
        } else error();
      } else error();
    } else error();
  } else error();
}

void L() {
  if (tkn.id == KEYWD_TK && tkn.str == "Flip") {
    tkn = scanner();
    if (tkn.id == ID_TK) {
      tkn = scanner();
      
      return;
    } else error();
  } else error();
}

void W() {
  if (tkn.id == NUM_TK) {
    tkn = scanner();
    if (tkn.id == OP_TK) {
      if (tkn.str == ".") {
        tkn = scanner();
        
        return;
      } else {
        V();  // TODO: test this implementation
        
        return;
      }
    } else error();
  }
}

void Z() {
  if (tkn.id == ID_TK) {
    tkn = scanner();
    
    return;
  } else if (tkn.id == NUM_TK) {
    tkn = scanner();
    
    return;
  } else error();  
}
