#include "VariableExprAST.h"
#include <map>
#include <string>
#include "llvm/IR/Value.h"
#include "../Logger.h"

llvm::Value* VariableExprAST::codegen() {
  extern std::map<std::string, llvm::Value *> NamedValues;
  llvm::Value *V = NamedValues[Name];
  if (!V)
    LogErrorV("Unknown variable name");
  return V;
}
