package com.company;
import edu.princeton.cs.algs4.*;

public class ResizingArrayQueueOfStrings {

    private String[] innerArr;
    public int headIdx = 0;
    public int tailIdx = 0;

    public ResizingArrayQueueOfStrings() {
        this.innerArr = new String[ 100 ];
    }

    public ResizingArrayQueueOfStrings( int cap ) {
        this.innerArr = new String[ cap ];
    }

    public void enqueue( String item ) {
        // Extending innerArr
        if ( this.tailIdx > this.innerArr.length - 1 ) {
            // StdOut.println( "EXTENDING INNERARR CAPACITY: " + java.util.Arrays.toString( this.innerArr ) );

            String[] tempArr = new String[ 2 * this.innerArr.length ];
            for ( int i = 0; i < this.tailIdx - this.headIdx; ++i ) {
                // if ( this.innerArr[ this.headIdx + i ] != null ) {
                tempArr[ i ] = this.innerArr[ this.headIdx + i ];
                // }
            }
            this.innerArr = tempArr;
            this.tailIdx = this.tailIdx - this.headIdx;
            this.headIdx = 0;
        }

        this.innerArr[ this.tailIdx++ ] = item;
    }

    public String dequeue() {
        return this.innerArr[ this.headIdx++ ];
    }

    public boolean isEmpty() {
        return ( this.tailIdx == this.headIdx );
    }

    public int size() {
        return this.tailIdx = this.headIdx;
    }

    public static void main( String[] args ) {
        StdOut.print( "DEBUG: " );

        ResizingArrayQueueOfStrings queue = new ResizingArrayQueueOfStrings( 10 );

        for ( int i = 0; i < 100; ++i ) {
            queue.enqueue( "" + i );
            // StdOut.println( "DEBUG: i: " + i + "; i % 5 = " + ( i % 5 ) );

            if ( i % 5 == 0 ) {
                 StdOut.println( "DEQUEUE-ING: i: " + i );
                 StdOut.println( "DEQUEUE-ING: " + queue.dequeue() );
                 StdOut.println( "DEQUEUE-ING HEADIDX: " + queue.headIdx );
                 StdOut.println( "DEQUEUE-ING TAILIDX: " + queue.tailIdx + '\n' );
            }
        }

        while ( ! queue.isEmpty() ) {
            StdOut.print( queue.dequeue() + " " );
        }
        StdOut.println();
    }
}
