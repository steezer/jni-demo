ifeq ($(shell uname),Darwin)
EXT=jnilib
LDFLAGS=-dynamiclib
else
EXT=so
LDFLAGS=-shared -fPIC
endif


HelloWorld.class: lib/libhello.$(EXT) HelloWorld.java
	@javac HelloWorld.java

lib/libhello.$(EXT): lib/HelloWorldImpl.c Test.class
	@gcc $(LDFLAGS)  -o lib/libhello.$(EXT) lib/*.c

lib/HelloWorldImpl.c: lib/HelloWorld.h
Test.class: Test.java
	@javac Test.java

.PHONY: clean run

run: HelloWorld.class
	@java -Djava.library.path=lib HelloWorld

clean:
	@rm -f lib/*.$(EXT) *.class
