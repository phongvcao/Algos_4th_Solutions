package com.company;
import edu.princeton.cs.algs4.*;

public class DequeWithThreeStacks< Item > {

    private Stack< Item > leftStack;
    private Stack< Item > middleStack;
    private Stack< Item > rightStack;

    public DequeWithThreeStacks() {
        leftStack = new Stack< Item >();
        middleStack = new Stack< Item >();
        rightStack = new Stack< Item >();
    }

    public boolean isEmpty() {
        return leftStack.isEmpty() && middleStack.isEmpty() && rightStack.isEmpty();
    }

    public int size() {
        return leftStack.size() + middleStack.size() + rightStack.size();
    }

    public void pushLeft( Item item ) {
        leftStack.push( item );
    }

    public void pushRight( Item item ) {
        rightStack.push( item );
    }

    public Item popLeft() {
        if ( leftStack.isEmpty() ) {
            for ( int i = 0; i < rightStack.size() / 2; ++i ) {
                middleStack.push( rightStack.pop() );
            }

            while ( ! rightStack.isEmpty() ) {
                leftStack.push( rightStack.pop() );
            }

            while ( ! middleStack.isEmpty() ) {
                rightStack.push( middleStack.pop() );
            }
        }

        return leftStack.pop();
    }

    public Item popRight() {
        if ( rightStack.isEmpty() ) {
            for ( int i = 0; i < leftStack.size() / 2; ++i ) {
                middleStack.push( leftStack.pop() );
            }

            while ( ! leftStack.isEmpty() ) {
                rightStack.push( leftStack.pop() );
            }

            while ( ! middleStack.isEmpty() ) {
                leftStack.push( middleStack.pop() );
            }
        }

        return rightStack.pop();
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        DequeWithThreeStacks< String> deque = new DequeWithThreeStacks< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            deque.pushLeft( strArr[ i ] );
            deque.pushRight( strArr[ i ] );
        }

        while ( ! deque.isEmpty() ) {
            StdOut.println( "DEBUG: " + deque.popRight() );
        }
    }
}
