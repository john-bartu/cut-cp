import java.util.*;

record Section(int start, int end) {
}

class PrimeThread extends Thread {

    private final int[] numbers;
    private final Section section;

    public PrimeThread(int[] numbers, Section section) {
        this.numbers = numbers;
        this.section = section;
    }

    public void run() {
        int prime = 2;
        while (prime < Math.sqrt(numbers.length)) {
            System.out.println("[" + section.start() + " - " + section.end() + "] Eliminating " + prime);

            for (int i = firstIndex(prime); i <= section.end(); i += prime) {
                numbers[i] = 0;
            }

            numbers[prime] = prime;

            do {
                prime++;
            } while (numbers[prime] == 0);
        }
    }

    private int firstIndex(int eliminator) {
        return section.start() - Math.floorMod(section.start(), eliminator);
    }
}


public class Exercise3 {

    public static void main(String[] args) {

        int numbers_range = 1000;
        int numbers_of_threads = 4;
        int[] isPrime = new int[numbers_range];

        // Fill with numbers
        for (int i = 0; i < numbers_range; i++) {
            isPrime[i] = i;
        }

        // Prime number should be dividable by exactly 2 numbers (itself and one)
        isPrime[1] = 0;

        // Thread and section
        var threads = new ArrayList<PrimeThread>();
        var sections = ChunkySection(numbers_range, numbers_of_threads);

        // Run threads
        for (int i = 0; i < numbers_of_threads; i++) {
            var section = sections.get(i);
            PrimeThread thread = new PrimeThread(isPrime, section);
            thread.start();
            threads.add(thread);
            System.out.println("T <" + i + "> check primary at range: " + section);
        }

        // Wait for threads
        for (var thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        // Display results
        System.out.println("Primes: " + Arrays.toString(Arrays.stream(isPrime).filter(num -> num != 0).toArray()));
    }

    public static List<Section> ChunkySection(int n, int count) {
        List<Section> chunks = new ArrayList<>();

        int base_count = n / count;
        int start_number;

        for (start_number = 0; start_number + base_count * 2 <= n; start_number += base_count) {
            chunks.add(new Section(start_number + 1, base_count + start_number));
        }

        chunks.add(new Section(start_number + 1, n - 1));
        return chunks;
    }
}