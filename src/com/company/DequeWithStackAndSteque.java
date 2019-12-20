package com.company;
import edu.princeton.cs.algs4.*;

public class DequeWithStackAndSteque< Item > {

    private Stack< Item > leftStack;
    private Steque< Item > rightSteque;

    public DequeWithStackAndSteque() {
        leftStack = new Stack< Item >();
        rightSteque = new Steque< Item >();
    }

    public boolean isEmpty() {
        return leftStack.isEmpty() && rightSteque.isEmpty();
    }

    public int size() {
        return leftStack.size() + rightSteque.size();
    }

    public void pushLeft( Item item ) {
        leftStack.push( item );
    }

    public void pushRight( Item item ) {
        rightSteque.push( item );
    }

    public Item popLeft() {
        if ( leftStack.isEmpty() )  {
            while ( ! rightSteque.isEmpty() ) {
                leftStack.push( rightSteque.pop() );
            }
        }

        return leftStack.pop();
    }

    public Item popRight() {
        if ( rightSteque.isEmpty() ) {
            while ( ! leftStack.isEmpty() ) {
                rightSteque.push( leftStack.pop() );
            }
        }

        return rightSteque.pop();
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        DequeWithStackAndSteque< String > deque = new DequeWithStackAndSteque< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            deque.pushLeft( strArr[ i ] );
            deque.pushRight( strArr[ i ] );
        }

        while ( ! deque.isEmpty() ) {
            StdOut.println( "DEBUG: " + deque.popRight() );
        }
    }
}
