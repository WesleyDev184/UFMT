import java.util.Scanner;

public class QuestionGenerator {

    public static void questionGenerator() {
        Scanner input = new Scanner(System.in);
        System.out.println("Escolha um tipo de problema de aritmética a ser estudado:");
        System.out.println("1. Adição");
        System.out.println("2. Subtração");
        System.out.println("3. Multiplicação");
        System.out.println("4. Divisão");
        System.out.println("5. Mix de problemas");
        System.out.print("Opção: ");
        int option = input.nextInt();
        System.out.print("\n");

        System.out.println("Escolha um nível de dificuldade:");
        System.out.println("1. Fácil");
        System.out.println("2. Médio");
        System.out.println("3. Difícil");
        System.out.print("Opção: ");
        int level = input.nextInt();

        if (option == 1) {
            AdditionQuiz.additionQuiz(level);
        } else if (option == 2) {
            SubtractionQuiz.subtractionQuiz(level);
        } else if (option == 3) {
            MultiplicationQuiz.multiplicationQuiz(level);
        } else if (option == 4) {
            DivisionQuiz.divisionQuiz(level);
        } else if (option == 5) {
            MixQuiz.mixQuiz(level);
        } else {
            System.out.println("Opção inválida.");
        }

    }
}
