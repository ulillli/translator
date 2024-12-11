#pragma once
#include "lexicalAnalyzer.h"
#include "syntaxAnalyzer.h"
#include "translator.h"
#include "calculator.h"

class workWithExpression {
public:
	void printVectorOfTerm(std::vector<Term*> v) {
		for (int i = 0; i < v.size(); i++) {
			Term* curr = v[i];
			if (dynamic_cast<Number*>(curr)) {
				std::cout << dynamic_cast<Number*>(curr)->getData();
			}
			if (dynamic_cast<Variable*>(curr)) {
				std::cout << dynamic_cast<Variable*>(curr)->getName();
			}
			if (dynamic_cast<Bracket*>(curr) && dynamic_cast<Bracket*>(curr)->getFlag() == 0) std::cout << "(";
			if (dynamic_cast<Bracket*>(curr) && dynamic_cast<Bracket*>(curr)->getFlag() == 1) std::cout << ")";
			if (dynamic_cast<BinaryFunction*>(curr)) {
				if (dynamic_cast<BinaryFunction*>(curr)->getFunc() == ADD) std::cout << "+";
				if (dynamic_cast<BinaryFunction*>(curr)->getFunc() == SUB) std::cout << "-";
				if (dynamic_cast<BinaryFunction*>(curr)->getFunc() == DIV) std::cout << "/";
				if (dynamic_cast<BinaryFunction*>(curr)->getFunc() == MUL) std::cout << "*";
			}
			if (dynamic_cast<UnaryFunction*>(curr)) {
				if (dynamic_cast<UnaryFunction*>(curr)->getFunc() == SIN) std::cout << "SIN";
				if (dynamic_cast<UnaryFunction*>(curr)->getFunc() == EXP) std::cout << "EXP";
			}
		}
		std::cout << std::endl;
	}
	double forTests(std::string str) {
		syntaxAnalyzer S;
		lexicalAnalyzer L;
		std::vector<Term*> v = L.getVectorOfTerms(str);
		if (S.correctly(v)) {
			translator T;
			std::vector<Term*> t = T.getPostfix(v);
			return calculator().calculate(t);
		}
		else throw "Expression is not correctly\n";
	}
	void Expression() {
			std::string str;
			syntaxAnalyzer S;
			lexicalAnalyzer L;
			std::cin >> str;
			std::vector<Term*> v = L.getVectorOfTerms(str);
			//printVectorOfTerm(v);
			while (S.correctly(v) == 0) {
				std::cout << "Expression is not correctly, input a new expression\n";
				std::cin >> str;
				v = L.getVectorOfTerms(str);
				if (str == "stop") {
					break;
				}
			}
			//v = L.getVectorOfTerms(str);
			translator T;
			std::vector<Term*> t = T.getPostfix(v);
			printVectorOfTerm(t);
			for (int i = 0; i < t.size(); i++) {
				if (dynamic_cast<Variable*>(t[i])) {
					double x;
					std::cout << dynamic_cast<Variable*>(t[i])->getName() << "=";
					std::cin >> x;
					dynamic_cast<Variable*>(t[i])->setData(x);
				}
			}
			calculator C;
			double res = C.calculate(t);
			std::cout << res;
	}
};
