
class Test {
    private int version=0;

    public Test(int v){
        this.version=v;
    }

    public void show(){
        System.out.println("in java=> show version: "+this.version);
    }

    public static double pow(double base, double power){
        System.out.println("base: "+base+", power:"+power);
        return Math.pow(base, power);
    }

    public static void main(String[] args)  
    {
        Test test=new Test(10);
        test.show();
        int num=10;
        System.out.println("num: "+num);
    }
    
}
