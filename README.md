## Mac上编译jni操作步骤

### 第一步：编译java类，生成.class文件
*注：java文件中有声明为public native的方法*
javac HelloWorld.java

### 第二步：生成C头文件
javah HelloWorld

### 第三步：实现C头文件定义的方法，然后编译实现文件.c
*注：如果提示找不到jni.h头文件，需要在java的安装目录下查找jni.h文件所在目录，并将目录加入到include路径*
gcc -dynamiclib -o libhello.jnilib HelloWorld.c

## Linux上编译jni操作步骤
### 第一步：同上
### 第二步：同上
### 第三步：实现C头文件定义的方法，然后编译实现文件.c
### 注：如果提示找不到jni.h头文件，需要在java的安装目录下查找jni.h文件所在目录，并将目录加入到include路径
gcc -shared -fPIC -o libhello.jnilib HelloWorld.c

# JNI官方手册
https://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html

