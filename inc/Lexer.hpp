#ifndef ABSTRACT_VM_LEXER_HPP
#define ABSTRACT_VM_LEXER_HPP

#include <string>
#include <list>
#include "Commands.hpp"
#include <regex>

class Lexer {
public:
	static void checkForLexErrors(int argc, char **argv, std::list<command> *list);
private:
	static bool							checkInput(std::string s, std::list<command> *list);
	static void							readFromFile(std::list<command> *list, char *filename);
	static void							readFromStdIn(std::list<command> *list);
	static void							createCommand(std::list<command> *list,
										const std::array<std::regex, 24> &regex,
										std::string &item);
	static const std::string			&trim(std::string &s);
	};


#endif
