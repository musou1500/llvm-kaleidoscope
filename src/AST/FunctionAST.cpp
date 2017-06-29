#include "FunctionAST.h"
#include <memory>
#include <map>
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LegacyPassManager.h"
#include "../Logger.h"

using namespace llvm;

llvm::Function *FunctionAST::codegen() {
  extern std::unique_ptr<llvm::Module> TheModule;
  extern llvm::LLVMContext TheContext;
  extern llvm::IRBuilder<> Builder;
  extern std::map<std::string, llvm::Value *> NamedValues;
  extern std::unique_ptr<legacy::FunctionPassManager> TheFPM;
  Function *TheFunction = TheModule->getFunction(Proto->getName());
  if (!TheFunction) {
    TheFunction = Proto->codegen();
  }

  if (!TheFunction) {
    return nullptr;
  }

  if (!TheFunction->empty()) {
    return (Function *)LogErrorV("Function cannot be redefined.");
  }

  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
  Builder.SetInsertPoint(BB);

  NamedValues.clear();
  for (auto &Arg : TheFunction->args()) {
    NamedValues[Arg.getName()] = &Arg;
  }

  if (Value *RetVal = Body->codegen()) {
    Builder.CreateRet(RetVal);
    llvm::verifyFunction(*TheFunction);
    TheFPM->run(*TheFunction);
    return TheFunction;
  }

  TheFunction->eraseFromParent();
  return nullptr;
};
