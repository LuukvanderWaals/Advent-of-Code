import java.io.*;
import java.util.*;

public class Day3 {
    public static void main(String[] args) throws IOException{
        Scanner scanner = new Scanner(new File("Day3.txt"));

        ArrayList<String> strings = new ArrayList<>();
        while (scanner.hasNext()) {
            strings.add(scanner.next());
        }

        int gamma = 0;
        for (int bit = 0; bit < strings.get(0).length(); bit++) {
            int n = 0;
            for (int string = 0; string < strings.size(); string++) {
                if (strings.get(string).charAt(strings.get(0).length() - 1 - bit) == '1') {
                    n++;
                }
            }

            if (n > strings.size() / 2) {
                gamma += Math.pow(2, bit);
            }
        }
        int epsilon = ((int) Math.pow(2, strings.get(0).length()) - 1) ^ gamma;

        System.out.println(gamma * epsilon);
    }
}
