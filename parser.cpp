// Lexi Anderson
// CS4280, Proj 2
// parser.cpp

#include <iostream>

#include "node.h"
#include "parser.h"
#include "scanner.h"
#include "token.h"

token_t tkn;
std::istream* fp;

node_t* parser(std::istream &input) {
  node_t* root;

  fp = &input;
  tkn = scanner(*fp);
  root = S();
  
  std::cout << tkn.str << tkn.id << std::endl;
  
  if (tkn.id != EOF_TK) error();
  else std::cout << "Successfully parsed program" << std::endl;
  
  return root;
}

// Abort program on parsing error
void error() {
  std::cout << "Parsing error at " << tkn.id << " token \'" << tkn.str << "\' on line " << tkn.line << std::endl;
  exit(0);
}

// Create an empty node with label
node_t* getNode(char label) {
  node_t* node = malloc(sizeof(node_t));
  node.label = label;
  // all ptr members should be null
  
  return node;
}

// nonterminal functions

node_t* S() {
  node_t* node = getNode(S);
  if (tkn.id == KEYWD_TK && tkn.str == "Name") {
    tkn = scanner(*fp);
    if (tkn.id == ID_TK) {
      tkn = scanner(*fp);
      if (tkn.id == KEYWD_TK && tkn.str == "Spot") {
        tkn = scanner(*fp);
        if (tkn.id == ID_TK) {
          tkn = scanner(*fp);
          R();
          E();
          
          return;
        } else error();
      } else error();
    } else error();
  } else error();
}

void R() {
  if (tkn.id == KEYWD_TK && tkn.str == "Place") {
    tkn = scanner(*fp);
    A();
    B();
    if (tkn.id == KEYWD_TK && tkn.str == "Home") {
      tkn = scanner(*fp);
      
      return;
    } else error();
  } else error();
}

void E() { // working
  if (tkn.id == KEYWD_TK && tkn.str == "Show") {
    tkn = scanner(*fp);
    if (tkn.id == ID_TK) {
      //std::cout << "E: parsed " << tkn.str << std::endl;
      tkn = scanner(*fp);
      //std::cout << "E: returning " << tkn.str << std::endl;
      return;
    } else error();
  } else error();
}

void A() { // working
  if (tkn.id == KEYWD_TK && tkn.str == "Name") {
    tkn = scanner(*fp);
    if (tkn.id == ID_TK) {
      tkn = scanner(*fp);
      
      return;
    } else error();
  } else error();
}

void B() {
  if (tkn.id == OP_TK && tkn.str == ".") {
    tkn = scanner(*fp);
    //std::cout << "B: calling C to parse " << tkn.str << std::endl;
    C();
    if (tkn.id == OP_TK && tkn.str == ".") {
      tkn = scanner(*fp);
      //std::cout << "B: calling B to parse " << tkn.str << std::endl;
      B();
      
      return;
    } else error();
  } else if ((tkn.id == OP_TK && (tkn.str == "/" || tkn.str == "{")) || (tkn.id == KEYWD_TK && (tkn.str == "Assign" || tkn.str == "Spot" || tkn.str == "Move" || tkn.str == "Flip" || tkn.str == "Show"))) {
    //std::cout << "B: calling D to parse " << tkn.str << std::endl;
    D();
    //std::cout << "B: calling B to parse " << tkn.str << std::endl;
    B();
    
    return;
  } else return;  // nullable
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
      std::cout << "D: calling E to parse " << tkn.str << std::endl;
      E();
      
      return;
    } else error();
  } else error();
}

void F() {
  if (tkn.id == OP_TK && tkn.str == "{") {
    tkn = scanner(*fp);
    if (tkn.id == KEYWD_TK) {
      if (tkn.str == "If") {
        tkn = scanner(*fp);
        if (tkn.id == ID_TK) {
          tkn = scanner(*fp);
          T();
          W();
          D();
          // finish after if-statement
        } else error();
      } else if (tkn.str == "Do") {
        tkn = scanner(*fp);
        if (tkn.id == KEYWD_TK && tkn.str == "Again") {
          tkn = scanner(*fp);
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
    tkn = scanner(*fp);
            
    return;
  } else error();
}

void G() {
  if (tkn.id == KEYWD_TK && tkn.str == "Here") {
    tkn = scanner(*fp);
    if (tkn.id == NUM_TK) {
      tkn = scanner(*fp);
      if (tkn.id == KEYWD_TK && tkn.str == "There") {
        tkn = scanner(*fp);
        
        return;
      } else error();
    } else error();
  } else error();
}

void T() {
  if (tkn.id == OP_TK) {
    if (tkn.str == "<<" || tkn.str == "<-") {
      tkn = scanner(*fp);
      
      return;
    } else error();
  } else error();
}

void V() {
  if (tkn.id == OP_TK) {
    if (tkn.str == "+" || tkn.str == "%" || tkn.str == "&") {
      tkn = scanner(*fp);
      
      return;
    } else error();
  } else error();
}

void H() {
  if (tkn.id == OP_TK && tkn.str == "/") {
    tkn = scanner(*fp);
    Z();
    
    return;
  } else error();
}

void J() {
  if (tkn.id == KEYWD_TK && tkn.str == "Assign") {
    tkn = scanner(*fp);
    if (tkn.id == ID_TK) {
      tkn = scanner(*fp);
      D();
      
      return;
    } else error();
  } else error();
}

void K() {
  if (tkn.id == KEYWD_TK) {
    if (tkn.str == "Spot") {
      tkn = scanner(*fp);
      if (tkn.id == NUM_TK) {
        tkn = scanner(*fp);
        if (tkn.id == KEYWD_TK && tkn.str == "Show") {
          tkn = scanner(*fp);
          if (tkn.id == NUM_TK) {
            tkn = scanner(*fp);
            
            return;
          } else error();
        } else error();
      } else error();
    } else if (tkn.str == "Move") {
      tkn = scanner(*fp);
      if (tkn.id == ID_TK) {
        tkn = scanner(*fp);
        if (tkn.id == KEYWD_TK && tkn.str == "Show") {
          tkn = scanner(*fp);
          if (tkn.id == ID_TK) {
            tkn = scanner(*fp);
            
            return;
          } else error();
        } else error();
      } else error();
    } else error();
  } else error();
}

void L() {
  if (tkn.id == KEYWD_TK && tkn.str == "Flip") {
    tkn = scanner(*fp);
    if (tkn.id == ID_TK) {
      tkn = scanner(*fp);
      
      return;
    } else error();
  } else error();
}

void W() {
  if (tkn.id == NUM_TK) {
    tkn = scanner(*fp);
    if (tkn.id == OP_TK) {
      if (tkn.str == ".") {
        tkn = scanner(*fp);
        
        return;
      } else {
        V();  // TODO: test this implementation
        
        return;
      }
    } else error();
  }
}

// TODO: implement tree node
void Z() {
  node_t* node = getNode('Z');
  
  if (tkn.id == ID_TK) {
    tkn = scanner(*fp);
    
    return;
  } else if (tkn.id == NUM_TK) {
    tkn = scanner(*fp);
    
    return;
  } else error();  
}
