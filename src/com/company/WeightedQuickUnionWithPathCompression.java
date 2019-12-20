package com.company;
import edu.princeton.cs.algs4.*;

public class WeightedQuickUnionWithPathCompression {

    private int[] id;
    private int[] sz;
    private int count;

    public WeightedQuickUnionWithPathCompression( int N ) {
        count = N;

        id = new int[ N ];
        for ( int i = 0; i < id.length; ++i ) {
            id [ i ] = i;
        }

        sz = new int[ N ];
        for ( int i = 0; i < id.length; ++i ) {
            sz[ i ] = 1;
        }
    }

    public int count() {
        return count;
    }

    public boolean connected( int p, int q ) {
        return find( p ) == find( q );
    }

    public int find( int p ) {
        int root = p;
        while ( root != id[ root ] ) root = id[ root ];

        // PATH COMPRESSION
        while ( p != root ) {
            int newP = id[ p ];
            id[ p ] = root;
            p = newP;
        }

        return root;
    }

    public void union( int p, int q ) {
        int rootP = find( p );
        int rootQ = find( q );

        if ( rootP == rootQ ) return;

        if ( sz[ rootP ] < sz[ rootQ ] ) {
            id[ rootP ] = id[ rootQ ];
            sz[ rootQ ] += sz[ rootP ];
        } else {
            id[ rootQ ] = id[ rootP ];
            sz[ rootP ] += sz[ rootQ ];
        }
        --count;
    }

    public String toString() {
        String rv = "\nid : { ";

        for ( int i = 0; i < id.length; ++i ) {
            rv += i + " : " + id[ i ] + " | ";
        }
        rv += "}; \nsz : { ";
        for ( int i = 0; i < sz.length; ++i ) {
            rv += i + " : " + sz[ i ] + " | ";
        }

        rv += "}";
        return rv;
    }

    public static void main( String[] args ) {
        WeightedQuickUnionWithPathCompression wQuickUnion = new WeightedQuickUnionWithPathCompression( 10 );

        StdOut.println( "\nDEBUG: " + wQuickUnion.toString() );

        wQuickUnion.union( 0, 1 );
        StdOut.println( "\nDEBUG: p : 0 | q : 1 : " + wQuickUnion.toString() );

        wQuickUnion.union( 0, 2 );
        StdOut.println( "\nDEBUG: p : 0 | q : 2 : " + wQuickUnion.toString() );

        wQuickUnion.union( 0, 3 );
        StdOut.println( "\nDEBUG: p : 0 | q : 3 : " + wQuickUnion.toString() );
    }
}
