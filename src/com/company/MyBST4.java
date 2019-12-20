package com.company;
import edu.princeton.cs.algs4.*;

public class MyBST4< Key extends Comparable< Key >, Value > {

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
                rv += " ; left : " + this.left.key;
            } else {
                rv += " ; left : null";
            }

            if ( this.right != null ) {
                rv += " ; right : " + this.right.key;
            } else {
                rv += " ; right : null";
            }
            rv += " | ";
            return rv;
        }
    }

    private Node root = null;

    public MyBST4() {
        // Not implemented
    }

    public boolean isEmpty() {
        return size() == 0;
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

    public void put( Key key, Value value ) {
        root = put( root, key, value );
    }

    public Node put( Node x, Key key, Value value ) {
        if ( x == null ) {
            return new Node( key, value, 1 );
        }

        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return put( x.left, key, value );
        } else if ( cmp > 0 ) {
            return put( x.right, key, value );
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
        if ( x == null ) {
            return null;
        }

        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return get( x.left, key );
        } else if ( cmp > 0 ) {
            return get( x.right, key );
        } else {
            return x;
        }
    }

    public Key min() {
        return min( root ).key;
    }

    public Node min( Node x ) {
        if ( x == null ) {
            return null;
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
            return null;
        }

        if ( x.right == null ) {
            return x;
        }
        return max( x.right );
    }

    public Key select( int k ) {
        return select( root, k ).key;
    }

    public Node select( Node x, int k ) {
        if ( x == null ) {
            return null;
        }
        int size = size( x.left );
        if ( k > size ) {
            // Recurse on the right
            return select( x.right, k - size - 1 );
        } else if ( k < size ) {
            return select( x.left, k );
        } else {
            return x;
        }
    }

    public int rank( Key key ) {
        return rank( root, key );
    }

    public int rank( Node x, Key key ) {
        if ( x == null ) {
            return 0;
        }

        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return rank( x.left, key );
        } else if ( cmp > 0 ) {
            return 1 + size( x.left ) + rank( x.right, key );
        } else {
            return size( x.left );
        }
    }

    public int height() {
        return height( root, -1 );
    }

    public int height( Node x, int count ) {
        if ( x == null ) return count;
        int leftHeight = height( x.left, count + 1 );
        int rightHeight = height( x.right, count + 1 );
        return count;
    }

    public Key floor( Key key ) {
        return floor( root, key ).key;
    }

    public Node floor( Node x, Key key ) {
        if ( x == null ) {
            return null;
        }

        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return floor( x.left, key );
        } else if ( cmp == 0 ) {
            return x;
        }

        Node t = floor( x.right, key );
        if ( t != null ) {
            return t;
        }
        return x;
    }

    public String toString() {
        return toString( root );
    }

    public String toString( Node x ) {
        if ( x == null ) return "";
        String rv = "";
        rv += toString( x.left );
        rv += x.toString();
        rv += toString( x.right );
        return rv;
    }

    public void deleteMin() {
        root = deleteMin( root );
    }

    public Node deleteMin( Node x ) {
        if ( x == null ) return null;

        if ( x.left == null ) return x.right;
        x.left = deleteMin( x.left );
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
     }

    public void delete( Key key ) {
        root = delete( root, key );
    }

    public Node delete( Node x, Key key ) {
        if ( x == null ) return null;
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            x.left = delete( x.left, key );
        } else if ( cmp > 0 ) {
            x.right = delete( x.right, key );
        } else {
            if ( x.right == null ) return x.left;
            if ( x.left == null ) return x.right;
            Node t = x;
            x = min( t.right );
            x.right = deleteMin( t.right );
            x.left = t.left;
        }
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public static void main( String[] args ) {

    }
}
