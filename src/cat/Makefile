CC			:= gcc
NAME		:= fake_cat
SRC			:= $(NAME).c
HEADER		:= $(NAME).h

all: $(NAME) test leak style


fake_cat: $(SRC) $(HEADER)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)	

test: $(NAME)
	python3 ./test.py
leak: $(NAME)
	valgrind --tool=memcheck --leak-check=yes ./$(NAME)
style: $(NAME)
	clang-format -style=Google -n *.c *.h
clean:
	rm -rf *.o *.a
	rm -f $(NAME) *.o

rebuild: clean $(NAME)