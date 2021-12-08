
ifdef win32
TARGET=hello
EXT=dll
LDFLAGS=-shared -fPIC -lstzc
else ifeq ($(shell uname),Darwin)
TARGET=libhello
EXT=jnilib
LDFLAGS=-shared -fPIC -lstzc
else
TARGET=libhello
EXT=so
LDFLAGS=-shared -fPIC -lstzc
endif

all: run

HelloWorld.class: lib/$(TARGET).$(EXT) HelloWorld.java
	@javac HelloWorld.java

lib/$(TARGET).$(EXT): lib/HelloWorldImpl.c Test.class
	gcc -std=c99 $(LDFLAGS)  -o lib/$(TARGET).$(EXT) lib/*.c

lib/HelloWorldImpl.c: lib/HelloWorld.h
Test.class: Test.java
	@javac Test.java

.PHONY: clean run

run: HelloWorld.class
	@java -Djava.library.path=lib:/usr/local/lib HelloWorld

clean:
	@rm -f lib/*.$(EXT) *.class
