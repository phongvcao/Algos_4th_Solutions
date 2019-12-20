package com.company;
import edu.princeton.cs.algs4.*;
import java.lang.Math;

public class PointsInThePlane {

    private static class Point2D {
        private double x = 0;
        private double y = 0;
        private double distance = 0;

        public Point2D( double x, double y ) {
            this.x = x;
            this.y = y;
            this.distance = Math.sqrt( Math.pow( this.x, 2 ) + Math.pow( this.y, 2 ) );
        }

        public double distanceToOrigin() {
            return this.distance;
        }

        public double distanceTo( Point2D other ) {
            return Math.sqrt( Math.pow( this.x - other.x, 2 ) + Math.pow( this.y - other.y, 2 ) );
        }

        public int compareByDistanceToPoint( Point2D point, Point2D other ) {
            double thisDistance = this.distanceTo( point );
            double otherDistance = other.distanceTo( point );

            if ( thisDistance < otherDistance ) {
                return -1;
            } else if ( thisDistance > otherDistance ) {
                return 1;
            }

            return 0;
        }

        public double theta() {
            return Math.atan2( this.y, this.x );
        }

        public double theta( Point2D point ) {
            return Math.atan2( this.y - point.y, this.x - point.x );
        }

        public int compareByThetaToPoint( Point2D point, Point2D other ) {
            double thisTheta = this.theta( point );
            double otherTheta = other.theta( point );

            if ( thisTheta < otherTheta ) {
                return -1;
            } else if ( thisTheta > otherTheta ) {
                return 1;
            }

            return 0;
        }
    }

    public static int compareByX( Point2D a, Point2D b ) {
        if ( a.x < b.x ) {
            return -1;
        } else if ( a.x > b.x ) {
            return 1;
        }
        return 0;
    }

    public static int compareByY( Point2D a, Point2D b ) {
        if ( a.y < b.y ) {
            return -1;
        } else if ( a.y > b.y ) {
            return 1;
        }
        return 0;
    }

    public static int compareByDistanceToOrigin( Point2D a, Point2D b ) {
        if ( a.distanceToOrigin() < b.distanceToOrigin() ) {
            return -1;
        } else if ( a.distanceToOrigin() > b.distanceToOrigin() ) {
            return 1;
        }
        return 0;
    }

    public static void main( String[] args ) {
        double[] a = { 1.0, 2.0 };
        double[] b = { 3.0, 4.0 };
        double[] c = { 5.0, 6.0 };

        Point2D pointA = new Point2D( a[ 0 ], a[ 1 ] );
        Point2D pointB = new Point2D( b[ 0 ], b[ 1 ] );
        Point2D pointC = new Point2D( c[ 0 ], c[ 1 ] );

        StdOut.println( "DEBUG: compareByX: " + compareByX( pointA, pointB ) );
        StdOut.println( "DEBUG: compareByY: " + compareByY( pointA, pointB ) );
        StdOut.println( "DEBUG: compareByDistanceToOrigin: " + compareByDistanceToOrigin( pointA, pointB ) );
        StdOut.println( "DEBUG: compareByDistanceToPoint: " + pointA.compareByDistanceToPoint( pointC, pointB ) );
        StdOut.println( "DEBUG: compareByThetaToPoint: " + pointA.compareByThetaToPoint( pointC, pointB ) );
    }
}
