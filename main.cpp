// Lexi Anderson
// CS4280, Proj 2
// main.cpp

#include <fstream>
#include <iostream>
#include <stdio.h>

#include "parser.h"
#include "testTree.h"

std::string fileName;

void printArgV(int, char*[]);


int main(int argc, char* argv[]) {
  std::istream* fp;
  
  // TODO: implement for parser and testTree
  
  if (argc == 0 || argc > 2) {
    printf("Fatal: Improper usage\nUsage:");
    printArgV(argc, argv);
    exit(1);
  }
  else if (argc == 2) fp = new std::ifstream(argv[1]);
  else if (argc == 1) fp = &std::cin;
  
  parser(*fp);
  
  //testScanner(*fp);
  
  if (fp != &std::cin) delete fp;
  
  std::cout << "Finished scanning" << std::endl;
  
  return 0;
}

// Print the entered command followed by line break
// argc -- argument count
// argv -- argument array
void printArgV(int argc, char* argv[]) {
  int i;
  for (i = 0; i < argc; i++) std::cout << " " << argv[i];
  std::cout << std::endl;
}
