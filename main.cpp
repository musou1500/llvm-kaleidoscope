#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <utility>
#include <vector>

enum Token {
  tok_eof = -1,
  tok_def = -2,
  tok_extern = -3,
  tok_identifier = -4,
  tok_number = -5
};

static std::string IdentifierStr;
static double NumVal;

static int gettok() {
  static int LastChar = ' ';

  while(isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar())))
      IdentifierStr += LastChar;

    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;

    return tok_identifier;
  }

  if (isdigit(LastChar) || LastChar == '.') {
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');
    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;
  }

  if (LastChar == '#') {
    do
      LastChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF)
      return gettok();
  }

  if (LastChar == EOF)
    return tok_eof;

  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}

class ExprAst {
public:
  virtual ~ExprAst() {}
};

class NumberExprAst : public ExprAst {
  double Val;
public:
  NumberExprAst(double Val): Val(Val) {}
};

class VariableExprAst : public ExprAst {
  std::string Name;
public:
  VariableExprAst(const std::string &Name) : Name(Name) {}
};

class BinaryExprAST : public ExprAst {
  char Op;
  std::unique_ptr<ExprAst> LHS, RHS;
public:
  BinaryExprAST(char op, std::unique_ptr<ExprAst> LHS, std::unique_ptr<ExprAst> RHS)
    : Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

class CallExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAst>> Args;
public:
  CallExprAST(const std::string &Callee, std::vector<std::unique_ptr<ExprAst>> Args)
    : Callee(Callee), Args(std::move(Args)) {}
};

class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;
public:
  PrototypeAST(const std::string &name, std::vector<std::string> Args)
    : Name(name), Args(std::move(Args)) {}

  const std::string &getName() const { return Name; }
};

class FunctionAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<ExprAst> Body;
public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<ExprAst> Body)
    : Proto(std::move(Proto)), Body(std::move(Body)) {}
};

int main(int argc, char const* argv[])
{

  return 0;
}
