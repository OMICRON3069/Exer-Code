package com.easybuy.test;

public class GetClassUser {
    public static void main(String[] args) throws ClassNotFoundException {
        Class cls = Class.forName("com.easybuy.entity.User");

        Package pkg = cls.getPackage();

        System.out.println("The path of "+cls.getSimpleName()+" is "+pkg.getName());

        Class superclass = cls.getSuperclass();

        System.out.println("SuperClass of " + cls.getSimpleName()+" is " + superclass.getName());

        System.out.println("Powered by 许力升 计算机2班");

    }
}
