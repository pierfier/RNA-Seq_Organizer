FLAGS = -g
SRC = experiment.cpp gene.cpp parsers.cpp main.cpp
ARGS = -c config -ol -pol overlap.csv

all: data_org

data_org: $(SRC)
	g++ $(FLAGS) $(SRC) -o data_org

debug:
	valgrind ./data_org $(ARGS)

run:
	./data_org $(ARGS)
