import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.math.BigInteger;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

public class LinearProbingHashSTKeys {

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader( InputStream stream ) {
            reader = new BufferedReader( new InputStreamReader( stream ), 32768 );
            tokenizer = null;
        }

        public String next() {
            while ( tokenizer == null || !tokenizer.hasMoreTokens() ) {
                try {
                    tokenizer = new StringTokenizer( reader.readLine() );
                } catch ( IOException e ) {
                    throw new RuntimeException( e );
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt( next() );
        }

        public long nextLong() {
            return Long.parseLong( next() );
        }
    }

    public static void main( String[] args ) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader( inputStream );
        PrintWriter out = new PrintWriter( outputStream );
        Task solver = new Task();
        solver.solve( 1, in, out );
        out.close();
    }

    static class Task {

        static class LinearProbingHashST< Key, Value > {
            private Key[] keys;
            private Value[] values;
            private int M = 16;
            private int N = 0;

            public LinearProbingHashST() {
                this( 997 );
            }

            public LinearProbingHashST( int M ) {
                this.M = M;
                keys = ( Key[] ) new Object[ M ];
                values = ( Value[] ) new Object[ M ];
            }

            public void put( Key key, Value value ) {
            }

            public Value get( Key key, Value value ) {

            }

            public String toString() {

            }

            private int hash( Key key ) {

            }

            private void resize( int cap ) {

            }

            public void delete( Key key ) {

            }

            public Iterable< Key > keys() {

            }
        }

        public void solve( int testNumber, InputReader in, PrintWriter out ) {

        }
    }
}
