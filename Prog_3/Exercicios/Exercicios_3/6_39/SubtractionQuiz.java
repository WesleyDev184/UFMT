import java.security.SecureRandom;
import java.util.Scanner;

public class SubtractionQuiz {
    public static void subtractionQuiz(int level) {
        SecureRandom random = new SecureRandom();
        int res = 0;
        int correct = 0;
        int wrong = 0;
        int total = 1;
        int number1;
        int number2;

        Scanner input = new Scanner(System.in);
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

            while (res != number1 - number2 && wrong < 10) {
                System.out.printf("\nQuanto é %d menos %d? ", number1, number2);

                res = input.nextInt();
                if (res == number1 - number2) {
                    Responses.goodResponses(random.nextInt(4));
                    correct++;
                } else {
                    Responses.badResponses(random.nextInt(4));
                    wrong++;
                }
            }
            total++;
        }

        double percentage = (double) correct / total * 100;

        if (percentage < 75) {
            System.out.println("\nPeça ajuda extra ao seu professor.");
        } else {
            System.out.println("\nParabéns, você está pronto para avançar para o próximo nível!");
        }
    }
}
