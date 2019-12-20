package com.company;
import edu.princeton.cs.algs4.*;

public class MyBST3< Key extends Comparable< Key >, Value > {

    private class Node {
        private Key key = null;
        private Value value = null;
        private int N = 0;
        private Node left = null;
        private Node right = null;

        public Node( Key key, Value value, int N ) {
            this.key = key;
            this.value = value;
            this.N = N;
        }

        public String toString() {
            String rv = "";
            rv += " | " + this.key + " : " + this.value;

            if ( this.left != null ) {
                rv += " ; left : " + this.left;
            } else {
                rv += " ; left : null";
            }

            if ( this.right != null ) {
                rv += " ; right : " + this.right;
            } else {
                rv += " ; right : null";
            }

            rv += " | ";
            return rv;
        }
    }

    private Node root = null;

    public MyBST3() {

    }

    public void put( Key key, Value value ) {
        root = put( root, key, value );
    }

    public Node put( Node x, Key key, Value value ) {
        if ( x == null ) {
            return new Node( key, value, 1 );
        }

        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            x.left = put( x.left, key, value );
        } else if ( cmp > 0 ) {
            x.right = put( x.right, key, value );
        } else {
            x.value = value;
        }
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public Value get( Key key ) {
        return get( root, key );
    }

    public Value get( Node x, Key key ) {
        if ( x == null ) {
            return null;
        }

        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return get( x.left, key );
        } else if ( cmp > 0 ) {
            return get( x.right, key );
        } else {
            return x.value;
        }
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

    public Key floor( Key key ) {
        return floor( root, key ).key;
    }

    public Node floor( Node x, Key key ) {
        if ( x == null ) return null;

        int cmp = key.compareTo( x.key );
        if ( cmp == 0 ) return x;
        else if ( cmp < 0 ) return floor( x, key );

        Node t = floor( x.right, key );
        if ( t != null ) return t;
        else return x;
    }

    public int height() {
        return height( root, -1 );
    }

    public int height( Node x, int count ) {
        if ( x == null ) return count;
        int leftHeight = height( x.left, count + 1 );
        int rightHeight = height( x.right, count + 1 );
        return leftHeight < rightHeight ? rightHeight : leftHeight;
    }

    public Key select( int k ) {
        return select( root, k ).key;
    }

    public Node select( Node x, int k ) {
        if ( x == null ) return null;

        int size = size( x.left );
        if ( k == size ) return x;
        else if ( k < size ) return select( x.left, k );
        else return select( x.right, k - size - 1 );
    }

    public Key min() {
        return min( root ).key;
    }

    public Node min( Node x ) {
        if ( x == null ) {
            return x;
        }

        if ( x.left == null ) {
            return x;
        }
        return min( x.left );
    }

    public Key max() {
        return max( root ).key;
    }

    public Node max( Node x ) {
        if ( x == null ) {
            return x;
        }

        if ( x.right == null ) {
            return x;
        }
        return max( x.right );
    }

    public String toString() {
        return toString( root );
    }

    public String toString( Node x ) {
        if ( x == null ) {
            return "";
        }

        String rv = "";
        rv += toString( x.left );
        rv += x.toString();
        rv += toString( x.right );

        return rv;
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
            return 1 + size( x.left ) + rank( x.right, key );
        } else {
            return size( x.left );
        }
    }

    public static void main( String[] args ) {

    }
}
