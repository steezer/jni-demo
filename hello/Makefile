HelloWorld.class: lib/libhello.so HelloWorld.java
	@javac HelloWorld.java

lib/libhello.so: lib/HelloWorldImpl.c Test.class
	@gcc -shared -fPIC  -o lib/libhello.so lib/*.c

lib/HelloWorldImpl.c: lib/HelloWorld.h
Test.class: Test.java
	@javac Test.java

.PHONY: clean run

run: HelloWorld.class
	@java -Djava.library.path=lib HelloWorld

clean:
	@rm -f lib/*.jnilib lib/*.so *.class
