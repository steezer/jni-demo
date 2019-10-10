#include "HelloWorld.h"  
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

//读取类文件
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

//从原始类数据的缓冲区中加载类
void testDefineClass(JNIEnv *env)
{
    int ifilecount=0;
    char *szDataIn=getClassContent("../demo/HelloWorld.class" , &ifilecount);
    if(szDataIn!=NULL){
        //定义类
        jclass test=(*env)->DefineClass(env, "HelloWorld", NULL, (const jbyte*)szDataIn, ifilecount);
        //释放类原始数据内存
        free(szDataIn);

        //实例化类并执行方法
        if(test!=NULL){
            printf("DefineClass success\n"); 
            jobject obj=(*env)->AllocObject(env, test);
            jmethodID showId=(*env)->GetMethodID(env, test, "show", "()V");
            if(showId!=NULL){
                (*env)->CallVoidMethod(env, obj, showId);
                printf("CallVoidMethod success\n"); 
            }
        }
    }
    printf("testDefineClass finished\n\n"); 
}

//该函数用于加载本地定义的类
void testFindClass(JNIEnv *env)
{
    jclass test=(*env)->FindClass(env, "Test");
    if(test!=NULL){
        //调用静态方法
        jmethodID powId=(*env)->GetStaticMethodID(env, test, "pow", "(DD)D");
        jdouble result=(*env)->CallStaticDoubleMethod(env, test, powId, 2.0, 4.0);
        printf("2^3: %lf\n", result);
        

        //不调用构造函数
        //jobject obj=(*env)->AllocObject(env, test);
        
        //调用构造函数
        jmethodID initId=(*env)->GetMethodID(env, test, "<init>", "(I)V");
        jobject obj=(*env)->NewObject(env, test, initId, 13L);

        //获取对象调用的方法
        jmethodID showId=(*env)->GetMethodID(env, test, "show", "()V");
        if(showId!=NULL){
            (*env)->CallVoidMethod(env, obj, showId);
            // (*env)->call
            printf("CallVoidMethod success\n"); 
        }
    }
    printf("testFindClass finished\n\n"); 
}

JNIEXPORT void JNICALL Java_HelloWorld_displayHelloWorld(JNIEnv *env, jobject obj)  
{
    //获取版本号
    int version=(*env)->GetVersion(env);
    printf("version:%d.%d\n", version>>16, version&0xffff);

    //从原始类数据的缓冲区中加载类
    testDefineClass(env);
    
    //调用其它类
    testFindClass(env);

    //调用本类
    jclass clazz=(*env)->GetObjectClass(env, obj);
    jmethodID sumId=(*env)->GetMethodID(env, clazz, "sum", "(II)I");
    jint total=(*env)->CallIntMethod(env, obj, sumId, 23, 45);
    printf("total: %d\n", total);

    //获取对象字段（可以是private）
    jfieldID nameId = (*env)->GetFieldID(env, clazz, "name", "Ljava/lang/String;");
    if(nameId!=NULL){
        jstring jstr = (*env)->GetObjectField(env, obj, nameId);
        const char *str = (*env)->GetStringUTFChars(env, jstr, NULL); 
        if (str != NULL) {
            printf("this.name = \"%s\"\n", str); 
            (*env)->ReleaseStringUTFChars(env, jstr, str); 
             jstring jstr = (*env)->NewStringUTF(env, "liming"); 
             if (jstr != NULL) {
                //设置对象字段
                (*env)->SetObjectField(env, obj, nameId, jstr); 
             } 
        } 
    }

    //获取静态字段（可以是private）
    jfieldID versionId = (*env)->GetStaticFieldID(env, clazz, "version", "I");
    if(versionId!=NULL){
        jint version = (*env)->GetStaticIntField(env, obj, versionId);
        printf("version: %d\n", version);
        //设置类字段
        (*env)->SetStaticIntField(env, clazz, versionId, 200);
    }

    printf("Call displayHelloWorld from c++ finished!\n\n"); 
}

//字符串的接受与返回
JNIEXPORT jstring JNICALL Java_HelloWorld_hello(JNIEnv *env, jobject obj, jstring contentStr) 
{
    //获取字符串指针，必须使用指针，不能使用char strContent[],因为GetStringUTFChars()返回值为const char *;
    const char *strContent = (*env)->GetStringUTFChars(env, contentStr, JNI_FALSE);
    char str[] = "欢迎你的到来！！";
 
    //字符串拼接,实现strContent+str1,因为strcat的第一个参数必须为非const类型(可变)，所以不能直接使用strcat()
    //创建一个新的字符串指针
    char *strTemp = (char *) malloc(strlen(strContent) + strlen(str) + 3);
    //拷贝常量到字符串指针
    strcpy(strTemp, strContent);
    //拼接str1到strTemp
    strcat(strTemp,": ");
    strcat(strTemp,str);
    
    //通知虚拟机平台相关代码无需再访问contentStr
    (*env)->ReleaseStringUTFChars(env, contentStr, strContent);
    printf("Call hello from c++ finished!\n\n"); 
    
    //返回一个utf的jstring
    return (*env)->NewStringUTF(env, strTemp);
}

