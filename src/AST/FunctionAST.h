#pragma once
#include <memory>
#include <utility>
#include "ExprAST.h"
#include "PrototypeAST.h"
#include "llvm/IR/Function.h"

class FunctionAST : public ExprAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<ExprAST> Body;
public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<ExprAST> Body)
    : Proto(std::move(Proto)), Body(std::move(Body)) {}
  virtual llvm::Function *codegen() override;
};
