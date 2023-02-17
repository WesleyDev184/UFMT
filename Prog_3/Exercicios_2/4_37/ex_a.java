import java.util.Scanner;

public class ex_a {
    public static void main(String[] args) {
        try (Scanner input = new Scanner(System.in)) {
            int val;
            int res = 1;

            System.out.print("\nDigite um valor positivo para saber seu fatorial: \n");
            val = input.nextInt();

            if (val < 0) {
                System.out.println("Valor inválido: apenas valores positivos");
            } else {
                for (int i = 1; i < val; i++) {
                    res = res * i;
                }
                System.out.println("\nO resultado do fatorial e: " + res);
            }

        }
    }
}
