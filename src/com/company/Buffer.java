package com.company;
import edu.princeton.cs.algs4.*;

public class Buffer {

    private Stack< String > leftStack;
    private Stack< String > rightStack;

    public Buffer() {
        leftStack = new Stack< String >();
        rightStack = new Stack< String >();
    }

    public void insert( char c ) {
        leftStack.push( "" + c );
    }

    public char delete() {
        return rightStack.pop().charAt( 0 );
    }

    public void left( int k ) {
        for ( int i = 0; i < k; ++i ) {
            rightStack.push( leftStack.pop() );
        }
    }

    public void right( int k ) {
        for ( int i = 0; i < k; ++i ) {
            leftStack.push( rightStack.pop() );
        }
    }

    public int size() {
        return leftStack.size() + rightStack.size();
    }

    public boolean isEmpty() {
        return ( leftStack.size() + rightStack.size() ) == 0;
    }

    public String toString() {
        return "LEFT STACK: " + leftStack.toString() + "; RIGHT STACK: " + rightStack.toString();
    }

    public static void main( String[] args ) {
        String str = "TOI LA PHONG";
        Buffer buffer = new Buffer();

        for ( int i = 0; i < str.length(); ++i ) {
            buffer.insert( str.charAt( i ) );
        }

        StdOut.println( "DEBUG: buffer ( 0 ): " + buffer.toString() );

        buffer.left( 3 );
        StdOut.println( "DEBUG: buffer ( 1 ): " + buffer.toString() );

        buffer.delete();
        StdOut.println( "DEBUG: buffer ( 2 ): " + buffer.toString() );

        buffer.right( 1 );
        StdOut.println( "DEBUG: buffer ( 3 ): " + buffer.toString() );
    }
}
