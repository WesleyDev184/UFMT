import java.security.SecureRandom;
import java.util.Scanner;

public class MixQuiz {
    public static void mixQuiz(int level) {
        SecureRandom random = new SecureRandom();
        int res = 0;
        Double res3 = 0.0;
        int correct = 0;
        int wrong = 0;
        int total = 1;
        int number1;
        int number2;
        double result = 0.0;

        Scanner input = new Scanner(System.in);
        while (total < 10) {
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

            while (wrong < 10 && res == number1 + number2 && res == number1 - number2 && res == number1 * number2
                    && Math.abs(res - (double) number1 / number2) < 0.1) {
                int operation = random.nextInt(4);

                switch (operation) {
                    case 0:
                        System.out.printf("\nQuanto é %d mais %d? ", number1, number2);
                        res = input.nextInt();
                        if (res == number1 + number2) {
                            Responses.goodResponses(random.nextInt(4));
                            correct++;
                        } else {
                            Responses.badResponses(random.nextInt(4));
                            wrong++;
                        }
                        total++;
                        break;
                    case 1:
                        System.out.printf("\nQuanto é %d menos %d? ", number1, number2);
                        res = input.nextInt();

                        if (res == number1 - number2) {
                            Responses.goodResponses(random.nextInt(4));
                            correct++;
                        } else {
                            Responses.badResponses(random.nextInt(4));
                            wrong++;
                        }
                        total++;
                        break;
                    case 2:
                        System.out.printf("\nQuanto é %d vezes %d? ", number1, number2);
                        res = input.nextInt();

                        if (res == number1 * number2) {
                            Responses.goodResponses(random.nextInt(4));
                            correct++;
                        } else {
                            Responses.badResponses(random.nextInt(4));
                            wrong++;
                        }
                        total++;
                        break;
                    case 3:
                        System.out.printf("\nQuanto é %d dividido por %d? ", 1 + number1, 1 + number2);
                        res3 = input.nextDouble();

                        result = (double) 1 + number1 / 1 + number2;
                        if (Math.abs(res3 - result) < 0.1) {
                            Responses.goodResponses(random.nextInt(4));
                            correct++;
                        } else {
                            Responses.badResponses(random.nextInt(4));
                            wrong++;
                        }
                        total++;
                        break;
                    default:
                        break;

                }
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
