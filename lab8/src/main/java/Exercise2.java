import java.util.*;


class MapThread extends Thread {

    private final char[][] map;
    HashMap<Character, Integer> list;
    private final List<Character> characterLookup;

    public MapThread(char[][] map, List<Character> charValues) {
        this.map = map;
        this.list = new HashMap<>();
        this.characterLookup = charValues;
    }

    public void run() {
        for (char character : characterLookup) {
            list.put(character, 0);
        }

        for (char[] line : map) {
            for (char character : line) {
                if (characterLookup.contains(character))
                    list.put(character, list.get(character) + 1);
            }
        }
    }
}


public class Exercise2 {

    public static void main(String args[]) {

        int n = 16, m = 64;
        int num_threads = 6;

        char[][] vector1 = new char[n][m];

        var symbols = new ArrayList<>(Arrays.asList('!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_'));

        var random = new Random();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                vector1[i][j] = (char) (random.nextInt(95)+27);


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                System.out.print(vector1[i][j]);
            System.out.println();
        }


        var threads = new ArrayList<MapThread>();
        var chunks = Chunky(symbols, num_threads);

        for (int i = 0; i < num_threads; i++) {
            var chunk = chunks.get(i);
            MapThread thread = new MapThread(vector1, chunk);
            thread.start();
            threads.add(thread);
            System.out.printf("Thread %d calculates %s\n", i, chunk);
        }
        for (var thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        for (var thread : threads) {
            System.out.println(thread.toString() + " :");
            thread.list.forEach((character, integer) -> System.out.println(character + " : " + integer));
            System.out.println();
        }


    }

    public static <T> HashMap<Integer, ArrayList<T>> Chunky(ArrayList<T> list, int count) {
        HashMap<Integer, ArrayList<T>> chunks = new HashMap<>();

        for (int i = 0; i < count; i++)
            chunks.put(i, new ArrayList<>());

        for (int i = 0; i < list.size(); i++) {
            int threadNum = Math.floorMod(Math.floorMod(i + 1, count) - 1, count);
            chunks.get(threadNum).add(list.get(i));
        }

        return chunks;
    }
}