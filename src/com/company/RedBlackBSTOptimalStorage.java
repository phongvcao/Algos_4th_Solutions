package com.company;
import edu.princeton.cs.algs4.*;

public class RedBlackBSTOptimalStorage< Key extends Comparable< Key >, Value > {

    // The Node is BLACK by default, unlike original implementation
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
            rv += " | ";
            return rv;
        }
    }

    private Node root = null;

    private boolean isRed( Node h, Node parent ) {
        if ( h == null ) return false;
        if ( parent == null ) return false;
        // If h has no sibling, h is RED
        if ( parent.left != null && parent.right == null ) {
            return true;
        }

        if ( parent.right != null && parent.left == null ) {
            return true;
        }

        // If either or both of h children is NULL, h is BLACK
        if ( h.left == null || h.right == null ) {
            return false;
        }

        // If h has sibling, then:
        // - If h has either of the children NULL, h is BLACK (since the child will be RED since the child has no sibling)
        // - If h has both children not NULL, compare the children to see if they're swapped
        return h.left.key.compareTo( h.right.key ) > 0;
    }

    public Node swapChildren( Node h ) {
        // if ( h == null ) return h;
        Node temp = h.left;
        h.left = h.right;
        h.right = temp;
        return h;
    }

    public Node rotateLeft( Node h, Node parent ) {
        // OLD CODE
        boolean isHRedOriginally = isRed( h, parent );
        if ( isHRedOriginally ) {
            swapChildren( h );
        }

        Node x = h.right;

        boolean isXRedOriginally = isRed( h.right, h );
        if ( isXRedOriginally ) {
            swapChildren( x );
        }

        h.right = x.left;
        x.left = h;

        swapChildren( h );

        if ( isHRedOriginally ) {
            swapChildren( x );
        }

        // x.color = h.color;
        // h.color = RED;
        x.N = h.N;
        h.N = size( h.left ) + size( h.right ) + 1;
        // END OF OLD CODE
        return x;
    }

    public Node rotateRight( Node h, Node parent ) {
        // OLD CODE
        boolean isHRedOriginally = isRed( h, parent );
        if ( isHRedOriginally ) {
            swapChildren( h );
        }

        Node x = h.left;

        boolean isXRedOriginally = isRed( h.left, h );
        if ( isXRedOriginally ) {
            swapChildren( x );
        }

        h.left = x.right;
        x.right = h;

        swapChildren( h );

        if ( isHRedOriginally ) {
            swapChildren( x );
        }

        // x.color = h.color;
        // h.color = RED;
        x.N = h.N;
        h.N = size( h.left ) + size( h.right ) + 1;
        // END OF OLD CODE
        return x;
    }

    public void flipColors( Node h ) {
        swapChildren( h );
        swapChildren( h.left );
        swapChildren( h.right );
    }

    public void put( Key key, Value value ) {
        root = put( root, null, key, value );
    }

    // NEEDS MODIFICATION
    public Node put( Node h, Node parent, Key key, Value value ) {
        if ( h == null ) return new Node( key, value, 1 );
        int cmp = key.compareTo( h.key );
        if ( cmp < 0 ) {
            if ( ! isRed( h, parent ) ) {
                h.left = put( h.left, h, key, value );
            } else {
                h.right = put( h.right, h, key, value );
            }
        } else if ( cmp > 0 ) {
            if ( ! isRed( h, parent ) ) {
                h.right = put( h.right, h, key, value );
            } else {
                h.left = put( h.left, h, key, value );
            }
        } else {
            h.value = value;
        }

        if ( ! isRed( h, parent ) && ! isRed( h.left, h ) && ! isRed( h.right, h ) ) swapChildren( h );
        if ( isRed( h.right, h ) && ! isRed( h.left, h ) ) h = rotateLeft( h, parent );
        if ( isRed( h.left, h ) && isRed( h.left.left, h.left ) ) h = rotateRight( h, parent );
        if ( isRed( h.left, h ) && isRed( h.right, h ) ) flipColors( h );

        h.N = size( h.left ) + size( h.right ) + 1;
        return h;
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
        return height( root, 0 );
    }

    public int height( Node h, int count ) {
        if ( h == null ) return count;
        int leftHeight = height( h.left, count + 1 );
        int rightHeight = height( h.right, count + 1 );
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

    // NEEDS MODIFICATION
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

    // NEEDS MODIFICATION
    public Node min( Node h ) {
        if ( h == null ) return h;
        if ( h.left == null ) return h;
        return min( h.left );
    }

    public Key max() {
        return max( root ).key;
    }

    // NEEDS MODIFICATION
    public Node max( Node h ) {
        if ( h == null ) return h;
        if ( h.right == null ) return h;
        return max( h.right );
    }

    public int rank( Key key ) {
        return rank( root, key );
    }

    // NEEDS MODIFICATION
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

    // NEEDS MODIFICATION
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

    // NEEDS MODIFICATION
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

    // NEEDS MODIFICATION
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
        RedBlackBSTOptimalStorage< String, String > bst = new RedBlackBSTOptimalStorage< String, String >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst.toString(): " + bst.toString() );
        StdOut.println( "DEBUG: bst.height(): " + bst.height() );
        StdOut.println( "DEBUG: bst.min(): " + bst.min() );
        StdOut.println( "DEBUG: bst.max(): " + bst.max() );
        StdOut.println( "DEBUG: bst.keys(): " + bst.keys() );
    }
}
