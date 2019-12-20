package com.company;
import edu.princeton.cs.algs4.*;

public class StackGenerability {

    public static Queue< Integer > generateInputQueue( int cap ) {
        Queue< Integer > inputQueue = new Queue< Integer >();

        for ( int i = 0; i < cap; ++i ) {
            inputQueue.enqueue( i );
        }

        return inputQueue;
    }

    public static Queue< Integer > generateOutputQueue( int[] intArr ) {
        Queue< Integer > outputQueue = new Queue< Integer >();

        for ( int i = 0; i < intArr.length; ++i ) {
            outputQueue.enqueue( intArr[ i ] );
        }

        return outputQueue;
    }

    public static boolean isPermutation( Queue< Integer > inputQueue, Queue< Integer > outputQueue ) {
        Stack< Integer > tempStack = new Stack< Integer >();

        while ( ! inputQueue.isEmpty() ) {
            try {
                Integer topInputQueueElement = inputQueue.dequeue();

                if ( ! topInputQueueElement.equals( outputQueue.peek() ) ) {
                    tempStack.push( topInputQueueElement );
                } else {
                    outputQueue.dequeue();

                    while ( ! tempStack.isEmpty() ) {
                        if ( outputQueue.peek().equals( tempStack.peek() ) ) {
                            outputQueue.dequeue();
                            tempStack.pop();
                        } else {
                            break;
                        }
                    }

                }
            } catch ( java.util.NoSuchElementException e ) {
                continue;
            }
        }

        StdOut.println( "=====================================================================" );
        StdOut.println( "DEBUG: inputQueue: " + inputQueue.toString() );
        StdOut.println( "DEBUG: outputQueue: " + outputQueue.toString() );
        StdOut.println( "DEBUG: orgStack: " + tempStack.toString() );

        return tempStack.isEmpty();
    }

    public static void main( String[] args ) {
        int[][] intArrs = {
                { 4, 3, 2, 1, 0, 9, 8, 7, 6, 5 },
                { 4, 6, 8, 7, 5, 3, 2, 9, 0, 1 },
                { 2, 5, 6, 7, 4, 8, 9, 3, 1, 0 },
                { 4, 3, 2, 1, 0, 5, 6, 7, 8, 9 },
                { 1, 2, 3, 4, 5, 6, 9, 8, 7, 0 },
                { 0, 4, 6, 5, 3, 8, 1, 7, 2, 9 },
                { 1, 4, 7, 9, 8, 6, 5, 3, 0, 2 },
                { 2, 1, 4, 3, 6, 5, 8, 7, 9, 0 },
        };

        /* int[][] intArrs = {
                // { 2, 5, 6, 7, 4, 8, 9, 3, 1, 0 },
                { 4, 6, 8, 7, 5, 3, 2, 9, 0, 1 },
        }; */

        /* int charInt = 'a';
        char c = (char)charInt;
        StdOut.println( "" + c ); */

        for ( int i = 0; i < intArrs.length; ++i ) {
            if ( isPermutation( generateInputQueue( 10), generateOutputQueue( intArrs[ i ] ) ) ) {
                StdOut.println( "DEBUG: " + (char)( 'a' + i ) + ": IS PERMUTATION" );
            } else {
                StdOut.println( "DEBUG: " + (char)( 'a' + i ) + ": IS NOT PERMUTATION" );
            }
        }
    }
}
