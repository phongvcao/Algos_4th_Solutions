package com.company;
import java.util.Random;
import java.util.Iterator;
import java.util.Collections;
import java.util.Arrays;
import edu.princeton.cs.algs4.*;

public class RandomQueue< Item > implements Iterable< Item > {
    private int N = 0;
    private Item[] array;
    private int limit = 5;

    public RandomQueue() {
        array = ( Item[] )new Object[ limit ];
    }

    public RandomQueue( int cap ) {
        limit = cap;
        array = ( Item[] )new Object[ limit ];
    }

    private void doubleArraySize() {
        Item[] newArray = ( Item[] )new Object[ limit * 2 ];
        for ( int i = 0; i < array.length; ++i ) {
            newArray[ i ] = array[ i ];
        }
        array = newArray;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public void enqueue( Item item ) {
        if ( N == limit ) {
            doubleArraySize();
        }
        array[ N++ ] = item;
    }

    public Item dequeue() {
        // Choose a random index
        Random rand = new Random();
        int index = rand.nextInt( N );

        // Swap random index with last item
        Item temp = array[ index ];
        array[ index ] = array [ N - 1 ];
        array[ N - 1 ] = temp;

        // Remove last item
        Item removedItem = array[ N - 1 ];
        array[ --N ] = null;

        return removedItem;
    }

    public Item sample() {
        // Choose a random index
        Random rand = new Random();
        int index = rand.nextInt( N );
        return array[ index ];
    }

    public String toStringRaw() {
        return java.util.Arrays.toString( array );
    }

    public String toString() {
        String rv = "{";
        for ( int i = 0; i < array.length; ++i ) {
            rv += " " + array[ i ] + ",";
        }
        rv += " }";
        return rv;
    }

    public Iterator< Item > iterator() {
        return new ArrayIterator();
    }

    public class ArrayIterator implements Iterator< Item > {
        private Item[] iterArray = array;
        private int curIdx = 0;

        public ArrayIterator() {
            // Randomize order of array's elements
            Collections.shuffle( Arrays.asList( iterArray ) );
        }

        public boolean hasNext() {
            return N == 0;
        }

        public void remove() {

        }

        public Item next() {
            return iterArray[ curIdx++ ];
        }

        public String toString() {
            String rv = "{";
            for ( int i = 0; i < iterArray.length; ++i ) {
                rv += " " + iterArray[ i ] + ",";
            }
            rv += " }";
            return rv;
        }
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        RandomQueue< String > randomQueue = new RandomQueue< String >( 5 );

        for ( int i = 0; i < strArr.length; ++i ) {
            randomQueue.enqueue( strArr[ i ] );
        }

        Iterator< String > iter = randomQueue.iterator();
        StdOut.println( "DEBUG (iterator): " + iter.toString() );

        StdOut.println( "DEBUG: " + randomQueue.toString() );
        StdOut.println( "DEBUG: " + randomQueue.toStringRaw() );

        String[] strArr1 = new String[ strArr.length ];
        for ( int i = 0; i < strArr.length; ++i ) {
            strArr1[ i ] = randomQueue.dequeue();
        }

        StdOut.println( "DEBUG: " + java.util.Arrays.toString( strArr1 ) );
    }
}
