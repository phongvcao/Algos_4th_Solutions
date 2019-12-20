package com.company;
import edu.princeton.cs.algs4.*;

import java.lang.reflect.Array;

public class BinarySearchSTUsingItem< Key extends Comparable< Key >, Value > {

    public class Item implements Comparable< Item > {
        public Key key = null;
        public Value value = null;

        public Item( Key key, Value value ) {
            this.key = key;
            this.value = value;
        }

        public int compareTo( Item other ) {
            return this.key.compareTo( other.key );
        }

        public String toString() {
            return " | " + this.key + " : " + this.value + " | ";
        }
    }

    private Item[] items;
    private int N = 0;

    public BinarySearchSTUsingItem( int cap ) {
        items = new BinarySearchSTUsingItem.Item[ cap ];
    }

    public BinarySearchSTUsingItem( Item[] a ) {
        this.N = a.length;
        this.items = a;
        sort( this.items );
    }

    private void sort( Item[] a ) {
        Item[] aux = new BinarySearchSTUsingItem.Item[ a.length ];
        sort( a, aux, 0, a.length - 1 );
    }

    private void sort( Item[] a, Item[] aux, int low, int high ) {
        if ( low >= high ) return;
        int mid = low + ( high - low ) / 2;

        sort( a, aux, low, mid );
        sort( a, aux, mid + 1, high );
        merge( a, aux, low, mid, high );
    }

    private void merge( Item[] a, Item[] aux, int low, int mid, int high ) {
        for ( int k = low; k <= high; ++k ) {
            aux[ k ] = a[ k ];
        }

        int i = low;
        int j = mid + 1;
        for ( int k = low; k <= high; ++k ) {
            if ( i > mid ) {
                a[ k ] = aux[ j++ ];
            } else if ( j > high ) {
                a[ k ] = aux[ i++ ];
            } else if ( less( aux[ i ], aux[ j ] ) ) {
                a[ k ] = aux[ i++ ];
            } else {
                a[ k ] = aux[ j++ ];
            }
        }
    }

    private boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public void put( Key key, Value value ) {
        int i = rank( key );

        if ( i < N && items[ i ].key.compareTo( key ) == 0 ) {
            items[ i ].value = value;
        } else {
            for ( int j = N; j > i; --j ) {
                items[ j ] = items[ j - 1 ];
            }
            items[ i ] = new Item( key, value );
            ++N;
        }
    }

    public int rank( Key key ) {
        int low = 0;
        int high = N - 1;
        while ( low <= high ) {
            int mid = low + ( high - low ) / 2;
            int cmp = key.compareTo( items[ mid ].key );
            if ( cmp < 0 ) {
                high = mid - 1;
            } else if ( cmp > 0 ) {
                low = mid + 1;
            } else {
                return mid;
            }
        }
        return low;
    }

    public boolean contains( Key key ) {
        return get( key ) != null;
    }

    public Value get( Key key ) {
        int i = rank( key );
        if ( items[ i ] != null && items[ i ].key.compareTo( key ) == 0 ) {
            return items[ i ].value;
        }
        return null;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > q = new Queue< Key >();
        if ( less( high, low ) ) return q;
        int lowRank = rank( low );
        int highRank = rank( high );
        for ( int i = lowRank; i < highRank; ++i ) {
            q.enqueue( items[ i ].key );
        }
        return q;
    }

    public Iterable< Key > keys() {
        return keys( min(), max() );
    }

    public Key min() {
        return items[ 0 ].key;
    }

    public Key max() {
        return items[ N - 1 ].key;
    }

    public String toString() {
        return java.util.Arrays.toString( this.items );
    }

    public Item[] constructItemArray( Key[] keys, Value[] values ) {
        Item[] items = new BinarySearchSTUsingItem.Item[ keys.length ];
        for ( int i = 0; i < keys.length; ++i ) {
            items[ i ] = new Item( keys[ i ], values[ i ] );
        }
        return items;
    }

    public static void main( String[] args ) {
        Integer[] strArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        // First way
        BinarySearchSTUsingItem< Integer, Integer > st = new BinarySearchSTUsingItem< Integer, Integer >( strArr.length );
        for ( int i = 0; i < strArr.length; ++i ) {
            st.put( strArr[ i ], intArr[ i ] );
        }
        StdOut.println( "DEBUG: st: " + st.toString() );

        // Second way
        BinarySearchSTUsingItem< Integer, Integer > st1 = new BinarySearchSTUsingItem< Integer, Integer >( st.constructItemArray( strArr, intArr ) );
        StdOut.println( "DEBUG: st (SECOND WAY: " + st.toString() );
    }
}
