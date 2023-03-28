public class Main {
    public static void main(String[] args) {
        Employee[] employees = new Employee[4];
        employees[0] = new SalariedEmployee("John", "Smith", 111111111, 800.00);
        employees[1] = new HourlyEmployee("Karen", "Price", 222222222, 16.75, 41);
        employees[2] = new CommissionEmployee("Sue", "Jones", 333333333, 10000, .06);
        employees[3] = new BasePlusCommitionEmployee("Bob", "Lewis", 444444444, 5000, .04, 300);

        for (Employee currentEmployee : employees) {
            System.out.println(currentEmployee);
            if (currentEmployee instanceof BasePlusCommitionEmployee) {
                BasePlusCommitionEmployee employee = (BasePlusCommitionEmployee) currentEmployee;
                employee.setBaseSalary(1.10 * employee.getBaseSalary());
                System.out.printf("new base salary with 10%% increase is: $%,.2f%n", employee.getBaseSalary());
            }
            System.out.printf("earned $%,.2f%n%n", currentEmployee.earnings());
        }
    }
}