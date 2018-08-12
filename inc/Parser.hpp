#ifndef ABSTRACT_VM_PARSER_HPP
#define ABSTRACT_VM_PARSER_HPP


#include <list>
#include <forward_list>
#include "Commands.hpp"
#include "IOperand.hpp"
#include "../inc/OperandFactory.hpp"
#include <math.h>
#include <sstream>

class Parser {
public:
	static void									executeCommands(std::list<command> commands);
private:
	Parser();
	~Parser();
	Parser(const Parser&);
	const										Parser &operator=(const Parser&);
	static void									checkValue(const command &cmd);
	static void									push(const command &cmd);
	static void									pop();
	static void									dump();
	static void									assert(const command &cmd);
	static void									add();
	static void									sub();
	static void									mul();
	static void									div();
	static void									mod();
	static void									pow();
	static void									sqrt();
	static void									min();
	static void									max();
	static void									clear();
	static void									print();
	static void 								checkForEmptyStack();
	static void 								checkForEqualTypes(const IOperand *op1, const IOperand *op2);

	static std::forward_list<const IOperand *>	_operands;
};


#endif
