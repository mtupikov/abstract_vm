#ifndef COMMANDS_H
# define COMMANDS_H

#include "eOperandType.hpp"
#include <string>

enum commandType {
	Push,
	Assert,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Pow,
	Pop,
	Dump,
	Print,
	Exit
};

typedef struct {
	commandType		type;
	eOperandType	valueType;
	long double		value;
	std::string		strValue;
}					command;

#endif
