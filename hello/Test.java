
class Test {
    private int version=0;

    public Test(int v){
        this.version=v;
    }

    public void show(){
        //错误测试
        int a=1;
        int b=5;
        int c=a/b;
        System.out.println("in java=> show version: "+this.version);
    }

    public static double pow(double base, double power){
        System.out.println("base: "+base+", power:"+power);
        return Math.pow(base, power);
    }

    public static void main(String[] args)  
    {
        System.out.println("java.library.path: ");
        System.out.println(System.getProperty("java.library.path"));
        Test test=new Test(10);
        test.show();
        int num=10;
        System.out.println("num: "+num);
    }
    
}
