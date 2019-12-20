package com.company;
import edu.princeton.cs.algs4.*;

public class QuickUnionUF {

    private int[] id;
    private int count;

    public QuickUnionUF( int N ) {
        count = N;
        id = new int[ N ];
        for ( int i = 0; i < id.length; ++i ) {
            id[ i ] = i;
        }
    }

    public int count() {
        return count;
    }

    public boolean connected( int p, int q ) {
        return find( p ) == find( q );
    }

    public int find( int p ) {
        // Follow link to a root
        while ( p != id[ p ] ) p = id[ p ];
        return p;
    }

    public void union( int p , int q ) {
        // Find root of p
        int i = find( p );
        // Find root of q
        int j = find( q );

        // If same root => connected => nothing to do
        if ( i == j ) return;

        // If not same root => i should be connected to root j of element q.
        id[ i ] = j;
        --count;
    }

    public String toString() {
        String rv = "\nid: { ";

        for ( int i = 0; i < id.length; ++i ) {
            rv += i + " : " + id[ i ] + " | ";
        }

        rv += "};";
        return rv;
    }

    public static void main( String[] args ) {
        QuickUnionUF quickUnion = new QuickUnionUF( 10 );

        StdOut.println( "\nDEBUG: original: " + quickUnion.toString() );

        quickUnion.union( 0, 1 );
        StdOut.println( "\nDEBUG: p : 0 | q : 1 : " + quickUnion.toString() );

        quickUnion.union( 0, 2 );
        StdOut.println( "\nDEBUG: p : 0 | q : 2 : " + quickUnion.toString() );

        quickUnion.union( 0, 3 );
        StdOut.println( "\nDEBUG: p : 0 | q : 3 : " + quickUnion.toString() );

        quickUnion.union( 0, 4 );
        StdOut.println( "\nDEBUG: p : 0 | q : 4 : " + quickUnion.toString() );
    }
}
