#include <iostream>
#include <list>
#include "../inc/Lexer.hpp"
#include "../inc/Parser.hpp"
#include "../inc/Exceptions.hpp"

int main(int argc, char **argv) {
	std::list<command> commands;
	OperandFactory::static_init();
	try {
		Lexer::checkForLexErrors(argc, argv, &commands);
	} catch (LexerException &e) {
		std::cout << e.what() << std::endl;
		return 0;
	} catch (TooManyArgsException &e) {
		std::cout << e.what() << std::endl;
		return 0;
	} catch (OpenFileException &e) {
		std::cout << e.what() << std::endl;
		return 0;
	} catch (std::out_of_range &e) {
		std::cout << e.what() << std::endl;
		return 0;
	}
	std::cout << "\nOUTPUT:\n" << std::endl;
	Parser::executeCommands(commands);
	return 0;
}