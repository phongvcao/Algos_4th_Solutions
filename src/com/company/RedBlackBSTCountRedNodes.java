package com.company;
import edu.princeton.cs.algs4.*;

public class RedBlackBSTCountRedNodes< Key extends Comparable< Key >, Value > {

    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private class Node {
        private Key key = null;
        private Value value = null;
        private Node left = null;
        private Node right = null;
        private int N = 0;
        private boolean color = RED;

        public Node( Key key, Value value, int N, boolean color ) {
            this.key = key;
            this.value = value;
            this.N = N;
            this.color = color;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value + " ; size : " + this.N + " ; color : " + this.color;
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

    public int countRedNodes() {
        return countRedNodes( root, 0 );
    }

    public int countRedNodes( Node h, int count ) {
        if ( h == null ) return 0;
        if ( isRed( h ) ) ++count;
        int leftRedCount = countRedNodes( h.left, count );
        int rightRedCount = countRedNodes( h.right, count );
        return count + leftRedCount + rightRedCount;
    }

    private boolean isRed( Node h ) {
        if ( h == null ) return false;
        return h.color == RED;
    }

    private Node rotateLeft( Node h ) {
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = size( h.left ) + size( h.right ) + 1;
        return x;
    }

    private Node rotateRight( Node h ) {
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = size( h.left ) + size( h.right ) + 1;
        return x;
    }

    private void flipColors( Node h ) {
        h.color = ! h.color;
        h.left.color = ! h.left.color;
        h.right.color = ! h.right.color;
    }

    public void put( Key key, Value value ) {
        root = put( root, key, value );
        root.color = BLACK;
    }

    public Node put( Node h, Key key, Value value ) {
        if ( h == null ) return new Node( key, value, 1, RED );
        int cmp = key.compareTo( h.key );
        if ( cmp < 0 ) {
            h.left = put( h.left, key, value );
        } else if ( cmp > 0 ) {
            h.right = put( h.right, key, value );
        } else {
            h.value = value;
        }

        if ( isRed( h.right ) && ! isRed( h.left ) ) h = rotateLeft( h );
        if ( isRed( h.left ) && isRed( h.left.left ) ) h = rotateRight( h );
        if ( isRed( h.left ) && isRed( h.right ) ) flipColors( h );

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
        return height( root, -1 );
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
            return size( h.left );
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
            return select( h.right, k - 1 - size );
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

    public Key min() {
        return min( root ).key;
    }

    public Node min( Node h ) {
        if ( h == null ) return null;
        if ( h.left == null ) return h;
        return min( h.left );
    }

    public Key max() {
        return max( root ).key;
    }

    public Node max( Node h ) {
        if ( h == null ) return null;
        if ( h.right == null ) return h;
        return max( h.right );
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

    private Node balance( Node h ) {
        if ( isRed( h.right ) ) h = rotateLeft( h );
        if ( isRed( h.left ) && isRed( h.left.left ) ) h = rotateRight( h );
        if ( isRed( h.left ) && isRed( h.right ) ) flipColors( h );

        h.N = size( h.left ) + size( h.right ) + 1;
        return h;
    }

    private Node moveRedLeft( Node h ) {
        flipColors( h );
        if ( isRed( h.right.left ) ) {
            h.right = rotateRight( h.right );
            h = rotateLeft( h );
            flipColors( h );
        }
        return h;
    }

    private Node moveRedRight( Node h ) {
        flipColors( h );
        if ( isRed( h.left.left ) ) {
            h = rotateRight( h );
            flipColors( h );
        }
        return h;
    }

    public void deleteMin() {
        if ( ! isRed( root.left ) && ! isRed( root.right ) ) {
            root.color = RED;
        }
        root = deleteMin( root );
        if ( ! isEmpty() ) root.color = BLACK;
    }

    public Node deleteMin( Node h ) {
        if ( h.left == null ) return null;
        if ( ! isRed( h.left ) && ! isRed( h.left.left ) ) {
            h = moveRedLeft( h );
        }
        h.left = deleteMin( h.left );
        return balance( h );
    }

    public void deleteMax() {
        if ( ! isRed( root.left ) && ! isRed( root.right ) ) {
            root.color = RED;
        }
        root = deleteMax( root );
        if ( ! isEmpty() ) root.color = BLACK;
    }

    public Node deleteMax( Node h ) {
        if ( isRed( h.left ) ) {
            h = rotateRight( h );
        }
        if ( h.right == null ) return null;
        if ( ! isRed( h.right ) && ! isRed( h.right.left ) ) {
            h = moveRedRight( h );
        }
        h.right = deleteMax( h.right );
        return balance( h );
    }

    public void delete( Key key ) {
        if ( ! isRed( root.left ) && ! isRed( root.right ) ) {
            root.color = RED;
        }
        root = delete( root, key );
        if ( ! isEmpty() ) root.color = BLACK;
    }

    public Node delete( Node h, Key key ) {
        if ( h == null ) return h;
        int cmp = key.compareTo( h.key );
        if ( cmp < 0 ) {
            if ( h.left == null ) return null;
            if ( ! isRed( h.left ) && isRed( h.left.left ) ) {
                h = moveRedLeft( h );
            }
            h.left = delete( h.left, key );
        } else {
            if ( isRed( h.left ) ) {
                h = rotateRight( h );
            }
            if ( key.compareTo( h.key ) == 0 && h.right == null ) return null;
            if ( ! isRed( h.right ) && ! isRed( h.right.left ) ) {
                h = moveRedRight( h );
            }
            if ( key.compareTo( h.key ) == 0 ) {
                Node temp = h;
                h = min( temp.right );
                h.right = deleteMin( temp.right );
                h.left = temp.left;
            } else {
                h.right = delete( h.right, key );
            }
        }
        return balance( h );
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        RedBlackBSTCountRedNodes< String, String > bst = new RedBlackBSTCountRedNodes< String, String >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst: " + bst.toString() );
        StdOut.println( "DEBUG: size: " + bst.size() );
        StdOut.println( "DEBUG: height: " + bst.height() );
        StdOut.println( "DEBUG: get( M ): " + bst.get( "M" ) );
        StdOut.println( "DEBUG: get( H ): " + bst.get( "H" ) );
        StdOut.println( "DEBUG: get( L ): " + bst.get( "L" ) );
        StdOut.println( "DEBUG: rank( L ): " + bst.rank( "L" ) );
        StdOut.println( "DEBUG: rank( C ): " + bst.rank( "C" ) );
        StdOut.println( "DEBUG: select( 1 ): " + bst.select( 1 ) );
        StdOut.println( "DEBUG: min(): " + bst.min() );
        StdOut.println( "DEBUG: max(): " + bst.max() );
        StdOut.println( "DEBUG: floor( C ): " + bst.floor( "C" ) );
        StdOut.println( "DEBUG: floor( D ): " + bst.floor( "D" ) );
        StdOut.println( "DEBUG: ceiling( C ): " + bst.ceiling( "C" ) );
        StdOut.println( "DEBUG: ceiling( D ): " + bst.ceiling( "D" ) );
        StdOut.println( "DEBUG: keys(): " + bst.keys() );
        StdOut.println( "DEBUG: countRedNodes(): " + bst.countRedNodes() );

        bst.deleteMin();
        StdOut.println( "DEBUG: keys() (AFTER deleteMin()): " + bst.keys() );
        StdOut.println( "DEBUG: bst (AFTER deleteMin()): " + bst.toString() );

        bst.deleteMax();
        StdOut.println( "DEBUG: keys() (AFTER deleteMax()): " + bst.keys() );
        StdOut.println( "DEBUG: bst (AFTER deleteMax()): " + bst.toString() );

        bst.delete( "L" );
        StdOut.println( "DEBUG: keys() (AFTER delete( L )): " + bst.keys() );
        StdOut.println( "DEBUG: bst (AFTER delete( L )): " + bst.toString() );
    }
}
