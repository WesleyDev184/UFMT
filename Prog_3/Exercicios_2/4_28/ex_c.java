
import java.util.Scanner;

public class ex_c {
    public static void main(String[] args) {
        int x = 0;
        int y = 0;

        try (Scanner input = new Scanner(System.in)) {

            System.out.print("X: ");
            x = input.nextInt();

            System.out.print("Y: ");
            y = input.nextInt();
        }

        if (y == 8)
            if (x == 5)
                System.out.println("@@@@@");
            else {
                System.out.println("#####");
                System.out.println("$$$$$");
                System.out.println("&&&&&");
            }
    }
}