import java.util.Scanner;

public class SalarioBruto {
    public static void main(String[] args) {
        try (Scanner input = new Scanner(System.in)) {
            for (int i = 1; i <= 3; i++) {
                System.out.println("Empregado " + i);
                System.out.print("Horas trabalhadas: ");
                int workedHours = input.nextInt();
                System.out.print("Salário-hora: R$");
                double salaryTime = input.nextDouble();

                double grossSalary;
                if (workedHours <= 40) {
                    grossSalary = workedHours * salaryTime;
                } else {
                    int horasExtras = workedHours - 40;
                    grossSalary = 40 * salaryTime + horasExtras * salaryTime * 1.5;
                }

                System.out.printf("Salário bruto: R$%.2f\n\n", grossSalary);
            }
        }
    }
}
