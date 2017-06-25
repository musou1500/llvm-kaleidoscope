#pragma once
#include <stdio.h>
#include <memory>
#include "AST/ExprAST.h"
#include "AST/PrototypeAST.h"
#include "llvm/IR/Value.h"

inline std::unique_ptr<ExprAST> LogError(const char* Str) {
  fprintf(stderr, "LogError: %s\n", Str);
  return nullptr;
}

inline std::unique_ptr<PrototypeAST> LogerrorP(const char *Str) {
  LogError(Str);
  return nullptr;
};

inline llvm::Value *LogErrorV(const char *Str) {
  LogError(Str);
  return nullptr;
}
