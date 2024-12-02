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

            }
        } else if (token == "LIST") {
            int current = program.getFirstLineNumber();
            while (current!= -1) {
                std::cout << program.getSourceLine(current) << std::endl;
                current = program.getNextLineNumber(current);
            }
        } else if (token == "CLEAR") {
            program.clear();
        } else if (token == "QUIT") {
            exit(0);
        } else if (token == "HELP") {

        } else if (token == "LET") {
            std::string var = scanner.nextToken();
            scanner.nextToken();
            if (var == "LET") {
                throw ErrorException("SYNTAX ERROR");
            }
        } else if (token == "INPUT") {
            std::string var;
            std::cin >> var;

        } else if (token == "PRINT") {
            //PrintStmt print_stmt;
            Expression* exp = parseExp(scanner);
            int value = exp->eval(state);
            std::cout << value << std::endl;
        } else {
            throw ErrorException("SYNTAX ERROR");
        }
    }
}

