package com.company;
import edu.princeton.cs.algs4.*;

public class QuickUnionWithPathCompression {

    private int[] id;
    private int count;

    public QuickUnionWithPathCompression( int N ) {
        id = new int[ N ];
        count = N;

        for ( int i = 0; i < N; ++i ) {
            id[ i ] = i;
        }
    }

    public int count() {
        return count;
    }

    public int find( int p ) {
        int root = p;
        // Locate root of p
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
        // Find root of p
        int pID = find( p );

        // Find root of q
        int qID =  find( q );

        if ( pID == qID ) return;

        // Link root of p with root of q
        id[ pID ] = qID;
        --count;
    }

    public boolean connected( int p, int q ) {
        return find( p ) == find( q );
    }

    public String toString() {
        String rv = "{ ";

        for ( int i = 0; i < id.length; ++i ) {
            rv += i + " : " + id[ i ] + " | ";
        }
        rv += "}";
        return rv;
    }

    public static void main( String[] args ) {
        QuickUnionWithPathCompression qUnionPC = new QuickUnionWithPathCompression( 10 );

        StdOut.println( "DEBUG: " + qUnionPC.toString() );

        qUnionPC.union( 0, 1 );
        StdOut.println( "DEBUG: " + qUnionPC.toString() );

        qUnionPC.union( 2, 3 );
        StdOut.println( "DEBUG: " + qUnionPC.toString() );

        qUnionPC.union( 4, 5 );
        StdOut.println( "DEBUG: " + qUnionPC.toString() );

        qUnionPC.union( 6, 7 );
        StdOut.println( "DEBUG: " + qUnionPC.toString() );

        qUnionPC.union( 6, 4 );
        StdOut.println( "DEBUG: " + qUnionPC.toString() );

        qUnionPC.union( 4, 2 );
        StdOut.println( "DEBUG: " + qUnionPC.toString() );

        qUnionPC.union( 2, 0 );
        StdOut.println( "DEBUG: " + qUnionPC.toString() );

        /* qUnionPC.union( 6, 7 );
        StdOut.println( "DEBUG: " + qUnionPC.toString() ); */


    }
}
