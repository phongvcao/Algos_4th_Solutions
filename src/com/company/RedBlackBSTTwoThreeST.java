package com.company;
import edu.princeton.cs.algs4.*;

public class RedBlackBSTTwoThreeST< Key extends Comparable< Key >, Value > {

    public enum NodeType {
        TWO( 1 ),
        THREE( 2 ),
        FOUR ( 3 );

        private final int value;
        private NodeType( int value ) {
            this.value = value;
        }

        public int getValue() {
            return value;
        }
    }

    private class Node {
        public Key key = null;
        public Value value = null;
        public int N = 1;
        public Node left = null;
        public Node right = null;
        public NodeType nodeType = NodeType.TWO;

        public Node() {
            // Not implemented
        }

        public Node( Key key, Value value, int N ) {
            this.key = key;
            this.value = value;
            this.N = N;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value + " ; size : " + this.N + " ; nodeType : " + this.nodeType.name();
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
            rv += " | \n";
            return rv;
        }

        public NodeType type() {
            return this.nodeType;
        }

        public int compareTo( Node other ) {
            return this.key.compareTo( other.key );
        }
    }

    private class TwoNode extends Node {
        public TwoNode( Key key, Value value, int N ) {
            super( key, value, N );
            this.nodeType = NodeType.TWO;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value + " ; size : " + this.N + " ; nodeType : " + this.nodeType.name();
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
            rv += " | \n";
            return rv;
        }
    }

    private class ThreeNode extends Node {
        public Key leftKey = null;
        public Value leftValue = null;

        public Key rightKey = null;
        public Value rightValue = null;

        public Node middle = null;

        public ThreeNode() {
            this.nodeType = NodeType.THREE;
            this.N = 2;
        }

        public ThreeNode( Key leftKey, Value leftValue, Key rightKey, Value rightValue ) {
            this.leftKey = leftKey;
            this.leftValue = leftValue;
            this.rightKey = rightKey;
            this.rightValue = rightValue;
            this.nodeType = NodeType.THREE;
            this.N = 2;
        }

        public ThreeNode( Key key, Value value, int N ) {
            super( key, value, N );
            this.nodeType = NodeType.THREE;
            this.N = 2;;
        }

        public String toString() {
            String rv = " | | " + this.leftKey + " : " + this.leftValue + " ;; " + this.rightKey + " : " + this.rightValue + " | ; size : " + this.N + " ; nodeType : " + this.nodeType.name();
            if ( this.left != null ) {
                rv += " ; left : " + this.left;
            } else {
                rv += " ; left : null";
            }

            if ( this.middle != null ) {
                rv += " ; middle : " + this.middle;
            } else {
                rv += " ; middle : null";
            }

            if ( this.right != null ) {
                rv += " ; right : " + this.right;
            } else {
                rv += " ; right : null";
            }

            rv += " | \n";
            return rv;
        }
    }

    private class FourNode extends Node {
        public Key leftKey = null;
        public Value leftValue = null;

        public Key middleKey = null;
        public Value middleValue = null;

        public Key rightKey = null;
        public Value rightValue = null;

        public Node middle1 = null;
        public Node middle2 = null;

        public FourNode() {
            this.nodeType = NodeType.FOUR;
            this.N = 3;
        }

        public FourNode( Key leftKey, Value leftValue, Key middleKey, Value middleValue, Key rightKey, Value rightValue ) {
            this.leftKey = leftKey;
            this.leftValue = leftValue;
            this.middleKey = middleKey;
            this.middleValue = middleValue;
            this.rightKey = rightKey;
            this.rightValue = rightValue;
            this.nodeType = NodeType.FOUR;
            this.N = 3;
        }

        public FourNode( Key key, Value value, int N ) {
            super( key, value, N );
            this.nodeType = NodeType.FOUR;
            this.N = 3;
        }

        public String toString() {
            String rv = " | | " + this.leftKey + " : " + this.leftValue + " ;; " +
                    this.middleKey + " : " + this.middleValue + " ;; " +
                    this.rightKey + " : " + this.rightValue + " | ; size : " + this.N + " ; nodeType : " + this.nodeType.name();
            if ( this.left != null ) {
                rv += " ; left : " + this.left;
            } else {
                rv += " ; left : null";
            }

            if ( this.middle1 != null ) {
                rv += " ; middle1 : " + this.middle1;
            } else {
                rv += " ; middle1 : null";
            }

            if ( this.middle2 != null ) {
                rv += " ; middle2 : " + this.middle2;
            } else {
                rv += " ; middle2 : null";
            }

            if ( this.right != null ) {
                rv += " ; right : " + this.right;
            } else {
                rv += " ; right : null";
            }

            rv += " | \n";
            return rv;
        }
    }

