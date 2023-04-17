import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try (Scanner input = new Scanner(System.in)) {
            int edge;

            System.out.print("Digite o tamanho da borda com no máximo 20: \n");
            edge = input.nextInt();

            if (edge > 20 || edge < 1) {
                System.out.println("\nO tamanho da borda não pode ser maior que 20 e no mínimo 1\n");
            } else {
                for (int i = 0; i < edge; i++) {
                    for (int j = 0; j < edge; j++) {
                        if (i == 0 || i == edge - 1) {
                            System.out.print("*");
                        } else if (j == 0 || j == edge - 1) {
                            System.out.print("*");
                        } else {
                            System.out.print(" ");
                        }
                    }
                    System.out.println();
                }
            }

        }
    }
}
