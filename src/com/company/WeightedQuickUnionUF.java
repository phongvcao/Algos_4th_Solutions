package com.company;
import edu.princeton.cs.algs4.*;

public class WeightedQuickUnionUF {
    private int[] id;
    private int[] sz;
    private int count;

    public WeightedQuickUnionUF( int N ) {
        count = N;
        id = new int[ N ];
        for ( int i = 0; i < N; ++i ) {
            id[ i ] = i;
        }

        sz = new int[ N ];
        for ( int i = 0; i < N; ++i ) {
            sz[ i ] = 1;
        }
    }

    public int count() {
        return count;
    }

    public boolean connected( int p, int q ) {
        return find( p ) == find( q );
    }

    private int find( int p ) {
        // Follow links to find a root
        while ( p != id[ p ] ) p = id[ p ];
        return p;
    }

    public void union( int p, int q ) {
        int i = find( p );
        int j = find( q );
        if ( i == j ) return;

        if ( sz[ i ] < sz[ j ] ) {
            id[ i ] = j;
            sz[ j ] += sz[ i ];
        } else {
            id[ j ] = i;
            sz[ i ] += sz[ j ];
        }
        --count;
    }

    public String toString() {
        String rv = "\nid: { ";

        for ( int i = 0; i < id.length; ++i ) {
            rv += i + " : " + id[ i ] + " | ";
        }

        rv += "}; \nsz: { ";

        for ( int i = 0; i < sz.length; ++i ) {
            rv += i + " : " + sz[ i ] + " | ";
        }

        rv += "}";
        return rv;
    }

    public static void main( String[] args ) {
        WeightedQuickUnionUF wQuickUnion = new WeightedQuickUnionUF( 10 );

        StdOut.println( "\nDEBUG: original: " + wQuickUnion.toString() );

        wQuickUnion.union( 4, 3 );
        StdOut.println( "\nDEBUG: p : 4 | q : 3 : " + wQuickUnion.toString() );

        wQuickUnion.union( 3, 8 );
        StdOut.println( "\nDEBUG: p : 3 | q : 8 : " + wQuickUnion.toString() );

        wQuickUnion.union( 6, 5 );
        StdOut.println( "\nDEBUG: p : 6 | q : 5 : " + wQuickUnion.toString() );

        wQuickUnion.union( 9, 4 );
        StdOut.println( "\nDEBUG: p : 9 | q : 4 : " + wQuickUnion.toString() );

        wQuickUnion.union( 2, 1 );
        StdOut.println( "\nDEBUG: p : 2 | q : 1 : " + wQuickUnion.toString() );

        wQuickUnion.union( 8, 9 );
        StdOut.println( "\nDEBUG: p : 8 | q : 9 : " + wQuickUnion.toString() );

        wQuickUnion.union( 5, 0 );
        StdOut.println( "\nDEBUG: p : 5 | q : 0 : " + wQuickUnion.toString() );

        wQuickUnion.union( 7, 2 );
        StdOut.println( "\nDEBUG: p : 7 | q : 2 : " + wQuickUnion.toString() );

        wQuickUnion.union( 6, 1 );
        StdOut.println( "\nDEBUG: p : 6 | q : 1 : " + wQuickUnion.toString() );

        wQuickUnion.union( 1, 0 );
        StdOut.println( "\nDEBUG: p : 1 | q : 0 : " + wQuickUnion.toString() );

        wQuickUnion.union( 6, 7 );
        StdOut.println( "\nDEBUG: p : 6 | q : 7 : " + wQuickUnion.toString() );
    }
}
