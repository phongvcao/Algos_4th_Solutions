package com.company;
import edu.princeton.cs.algs4.*;

public class StackWithAQueue< Item > {

    private Queue< Item > queue;

    public StackWithAQueue() {
        queue = new Queue< Item >();
    }

    public void push( Item item ) {
        queue.enqueue( item );
    }

    public Item pop() {
        Item lastPoppedItem = null;
        int count = 0;
        while ( count < queue.size() - 1 ) {
            queue.enqueue( queue.dequeue() );
            ++count;
        }

        return queue.dequeue();
    }

    public boolean isEmpty() {
        return queue.isEmpty();
    }

    public int size() {
        return queue.size();
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        StackWithAQueue< String > stack = new StackWithAQueue< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            stack.push( strArr[ i ] );
        }

        while ( ! stack.isEmpty() ) {
            StdOut.println( "DEBUG: " + stack.pop() );
        }
    }
}
