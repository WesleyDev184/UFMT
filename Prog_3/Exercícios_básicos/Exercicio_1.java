import java.util.Scanner;

public class Exercicio_1 {
   public static void main(String[] args) {
      try (Scanner input = new Scanner(System.in)) {
        System.out.print("Entre com o raio: ");
          int radius = input.nextInt();

          double diameter = 2 * radius;
          double circumference = 2 * Math.PI * radius;
          double area = Math.PI * radius * radius;

          System.out.printf("Diâmetro: %.2f%n", diameter);
          System.out.printf("Circunferência: %.2f%n", circumference);
          System.out.printf("Area: %.2f%n", area);
    }
   }
}
