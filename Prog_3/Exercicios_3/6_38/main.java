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

    public static void questionGenerator() {
        SecureRandom random = new SecureRandom();
        int res = 0;
        int correct = 0;
        int wrong = 0;
        int total = 0;
        int level;
        int number1;
        int number2;

        Scanner input = new Scanner(System.in);
        System.out.println("Escolha um nível de dificuldade:");
        System.out.println("1. Fácil");
        System.out.println("2. Médio");
        System.out.println("3. Difícil");
        System.out.print("Opção: ");
        level = input.nextInt();

        while (total < 10 && wrong < 10) {
            if (level == 1) {
                number1 = random.nextInt(10); // generates a random integer between 0 and 9 (inclusive)
                number2 = random.nextInt(10); // generates a random integer between 0 and 9 (inclusive)
            } else if (level == 2) {
                number1 = random.nextInt(100); // generates a random integer between 0 and 99 (inclusive)
                number2 = random.nextInt(100); // generates a random integer between 0 and 99 (inclusive)
            } else {
                number1 = random.nextInt(1000); // generates a random integer between 0 and 999 (inclusive)
                number2 = random.nextInt(1000); // generates a random integer between 0 and 999 (inclusive)
            }

            while (res == number1 * number2 && wrong < 10) {
                System.out.printf("Quanto é %d vezes %d? ", number1, number2);

                res = input.nextInt();
                if (res == number1 * number2) {
                    Responses.goodResponses(random.nextInt(4));
                    correct++;
                } else {
                    Responses.badResponses(random.nextInt(4));
                    wrong++;
                }
                total++;
            }
        }

        double percentage = (double) correct / total * 100;

        if (percentage < 75) {
            System.out.println("\nPeça ajuda extra ao seu professor.");
        } else {
            System.out.println("\nParabéns, você está pronto para avançar para o próximo nível!");
        }
    }
}
