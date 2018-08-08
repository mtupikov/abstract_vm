#ifndef EXCEPTIONS_H
# define EXCEPTIONS_H

#include <iostream>
#include <exception>

class OverflowException : std::overflow_error {
public:
	explicit OverflowException(const std::string &__arg):
	overflow_error(__arg),
	_msg(__arg) {}

	virtual const char *what() const throw() override {
		return _msg.c_str();
	}
private:
	std::string		_msg;
};

class UnderflowException : std::underflow_error {
public:
	explicit UnderflowException(const std::string &__arg):
	underflow_error(__arg),
	_msg(__arg) {}

	virtual const char *what() const throw() override {
		return _msg.c_str();
	}
private:
	std::string		_msg;
};

class DivisionByZeroException : std::exception {
public:
	virtual const char *what() const throw() override {
		return "Division by zero";
	}
};

class TooManyArgsException : std::exception {
public:
	virtual const char *what() const throw() override {
		return "Too many arguments";
	}
};

class OpenFileException : std::exception {
public:
	virtual const char *what() const throw() override {
		return "Cannot open a file";
	}
};

class EmptyStackException : std::exception {
public:
	virtual const char *what() const throw() override {
		return "Stack is empty";
	}
};

class TypesAreNotEqualException : std::exception {
public:
	virtual const char *what() const throw() override {
		return "Types of variables are not equal";
	}
};

class AssertException : std::exception {
public:
	virtual const char *what() const throw() override {
		return "Values in assert are not equal";
	}
};

class NotInt8Exception : std::exception {
public:
	virtual const char *what() const throw() override {
		return "Values isn't int8, cannot print";
	}
};

class LexerException : std::exception {
public:
	virtual const char *what() const throw() override {
		return "Cannot run commands, lexer error(s)";
	}
};

class PrecisionInIntTypeException : std::exception {
public:
	virtual const char *what() const throw() override {
		return "Int(*) cannot contain a precision (.)";
	}
};

#endif
