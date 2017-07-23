CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	lsort

all:		$(TARGETS)

# TODO: Add rules for liblist.a, test_node, test_list, lsort, and any intermediate objects

node.o: node.c node.h list.h
	@echo Compiling node.o...
	@$(CC) $(CFLAGS) -fPIC -c -o $@ $<

list.o: list.c node.h list.h
	@echo Compiling list.o...
	@$(CC) $(CFLAGS) -fPIC -c -o $@ $<

test_node.o: test_node.c node.h list.h
	@echo Compiling test_node.o...
	@$(CC) $(CFLAGS) -fPIC -c -o $@ $<

test_list.o: test_list.c node.h list.h
	@echo Compiling test_list.o...
	@$(CC) $(CFLAGS) -fPIC -c -o $@ $<

lsort.o: lsort.c node.h list.h
	@echo Compiling lsort.o...
	@$(CC) $(CFLAGS) -fPIC -c -o $@ $<

liblist.a:	node.o list.o
	@echo Linking liblist.a...
	@$(AR) $(ARFLAGS) $@ $^ 

test_node:	test_node.o liblist.a 
	@echo Linking test_node...
	@$(LD) $(LDFLAGS) -o $@ $^

test_list:	test_list.o liblist.a
	@echo Linking test_list...
	@$(LD) $(LDFLAGS) -o $@ $^

lsort: lsort.o liblist.a
	@echo Linking lsort...
	@$(LD) $(LDFLAGS) -o $@ $^

measure.o: measure.c
	$(CC) $(CCFLAGS) -c -o $@ $^

test:		test-node test-list test-lsort

test-node:	test_node
	@echo Testing node...
	@[ `valgrind --leak-check=full ./test_node 2>&1 | tee test_node.log | grep ERROR | awk '{print $$4}'` = 0 ] || cat test_node.log

test-list:	test_list
	@echo Testing list...
	@[ `valgrind --leak-check=full ./test_list 2>&1 | tee test_list.log | grep ERROR | awk '{print $$4}'` = 0 ] || cat test_list.log

test-lsort:	lsort test_lsort.sh
	@echo Testing lsort...
	@./test_lsort.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) test_node test_list *.a *.o *.log *.input

.PHONY:		all test test-node test-list test-lsort clean


