package com.company;
import edu.princeton.cs.algs4.*;

public class VersionDataType {

    private static class Version implements Comparable< Version > {
        public int major = 0;
        public int minor = 0;
        public int patch = 0;

        public Version( String versionStr ) {
            String[] versions = versionStr.split( "[.]" );
            this.major = Integer.parseInt( versions[ 0 ] );
            this.minor = Integer.parseInt( versions[ 1 ] );
            this.patch = Integer.parseInt( versions[ 2 ] );
        }

        public int compareTo( Version other ) {
            if ( this.major < other.major ) {
                return -1;
            } else if ( this.major > other.major ) {
                return 1;
            }

            if ( this.minor < other.minor ) {
                return -1;
            } else if ( this.minor > other.minor ) {
                return 1;
            }

            if ( this.patch < other.patch ) {
                return -1;
            } else if ( this.patch > other.patch ) {
                return 1;
            }

            return 0;
        }
    }

    public static void main( String[] args ) {

    }
}
