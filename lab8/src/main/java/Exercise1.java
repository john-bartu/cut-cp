import java.util.*;


class SumThread extends Thread {

    private final int[] vecSum;
    private final int[] vec1;
    private final int[] vec2;
    private final List<Integer> indexes;

    public SumThread(int[] vecSum, int[] vec1, int[] vec2, List<Integer> indexes) {
        this.vecSum = vecSum;
        this.vec1 = vec1;
        this.vec2 = vec2;
        this.indexes = indexes;
    }

    public void run() {
        for (int i : indexes) {
            vecSum[i] = vec1[i] + vec2[i];
        }
    }
}


public class Exercise1 {

    public static void main(String args[]) {

        int vecSize = 64;
        int num_threads = 10;

        int[] vectorSum = new int[vecSize];
        int[] vector1 = new int[vecSize];
        int[] vector2 = new int[vecSize];


        var random = new Random();

        for (int i = 0; i < vecSize; i++) {
            vector1[i] = random.nextInt(10);
            vector2[i] = random.nextInt(10);
        }


        var threads = new ArrayList<SumThread>();
        var chunks = Chunky(vecSize, num_threads);

        for (int i = 0; i < num_threads; i++) {
            var chunk = chunks.get(i);
            SumThread thread = new SumThread(vectorSum, vector1, vector2, chunk);
            thread.start();
            threads.add(thread);
            System.out.printf("Thread %d adding elements at %s\n", i, chunk);
        }
        for (var thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        System.out.println(Arrays.toString(vector1));
        System.out.println(Arrays.toString(vector2));
        System.out.println(Arrays.toString(vectorSum));
    }

    public static HashMap<Integer, ArrayList<Integer>> Chunky(int n, int count) {
        HashMap<Integer, ArrayList<Integer>> chunks = new HashMap<>();

        for (int i = 0; i < count; i++)
            chunks.put(i, new ArrayList<>());

        for (int i = 0; i < n; i++) {
            int threadNum = Math.floorMod(Math.floorMod(i + 1, count) - 1, count);
            chunks.get(threadNum).add(i);
        }

        return chunks;
    }
}