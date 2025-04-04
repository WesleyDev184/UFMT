import java.security.SecureRandom;
import java.util.Scanner;
import java.lang.Math;

public class DivisionQuiz {
    public static void divisionQuiz(int level) {
        SecureRandom random = new SecureRandom();
        double res = 0;
        int correct = 0;
        int wrong = 0;
        int total = 1;
        int number1;
        int number2;
        double result = 0.0;

        Scanner input = new Scanner(System.in);
        while (total < 10 && wrong < 10) {
            if (level == 1) {
                number1 = 1 + random.nextInt(9); // generates a random integer between 1 and 9 (inclusive)
                number2 = 1 + random.nextInt(9); // generates a random integer between 1 and 9 (inclusive)
            } else if (level == 2) {
                number1 = 1 + random.nextInt(99); // generates a random integer between 1 and 99 (inclusive)
                number2 = 1 + random.nextInt(99); // generates a random integer between 1 and 99 (inclusive)
            } else {
                number1 = 1 + random.nextInt(999); // generates a random integer between 1 and 999 (inclusive)
                number2 = 1 + random.nextInt(999); // generates a random integer between 1 and 999 (inclusive)
            }

            while (Math.abs(res - (double) number1 / number2) < 0.1 && wrong < 10) {
                System.out.printf("\nQuanto é %d divido por %d? ", number1, number2);

                res = input.nextDouble();
                result = (double) number1 / number2;
                if (Math.abs(res - result) < 0.1) {
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
