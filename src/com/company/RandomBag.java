package com.company;
import java.util.Iterator;
import edu.princeton.cs.algs4.*;
import java.util.Collections;
import java.util.Arrays;

public class RandomBag < Item > implements Iterable< Item > {

    private int N = 0;
    public Item[] array;

    public RandomBag( int cap ) {
        array = ( Item[] )new Object[ cap ];
    }

    public RandomBag() {
        array = ( Item[] )new Object[ 5 ];
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public void add( Item item ) {
        array[ N++ ] = item;
    }

    public Iterator< Item > iterator() {
        return new ArrayIterator();
    }

    public String toString() {
        String rv = "{";
        for ( int i = 0; i < array.length; ++i ) {
            rv += " " + array[ i ] + ",";
        }
        rv += " }";
        return rv;
    }

    private class ArrayIterator implements Iterator< Item > {
        private Item[] iterArray = array;
        private int curIdx = 0;

        public ArrayIterator() {
            // Randomize order of array's elements
            Collections.shuffle( Arrays.asList( iterArray ) );
        }

        public boolean hasNext() {
            return curIdx < N;
        }

        public void remove() {
            // Not required to be implemented
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
        RandomBag< String > strBag = new RandomBag< String >( strArr.length );

        for ( int i = 0; i < strArr.length; ++i ) {
            strBag.add( strArr[ i ] );
        }

        StdOut.println( "DEBUG: " + strBag.toString() );
        StdOut.println( "DEBUG: " + strBag.iterator().toString() );
        StdOut.println( "DEBUG: " + strBag.iterator().toString() );
    }
}
