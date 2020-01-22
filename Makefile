#
# GNU makefile for fastclsuster demo program
#============================================


# compiler options
#--------------------------------------------
CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lstdc++

# project files
#--------------------------------------------
PROGRAM = hclust-demo
OBJECTS = demo.o fastcluster.o
TGZDIR = hclust-cpp


# rules
#--------------------------------------------
all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $+ $(LDFLAGS)

# generic rule for compiling *.cpp -> *.o
%.o: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $*.cpp

clean:
	rm -f $(PROGRAM) $(OBJECTS)

tgz:
	ln -s . $(TGZDIR)
	tar cvzf $(TGZDIR).tgz \
		$(TGZDIR)/*.cpp $(TGZDIR)/*.h $(TGZDIR)/*.csv $(TGZDIR)/*.r \
		$(TGZDIR)/README.md $(TGZDIR)/LICENSE $(TGZDIR)/Makefile $(TGZDIR)/CHANGES
	rm $(TGZDIR)
