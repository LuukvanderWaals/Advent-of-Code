import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Day9 {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("Day9.txt"));

        ArrayList<int[]> map = new ArrayList<>();

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            int[] row = new int[line.length()];
            for (int i = 0; i < line.length(); i++) {
                row[i] = line.charAt(i) - 48;
            }
            map.add(row);
        }

        int res = 0;
        for (int y = 0; y < map.size(); y++) {
            for (int x = 0; x < map.get(y).length; x++) {
                int n = map.get(y)[x];

                if (y - 1 >= 0 && map.get(y - 1)[x] <= n ||
                    y + 1 < map.size() && map.get(y + 1)[x] <= n ||
                    x - 1 >= 0 && map.get(y)[x - 1] <= n ||
                    x + 1 < map.get(y).length && map.get(y)[x + 1] <= n) {
                    continue;
                }
                res += n + 1;
            }
        }
        System.out.println(res);
    }
}