#include <iostream>
#include <string>
#include <cmath>
#include "stack.cpp"
using namespace std;

enum preced { PCPAR = 0, PADD = 10, PMULT = 15, PEXP = 20, PSIGN = 25, POPAR = 30 };
enum symbolType { UNKNOWN = 0, OPERATOR, OPERAND };
enum Operators { CPAR = ')', ADD = '+', SUB = '-', MULT = '*', DIV = '/', EXP = '^', OPAR = '(' };

int symbolType (char symbol) {
	if (symbol == ADD || symbol == SUB || symbol == MULT || symbol == EXP || symbol == DIV || symbol == OPAR) return OPERATOR;
	else if (symbol >= '1' && symbol <= '9' || symbol == '.' || symbol == '0') return OPERAND;
	else return UNKNOWN;
}

// the next two functions handle the associativity of the operators
int inPrecValue (char input) {
	if (input == ADD || input == SUB) return PADD;
	else if (input == MULT || input == DIV) return PMULT;
	else if (input == EXP) return PEXP;
	else if (input == OPAR) return PCPAR;
}

int outPrecValue (char input) {
	if (input == ADD || input == SUB) return PADD;
	else if (input == MULT || input == DIV) return PMULT;
	else if (input == EXP) return PEXP;
	else if (input == OPAR) return POPAR;
}

void toPostfix (string infix, string &postfix) {
	Stack<char> s;
	string temp = "";

	/* 1+2*3-(4/5+6^7^8) */
	s.empty ();
	for (size_t i = 0; i < infix.size (); i++) {
		if (symbolType(infix[i]) == OPERATOR) temp += " ";
		if (symbolType(infix[i]) == OPERAND) {
			temp += infix[i];
		}

		else if (symbolType (infix[i]) == OPERATOR && infix[i] != '^') {
			if (s.isEmpty () || outPrecValue (infix[i]) > inPrecValue (s.peek ()))
				s.push (infix[i]);
			else {
				while (!s.isEmpty () && outPrecValue (infix[i]) <= inPrecValue (s.peek ())) {
					temp += " ";
					temp += s.pop ();
				}
				s.push (infix[i]);
			}
		}

		else if (infix[i] == '^') {
			if (s.isEmpty () || outPrecValue (infix[i]) >= inPrecValue (s.peek ()))
				s.push (infix[i]);
			else {
				while (!s.isEmpty () && outPrecValue (infix[i]) < inPrecValue (s.peek ())) {
					temp += " ";
					temp += s.pop ();
				}
				s.push (infix[i]);
			}
		}

		else if (infix[i] == ')') {
			while (s.peek () != '(') {
				temp += " ";
				temp += s.pop ();

				if (s.isEmpty ()) {
					cout << "Invalid Expression." << endl;
				}
			}
			s.pop ();
		}
	}

	while (!s.isEmpty ()) {
		if (s.peek () == '(') {
			cout << "Invalid Expression." << endl;
			system ("pause");
			exit (1);
		}
		temp += " ";
		temp += s.peek ();
		
		s.pop ();
	}
	postfix = temp;
}

void removeWhiteSpaces(string &infix){
	string temp = "";
	for (size_t i = 0; i < infix.size (); i++) {
		if (infix[i] != '\n' && infix[i] != '\t' && infix[i] != ' ')
			temp += infix[i];
	}
	infix = temp;
}

bool isWhiteSpace (char symbol) {
	if (symbol == '  ' || symbol == '\n' || symbol == '\t') return true;
	else return false;
}

double evaluate (string postfix) {
	Stack<double> result;

	for (size_t i = 0; i < postfix.size (); i++) {
		if (isWhiteSpace (postfix[i])) continue;
		else if (symbolType (postfix[i]) == OPERATOR) {
			double oprnd2 = result.pop ();
			double oprnd1 = result.pop ();
			double tmp = 0;

			switch (postfix[i]) {
				case ADD: {
					tmp = oprnd1 + oprnd2;
					break;
				}
				case SUB: {
					tmp = oprnd1 - oprnd2;
				}
				case MULT: {
					tmp = oprnd1 * oprnd2;
					break;
				}
				case DIV: {
					tmp = oprnd1 / oprnd2;
				}
				case EXP: {
					tmp = pow (oprnd1, oprnd2);
				}
				default:
					break;
			}
			result.push (tmp);
		}
		else if (symbolType (postfix[i]) == OPERAND) {
			// double oprnd = 0;
			string tmp = "";
			while (i < postfix.size () && symbolType (postfix[i]) == OPERAND) {
				tmp += postfix[i];
				i++;
			}
			i--;
			result.push (stod (tmp));
		}
	}
	return result.pop ();
}

int main () {
	Stack<char> s;
	string infix, postfix;
	cout << "Please enter the infix expression below." << endl;
	cout << "	>";
	getline (cin, infix);
	
	removeWhiteSpaces (infix);
	toPostfix (infix, postfix); //	1+2*3-(4/5+6^7^8)
	cout << postfix << endl;

	double result = evaluate (postfix);
	cout << "Result = " << result << endl;

	system ("pause");
	return 0;
}