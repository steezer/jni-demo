HelloWorld.class: lib/libhello.jnilib HelloWorld.java
	@javac HelloWorld.java

lib/libhello.jnilib: lib/HelloWorldImpl.c Test.class
	@gcc -dynamiclib -o lib/libhello.jnilib lib/*.c

lib/HelloWorldImpl.c: lib/HelloWorld.h
Test.class: Test.java
	@javac Test.java

.PHONY: clean run

run: HelloWorld.class
	@java -Djava.library.path=lib HelloWorld

clean:
	@rm -f lib/*.jnilib lib/*.so *.class
