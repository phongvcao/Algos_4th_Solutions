package com.company;
import edu.princeton.cs.algs4.*;

public class RedBlackAVLTree< Key extends Comparable< Key >, Value > {

    private class Node {
        private Key key = null;
        private Value value = null;
        private int N = 0;
        private Node left = null;
        private Node right = null;
        private int height = 0;

        public Node( Key key, Value value, int height, int N ) {
            this.key = key;
            this.value = value;
            this.height = height;
            this.N = N;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value + " ; size : " + this.N + " ; height : " + this.height;
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
            rv += " | \n";
            return rv;
        }
    }

    private Node root = null;

    private Node rotateLeft( Node h ) {
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.N = h.N;
        h.N = size( h.left ) + size( h.right ) + 1;
        x.height = 1 + Math.max( height( x.left ), height( x.right ) );
        h.height = 1 + Math.max( height( h.left ), height( h.right ) );
        return x;
    }

    private Node rotateRight( Node h ) {
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.N = h.N;
        h.N = size( h.left ) + size( h.right ) + 1;
        x.height = 1 + Math.max( height( x.left ), height( x.right ) );
        h.height = 1 + Math.max( height( h.left ), height( h.right ) );
        return x;
    }

    private int balanceFactor( Node h ) {
        return height( h.left ) - height( h.right );
    }

    private Node balance( Node h ) {
        if ( balanceFactor( h ) < -1 ) {
            if ( balanceFactor( h.right ) > 0 ) {
                h.right = rotateRight( h.right );
            }
            h = rotateLeft( h );
        } else if ( balanceFactor( h ) > 1 ) {
            if ( balanceFactor( h.left ) < 0 ) {
                h.left = rotateLeft( h.left );
            }
            h = rotateRight( h );
        }
        return h;
    }

    public void put( Key key, Value value ) {
        root = put( root, key, value );
    }

    public Node put( Node h, Key key, Value value ) {
        if ( h == null ) return new Node( key, value, 0, 1 );
        int cmp = key.compareTo( h.key );
        if ( cmp < 0 ) {
            h.left = put( h.left, key, value );
        } else if ( cmp > 0 ) {
            h.right = put( h.right, key, value );
        } else {
            h.value = value;
            return h;
        }

        h.N = size( h.left ) + size( h.right ) + 1;
        h.height = 1 + Math.max( height( h.left ), height( h.right ) );
        return balance( h );
    }

    public int size() {
        return size( root );
    }

    public int size( Node h ) {
        if ( h == null ) {
            return 0;
        } else {
            return h.N;
        }
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int height() {
        return height( root );
    }

    public int height( Node h ) {
        if ( h == null ) {
            return 0;
        } else {
            return h.height;
        }
    }

    public int heightRecursively() {
        return heightRecursively( root, 0 );
    }

    public int heightRecursively( Node h, int count ) {
        if ( h == null ) return count;
        int leftHeight = heightRecursively( h.left, count );
        int rightHeight = heightRecursively( h.right, count );
        return leftHeight < rightHeight ? rightHeight : leftHeight;
    }

    public String toString() {
        String rv = "\nROOT : " + root.key + "\n";
        rv += toString( root );
        return rv;
    }

    public String toString( Node h ) {
        if ( h == null ) return "";
        String rv = toString( h.left );
        rv += h.toString();
        rv += toString( h.right );
        return rv;
    }

    public Value get( Key key ) {
        return get( root, key ).value;
    }

    public Node get( Node h, Key key ) {
        if ( h == null ) return h;
        int cmp = key.compareTo( h.key );
        if ( cmp < 0 ) {
            return get( h.left, key );
        } else if ( cmp > 0 ) {
            return get( h.right, key );
        } else {
            return h;
        }
    }

    public Key min() {
        return min( root ).key;
    }

    public Node min( Node h ) {
        if ( h == null ) return h;
        if ( h.left == null ) return h;
        return min( h.left );
    }

    public Key max() {
        return max( root ).key;
    }

    public Node max( Node h ) {
        if ( h == null ) return h;
        if ( h.right == null ) return h;
        return max( h.right );
    }

    public int rank( Key key ) {
        return rank( root, key );
    }

    public int rank( Node h, Key key ) {
        if ( h == null ) return 0;
        int cmp = key.compareTo( h.key );
        if ( cmp < 0 ) {
            return rank( h.left, key );
        } else if ( cmp > 0 ) {
            return rank( h.right, key ) + 1 + size( h.left );
        } else {
            return 0;
        }
    }

    public Key select( int k ) {
        return select( root, k ).key;
    }

    public Node select( Node h, int k ) {
        if ( h == null ) return h;
        int size = size( h.left );
        if ( k < size ) {
            return select( h.left, k );
        } else if ( k > size ) {
            return select( h.right, k - size - 1 );
        } else {
            return h;
        }
    }

    public Key floor( Key key ) {
        return floor( root, key ).key;
    }

    public Node floor( Node h, Key key ) {
        if ( h == null ) return h;
        int cmp = key.compareTo( h.key );
        if ( cmp < 0 ) {
            return floor( h.left, key );
        } else if ( cmp == 0 ) {
            return h;
        }

        Node temp = floor( h.right, key );
        if ( temp != null ) {
            return temp;
        }
        return h;
    }

    public Key ceiling( Key key ) {
        return ceiling( root, key ).key;
    }

    public Node ceiling( Node h, Key key ) {
        if ( h == null ) return h;
        int cmp = key.compareTo( h.key );
        if ( cmp > 0 ) {
            return ceiling( h.right, key );
        } else if ( cmp == 0 ) {
            return h;
        }

        Node temp = ceiling( h.left, key );
        if ( temp != null ) {
            return temp;
        }
        return h;
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

    public void keys( Node h, Queue< Key > queue, Key low, Key high ) {
        if ( h == null ) return;
        int cmpLow = h.key.compareTo( low );
        int cmpHigh = h.key.compareTo( high );
        if ( cmpLow < 0 ) return;
        if ( cmpHigh > 0 ) return;
        keys( h.left, queue, low, high );
        queue.enqueue( h.key );
        keys( h.right, queue, low, high );
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        RedBlackAVLTree< String, String > bst = new RedBlackAVLTree< String, String >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst: " + bst.toString() );
        StdOut.println( "DEBUG: bst.height(): " + bst.height() );
    }
}
