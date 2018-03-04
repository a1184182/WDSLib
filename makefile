IDIR =./include
CC=g++
CFLAGS=-I$(IDIR)
RM = rm -f

ODIR=../obj
LDIR =../lib/LinuxLib
LFLAGS=-L$(LDIR)


LIBS=-lcxsparse -lepanet2 

_DEPS = cs.h ELVA.h epanet2.h Flag.h GGAsolver.h Input.h Matrix.h Net.h node.h Parameter.h pipe.h RCTMsolver.h result.h Simulation.h solver.h SuiteSparse_config.h topology.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ELVA.o Flag.o GGAsolver.o Input.o Matrix.o Net.o node.o Parameter.o pipe.o RCTMsolver.o result.o Simulation.o solver.o topology.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

ARCHIVE = $(AR) $(ARFLAGS)

NetSolver:
	( cd Network && $(MAKE))
	( cd Network/Edge/PIPES && $(MAKE))
	( cd Network/Vertex/NODE && $(MAKE))
	( cd Network/Geometry && $(MAKE))
	( cd Simulation && $(MAKE))
	( cd math && $(MAKE))
	( cd IO && $(MAKE))
	( cd hydraulic && $(MAKE))
	( cd hydraulic/GGA && $(MAKE))
	( cd hydraulic/RCTM && $(MAKE))
	( cd obj && ar -x $(LDIR)/libepanet2.a)
	( cd obj && ar -x $(LDIR)/libcxsparse.a)
	( cd lib && $(ARCHIVE) libWDSLib.a $(OBJ) $(ODIR)/*.o)

	$(CC) -o $@ NetSolver.cc -Llib -lWDSLib -O3 -std=c++11 

clean:
	$(RM) *.o
