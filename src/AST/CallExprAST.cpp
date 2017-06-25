#include "CallExprAST.h"
#include <memory>
#include <vector>
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "../Logger.h"

llvm::Value *CallExprAST::codegen() {
  extern std::unique_ptr<llvm::Module> TheModule;
  extern llvm::IRBuilder<> Builder;
  llvm::Function *CalleeF = TheModule->getFunction(Callee);
  if (!CalleeF) {
    return LogErrorV("unknown function referenced");
  }

  if(CalleeF->arg_size() != Args.size()) {
    return LogErrorV("Incorrect # arguments passed");
  }

  std::vector<llvm::Value *> ArgsV;
  for (unsigned i = 0, e = Args.size(); i != e; ++i) {
    ArgsV.push_back(Args[i]->codegen());
    if (!ArgsV.back()) {
      return nullptr;
    }
  }

  return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}
