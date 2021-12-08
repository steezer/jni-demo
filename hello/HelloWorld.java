class HelloWorld {
    private String name="springs";
    public static int version=4;
      
    //本地化函数声明，只声明不定义，main函数里直接调用  
    public native void displayHelloWorld();  
    public native String hello(String name);
    public native String[] md5(String[] strs);
      
    static {
        //加载C模块，window下是hello.dll文件，mac下是libhello.jnilib文件  
        //由下面的操作生成  
        System.loadLibrary("hello");
    }
    
    public int sum(int a, int b){
        return a+b;
    }
      
    public static void main(String[] args) {
        
        System.out.print("java.library.path: ");
        System.out.println(System.getProperty("java.library.path"));
        
        //调用上面声明的本地化方法  
        HelloWorld helloWorld=new HelloWorld();

        //调用native方法：不带参数和返回值
        helloWorld.displayHelloWorld();  

        //调用native方法：字符串参数传递与返回
        System.out.println(helloWorld.hello("谢春平"));

        //测试jni改变后的属性
        System.out.println("HelloWorld.version: "+ HelloWorld.version);
        System.out.println("helloWorld.name: "+ helloWorld.name);

        //数组传递测试
        String strs[]=new String[3];
        strs[0]="hello";
        strs[1]="world";
        strs[2]="help";
        String[] array=helloWorld.md5(strs);
        for (String str : array) {
            System.out.println(str);
        }
        for (String str : strs) {
            System.out.println(str);
        }
    }
    
}
