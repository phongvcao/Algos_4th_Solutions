package com.company;
import edu.princeton.cs.algs4.*;

public class DynamicGrowth {

    private int count;
    private int[] parent;
    private int parentIdx = 0;
    private int[] sz;
    private int cap = 5;

    // Weighted Quick-Union with Linked-List implementation

    public DynamicGrowth() {
        parent = new int[ cap ];
        sz = new int[ cap ];
    }

    public boolean connected( int p, int q ) {
        return find( p ) == find( q );
    }

    public int find( int p ) {
        while ( p != parent[ p ] ) p = parent[ p ];
        return p;
    }

    public void union( int p, int q ) {
        int pRoot = find( p );
        int qRoot = find( q );
        if ( pRoot == qRoot ) return;

        if ( sz[ pRoot ] < sz[ qRoot ] ) {
            parent[ pRoot ] = qRoot;
            sz[ qRoot ] += sz[ pRoot ];
        } else {
            parent[ qRoot ] = pRoot;
            sz[ pRoot ] += sz[ qRoot ];
        }

        --count;
    }

    public int count() {
        return count;
    }

    private void extendInternalArray() {
        cap *= 2;
        int[] newParentArray = new int[ cap ];
        int[] newSizeArray = new int[ cap ];

        for ( int i = 0; i < parentIdx; ++i ) {
            newParentArray[ i ] = parent[ i ];
        }

        for ( int j = 0; j < parentIdx; ++j ) {
            newSizeArray[ j ] = sz[ j ];
        }

        parent = newParentArray;
        sz = newSizeArray;
    }

    public int newSite() {
        if ( parentIdx == parent.length ) {
            extendInternalArray();
        }
        parent[ parentIdx ] = parentIdx;
        sz[ parentIdx ] = 1;
        ++parentIdx;
        ++count;
        return parent[ parentIdx - 1 ];
    }

    public String toString() {
        String rv = "\nparent: { ";

        for ( int i = 0; i < parentIdx; ++i ) {
            rv += " | " + i + " : " + parent[ i ] + " | ";
        }
        rv += "} \nsz:     { ";
        for ( int i = 0; i < parentIdx; ++i ) {
            rv += " | " + i + " : " + sz[ i ] + " | ";
        }

        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        int N = 10;
        DynamicGrowth dg = new DynamicGrowth();
        for ( int i = 0; i < N; ++i ) {
            dg.newSite();
        }

        StdOut.println( "DEBUG: dg.toString(): ORIGINAL: " + dg.toString() );

        dg.union( 0, 1 );
        StdOut.println( "DEBUG: p : 0 ; q : 1 " + dg.toString() );

        dg.union( 2, 3 );
        StdOut.println( "DEBUG: p : 2 ; q : 3 " + dg.toString() );
    }
}
