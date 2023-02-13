import java.util.Scanner;

public class Exercicio_3 {
   public static void main(String[] args) {
      try (Scanner input = new Scanner(System.in)) {
         System.out.print("Entre Com o peso em KG: ");
         double weight = input.nextDouble();
         System.out.print("Entre com a autura em metros: ");
         double height = input.nextDouble();
         double bmi = weight / (height * height);
         System.out.println("BMI is " + bmi);
      }
      System.out.println("BMI VALUES");
      System.out.println("Underweight: less than 18.5");
      System.out.println("Normal: between 18.5 and 24.9");
      System.out.println("Overweight: between 25 and 29.9");
      System.out.println("Obese: 30 or greater");
   }
}

