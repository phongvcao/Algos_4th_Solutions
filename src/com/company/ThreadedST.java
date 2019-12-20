package com.company;
import edu.princeton.cs.algs4.*;

public class ThreadedST< Key extends Comparable< Key >, Value > {

    private class Node {
        private Key key = null;
        private Value value = null;
        private int N = 0;
        private Node left = null;
        private Node right = null;
        private Node pred = null;
        private Node succ = null;

        public Node( Key key, Value value, int N ) {
            this.key = key;
            this.value = value;
            this.N = N;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value + " ; size : " + this.N;
            if ( this.left != null ) {
                rv += " ; left : " + this.left.key;
            } else {
                rv += " ; left : null";
            }

            if ( this.right != null ) {
                rv += " ; right : " + this.right.key;
            } else {
                rv += " ; right : null";
            }

            if ( this.pred != null ) {
                rv += " ; pred : " + this.pred.key;
            } else {
                rv += " ; pred : null";
            }

            if ( this.succ != null ) {
                rv += " ; succ : " + this.succ.key;
            } else {
                rv += " ; succ : null";
            }

            rv += " | ";
            return rv;
        }
    }

    private Node root = null;

    public ThreadedST() {
        // Not implemented
    }

    public void put( Key key, Value value ) {
        root = put( root, key, value, null, null );
    }

    public Node put( Node x, Key key, Value value, Node pred, Node succ ) {
        if ( x == null ) {
            Node newNode = new Node( key, value, 1 );

            if ( pred != null) {
                newNode.pred = pred;
                pred.succ = newNode;
            }

            if ( succ != null ) {
                newNode.succ = succ;
                succ.pred = newNode;
            }

            return newNode;
        }
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            x.left = put( x.left, key, value, pred, x );
        } else if ( cmp > 0 ) {
            x.right = put( x.right, key, value, x, succ );
        } else {
            x.value = value;
        }
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public Value get( Key key ) {
        return get( root, key ).value;
    }

    public Node get( Node x, Key key ) {
        if ( x == null ) return x;
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return get( x.left, key );
        } else if ( cmp > 0 ) {
            return get( x.right, key );
        } else {
            return x;
        }
    }

    public String toString() {
        String rv = "\nROOT : " + root.key + "\n";
        rv += toString( root );
        return rv;
    }

    public String toString( Node x ) {
        if ( x == null ) return "";
        String rv = toString( x.left );
        rv += x.toString();
        rv += toString( x.right );
        return rv;
    }

    public int size() {
        return size( root );
    }

    public int size( Node x ) {
        if ( x == null ) {
            return 0;
        } else {
            return x.N;
        }
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public Key min() {
        return min( root ).key;
    }

    public Node min( Node x ) {
        if ( x == null ) return x;
        if ( x.left == null ) return x;
        return min( x.left );
    }

    public Key max() {
        return max( root ).key;
    }

    public Node max( Node x ) {
        if ( x == null ) return x;
        if ( x.right == null ) return x;
        return max( x.right );
    }

    public int rank( Key key ) {
        return rank( root, key );
    }

    public int rank( Node x, Key key ) {
        if ( x == null ) return 0;
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return rank( x.left, key );
        } else if ( cmp > 0 ) {
            return rank( x.right, key ) + size( x.left ) + 1;
        } else {
            return size( x.left );
        }
    }

    public Key select( int k ) {
        return select( root, k ).key;
    }

    public Node select( Node x, int k ) {
        if ( x == null ) return x;
        int size = size( x.left );
        if ( k < size ) {
            return select( x.left, k );
        } else if ( k > size ) {
            return select( x.right, k - size - 1 );
        } else {
            return x;
        }
    }

    public void deleteMin() {
        root = deleteMin( root, true );
    }

    public Node deleteMin( Node x, boolean updateSuccAndPred ) {
        if ( x == null ) return x;
        if ( x.left == null ) {
            if ( x.succ != null ) {
                x.succ.pred = null;
            }
            return x.right;
        }

        x.left = deleteMin( x.left, updateSuccAndPred );
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public void deleteMax() {
        root = deleteMax( root );
    }

    public Node deleteMax( Node x ) {
        if ( x == null ) return x;
        if ( x.right == null ) {
            if ( x.pred != null ) {
                x.pred.succ = null;
            }
            return x.left;
        }

        x.right = deleteMax( x.right );
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public void delete( Key key ) {
        root = delete( root, key );
    }

    public Node delete( Node x, Key key ) {
        if ( x == null ) return x;
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            x.left = delete( x.left, key );
        } else if ( cmp > 0 ) {
            x.right = delete( x.right, key );
        } else {
            if ( x.pred == null || x.succ == null ) {
                if ( x.pred != null ) {
                    x.pred.succ = x.succ;
                }
                if ( x.succ != null ) {
                    x.succ.pred = x.pred;
                }

                if ( x.left == null ) {
                    return x.right;
                } else if ( x.right == null ) {
                    return x.left;
                }
            } else {
                Node temp = x;
                x = min( temp.right );
                x.right = deleteMin( temp.right, false );
                x.left = temp.left;

                x.pred = temp.pred;
                if ( x.pred != null ) {
                    x.pred.succ = x;
                }
            }
        }
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public Iterable< Key > keys() {
        return keys( min(), max() );
    }

    public Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > queue = new Queue< Key >();
        if ( low.compareTo( high ) > 0 ) return queue;
        keys( root, queue, low, high );
        return queue;
    }

    public void keys( Node x, Queue< Key > queue, Key low, Key high ) {
        if ( x == null ) return;
        int cmpLow = x.key.compareTo( low );
        int cmpHigh = x.key.compareTo( high );
        if ( cmpLow < 0 ) return;
        if ( cmpHigh > 0 ) return;
        keys( x.left, queue, low, high );
        queue.enqueue( x.key );
        keys( x.right, queue, low, high );
    }

    public Key next( Key key ) {
        return null;
    }

    public Key prev( Key key ) {
        return null;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static Comparable select( Comparable[] a, int k ) {
        int low = 0;
        int high = a.length - 1;

        while ( low <= high ) {
            int j = partition( a, low, high );
            if ( k < j ) {
                high = j - 1;
            } else if ( k > j ) {
                low = j + 1;
            } else {
                return a[ k ];
            }
        }
        return a[ k ];
    }

    public static int partition( Comparable[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        Comparable pivot = a[ low ];

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( i >= j ) break;
            exchange( a, i, j );
        }
        exchange( a, low, j );
        return j;
    }

    public static void main( String[] args ) {
        Integer[] keyArr = { 7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14 };
        Integer[] valueArr = { 7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14 };
        /* Integer[] keyArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] valueArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 }; */
        ThreadedST< Integer, Integer > bst = new ThreadedST< Integer, Integer >();

        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst: " + bst.toString() );
    }
}
