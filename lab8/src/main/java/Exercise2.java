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

    public static void main(String[] args) {
        int size_y = 16, size_x = 64;
        int number_of_threads = 6;
        char[][] image = new char[size_y][size_x];
        var symbols = new ArrayList<>(Arrays.asList('!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_'));


        // Generate image (no white-spaces)
        var random = new Random();
        for (int i = 0; i < size_y; i++)
            for (int j = 0; j < size_x; j++)
                image[i][j] = (char) (random.nextInt(95) + 27);

        // Display image
        for (int i = 0; i < size_y; i++) {
            for (int j = 0; j < size_x; j++)
                System.out.print(image[i][j]);
            System.out.println();
        }

        // Threads, and chunks
        var threads = new ArrayList<MapThread>();
        var chunks = Chunky(symbols, number_of_threads);

        // Run jobs
        for (int i = 0; i < number_of_threads; i++) {
            var chunk = chunks.get(i);
            MapThread thread = new MapThread(image, chunk);
            thread.start();
            threads.add(thread);
            System.out.println("T<" + i + "> count symbols: " + chunk);
        }

        // Wait for Jobs
        for (var thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        // Show results
        for (var thread : threads) {
            System.out.println("-- " + thread.getName() + " --");
            thread.list.forEach((character, integer) -> System.out.println(character + " : " + integer));
            System.out.println();
        }
    }

    public static <T> ArrayList<ArrayList<T>> Chunky(ArrayList<T> t_to_distribute, int number_of_slices) {
        ArrayList<ArrayList<T>> chunks = new ArrayList<>();

        for (int i = 0; i < number_of_slices; i++)
            chunks.add(new ArrayList<>());

        for (int i = 0; i < t_to_distribute.size(); i++) {
            chunks.get(i % number_of_slices).add(t_to_distribute.get(i));
        }

        return chunks;
    }
}