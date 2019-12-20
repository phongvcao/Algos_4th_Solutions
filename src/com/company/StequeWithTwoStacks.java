package com.company;
import edu.princeton.cs.algs4.*;

public class StequeWithTwoStacks< Item > {

    private Stack< Item > headStack;
    private Stack< Item > tailStack;

    public StequeWithTwoStacks() {
        headStack = new Stack< Item >();
        tailStack = new Stack< Item >();
    }

    public void push( Item item ) {
        headStack.push( item );
    }

    public Item pop() {
        if ( headStack.isEmpty() ) {
            while ( ! tailStack.isEmpty() ) {
                headStack.push( tailStack.pop() );
            }
        }

        return headStack.pop();
    }

    public void enqueue( Item item ) {
        tailStack.push( item );
    }

    public boolean isEmpty() {
        return headStack.isEmpty() && tailStack.isEmpty();
    }

    public int size() {
        return headStack.size() + tailStack.size();
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        StequeWithTwoStacks< String > steque = new StequeWithTwoStacks< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            steque.push( strArr[ i ] );
            steque.enqueue( strArr[ i ] );
        }

        StdOut.println( "DEBUG: size: " + steque.size() );

        while ( ! steque.isEmpty() ) {
            StdOut.println( "DEBUG: " + steque.pop() );
        }
    }
}
