package org.gorway;

import java.util.List;

public class TestInnerClass {
    public TestInnerClass() {
        Inner s1 = new Inner();
        s1.a = 10;
        Inner s2 = new Inner();
        s2.a = 20;
        TestInnerClass.Inner s3 = new TestInnerClass.Inner();
        System.out.println(s3.a);
    }

    class Inner {
        public int a = 5;
    }

    public static void main(String[] args) {
        TestInnerClass t = new TestInnerClass();
        Inner inner = t.new Inner();
        System.out.println(inner.a);
    }
}
