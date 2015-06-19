ROOTFLAGS=`root-config --cflags`
ROOTLIBDIR=`root-config --libdir`
ROOTLIBFLAGS=`root-config --libs`
ROOTLIBFLAGS+=-lHistPainter
ifneq ($(strip $(BOOST_INCLUDE)),)
INCLUDEFLAGS=-I$(BOOST_INCLUDE)
endif
ifneq ($(strip $(BOOST_LIB)),)
BOOSTLIBFLAGS=-L$(BOOST_LIB)
endif
BOOSTLIBFLAGS+=-L$(BOOST_LIB) -lboost_system$(BOOST_SUFFIX) -lboost_filesystem$(BOOST_SUFFIX) -lboost_program_options$(BOOST_SUFFIX)
GEOMLIBFLAG=-lGeom
GLIBFLAGS=`root-config --glibs`
INCLUDEFLAGS+=-Iinclude/
SRCDIR=src
INCDIR=include
LIBDIR=lib
BINDIR=bin
TESTDIR=test
COMPILERFLAGS+=-std=c++11 
COMPILERFLAGS+=-g
COMPILERFLAGS+=-fpermissive
LINKERFLAGS+=-Wl,--copy-dt-needed-entries

CXX := g++

COMP=$(CXX) $(COMPILERFLAGS) $(INCLUDEFLAGS)

LINK=$(CXX) $(LINKERFLAGS)

all: example.bin

# ROOT-related stuff
$(LIBDIR)/rootweb.o: $(SRCDIR)/rootweb.cpp $(INCDIR)/rootweb.hh
	$(COMP) $(ROOTFLAGS) -c -o $(LIBDIR)/rootweb.o $(SRCDIR)/rootweb.cpp

$(LIBDIR)/example.o: $(SRCDIR)/example.cpp
	$(COMP) $(ROOTFLAGS) -c $(SRCDIR)/example.cpp -o $(LIBDIR)/example.o

# Binary
example.bin: $(LIBDIR)/rootweb.o $(LIBDIR)/example.o 
	$(LINK)	$(LIBDIR)/rootweb.o $(LIBDIR)/example.o \
	$(ROOTLIBFLAGS) $(GLIBFLAGS) $(BOOSTLIBFLAGS) \
	-o example.bin 

#CLEANUP
cleanall:
	@rm -rf $(LIBDIR)/* example.bin

clean: cleanall

