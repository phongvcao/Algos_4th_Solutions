package com.company;
import edu.princeton.cs.algs4.*;

public class RedBlackBSTCertification< Key extends Comparable< Key >, Value > {

    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private class Node {
        private Key key = null;
        private Value value = null;
        private int N = 0;
        private boolean color = RED;
        private Node left = null;
        private Node right = null;

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

        public int compareTo( Node other ) {
            return this.key.compareTo( other.key );
        }
    }

    private Node root = null;

    public boolean is23( Node h ) {
        // Check that no node is connected to 2 red links
        // Check that there are no right-leaning red links
        if ( h == null ) return true;
        if ( isRed( h.left ) && isRed( h.right ) ) return false;
        if ( isRed( h.right ) ) return false;
        return is23( h.left ) && is23( h.right );
    }

    public boolean isBalanced( Node h ) {
        // Check that all paths from the root to a null link have same number of black links
        Queue< Node > nodesQueue = new Queue< Node >();
        Queue< Integer > blackLinksQueue = new Queue< Integer >();
        nodesQueue.enqueue( h );
        blackLinksQueue.enqueue( 0 );
        Integer currentBlackLinkCount = -1;
        while ( ! nodesQueue.isEmpty() ) {
            Node node = nodesQueue.dequeue();
            Integer nodeBlackLink = blackLinksQueue.dequeue();
            /* StdOut.println( "DEBUG: CURRENT node: " + node );
            StdOut.println( "DEBUG: CURRENT nodeBlackLink: " + nodeBlackLink ); */
            if ( node != null ) {
                nodesQueue.enqueue( node.left );
                if ( ! isRed( node.left ) ) {
                    blackLinksQueue.enqueue( nodeBlackLink + 1 );
                } else {
                    blackLinksQueue.enqueue( nodeBlackLink );
                }

                nodesQueue.enqueue( node.right );
                if ( ! isRed( node.right ) ) {
                    blackLinksQueue.enqueue( nodeBlackLink + 1 );
                } else {
                    blackLinksQueue.enqueue( nodeBlackLink );
                }
            } else {
                if ( currentBlackLinkCount == -1 ) {
                    currentBlackLinkCount = nodeBlackLink;
                    /* StdOut.println( "DEBUG: currentBlackLinkCount: " + currentBlackLinkCount );
                    StdOut.println( "DEBUG: node: " + node ); */
                } else {
                    if ( currentBlackLinkCount.compareTo( nodeBlackLink ) != 0 ) {
                        /* StdOut.println( "DEBUG: currentBlackLinkCount: " + currentBlackLinkCount );
                        StdOut.println( "DEBUG: nodeBlackLink: " + nodeBlackLink );
                        StdOut.println( "DEBUG: node: " + node ); */
                        return false;
                    }
                }
            }
        }
        return true;
    }

    public boolean isBST( Node h ) {
        // Returns true if the argument node is the root of a binary search tree, false otherwise
        Queue< Node > nodesQueue = new Queue< Node >();
        nodesQueue.enqueue( h );
        while ( ! nodesQueue.isEmpty() ) {
            Node node = nodesQueue.dequeue();
            if ( node != null ) {
                if ( node.left != null ) {
                    if ( node.left.compareTo( node ) > 0 ) {
                        return false;
                    }
                }

                if ( node.right != null ) {
                    if ( node.right.compareTo( node ) < 0 ) {
                        return false;
                    }
                }

                nodesQueue.enqueue( node.left );
                nodesQueue.enqueue( node.right );
            }
        }

        return true;
    }

    public boolean isRedBlackBST( Node h ) {
        // Check that the tree is a red-black BST
        return isBST( h ) && is23( h ) && isBalanced( h );
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
        h.color = RED;
        h.left.color = BLACK;
        h.right.color = BLACK;
    }

    private boolean isRed( Node h ) {
        if ( h == null ) return false;
        return h.color == RED;
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
            return h;
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
            return select( h.right, k - size - 1 );
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
        RedBlackBSTCertification< String, String > bst = new RedBlackBSTCertification< String, String >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst: " + bst.toString() );
        StdOut.println( "DEBUG: bst.height(): " + bst.height() );
        StdOut.println( "DEBUG: bst.is23( bst.root ): " + bst.is23( bst.root ) );
        StdOut.println( "DEBUG: bst.isBalanced( bst.root ): " + bst.isBalanced( bst.root ) );
        StdOut.println( "DEBUG: bst.isBST( bst.root ): " + bst.isBST( bst.root ) );
        StdOut.println( "DEBUG: bst.isRedBlackBST( bst.root ): " + bst.isRedBlackBST( bst.root ) );
    }
}