    private Node root = null;

    public void put( Key key, Value value ) {
        root = put( root, null, key, value );
        // If root becomes a FourNode, break it down
        if ( root.nodeType == NodeType.FOUR ) {
            FourNode x = ( FourNode ) root;
            TwoNode newRoot = new TwoNode( x.middleKey, x.middleValue, 1 );
            newRoot.left = new TwoNode( x.leftKey, x.leftValue, 1 );
            newRoot.right = new TwoNode( x.rightKey, x.rightValue, 1 );
            newRoot.left.left = x.left;
            newRoot.left.right = x.middle1;
            newRoot.left.N = size( newRoot.left.left ) + size( newRoot.left.right ) + 1;
            newRoot.right.left = x.middle2;
            newRoot.right.right = x.right;
            newRoot.right.N = size( newRoot.right.left ) + size( newRoot.right.right ) + 1;
            root = newRoot;
        }

        // Calculate h.N
        switch ( root.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) root;
                x.N = size( x.left ) + size( x.right ) + 1;
                break;
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) root;
                x.N = size( x.left ) + size( x.middle ) + size( x.right ) + 2;
                break;
            }

            case FOUR: {
                FourNode x = ( FourNode ) root;
                x.N = size( x.left ) + size( x.middle1 ) + size( x.middle2 ) + size( x.right ) + 3;
                break;
            }

            default: {
                break;
            }
        }
    }

    public Node put( Node h, Node parent, Key key, Value value ) {
        if ( h == null ) {
            return new TwoNode( key, value, 1 );
        }

        switch ( h.nodeType ) {
            case TWO: {
                // Decide between left & right
                int cmp = key.compareTo( h.key );
                if ( cmp < 0 ) {
                    if ( h.left == null ) {
                        // This would result in a ThreeNode? - certainly, left-leaning RED
                        ThreeNode x = new ThreeNode( key, value, h.key, h.value );
                        x.right = h.right;
                        h = x;
                    } else {
                        h.left = put( h.left, h, key, value );
                    }
                } else if ( cmp > 0 ) {
                    if ( h.right == null ) {
                        // This would result in a ThreeNode - certainly - right-leaning
                        // Rotate immediately to make this a left-leaning RED
                        ThreeNode x = new ThreeNode( h.key, h.value, key, value );
                        x.left = h.left;
                        h = x;
                    } else {
                        h.right = put( h.right, h, key, value );
                    }
                } else {
                    h.value = value;
                }
                break;
            }

            case THREE: {
                // First decide between leftKey & right.key
                // Then decide between left.key & middle.key (if choosing the leftKey path)
                ThreeNode x = ( ThreeNode ) h;
                int cmp = key.compareTo( x.rightKey );
                if ( cmp < 0 ) {
                    // Choosing leftKey path
                    cmp = key.compareTo( x.leftKey );
                    if ( cmp < 0 ) {
                        if ( x.left == null ) {
                            // This would result in a FourNode? - certainly - totally left-leaning
                            // Need to rotate immediately to make middleKey connected to upstream
                            FourNode y = new FourNode( key, value, x.leftKey, x.leftValue, x.rightKey, x.rightValue );
                            y.middle2 = x.middle;
                            y.right = x.right;
                            h = y;
                        } else {
                            x.left = put( x.left, h, key, value );
                            h = x;
                        }
                    } else if ( cmp > 0 ) {
                        if ( x.middle == null ) {
                            // This would result in a FourNode? - certainly - rotateLeft() on leftKey immediately
                            // to make it totally left-leaning. Also, this is the only way we can construct FourNode.
                            FourNode y = new FourNode( x.leftKey, x.leftValue, key, value, x.rightKey, x.rightValue );
                            y.left = x.left;
                            y.right = x.right;
                            h = y;
                        } else {
                            x.middle = put( x.middle, h, key, value );
                            h = x;
                        }
                    } else {
                        x.leftValue = value;
                        h = x;
                    }
                } else if ( cmp > 0 ) {
                    if ( x.right == null ) {
                        // This would result in a FourNode? - certainly - with middleKey connected to upstream.
                        FourNode y = new FourNode( x.leftKey, x.leftValue, x.rightKey, x.rightValue, key, value );
                        y.left = x.left;
                        y.middle1 = x.right;
                        h = y;
                    } else {
                        x.right = put( x.right, h, key, value );
                        h = x;
                    }
                } else {
                    x.rightValue = value;
                    h = x;
                }
                break;
            }

            default: {
                break;
            }
        }

        // If h.left, h.middle or h.right become a FourNode, break it down
        if ( h.left != null && h.left.nodeType == NodeType.FOUR ) {
            FourNode x = ( FourNode ) h.left;
            TwoNode newHLeft = new TwoNode( x.middleKey, x.middleValue, 1 );
            newHLeft.left = new TwoNode( x.leftKey, x.leftValue, 1 );
            newHLeft.right = new TwoNode( x.rightKey, x.rightValue, 1 );
            newHLeft.left.left = x.left;
            newHLeft.left.right = x.middle1;
            newHLeft.right.left = x.middle2;
            newHLeft.right.right = x.right;

            switch ( h.nodeType ) {
                case TWO: {
                    ThreeNode y = new ThreeNode( newHLeft.key, newHLeft.value, h.key, h.value );
                    y.right = h.right;
                    h = y;
                    break;
                }

                case THREE: {
                    ThreeNode oldH = ( ThreeNode ) h;
                    FourNode y = new FourNode( newHLeft.key, newHLeft.value, oldH.leftKey, oldH.leftValue, oldH.rightKey, oldH.rightValue );
                    y.middle2 = oldH.middle;
                    y.right = oldH.right;
                    h = y;
                    break;
                }

                default: {
                    break;
                }
            }
        }

        if ( h.nodeType == NodeType.THREE && ( ( ThreeNode ) h ).middle != null && ( ( ThreeNode ) h ).middle.nodeType == NodeType.FOUR ) {
            ThreeNode oldH = ( ThreeNode ) h;
            FourNode x = ( FourNode ) oldH.middle;
            TwoNode newHMiddle = new TwoNode( x.middleKey, x.middleValue, 1 );
            newHMiddle.left = new TwoNode( x.leftKey, x.leftValue, 1 );
            newHMiddle.right = new TwoNode( x.rightKey, x.rightValue, 1 );
            newHMiddle.left.left = x.left;
            newHMiddle.left.right = x.middle1;
            newHMiddle.right.left = x.middle2;
            newHMiddle.right.right = x.right;

            FourNode y = new FourNode( oldH.leftKey, oldH.leftValue, newHMiddle.key, newHMiddle.value, oldH.rightKey, oldH.rightValue );
            y.left = oldH.left;
            y.middle1 = newHMiddle.left;
            y.middle2 = newHMiddle.right;
            y.right = oldH.right;
            h = y;
        }

        if ( h.right != null && h.right.nodeType == NodeType.FOUR ) {
            FourNode x = ( FourNode ) h.right;
            TwoNode newHRight = new TwoNode( x.middleKey, x.middleValue, 1 );
            newHRight.left = new TwoNode( x.leftKey, x.leftValue, 1 );
            newHRight.right = new TwoNode( x.rightKey, x.rightValue, 1 );
            newHRight.left.left = x.left;
            newHRight.left.right = x.middle1;
            newHRight.right.left = x.middle2;
            newHRight.right.right = x.right;

            switch ( h.nodeType ) {
                case TWO: {
                    ThreeNode y = new ThreeNode( h.key, h.value, newHRight.key, newHRight.value );
                    y.left = h.left;
                    y.middle = newHRight.left;
                    y.right = newHRight.right;
                    h = y;
                    break;
                }

                case THREE: {
                    ThreeNode oldH = ( ThreeNode ) h;
                    FourNode y = new FourNode( oldH.leftKey, oldH.leftValue, oldH.rightKey, oldH.rightValue, newHRight.key, newHRight.value );
                    y.left = oldH.left;
                    y.middle1 = oldH.middle;
                    y.middle2 = newHRight.left;
                    y.right = newHRight.right;
                    h = y;
                    break;
                }

                default: {
                    break;
                }
            }
        }

        // Calculate h.N
        switch ( h.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) h;
                x.N = size( x.left ) + size( x.right ) + 1;
                break;
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                x.N = size( x.left ) + size( x.middle ) + size( x.right ) + 2;
                break;
            }

            case FOUR: {
                FourNode x = ( FourNode ) h;
                x.N = size( x.left ) + size( x.middle1 ) + size( x.middle2 ) + size( x.right ) + 3;
                break;
            }

            default: {
                break;
            }
        }

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

    public int height() {
        return height( root, -1 );
    }

    public int height( Node h, int count ) {
        if ( h == null ) return count;
        switch ( h.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) h;
                int leftHeight = height( x.left, count + 1 );
                int rightHeight = height( x.right, count + 1 );
                return leftHeight < rightHeight ? rightHeight : leftHeight;
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                int leftHeight = height( x.left, count + 1 );
                int middleHeight = height( x.middle, count + 1 );
                int rightHeight = height( x.right, count + 1 );
                int maxHeight = leftHeight;
                if ( maxHeight < middleHeight ) {
                    maxHeight = middleHeight;
                }
                if ( maxHeight < rightHeight ) {
                    maxHeight = rightHeight;
                }
                return maxHeight;
            }

            default: {
                return count;
            }
        }
    }

    public String toString() {
        String rv = "\nROOT : " + root + "\n";
        rv += toString( root );
        return rv;
    }

    public String toString( Node h ) {
        if ( h == null ) return "";

        // We navigate depending on what type of Node h is
        switch ( h.nodeType ) {
            case TWO: {
                String rv = toString( h.left );
                rv += h.toString();
                rv += toString( h.right );
                return rv;
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                String rv = x.toString();
                rv += toString( x.left );
                rv += toString( x.middle );
                rv += toString( x.right );
                return rv;
            }

            default: {
                break;
            }
        }


        String rv = toString( h.left );
        rv += h.toString();
        rv += toString( h.right );
        return rv;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public Value get( Key key ) {
        return get( root, key ).value;
    }

    public Node get( Node h, Key key ) {
        if ( h == null ) return null;

        switch ( h.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) h;
                int cmp = key.compareTo( x.key );
                if ( cmp < 0 ) {
                    return get( x.left, key );
                } else if ( cmp > 0 ) {
                    return get( x.right, key );
                } else {
                    return x;
                }
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                int cmp = key.compareTo( x.rightKey );
                if ( cmp < 0 ) {
                    cmp = key.compareTo( x.leftKey );
                    if ( cmp < 0 ) {
                        return get( x.left, key );
                    } else if ( cmp > 0 ) {
                        return get( x.middle, key );
                    } else {
                        return new TwoNode( x.leftKey, x.leftValue, 1 );
                    }
                } else if ( cmp > 0 ) {
                    return get( x.right, key );
                } else {
                    return new TwoNode( x.rightKey, x.rightValue, 1 );
                }
            }

            default: {
                break;
            }
        }
        return null;
    }

    public int rank( Key key ) {
        return rank( root, key );
    }

    public int rank( Node h, Key key ) {
        if ( h == null ) return 0;

        switch ( h.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) h;
                int cmp = key.compareTo( x.key );
                if ( cmp < 0 ) {
                    return rank( x.left, key );
                } else if ( cmp > 0 ) {
                    return rank( x.right, key ) + 1 + size( h.left );
                } else {
                    return size( h.left );
                }
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                int cmp = key.compareTo( x.rightKey );
                if ( cmp < 0 ) {
                    cmp = key.compareTo( x.leftKey );
                    if ( cmp < 0 ) {
                        return rank( x.left, key );
                    } else if ( cmp > 0 ) {
                        return rank( x.middle, key ) + size( x.left ) + 1;
                    } else {
                        return size( x.left );
                    }
                } else if ( cmp > 0 ) {
                    // To be implemented
                    return rank( x.right, key ) + 1 + size( x.left ) + size( x.middle ) + 1;
                } else {
                    return size( x.left ) + size( x.middle ) + 1;
                }
            }

            default: {
                break;
            }
        }
        return 0;
    }

    public Key select( int k ) {
        return select( root, k ).key;
    }

    public Node select( Node h, int k ) {
        if ( h == null ) return h;
        switch ( h.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) h;
                int size = size( x.left );
                if ( k < size ) {
                    return select( x.left, k );
                } else if ( k > size ) {
                    return select( x.right, k - size - 1 );
                } else {
                    return x;
                }
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                int size = size( x.left ) + size( x.middle ) + 1;
                if ( k < size ) {
                    size = size( x.left );
                    if ( k < size ) {
                        return select( x.left, k );
                    } else if ( k > size ) {
                        return select( x.middle, k - size - 1 );
                    } else {
                        return new TwoNode( x.leftKey, x.leftValue, 1 );
                    }
                } else if ( k > size ) {
                    return select( x.right, k - 1 - size );
                } else {
                    return new TwoNode( x.rightKey, x.rightValue, 1 );
                }
            }

            default: {
                break;
            }
        }
        return null;
    }

    public Key min() {
        return min( root ).key;
    }

    public Node min( Node h ) {
        if ( h == null ) return h;
        switch ( h.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) h;
                if ( x.left == null ) return x;
                return min( x.left );
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                if ( x.left == null ) return new TwoNode( x.leftKey, x.leftValue, 1 );
                return min( x.left );
            }

            default: {
                break;
            }
        }
        return null;
    }

    public Key max() {
        return max( root ).key;
    }

    public Node max( Node h ) {
        if ( h == null ) return h;
        switch ( h.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) h;
                if ( h.right == null ) return h;
                return max( h.right );
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                if ( h.right == null ) return new TwoNode( x.rightKey, x.rightValue, 1 );
                return max( h.right );
            }

            default: {
                break;
            }
        }
        return null;
    }

    public Key floor( Key key ) {
        return floor( root, key ).key;
    }

    public Node floor( Node h, Key key ) {
        if ( h == null ) return h;
        switch ( h.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) h;
                int cmp = key.compareTo( h.key );
                if ( cmp < 0 ) {
                    return floor( x.left, key );
                } else if ( cmp == 0 ) {
                    return x;
                }

                Node temp = floor( x.right, key );
                if ( temp != null ) {
                    return temp;
                }
                return x;
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                int cmp = key.compareTo( x.rightKey );
                if ( cmp < 0 ) {
                    cmp = key.compareTo( x.leftKey );
                    if ( cmp < 0 ) {
                        return floor( x.left, key );
                    } else if ( cmp == 0 ) {
                        return new TwoNode( x.leftKey, x.leftValue, 1 );
                    }

                    Node temp = floor( x.middle, key );
                    if ( temp != null ) {
                        return temp;
                    }
                    return new TwoNode( x.leftKey, x.leftValue, 1 );
                } else if ( cmp == 0 ) {
                    return new TwoNode( x.rightKey, x.rightValue, 1 );
                }

                Node temp = floor( x.right, key );
                if ( temp != null ) {
                    return temp;
                }
                return new TwoNode( x.rightKey, x.rightValue, 1 );
            }

            default: {
                break;
            }
        }
        return h;
    }

    public Key ceiling( Key key ) {
        return ceiling( root, key ).key;
    }

    public Node ceiling( Node h, Key key ) {
        if ( h == null ) return h;
        switch ( h.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) h;
                int cmp = key.compareTo( x.key );
                if ( cmp > 0 ) {
                    return ceiling( x.right, key );
                } else if ( cmp == 0 ) {
                    return x;
                }

                Node temp = ceiling( x.left, key );
                if ( temp != null ) {
                    return temp;
                }
                return x;
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                int cmp = key.compareTo( x.rightKey );
                if ( cmp > 0 ) {
                    return ceiling( x.right, key );
                } else if ( cmp == 0 ) {
                    return new Node( x.rightKey, x.rightValue, 1 );
                }

                // Node temp = ceiling( x.leftKey, key );
                cmp = key.compareTo( x.leftKey );
                if ( cmp > 0 ) {
                    return ceiling( x.middle, key );
                } else if ( cmp == 0 ) {
                    return new TwoNode( x.leftKey, x.leftValue, 1 );
                }

                Node temp = ceiling( x.left, key );
                if ( temp != null ) {
                    return temp;
                }
                return new Node( x.rightKey, x.rightValue, 1 );
            }

            default: {
                break;
            }
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
        switch ( h.nodeType ) {
            case TWO: {
                TwoNode x = ( TwoNode ) h;
                int cmpLow = x.key.compareTo( low );
                int cmpHigh = x.key.compareTo( high );
                if ( cmpLow < 0 ) return;
                if ( cmpHigh > 0 ) return;
                keys( h.left, queue, low, high );
                queue.enqueue( h.key );
                keys( h.right, queue, low, high );
                break;
            }

            case THREE: {
                ThreeNode x = ( ThreeNode ) h;
                int cmpLow = x.rightKey.compareTo( low );
                int cmpHigh = x.leftKey.compareTo( high );
                if ( cmpLow < 0 ) return;
                if ( cmpHigh > 0 ) return;
                keys( x.left, queue, low, high );
                if ( x.leftKey.compareTo( low ) >= 0 && x.leftKey.compareTo( high ) <= 0 ) {
                    queue.enqueue( x.leftKey );
                }
                keys( x.middle, queue, low, high );
                if ( x.rightKey.compareTo( low ) >= 0 && x.rightKey.compareTo( high ) <= 0 ) {
                    queue.enqueue( x.rightKey );
                }
                keys( x.right, queue, low, high );
                break;
            }

            default: {
                break;
            }
        }
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        RedBlackBSTTwoThreeST< String, String > bst = new RedBlackBSTTwoThreeST< String, String >();
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
    }
}
