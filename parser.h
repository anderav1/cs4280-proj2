// Lexi Anderson
// CS4280, Proj 2
// parser.h

#ifndef PARSER_H
#define PARSER_H

#include "node.h"

node_t* parser(std::istream &input);
void error();
node_t* getNode(char);

// nonterminals
void S();
void R();
void E();
void A();
void B();
void C();
void D();
void F();
void G();
void T();
void V();
void H();
void J();
void K();
void L();
void W();
void Z();


#endif
