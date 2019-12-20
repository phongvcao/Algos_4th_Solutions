package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortIndirectSort {

    private static class Item implements Comparable< Item > {
        public int index = -1;
        public Comparable value = null;

        public Item( int index, Comparable value ) {
            this.index = index;
            this.value = value;
        }

        public int compareTo( Item item ) {
            return this.value.compareTo( item.value );
        }
    }

    public static boolean less( Item a, Item b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Item[] a, int i, int j ) {
        Item temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void sort( int[] perm, Item[] a ) {
        int[] permAux = new int[ perm.length ];

        sort( perm, permAux, a, 0, a.length - 1 );
    }

    public static void sort( int[] perm, int[] permAux, Item[] a, int low, int high ) {
        if ( low >= high ) return;
        int mid = ( low + high ) / 2;

        sort( perm, permAux, a, low, mid );
        sort( perm, permAux, a, mid + 1, high);
        merge( perm, permAux, a, low, mid, high );
    }

    public static void merge( int[] perm, int[] permAux, Item[] a, int low, int mid, int high ) {
        int i = low;
        int j = mid + 1;

        for ( int k = low; k <= high; ++k ) {
            permAux[ k ] = perm[ k ];
        }

        for ( int k = low; k <= high; ++k ) {
            if ( i > mid ) {
                perm[ k ] = permAux[ j++ ];
            } else if ( j > high ) {
                perm[ k ] = permAux[ i++ ];
            } else if ( less( a[ permAux[ j ] ], a[ permAux[ i ] ] ) ) {
                perm[ k ] = permAux[ j++ ];
            } else {
                perm[ k ] = permAux[ i++ ];
            }
        }
    }

    public static String toString( Item[] a ) {
        String rv = "{ ";

        for ( int i = 0; i < a.length; ++i ) {
            rv += " " + a[ i ].index + " : " + a[ i ].value + " | ";
        }

        rv += " }";
        return rv;
    }

    public static String toString( int[] perm, Item[] a ) {
        String rv = "{ ";

        for ( int i = 0; i < perm.length; ++i ) {
            rv += " " + a[ perm[ i ] ].index + " : " + a[ perm[ i ] ].value + " | ";
        }

        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Item[] itemArr = new Item[ intArr.length ];
        for ( int i = 0; i < intArr.length; ++i ) {
            itemArr[ i ] = new Item( i, intArr[ i ] );
        }

        int[] perm = new int[ itemArr.length ];
        for ( int i = 0; i < itemArr.length; ++i ) {
            perm[ i ] = itemArr[ i ].index;
        }

        StdOut.println( "DEBUG: itemArr (BEFORE): " + toString( itemArr ) );
        StdOut.println( "DEBUG: itemArr (BEFORE): " + toString( itemArr ) );
        StdOut.println( "DEBUG: itemArr with perm (BEFORE): " + toString( perm, itemArr ) );

        sort( perm, itemArr );

        StdOut.println( "DEBUG: itemArr (AFTER): " + toString( itemArr ) );
        StdOut.println( "DEBUG: itemArr with perm (AFTER): " + toString( perm, itemArr ) );
    }
}
