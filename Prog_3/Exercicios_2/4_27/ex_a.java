// x é 9 e y é 11:

// *****
// $$$$$

// x é 11 e y é 9

// $$$$$



import java.util.Scanner;

public class ex_a {
    public static void main(String[] args) {

        int x = 0;
        int y = 0;

        try (Scanner input = new Scanner(System.in)) {

            System.out.print("X: ");
            x = input.nextInt();

            System.out.print("Y: ");
            y = input.nextInt();
        }

        if (x < 10)
            if (y > 10)
                System.out.println("*****");
            else
                System.out.println("#####");
        System.out.println("$$$$$");

    }
}