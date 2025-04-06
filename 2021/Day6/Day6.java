import java.io.*;
import java.util.Scanner;

public class Day6 {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("Day6.txt"));
        String[] input = scanner.nextLine().split(",");
        long[] fishes = new long[9];

        for (int i = 0; i < input.length; i++) {
            fishes[Integer.parseInt(input[i])] += 1;
        }

        for (int day = 0; day < 256; day++) {
            long[] newFishes = new long[9];
            newFishes[6] = newFishes[8] = fishes[0];
            for (int i = 0; i < fishes.length - 1; i++) {
                newFishes[i] += fishes[i + 1];
            }
            fishes = newFishes;
        }

        long n = 0;
        for (int i = 0; i < fishes.length; i++) {
            n += fishes[i];
        }
        System.out.println(n);
    }
}
