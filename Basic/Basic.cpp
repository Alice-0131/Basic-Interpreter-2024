/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.hpp"
#include "parser.hpp"
#include "program.hpp"
#include "Utils/error.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"


/* Function prototypes */

void processLine(std::string line, Program &program, EvalState &state);

/* Main program */

int main() {
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            std::string input;
            getline(std::cin, input);
            if (input.empty())
                continue;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            std::cout << ex.getMessage() << std::endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(std::string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);

    //todo
    std::string token = scanner.nextToken();
    if (scanner.getTokenType(token) == NUMBER) { // a program line
        int lineNumber = stringToInteger(token);
        if (scanner.hasMoreTokens()) {
            program.addSourceLine(lineNumber, line);
        } else {
            program.removeSourceLine(lineNumber);
        }
    } else { // BASIC command
        if (token == "RUN") {
            int current = program.getFirstLineNumber();
            while (current != -1) {
                scanner.setInput(program.getSourceLine(current));
                scanner.nextToken();
                std::string command = scanner.nextToken();
                if (command == "LET") {
                    Expression* exp = parseExp(scanner);
                    try {
                        exp -> eval(state);
                        delete exp;
                    }
                    catch (ErrorException &ex) {
                        delete exp;
                        throw;
                    }
                } else if (command == "PRINT") {
                    Expression* exp = parseExp(scanner);
                    try {
                        PrintStmt print_stmt(exp->eval(state));
                        print_stmt.execute(state, program);
                        delete exp;
                    }
                    catch (ErrorException &ex) {
                        delete exp;
                        throw;
                    }
                } else if (command == "INPUT") {
                    std::string var = scanner.nextToken();
                    std::cout << " ? ";
                    std::string val;
                    while (true) {
                        try {
                            getline(std::cin, val);
                            int num = stringToInteger(val);
                            InputStmt input_stmt(var, num);
                            input_stmt.execute(state, program);
                            break;

                        }
                        catch(ErrorException &ex) {
                            std::cout << "INVALID NUMBER\n ? ";
                        }
                    }
                } else if (command == "END") {
                    break;
                } else if (command == "GOTO") {
                    int next = stringToInteger(scanner.nextToken());
                    if (program.getSourceLine(next).empty()) {
                        std::cout << "LINE NUMBER ERROR\n";
                        current = program.getNextLineNumber(current);
                    } else {
                        current = next;
                    }
                } else if (command == "IF") {
                    std::string exp = scanner.nextToken();
                    std::string tmp;
                    std::string op;
                    bool flag = false;
                    while (scanner.hasMoreTokens()) {
                        tmp = scanner.nextToken();
                        if (tmp == "=" || tmp == ">" || tmp == "<") {
                            op = tmp;
                            break;
                        } else {
                            exp += tmp;
                        }
                    }
                    TokenScanner exp_scanner;
                    exp_scanner.ignoreWhitespace();
                    exp_scanner.scanNumbers();
                    exp_scanner.setInput(exp);
                    Expression* lhs = parseExp(exp_scanner);
                    exp.clear();
                    while (scanner.hasMoreTokens()) {
                        tmp = scanner.nextToken();
                        if (tmp == "THEN") {
                            break;
                        } else {
                            exp += tmp;
                        }
                    }
                    exp_scanner.setInput(exp);
                    Expression* rhs = parseExp(exp_scanner);
                    if (op == "=") {
                        if (lhs -> eval(state) == rhs -> eval(state)) {
                            flag = true;
                        }
                    } else if (op == "<") {
                        if (lhs -> eval(state) < rhs -> eval(state)) {
                            flag = true;
                        }
                    } else if (op == ">") {
                        if (lhs -> eval(state) > rhs -> eval(state)) {
                            flag = true;
                        }
                    }
                    if (flag) {
                        int next = stringToInteger(scanner.nextToken());
                        if (program.getSourceLine(next).empty()) {
                            std::cout << "LINE NUMBER ERROR\n";
                            current = program.getNextLineNumber(current);
                        } else {
                            current = next;
                        }
                    } else {
                        current = program.getNextLineNumber(current);
                    }
                    delete lhs;
                    delete rhs;
                }
                if (command != "GOTO" && command != "IF") {
                    current = program.getNextLineNumber(current);
                }
            }
        } else if (token == "LIST") {
            int current = program.getFirstLineNumber();
            while (current!= -1) {
                std::cout << program.getSourceLine(current) << std::endl;
                current = program.getNextLineNumber(current);
            }
        } else if (token == "CLEAR") {
            program.clear();
            state.Clear();
        } else if (token == "QUIT") {
            exit(0);
        } else if (token == "LET") {
            Expression* exp = parseExp(scanner);
            try {
                exp -> eval(state);
                delete exp;
            }
            catch (ErrorException &ex) {
                delete exp;
                throw;
            }
        } else if (token == "INPUT") {
            std::string var = scanner.nextToken();
            std::cout << " ? ";
            std::string val;
            while (true) {
                try {
                    getline(std::cin, val);
                    int num = stringToInteger(val);
                    InputStmt input_stmt(var, num);
                    input_stmt.execute(state, program);
                    break;

                }
                catch(ErrorException &ex) {
                    std::cout << "INVALID NUMBER\n ? ";
                }
            }
        } else if (token == "PRINT") {
            Expression* exp = parseExp(scanner);
            try {
                PrintStmt print_stmt(exp->eval(state));
                print_stmt.execute(state, program);
                delete exp;
            }
            catch (ErrorException &ex) {
                delete exp;
                throw;
            }
        } else {
            throw ErrorException("SYNTAX ERROR");
        }
    }
}

