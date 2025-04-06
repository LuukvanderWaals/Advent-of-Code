import java.io.*;
import java.util.Scanner;


public class Day2 {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("Day2.txt"));
        int x = 0, depth = 0, aim = 0;

        while (scanner.hasNext()) {
            String[] line = scanner.nextLine().split(" ");
            int n = Integer.parseInt(line[1]);

            switch(line[0]) {
                case "up":
                    aim -= n;
                    break;
                case "down":
                    aim += n;
                    break;
                case "forward":
                    x += n;
                    depth += n * aim;
            }
        }

        System.out.println(x * depth);
    }
}
