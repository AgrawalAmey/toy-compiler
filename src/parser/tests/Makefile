# Make file for parser

compile:
	gcc create_parse_table.c create_parse_tree.c find_first_recursive.c read_ff.c \
	read_grammer.c ../../utils/stack.c ../../utils/tree.c ../../utils/token.c \
	-o ./bin/parser.exe

test_grammer:
	gcc ./tests/test_grammer.c read_grammer.c  ../../utils/token.c -o ./bin/test_grammer.exe

test_read_ff:
		gcc ./tests/test_read_ff.c read_ff.c  ../../utils/token.c -o ./bin/test_read_ff.exe

test_find_ff:
	gcc ./tests/test_find_ff.c find_first_and_follow.c  read_grammer.c \
	find_first.c find_follow.c ../../utils/token.c -o ./bin/test_find_ff.exe

test_parse_table:
	gcc create_parse_table.c find_first_and_follow.c  read_ff.c \
	read_grammer.c find_first.c find_follow.c find_first_recursive.c \
	../../utils/token.c  ./tests/test_parse_table.c -o ./bin/test_parse_table.exe

test_parse_tree:
	gcc -g create_parse_tree.c create_parse_table.c find_first_and_follow.c \
	read_grammer.c find_first.c find_follow.c find_first_recursive.c \
	../lexer/create_token.c ../lexer/get_stream.c ../lexer/get_tokens.c \
	../lexer/patterns.c ../lexer/remove_comments.c  read_ff.c \
	../../utils/token.c ../../utils/keyword.c  ../../utils/tree.c \
	../../utils/stack.c  ./tests/test_parse_tree.c \
	../../utils/token_to_symbol.c -o ./bin/test_parse_tree.exe
