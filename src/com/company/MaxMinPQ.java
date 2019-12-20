package com.company;
import edu.princeton.cs.algs4.*;

public class MaxMinPQ {

    private static class Item {
        public Comparable value = null;
        public int maxPQIndex = -1;
        public int minPQIndex = -1;

        public int compareTo( Item other ) {
            return this.value.compareTo( other.value );
        }

        public String toString() {
            return "" + this.value;
        }
    }

    private Item[] maxPQ;
    private Item[] minPQ;
    private int maxN = 0;
    private int minN = 0;

    public MaxMinPQ( int N ) {
        maxPQ = new Item[ N + 1 ];
        minPQ = new Item[ N + 1 ];
    }

    private boolean less( Item a, Item b ) {
        return a.compareTo( b ) == -1;
    }

    public int size() {
        return maxN > minN ? maxN : minN;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public void exchange( int i, int j, boolean isMaxPQ ) {
        if ( isMaxPQ ) {
            // Exchange inside maxPQ
            Comparable tempValue = maxPQ[ i ].value;
            maxPQ[ i ].value = maxPQ[ j ].value;
            maxPQ[ j ].value = tempValue;
        } else {
            // Exchange inside minPQ
            Comparable tempValue = minPQ[ i ].value;
            minPQ[ i ].value = minPQ[ j ].value;
            minPQ[ j ].value = tempValue;
        }
    }

    public void swim( int k, boolean isMaxPQ ) {
        if ( isMaxPQ ) {
            // Swim inside maxPQ
            while ( k > 1 && less( maxPQ[ k / 2 ], maxPQ[ k ] ) ) {
                exchange( k / 2, k, true );
                k /= 2;
            }
        } else {
            // Swim inside minHeap
            while ( k > 1 && less( minPQ[ k ], minPQ[ k / 2 ] ) ) {
                exchange( k / 2, k, false );
                k /= 2;
            }
        }
    }

    public void sink( int k, boolean isMaxPQ ) {
        if ( isMaxPQ ) {
            // Sink inside maxHeap
            while ( 2 * k <= maxN ) {
                int j = 2 * k;
                if ( j < maxN && less( maxPQ[ j ], maxPQ[ j + 1 ] ) ) ++j;
                if ( ! less( maxPQ[ k ], maxPQ[ j ] ) ) break;
                exchange( k, j, true );
                k = j;
            }
        } else {
            // Sink inside minHeap
            while ( 2 * k <= minN ) {
                int j = 2 * k;
                if ( j < minN && less( minPQ[ j + 1 ], minPQ[ j ] ) ) ++j;
                if ( ! less( minPQ[ j ], minPQ[ k ] ) ) break;
                exchange( k, j, false );
                k = j;
            }
        }
    }

    public Comparable delMax() {
        Comparable maxValue = maxPQ[ 1 ].value;
        int maxPQIndex = maxPQ[ 1 ].maxPQIndex;
        int minPQIndex = maxPQ[ 1 ].minPQIndex;

        // Delete in maxPQ
        exchange( 1, maxN--, true );
        maxPQ[ maxN + 1 ] = null;
        sink( 1, true );

        // Delete in minPQ
        exchange( minPQIndex, minN--, false );
        minPQ[ minN + 1 ] = null;
        sink( minPQIndex, false );

        return maxValue;
    }

    public Comparable delMin() {
        Comparable minValue = minPQ[ 1 ].value;
        int maxPQIndex = minPQ[ 1 ].maxPQIndex;
        int minPQIndex = minPQ[ 1 ].minPQIndex;

        // Delete in minPQ
        exchange( 1, minN--, false );
        minPQ[ minN + 1 ] = null;
        sink( 1, false );

        // Delete in maxPQ
        exchange( maxPQIndex, maxN--, true );
        maxPQ[ maxN + 1 ] = null;
        sink( maxPQIndex, true );

        return minValue;
    }

    public Comparable max() {
        return maxPQ[ 1 ].value;
    }

    public Comparable min() {
        return minPQ[ 1 ].value;
    }

    public void insert( Comparable key ) {
        // Constructing the Items
        Item maxPQItem = new Item();
        Item minPQItem = new Item();
        maxPQItem.value = key;
        minPQItem.value = key;

        // Insert into maxPQ & minPQ
        maxPQ[ ++maxN ] = maxPQItem;
        minPQ[ ++minN ] = minPQItem;

        // Modify the items
        maxPQItem.maxPQIndex = maxN;
        maxPQItem.minPQIndex = minN;
        minPQItem.maxPQIndex = maxN;
        minPQItem.minPQIndex = minN;

        // Swim the items
        swim( maxN, true );
        swim( minN, false );

        // DEBUG
        StdOut.println( "DEBUG: minPQIndex: " + minN + " ; maxPQIndex: " + maxN );
        // END OF DEBUG
    }

    public String toString() {
        return "maxPQ : " + java.util.Arrays.toString( maxPQ ) + " ; minPQ : " + java.util.Arrays.toString( minPQ );
    }

    public String toStringDelMax() {
        String rv = "{ ";

        while ( ! isEmpty() ) {
            rv += delMax() + ", ";
        }

        rv += "}";
        return rv;
    }

    public String toStringDelMin() {
        String rv = "{ ";

        while ( ! isEmpty() ) {
            rv += delMin() + ", ";
        }

        rv += "}";
        return rv;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MaxMinPQ maxMinPQ = new MaxMinPQ( intArr.length );
        for ( int i = 0; i < intArr.length; ++i ) {
            maxMinPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: maxMinPQ (BEFORE delMax()): " + maxMinPQ.toString() );
        StdOut.println( "DEBUG: maxMinPQ (AFTER delMax()): " + maxMinPQ.toStringDelMax() );
        StdOut.println( "DEBUG: maxMinPQ (AFTER delMax() - ALL): " + maxMinPQ.toString() );

        maxMinPQ = new MaxMinPQ( intArr.length );
        for ( int i = 0; i < intArr.length; ++i ) {
            maxMinPQ.insert( intArr[ i ] );
        }
        StdOut.println( "DEBUG: maxMinPQ (BEFORE delMin()): " + maxMinPQ.toString() );
        StdOut.println( "DEBUG: maxMinPQ (AFTER delMin()): " + maxMinPQ.toStringDelMin() );
        StdOut.println( "DEBUG: maxMinPQ (AFTER delMin() - ALL): " + maxMinPQ.toString() );
    }
}
