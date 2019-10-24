CC = gcc
EXE = 

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o $(EXE)

$(EXE) : % : %.o generacion.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o generacion.o


asm:
	for element in $(EXE); do \
		./$$element $$element.asm ; \
	done
