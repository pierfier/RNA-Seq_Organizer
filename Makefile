FLAGS = -g
SRC = experiment.cpp gene.cpp parsers.cpp main.cpp

all: data_org

data_org: $(SRC)
	g++ $(FLAGS) $(SRC) -o data_org
