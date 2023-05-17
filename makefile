EXE = producao
SRC = $(EXE).awk

all: $(EXE)

$(EXE): $(SRC)
	@ cp $< $@ && chmod +x $@
	@ echo "'$@' succesfully created!"

clean:
	@ rm -f $(EXE)

purge: clean

.PHONY: clean