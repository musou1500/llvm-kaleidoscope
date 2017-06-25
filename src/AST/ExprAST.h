#pragma once
#include "llvm/IR/Value.h"

class ExprAST {
public:
  virtual ~ExprAST() {}
  virtual llvm::Value *codegen() = 0;
};
