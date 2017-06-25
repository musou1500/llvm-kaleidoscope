#include "NumberExprAST.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"

llvm::Value *NumberExprAST::codegen() {
  extern llvm::LLVMContext TheContext;
  return llvm::ConstantFP::get(TheContext, llvm::APFloat(Val));
}
