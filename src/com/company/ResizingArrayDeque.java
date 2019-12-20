package com.company;
import edu.princeton.cs.algs4.*;

public class ResizingArrayDeque< Item > {

    private int N = 0;
    private int leftIdx = -1;
    private int rightIdx = -1;
    private int limit = 10;

    private Item[] array;

    public ResizingArrayDeque( int cap ) {
        limit = cap;
        array = ( Item[] )new Object[ cap ];
    }

    public ResizingArrayDeque() {
        array = ( Item[] )new Object[ limit ];
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    private void doubleArraySizeLeft() {
        limit *= 2;
        Item[] newArray = ( Item[] )new Object[ limit ];
        for ( int i = array.length - 1; i >= 0; --i ) {
            // if ( array[ i ] != null ) {
            newArray[ limit / 2 + i ] = array[ i ];
            // }
        }
        array = newArray;
        leftIdx = limit / 2 - 1;
        rightIdx = rightIdx + limit / 2;
    }

    private void reduceArraySizeLeft() {
        Item[] newArray = ( Item[] )new Object[ limit / 2 ];
        for ( int i = array.length - 1; i >= leftIdx; --i ) {
            newArray[ i - limit / 2 ] = array[ i ];
        }
        array = newArray;
        leftIdx = leftIdx - limit / 2 - 1;
        rightIdx = rightIdx - limit / 2;
    }

    public void pushLeft( Item item ) {
        if ( isEmpty() ) {
            leftIdx = 0;
            rightIdx = 0;
            array[ leftIdx-- ] = item;
        } else {
            if ( leftIdx == -1 ) {
                doubleArraySizeLeft();
            }
            array[ leftIdx-- ] = item;
        }

        ++N;
    }

    private void doubleArraySizeRight() {
        limit *= 2;
        Item[] newArray = ( Item[] )new Object[ limit ];
        for ( int i = 0; i < array.length; ++i ) {
            newArray[ i ] = array[ i ];
        }
        array = newArray;
    }

    private void reduceArraySizeRight() {
    }

    public void pushRight( Item item ) {
        if ( isEmpty() ) {
            leftIdx = 0;
            rightIdx = 0;
            array[ rightIdx++ ] = item;
        } else {
            if ( rightIdx == limit ) {
                doubleArraySizeRight();
            }
            array[ rightIdx++ ] = item;
        }

        ++N;
    }

    public Item popLeft() {
        Item rv = null;

        if ( leftIdx > -1 ) {
            while ( array[ leftIdx ] == null ) {
                ++leftIdx;
            }
            rv = array[ leftIdx++ ];
            array[ leftIdx - 1 ] = null;
        }

        --N;

        if ( leftIdx > limit / 4 * 3 ) {
            StdOut.println( "DEBUG: REDUCE ARRAY SIZE LEFT!!!" );
            reduceArraySizeLeft();
        }

        return rv;
    }

    public Item popRight() {
        Item rv = null;

        if ( rightIdx < limit ) {
            while ( array[ rightIdx ] == null ) {
                --rightIdx;
            }
            rv = array[ rightIdx-- ];
            array[ rightIdx + 1 ] = null;
        }

        --N;

        if ( rightIdx < limit / 4 ) {
            reduceArraySizeRight();
        }

        return rv;
    }

    public String toStringRaw() {
        return java.util.Arrays.toString( array );
    }

    public String toString() {
        String rv = "{";
        for ( int i = leftIdx; i < rightIdx + 1; ++i ) {
            if ( array[ i ] != null ) {
                rv += " " + array[ i ] + ",";
            }
        }
        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        ResizingArrayDeque< String > deque = new ResizingArrayDeque< String >();

        for ( int i = 0; i < strArr.length; ++i ) {
            StdOut.println( "DEBUG: " + i + ": " + deque.toStringRaw() );
            // deque.pushLeft( strArr[ i ] );
            deque.pushRight( strArr[ i ] );
        }

        StdOut.println( "DEBUG: " + deque.toString() );

        for ( int i = 0; i < 90; ++i ) {
            StdOut.println( "DEBUG: popLeft(): " + deque.popLeft() );

            StdOut.println( "DEBUG: " + deque.toStringRaw() );
        }

        // StdOut.println( "DEBUG: popRight(): " + deque.popRight() );

        // StdOut.println( "DEBUG: " + deque.toString() );
    }
}
