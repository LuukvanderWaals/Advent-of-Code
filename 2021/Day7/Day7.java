import java.io.*;
import java.util.Arrays;
import java.util.Scanner;

public class Day7 {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("Day7.txt"));
        String[] input = scanner.nextLine().split(",");

        int[] crabs = new int[input.length];
        for (int i = 0; i < input.length; i++) {
            crabs[i] = Integer.parseInt(input[i]);
        }

        Arrays.sort(crabs);
        int sum = 0;
        for (int i = 0; i < crabs.length; i++) {
            sum += crabs[i];
        }
        int pos = sum / crabs.length;

        int fuel = 0;
        for (int i = 0; i < crabs.length; i++) {
            int n = Math.abs(crabs[i] - pos);
            fuel += n * (n + 1) / 2;
        }
        System.out.println(fuel);
    }
}
