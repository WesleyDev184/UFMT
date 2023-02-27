import java.security.SecureRandom;
import java.util.Scanner;

public class main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int option = 0;

        while (option != 2) {

            System.out.println("\n");
            System.out.println("Menu:");
            System.out.println("1. Responder a uma questão");
            System.out.println("2. Sair do programa");
            System.out.print("Escolha uma opção: ");
            option = input.nextInt();
            System.out.println("\n");

            switch (option) {
                case 1:
                    questionGenerator();
                    break;
                case 2:
                    System.out.println("Saindo do programa...");
                    break;
                default:
                    System.out.println("Opção inválida. Tente novamente.");
                    break;
            }
        }
        input.close();
    }

    public static int questionGenerator() {
        SecureRandom random = new SecureRandom();
        int res = 0;
        int number1 = random.nextInt(101); // generates a random integer between 0 and 100 (inclusive)
        int number2 = random.nextInt(101); // generates a random integer between 0 and 100 (inclusive)

        while (res != number1 * number2) {
            System.out.printf("Quanto é %d vezes %d? ", number1, number2);
            Scanner input = new Scanner(System.in);
            res = input.nextInt();
            if (res == number1 * number2) {
                Responses.goodResponses(random.nextInt(4));
            } else {
                Responses.badResponses(random.nextInt(4));
            }
        }

        return 0;
    }
}