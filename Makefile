include ../Make.defaults
include ../Make.rules

SOURCES = main.o

all: main

main: $(HWOBJS)
	$(LD) -o $@ $^ $(PY_LDFLAGS) $(LDFLAGS) $(BOOST_LDFLAGS)

clean:
	rm -rf $(HWOBJS) main




