package com.company;
import edu.princeton.cs.algs4.*;

public class QueueWithTwoStacks< Item > {

    private Stack< Item > pushStack;
    private Stack< Item > popStack;

    public QueueWithTwoStacks() {
        pushStack = new Stack< Item >();
        popStack = new Stack< Item >();
    }

    public void enqueue( Item item ) {
        pushStack.push( item );
    }

    public Item dequeue() {
        if ( popStack.isEmpty() ) {
            while ( ! pushStack.isEmpty() ) {
                popStack.push( pushStack.pop() );
            }
        }

        return popStack.pop();
    }

    public boolean isEmpty() {
        return pushStack.isEmpty() && popStack.isEmpty();
    }

    public int size() {
        return pushStack.size() + popStack.size();
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        QueueWithTwoStacks< String > queue = new QueueWithTwoStacks< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            queue.enqueue( strArr[ i ] );
        }

        while ( ! queue.isEmpty() ) {
            StdOut.println( "DEBUG: " + queue.dequeue() );
        }
    }
}
