import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

public class Main {
    public static void main(String[] args) {
        Employee[] employees = new Employee[5];
        employees[0] = new SalariedEmployee("John", "Smith", 111111111, 800.00, new BirthDate(01, 01, 1990));
        employees[1] = new HourlyEmployee("Karen", "Price", 222222222, 16.75, 40, new BirthDate(02, 02, 1991));
        employees[2] = new CommissionEmployee("Sue", "Jones", 333333333, 10000, .06, new BirthDate(03, 03, 1992));
        employees[3] = new BasePlusCommissionEmployee("Bob", "Lewis", 444444444, 5000, .04, 300,
                new BirthDate(04, 04, 1993));
        employees[4] = new PieceWorker("John", "Doe", 555555555, 2.5, 40, new BirthDate(05, 05, 1994));

        for (Employee currentEmployee : employees) {

            System.out.println(currentEmployee);
            if (currentEmployee instanceof BasePlusCommissionEmployee) {
                BasePlusCommissionEmployee employee = (BasePlusCommissionEmployee) currentEmployee;
                employee.setBaseSalary(1.10 * employee.getBaseSalary());
                System.out.printf("new base salary with 10%% increase is: $%,.2f%n", employee.getBaseSalary());
            }
            printEarned(currentEmployee);
        }
    }

    public static void printEarned(Employee employee) {
        double earned = employee.earnings();
        String Birthday = employee.getBirthDate().toString();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("d/M/yyyy");
        LocalDate date = LocalDate.parse(Birthday, formatter);

        try {
            if (date.getMonthValue() == LocalDate.now().getMonthValue()) {
                System.out.printf("earned $%,.2f\n", earned + 100);
                System.out.println("Happy Birthday!\n\n");
            } else {
                System.out.printf("earned $%,.2f%n%n", earned);
            }
        } catch (DateTimeParseException e) {
            System.out.println("Invalid date format");
        }
    }
}