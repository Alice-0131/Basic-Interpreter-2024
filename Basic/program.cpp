/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.hpp"



Program::Program() = default;

Program::~Program() = default;

void Program::clear() {
    // Replace this stub with your own code
    //todo
    source_line.clear();
    parsed_statement.clear();
}

void Program::addSourceLine(int lineNumber, const std::string &line) {
    // Replace this stub with your own code
    //todo
    if (parsed_statement.find(lineNumber) != parsed_statement.end()) {
        parsed_statement.erase(lineNumber);
    }
    source_line[lineNumber] = line;
}

void Program::removeSourceLine(int lineNumber) {
    // Replace this stub with your own code
    //todo
    if (source_line.find(lineNumber) != source_line.end()) {
        source_line.erase(lineNumber);
        delete parsed_statement[lineNumber];
        parsed_statement.erase(lineNumber);
    }
}

std::string Program::getSourceLine(int lineNumber) {
    // Replace this stub with your own code
    //todo
    if (source_line.find(lineNumber) != source_line.end()) {
        return source_line[lineNumber];
    } else {
        return "";
    }
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    // Replace this stub with your own code
    //todo
    if (parsed_statement.find(lineNumber) != parsed_statement.end()) {
        delete parsed_statement[lineNumber];
        parsed_statement[lineNumber] = stmt;
    } else {
        throw ErrorException("LINE NUMBER ERROR");
    }
}

//void Program::removeSourceLine(int lineNumber) {

Statement *Program::getParsedStatement(int lineNumber) {
   // Replace this stub with your own code
   //todo
    if (parsed_statement.find(lineNumber) != parsed_statement.end()) {
        return parsed_statement[lineNumber];
    } else {
        return nullptr;
    }
}

int Program::getFirstLineNumber() {
    // Replace this stub with your own code
    //todo
    if (source_line.empty()) {
        return -1;
    } else {
        return source_line.begin() -> first;
    }
}

int Program::getNextLineNumber(int lineNumber) {
    // Replace this stub with your own code
    //todo
    if (source_line.upper_bound(lineNumber) == source_line.end()) {
        return -1;
    } else {
        return source_line.upper_bound(lineNumber) -> first;
    }
}

//more func to add
//todo


