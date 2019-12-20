package com.company;
import edu.princeton.cs.algs4.*;

public class PriorityQueueStockMarketTrading {

    private static class Buyer implements Comparable< Buyer > {
        private Integer numShares = null;
        private Double maxPrice = null;
        private Integer id = null;

        public Buyer( Integer id, Double maxPrice, Integer numShares ) {
            this.id = id;
            this.maxPrice = maxPrice;
            this.numShares = numShares;
        }

        public int compareTo( Buyer other ) {
            int cmp = this.maxPrice.compareTo( other.maxPrice );
            if ( cmp != 0 ) {
                return cmp;
            }

            return this.numShares.compareTo( other.numShares );
        }

        public boolean canTransact( Seller seller ) {
            return this.maxPrice >= seller.minPrice;
        }

        public int transact( Seller seller ) {
            if ( ! canTransact( seller ) ) {
                return 0;
            }
            int transactedShares = 0;

            int cmp = this.numShares.compareTo( seller.numShares );

            if ( cmp == -1 ) {
                seller.numShares -= this.numShares;
                transactedShares = this.numShares;
                this.numShares = 0;
            } else {
                this.numShares -= seller.numShares;
                transactedShares = seller.numShares;
                seller.numShares = 0;
            }

            return transactedShares;
        }

        public String toString() {
            return this.id + " " + this.maxPrice + " " + this.numShares;
        }
    }

    private static class Seller implements Comparable< Seller > {
        private Integer numShares = null;
        private Double minPrice = null;
        private Integer id = null;

        public Seller( Integer id, Double minPrice, Integer numShares ) {
            this.id = id;
            this.minPrice = minPrice;
            this.numShares = numShares;
        }

        public int compareTo( Seller other ) {
            int cmp = this.minPrice.compareTo( other.minPrice );
            if ( cmp != 0 ) {
                return cmp;
            }

            return this.numShares.compareTo( other.numShares );
        }

        public boolean canTransact( Buyer buyer ) {
            return this.minPrice <= buyer.maxPrice;
        }

        public int transact( Buyer buyer ) {
            if ( ! canTransact( buyer ) ) {
                return 0;
            }
            int transactedShares = 0;

            int cmp = this.numShares.compareTo( buyer.numShares );

            if ( cmp == -1 ) {
                buyer.numShares -= this.numShares;
                transactedShares = this.numShares;
                this.numShares = 0;
            } else {
                this.numShares -= buyer.numShares;
                transactedShares = buyer.numShares;
                buyer.numShares = 0;
            }

            return transactedShares;
        }

        public String toString() {
            return this.id + " " + this.minPrice + " " + this.numShares;
        }
    }

    private static class MaxMinPQ< Key extends Comparable< Key > > {
        private Key[] pq;
        private int N = 0;
        private boolean isMaxPQ = true;

        public MaxMinPQ( int size, boolean isMaxPQ ) {
            pq = ( Key[] )new Comparable[ size + 1 ];
            this.isMaxPQ = isMaxPQ;
        }

        private void sink( int k ) {
            while ( 2 * k <= N ) {
                int j = 2 * k;

                if ( this.isMaxPQ ) {
                    if ( j < N && less( j, j + 1 ) ) ++j;
                    if ( ! less( k, j ) ) break;
                } else {
                    if ( j < N && less( j + 1, j ) ) ++j;
                    if ( ! less( j, k ) ) break;
                }
                exchange( k, j );
                k = j;
            }
        }

        private void swim( int k ) {
            if ( this.isMaxPQ ) {
                while ( k > 1 && less( k / 2, k ) ) {
                    exchange( k / 2, k );
                    k /= 2;
                }
            } else {
                while ( k > 1 && less( k, k / 2 ) ) {
                    exchange( k / 2, k );
                    k /= 2;
                }
            }
        }

        public void insert( Key value ) {
            pq[ ++N ] = value;
            swim( N );
        }

        public Key delRoot() {
            Key root = pq[ 1 ];
            exchange( 1, N-- );
            pq[ N + 1 ] = null;
            sink( 1 );
            return root;
        }

        public Key root() {
            return pq[ 1 ];
        }

        private boolean less( int i, int j ) {
            return pq[ i ].compareTo( pq[ j ] ) == -1;
        }

        private void exchange( int i, int j ) {
            Key temp = pq[ i ];
            pq[ i ] = pq[ j ];
            pq[ j ] = temp;
        }

        public String toString() {
            return java.util.Arrays.toString( pq );
        }
    }

    public static void main( String[] args ) {
        Integer[] buyerArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] sellerArr = { 24, 22, 20, 18, 16, 14, 12, 10, 11, 13, 15, 17, 19, 21, 23 };
        MaxMinPQ< Buyer > buyerMaxPQ = new MaxMinPQ< Buyer >( buyerArr.length, true );
        MaxMinPQ< Seller > sellerMinPQ = new MaxMinPQ< Seller >( sellerArr.length, false );

        for ( int i = 0; i < buyerArr.length; ++i ) {
            buyerMaxPQ.insert( new Buyer( buyerArr[ i ], (Double)(double)buyerArr[ i ], buyerArr[ i ] ) );
        }

        StdOut.println( "DEBUG: buyerMaxPQ (BEFORE): " + buyerMaxPQ.toString() );

        for ( int i = 0; i < sellerArr.length; ++i ) {
            sellerMinPQ.insert( new Seller( sellerArr[ i ], (Double)(double)sellerArr[ i ], sellerArr[ i ] ) );
        }

        StdOut.println( "DEBUG: sellerMinPQ (BEFORE): " + sellerMinPQ.toString() );

        while ( buyerMaxPQ.root().canTransact( sellerMinPQ.root() ) ) {
            Buyer buyerRoot = buyerMaxPQ.delRoot();
            Seller sellerRoot = sellerMinPQ.delRoot();

            int transactedShares = buyerRoot.transact( sellerRoot );
            if ( buyerRoot.numShares > 0 ) {
                buyerMaxPQ.insert( buyerRoot );
            }
            if ( sellerRoot.numShares > 0 ) {
                sellerMinPQ.insert( sellerRoot );
            }

            StdOut.println( "DEBUG: Transaction: Buyer : " + buyerRoot.id + " ; Seller : " + sellerRoot.id + " ; transactedShares : " + transactedShares );
        }

        StdOut.println( "DEBUG: buyerMaxPQ (AFTER): " + buyerMaxPQ.toString() );
        StdOut.println( "DEBUG: sellerMinPQ (AFTER): " + sellerMinPQ.toString() );
    }
}
