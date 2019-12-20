package com.company;
import edu.princeton.cs.algs4.*;
import java.util.Random;

public class MergeSortMergingSortedQueues< Item > {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
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

        if ( queue1.isEmpty() ) {
            while ( ! queue2.isEmpty() ) {
                queue.enqueue( queue2.dequeue() );
            }
        }

        if ( queue2.isEmpty() ) {
            while ( ! queue1.isEmpty() ) {
                queue.enqueue( queue1.dequeue() );
            }
        }

        return queue;
    }

    public static void main( String[] args ) {
        Random rand = new Random();
        int queue1Size = rand.nextInt( 50 ) + 1;
        int queue2Size = rand.nextInt( 50 ) + 1;

        Queue< Comparable > queue1 = new Queue< Comparable >();
        Queue< Comparable > queue2 = new Queue< Comparable >();

        for ( int i = 0; i < queue1Size; ++i ) {
            if ( i % 2 == 0 ) {
                queue1.enqueue( i );
            }
        }

        for ( int i = 0; i < queue2Size; ++i ) {
            if ( i % 2 == 1 ) {
                queue2.enqueue( i );
            }
        }

        StdOut.println( "DEBUG: Queue1 (ORIGINAL): " + queue1.toString() );
        StdOut.println( "DEBUG: Queue2 (ORIGINAL): " + queue2.toString() );

        StdOut.println( "DEBUG: Merged Queue: " + merge( queue1, queue2 ).toString() );
    }
}
