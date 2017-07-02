#include "FunctionAST.h"
#include <memory>
#include <map>
#include <string>
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LegacyPassManager.h"
#include "../Logger.h"

using namespace llvm;

extern llvm::Function* getFunction(std::string name);

llvm::Function *FunctionAST::codegen() {
  extern std::unique_ptr<llvm::Module> TheModule;
  extern llvm::LLVMContext TheContext;
  extern llvm::IRBuilder<> Builder;
  extern std::map<std::string, llvm::Value *> NamedValues;
  extern std::unique_ptr<legacy::FunctionPassManager> TheFPM;
  extern std::map<std::string, std::unique_ptr<PrototypeAST>> FunctionProtos;
  auto &P = *Proto;
  FunctionProtos[Proto->getName()] = std::move(Proto);
  Function *TheFunction = getFunction(P.getName());
  if (!TheFunction) {
    return nullptr;
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
