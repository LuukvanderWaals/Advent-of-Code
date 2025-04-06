import java.io.*;
import java.util.Scanner;

public class Day1 {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("Day1.txt"));

        int[] depth = new int[4];
        for (int i = 0; i < 3; i++) {
            depth[i] = Integer.parseInt(scanner.nextLine());
        }

        int res = 0;
        while (scanner.hasNext()) {
            depth[3] = Integer.parseInt(scanner.nextLine());
            if (depth[3] > depth[0]) {
                res += 1;
            }
            for (int i = 0; i < 3; i++) {
                depth[i] = depth[i + 1];
            }
        }
        System.out.println(res);
    }
}