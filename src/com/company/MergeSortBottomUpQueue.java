package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortBottomUpQueue {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void sort( Queue< Queue< Comparable > > queue ) {
        while ( queue.size() > 1 ) {
            queue.enqueue( merge( queue.dequeue(), queue.dequeue() ) );
        }
    }

    public static Queue< Comparable > merge( Queue< Comparable > queue1, Queue< Comparable > queue2 ) {
        Queue< Comparable > queue = new Queue< Comparable >();
        while ( ( ! queue1.isEmpty() ) && ( ! queue2.isEmpty() ) ) {
            if ( less( queue1.peek(), queue2.peek() ) ) {
                queue.enqueue( queue1.dequeue() );
            } else {
                queue.enqueue( queue2.dequeue() );
            }
        }

        if ( queue2.isEmpty() ) {
            while ( ! queue1.isEmpty() ) {
                queue.enqueue( queue1.dequeue() );
            }
        }

        if ( queue1.isEmpty() ) {
            while ( ! queue2.isEmpty() ) {
                queue.enqueue( queue2.dequeue() );
            }
        }

        return queue;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11 };
        Queue< Queue< Comparable > > intQueue = new Queue< Queue< Comparable > >();

        for ( int i = 0; i < intArr.length; ++i ) {
            Queue< Comparable > tempQueue = new Queue< Comparable >();
            tempQueue.enqueue( intArr[ i ] );
            intQueue.enqueue( tempQueue );
        }

        StdOut.println( "DEBUG: intQueue (BEFORE): " + intQueue.toString() );

        sort( intQueue );

        StdOut.println( "DEBUG: intQueue (AFTER): " + intQueue.toString() );
    }
}
