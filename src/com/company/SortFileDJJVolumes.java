package com.company;
import edu.princeton.cs.algs4.*;

import java.math.BigInteger;

public class SortFileDJJVolumes {

    private static class VolumeByDate implements Comparable< VolumeByDate > {
        public String date = null;
        public BigInteger volume = null;

        public VolumeByDate( String date, BigInteger volume ) {
            this.date = date;
            this.volume = volume;
        }

        public int compareTo( VolumeByDate other ) {
            return this.volume.compareTo( other.volume );
        }

        public String toString() {
            return this.date + " " + this.volume;
        }
    }

    public static void main( String[] args ) {

    }
}
