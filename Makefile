NAME = avm

CC = clang++

SRC_PATH = ./src/
INC_PATH = ./inc/

INC =   eOperandType.hpp \
        Exceptions.hpp \
        IOperand.hpp \
        Lexer.hpp \
        Operand.hpp \
        OperandFactory.hpp \
        Parser.hpp \
        Commands.hpp \

SRC =	main.cpp \
        Lexer.cpp \
        OperandFactory.cpp \
        Parser.cpp \

OBJ = $(SRC:.cpp=.o)
OBJ_DIR = obj
OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ_SRC)
	$(CC) -std=c++11 -Wall -Werror -Wextra $(OBJ_SRC) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_PATH)%.cpp
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) -std=c++11 -Wall -Werror -Wextra -I$(INC_PATH) -c -o $@ $<

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all