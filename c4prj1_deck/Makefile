CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99
OBJS=cards.o deck.o eval.o

test-eval: deck.o eval.o cards.o test.c
	gcc $(CFLAGS) -o test test.c $(OBJS)

deck.o: deck.c
	gcc $(CFLAGS) -c deck.c

eval.o: eval.c
	gcc $(CFLAGS) -c eval.c

cards.o: cards.c
	gcc $(CFLAGS) -c cards.c

clean:
	rm -f test *.o *~
