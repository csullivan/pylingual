include ./Make.defaults
include ./Make.rules


SOURCES=main.cpp pylab.cpp #\
#	 pylab.cpp

OBJECTS=$(SOURCES:.cpp=.o )


all:	$(OBJECTS)
	$(LD) $(PY_LDFLAGS) $(LDFLAGS) $(BOOST_LDFLAGS) -o main $^
	@echo "VICTORY"


test:
	@echo $(INCDIR) $(PY_CFLAGS) $(CFLAGS) $(CPPFLAGS)

clean:
	rm -rf $(OBJECTS)
	rm -rf main 




