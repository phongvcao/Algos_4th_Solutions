package com.company;
import edu.princeton.cs.algs4.*;

public class Main {

    public static void main(String[] args) {
        // write your code here
        FixedCapacityStackOfStrings s;
        s = new FixedCapacityStackOfStrings(100);
        while (!StdIn.isEmpty())
        {
            String item = StdIn.readString();

            if (!item.equals("-")) {
                s.push(item);
//                StdOut.println( "PUSHING IN: " + item );

            } else if (!s.isEmpty()) {
                StdOut.print(s.pop() + " ");
//                StdOut.println( "POPPING OUT: " + item );
            }

            if ( item.contains( "EOF" ) ) {
                break;
            }
        }
        StdOut.println("(" + s.size() + " left on stack)");
    }
}
