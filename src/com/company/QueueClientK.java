package com.company;
import edu.princeton.cs.algs4.*;

public class QueueClientK {

    public static String printKString( Queue< String > queue, int k ) {
        Queue< String > newQueue = new Queue< String >();
        String strK = "";
        int indexCount = 0;
        int orgQueueSize = queue.size();

        while ( ! queue.isEmpty() ) {
            newQueue.enqueue( queue.dequeue() );
            if ( indexCount == orgQueueSize - k - 1 ) {
                strK = queue.peek();
                break;
            }

            ++indexCount;
        }

        return strK;
    }

    public static void main( String[] args ) {
        String[] inputArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        Queue< String > queue = new Queue< String >();

        for ( String item: inputArr ) {
            queue.enqueue( item );
        }

        StdOut.println( "DEBUG: " + printKString( queue, 2 ) );
    }
}
