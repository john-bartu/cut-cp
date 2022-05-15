import java.util.*;


class SumThread extends Thread {

    private final int[] sum_vector;
    private final int[] vector1;
    private final int[] vector2;
    private final List<Integer> indexes;

    public SumThread(int[] sum_vector, int[] vector1, int[] vector2, List<Integer> indexes) {
        this.sum_vector = sum_vector;
        this.vector1 = vector1;
        this.vector2 = vector2;
        this.indexes = indexes;
    }

    public void run() {
        for (int i : indexes) {
            sum_vector[i] = vector1[i] + vector2[i];
        }
    }
}


public class Exercise1 {

    public static void main(String[] args) {
        int number_of_numbers = 100;
        int number_of_threads = 15;

        // Vectors
        int[] vectorSum = new int[number_of_numbers];
        int[] vector1 = new int[number_of_numbers];
        int[] vector2 = new int[number_of_numbers];

        // Randomize
        var random = new Random();
        for (int i = 0; i < number_of_numbers; i++) {
            vector1[i] = random.nextInt(10);
            vector2[i] = random.nextInt(10);
        }

        // Threads, and chunks
        var threads = new ArrayList<SumThread>();
        var chunks = Chunky(number_of_numbers, number_of_threads);

        // Run jobs
        for (int i = 0; i < number_of_threads; i++) {
            var chunk = chunks.get(i);
            SumThread thread = new SumThread(vectorSum, vector1, vector2, chunk);
            thread.start();
            threads.add(thread);
            System.out.println("T<" + i + "> adds elements at indices: " + chunk);
        }

        // Wait for jobs
        for (var thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        // Display result
        System.out.println(Arrays.toString(vector1));
        System.out.println(Arrays.toString(vector2));
        System.out.println(Arrays.toString(vectorSum));
    }

    public static ArrayList<ArrayList<Integer>> Chunky(int max_number, int splits_count) {
        ArrayList<ArrayList<Integer>> chunks = new ArrayList<>();

        for (int i = 0; i < splits_count; i++)
            chunks.add(new ArrayList<>());

        // Exact distribution (like card distribution for players)
        for (int i = 0; i < max_number; i++) {
            int threadNum = i % splits_count;
            chunks.get(threadNum).add(i);
        }

        return chunks;
    }
}