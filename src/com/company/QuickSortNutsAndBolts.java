package com.company;
import edu.princeton.cs.algs4.*;

public class QuickSortNutsAndBolts {

    // Nut & Bolt classes
    private static class Nut {
        public Integer value = -1;
        public Integer id = -1;
        public Bolt bolt = null;

        public int compareTo( Bolt bolt ) {
            return this.value.compareTo( bolt.value );
        }
    }

    private static class Bolt {
        public Integer value = -1;
        public Integer id = -1;
        public Nut nut = null;

        public int compareTo( Nut nut ) {
            return this.value.compareTo( nut.value );
        }
    }
    // END OF Nut & Bolt class

    public static boolean equals( Nut a, Bolt b ) {
        return a.compareTo( b ) == 0;
    }

    public static boolean less( Nut a, Bolt b ) {
        return a.compareTo( b ) == -1;
    }

    public static boolean less( Bolt a, Nut b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchangeNut( Nut[] a, int i, int j ) {
        Nut temp = a [ i ];
        a[ i ] = a [ j ];
        a[ j ] = temp;
    }

    public static void exchangeBolt( Bolt[] a, int i, int j ) {
        Bolt temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void sort( Nut[] a, Bolt[] b, int low, int high ) {
        if ( low >= high ) return;

        Nut pivot = a[ low ];

        int boltPivotIdx = partitionBolt( b, pivot, low, high );
        int nutPivotIdx = partitionNut( a, b[ boltPivotIdx ], low, high );
        sort( a, b, low, boltPivotIdx - 1 );
        sort( a, b, low, nutPivotIdx - 1 );
        sort( a, b, boltPivotIdx + 1, high );
        sort( a, b, nutPivotIdx + 1, high );
    }

    public static int partitionNut( Nut[] a, Bolt pivot, int low, int high ) {
        int i = low - 1;
        int j = high + 1;

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( equals( a[ i ], pivot ) ) {
                pivot.nut = a[ i ];
                a[ i ].bolt = pivot;
            } else if ( equals( a[ j ], pivot ) ) {
                pivot.nut = a[ j ];
                a[ j ].bolt = pivot;
            }

            if ( i >= j ) break;

            exchangeNut( a, i, j );
        }

        StdOut.println( "DEBUG: partitionNut(): j : " + j );

        return j;
    }

    public static int partitionBolt( Bolt[] a, Nut pivot, int low, int high ) {
        int i = low - 1;
        int j = high + 1;

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( equals( pivot, a[ i ] ) ) {
                pivot.bolt = a[ i ];
                a[ i ].nut = pivot;
            } else if ( equals( pivot, a[ j ] ) ) {
                pivot.bolt = a[ j ];
                a[ j ].nut = pivot;
            }

            if ( i >= j ) break;

            exchangeBolt( a, i, j );
        }

        StdOut.println( "DEBUG: partitionBolt(): j : " + j );

        return j;
    }

    public static String toString( Nut[] a ) {
        String rv = "{";

        for ( int i = 0; i < a.length; ++i ) {
            rv += " | " + a[ i ].id + " : " + a [ i ].value;

            if ( a[ i ].bolt != null ) {
                rv += " : " + a[ i ].bolt.value;
            } else {
                rv += " : null";
            }
            rv += " | ;";
        }

        rv += " }";
        return rv;
    }

    public static String toString( Bolt[] a ) {
        String rv = "{";

        for ( int i = 0; i < a.length; ++i ) {
            rv += " | " + a[ i ].id + " : " + a [ i ].value;

            if ( a[ i ].nut != null ) {
                rv += " : " + a[ i ].nut.value;
            } else {
                rv += " : null";
            }
            rv += " | ;";
        }

        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        Integer[] nutIntArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Nut[] nutArr = new Nut[ nutIntArr.length ];

        for ( int i = 0; i < nutArr.length; ++i ) {
            nutArr[ i ] = new Nut();
            nutArr[ i ].id = i;
            nutArr[ i ].value = nutIntArr[ i ];
        }

        /* // DEBUG
        Bolt pivot = new Bolt();
        pivot.value = 2;
        pivot.id = 0;


        StdOut.println( "DEBUG: nutArr (BEFORE): " + toString( nutArr ) );

        partitionNut( nutArr, pivot, 0, nutArr.length - 1 );

        StdOut.println( "DEBUG: nutArr (AFTER): " + toString( nutArr ) );
        // END OF DEBUG */

        Integer[] boltIntArr = { 13, 11, 9, 7, 5, 3, 1, 0, 2, 4, 6, 8, 10, 12, 14 };
        Bolt[] boltArr = new Bolt[ boltIntArr.length ];

        for ( int i = 0; i < boltArr.length; ++i ) {
            boltArr[ i ] = new Bolt();
            boltArr[ i ].id = i;
            boltArr[ i ].value = boltIntArr[ i ];
        }

        StdOut.println( "DEBUG: nutArr (BEFORE): " + toString( nutArr ) );
        StdOut.println( "DEBUG: boltArr (BEFORE): " + toString( boltArr ) );

        sort( nutArr, boltArr, 0, nutArr.length - 1 );

        StdOut.println( "DEBUG: nutArr (AFTER): " + toString( nutArr ) );
        StdOut.println( "DEBUG: boltArr (AFTER): " + toString( boltArr ) );

        /* // DEBUG
        Nut pivot = new Nut();
        pivot.value = 2;
        pivot.id = 0;


        StdOut.println( "DEBUG: boltArr (BEFORE): " + toString( boltArr ) );

        partitionBolt( boltArr, pivot, 0, boltArr.length - 1 );

        StdOut.println( "DEBUG: boltArr (AFTER): " + toString( boltArr ) );
        // END OF DEBUG */

    }
}
