#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

//#!: -ljvm

/**
 * 读取类文件（需要free）
 * @param  path 文件路径
 * @param  &len 获取到的文件长度
 * @return      文件内容指针
 */
static char *getClassContent(const char* path, int *len)
{
    FILE *fp = fopen(path, "rb");
    //读取原始文件长度
    fseek(fp, 0, SEEK_END);
    int ifilecount = ftell(fp);
    *len=ifilecount;
    if(ifilecount){
        //读取文件
        char *szDataIn=(char *)calloc(ifilecount, 1);
        szDataIn[0]='\0';
        fseek(fp, 0, SEEK_SET);
        fread(szDataIn, ifilecount, 1, fp);
        fclose(fp);
        return szDataIn;       
    }
    return NULL;
}

/**
 * 从原始类数据的缓冲区中加载类
 * @param  env       JVM环境
 * @param  classpath 类文件路径
 * @param  classname 类名
 * @return           成功类引用，失败NULL
 */
jclass loadClass(JNIEnv *env, const char* classpath, const char* classname)
{
    int ifilecount=0;
    char *szDataIn=getClassContent(classpath, &ifilecount);
    if(szDataIn!=NULL){
        //定义类
        jclass test=(*env)->DefineClass(env, classname, NULL, (const jbyte*)szDataIn, ifilecount);
        //释放类原始数据内存
        free(szDataIn);
        //实例化类并执行方法
        if(test!=NULL){
            printf("loadClass %s success\n", classname); 
            return test;
        }
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    JavaVM *jvm;
    JNIEnv *env;
    JavaVMInitArgs vm_args;
    
    //初始化参数
    JavaVMOption options[4];
    options[0].optionString = "-Djava.compiler=NONE";
    options[1].optionString = "-Djava.class.path=.";
    options[2].optionString = "-verbose:NONE";
    options[3].optionString = "-Djava.library.path=lib";
    
    JNI_GetDefaultJavaVMInitArgs(&vm_args);
    vm_args.version=JNI_VERSION_1_8;
    vm_args.options = options;
    vm_args.nOptions = 4;
    vm_args.ignoreUnrecognized = 1;

    //创建虚拟机
    JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);

    //获取虚拟机版本
    int version=(*env)->GetVersion(env);
    printf("version:%d.%d\n", version>>16, version&0xffff);

    //加载类
    jclass cls = loadClass(env, "HelloWorld.class", "HelloWorld");
    if(cls!=NULL){
        //调用对象方法
        jobject obj=(*env)->AllocObject(env, cls);
        jmethodID showId=(*env)->GetMethodID(env, cls, "show", "()V");
        if(showId!=NULL){
            (*env)->CallVoidMethod(env, obj, showId);
        }

        //调用静态方法
        jmethodID mid = (*env)->GetStaticMethodID(env, cls, "test", "(I)I");
        (*env)->CallStaticVoidMethod(env, cls, mid, 100);
    }

    //卸载虚拟机
    (*jvm)->DestroyJavaVM(jvm);

    return 0;
}
