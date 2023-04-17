import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int option = 0;

        while (option != 2) {

            System.out.print("\n");
            System.out.println("Menu:");
            System.out.println("1. Responder a uma questão");
            System.out.println("2. Sair do programa");
            System.out.print("Escolha uma opção: ");
            option = input.nextInt();
            System.out.print("\n");

            switch (option) {
                case 1:
                    QuestionGenerator.questionGenerator();
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
}
