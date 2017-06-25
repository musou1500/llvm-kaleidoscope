#pragma once
#include <string>
#include <vector>
#include <utility>
#include "ExprAST.h"
#include "llvm/IR/IRBuilder.h"

class PrototypeAST : public ExprAST {
  std::string Name;
  std::vector<std::string> Args;
public:
  PrototypeAST(const std::string &name, std::vector<std::string> Args)
    : Name(name), Args(std::move(Args)) {}

  const std::string &getName() const { return Name; }
  virtual llvm::Function *codegen() override;
};
