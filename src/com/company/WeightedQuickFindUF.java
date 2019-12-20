package com.company;
import edu.princeton.cs.algs4.*;

public class WeightedQuickFindUF {

    private int[] id;
    private int[] sz;
    private int count;

    public WeightedQuickFindUF( int N ) {
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

    public int find( int p ) {
        return id[ p ];
    }

    public void union( int p, int q ) {
        int pID = find( p );
        int qID = find( q );
        if ( pID == qID ) return;

        // Implement weighted quick-find
        if ( sz[ pID ] > sz[ qID ] ) {
            for ( int i = 0; i < id.length; ++i ) {
                if ( id[ i ] == qID ) {
                    id[ i ] = pID;
                    ++sz[ pID ];
                }
            }
        } else {
            for ( int i = 0; i < id.length; ++i ) {
                if ( id[ i ] == pID ) {
                    id[ i ] = qID;
                    ++sz[ qID ];
                }
            }
        }

        --count;
    }

    public static void main( String[] args ) {
        WeightedQuickFindUF wQuickFind = new WeightedQuickFindUF( 10 );

        wQuickFind.union( 0, 9 );
        wQuickFind.union( 1, 8 );
        wQuickFind.union( 2, 7 );
        wQuickFind.union( 3, 0 );
        wQuickFind.union( 4, 3 );

        StdOut.println( "DEBUG: Components: " + wQuickFind.count() + " Expected: 5" );;
    }
}
