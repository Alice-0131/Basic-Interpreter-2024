/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.hpp"

#include <utility>


/* Implementation of the Statement class */

int stringToInt(std::string str);

Statement::Statement() = default;

Statement::~Statement() = default;

//todo
RenStmt::RenStmt() = default;
void RenStmt::execute(EvalState &state, Program &program) {}

LetStmt::LetStmt(int val, std::string var) :val(val), var(std::move(var)){}
void LetStmt::execute(EvalState &state, Program &program) {
 state.setValue(var, val);
}

PrintStmt::PrintStmt(int val) : val(val){}
void PrintStmt::execute(EvalState &state, Program &program) {
 std::cout << val << std::endl;
}

InputStmt::InputStmt(std::string var, int val) : val(val), var(std::move(var)) {}
void InputStmt::execute(EvalState &state, Program &program) {
 state.setValue(var, val);
}








