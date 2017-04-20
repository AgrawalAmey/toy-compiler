# Make file for lexer

test_lexer:
	gcc create_token.c get_stream.c remove_comments.c \
	patterns.c get_tokens.c ./tests/test_lexer.c ../../utils/keyword.c \
	../../utils/token.c -o ./bin/test_lexer.exe