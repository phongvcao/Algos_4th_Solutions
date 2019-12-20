package com.company;
import edu.princeton.cs.algs4.*;

public class WeightedQuickUnionByHeight {
    private int[] parent;
    private int[] height;
    private int count;

    public WeightedQuickUnionByHeight( int N ) {
        count = N;
        parent = new int[ N ];
        height = new int[ N ];

        for ( int i = 0; i < N; ++i ) {
            parent[ i ] = i;
            height[ i ] = 1;
        }
    }

    public int count() {
        return count;
    }

    public int find( int p ) {
        int root = p;
        while ( root != parent[ root ] ) {
            root = parent[ root ];
        }
        return root;
    }

    public boolean connected( int p, int q ) {
        return find( p ) == find( q );
    }

    public void union( int p, int q ) {
        // When union
        int pRoot = find( p );
        int qRoot = find( q );

        if ( pRoot == qRoot ) return;

        if ( height[ pRoot ] < height[ qRoot ] ) {
            parent[ pRoot ] = qRoot;
        } else if ( height[ qRoot ] < height[ pRoot ] ) {
            parent[ qRoot ] = pRoot;
        } else {
            parent[ pRoot ] = parent[ qRoot ];
            ++height[ pRoot ];
        }

        --count;
    }

    public String toString() {
        String rv = "\nparent: { ";

        for ( int i = 0; i < parent.length; ++i ) {
            rv += i + " : " + parent[ i ] + " | ";
        }
        rv += "}; \nheight: { ";
        for ( int i = 0; i < height.length; ++i ) {
            rv += i + " : " + height[ i ] + " | ";
        }

        rv += "}";
        return rv;
    }

    public static void main( String[] args ) {
        WeightedQuickUnionByHeight wQuickUnion = new WeightedQuickUnionByHeight( 19 );

        StdOut.println( "\nDEBUG: original: " + wQuickUnion.toString() );

        /* wQuickUnion.union( 0, 1 );
        StdOut.println( "\nDEBUG: p : 0 ; q : 1 : " + wQuickUnion.toString() );

        wQuickUnion.union( 2, 3 );
        StdOut.println( "\nDEBUG: p : 2 ; q : 3 : " + wQuickUnion.toString() );

        wQuickUnion.union( 2, 1 );
        StdOut.println( "\nDEBUG: p : 2 ; q : 1 : " + wQuickUnion.toString() ); */

        wQuickUnion.union(0, 1);
        wQuickUnion.union(0, 2);
        wQuickUnion.union(0, 3);
        wQuickUnion.union(6, 7);
        wQuickUnion.union(8, 9);
        wQuickUnion.union(6, 8);
        wQuickUnion.union(0, 6);
        wQuickUnion.union(10, 11);
        wQuickUnion.union(10, 12);
        wQuickUnion.union(10, 13);
        wQuickUnion.union(10, 14);
        wQuickUnion.union(10, 15);
        wQuickUnion.union(10, 16);
        wQuickUnion.union(10, 17);
        wQuickUnion.union(10, 18);
        wQuickUnion.union(0, 10);

        StdOut.println("Components: " + wQuickUnion.count() + " Expected: 3");
        StdOut.println("Maximum height: " + java.util.Arrays.toString( wQuickUnion.height ) + " Expected: Equal or less than 5 for N = 19" +
                " (lg 19 = 5)");
    }
}
