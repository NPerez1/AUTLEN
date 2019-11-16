CC = gcc
CFLAGS = -Wall -g -pedantic
EXE = ejemplo 

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o *.dot *.pdf $(EXE)

$(EXE) : % : %.o afnd.o transforma.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o afnd.o transforma.o

afnd.o : afnd.c afnd.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

transforma.o : transforma.c transforma.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

runv:
	valgrind -q --leak-check=yes --tool=memcheck ./ejemplo