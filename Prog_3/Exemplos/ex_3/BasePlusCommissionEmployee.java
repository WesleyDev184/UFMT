public class BasePlusCommissionEmployee extends CommissionEmployee {
    private double baseSalary;

    public BasePlusCommissionEmployee(String FirstName, String LastName, int SocialSecurityNumber, double grossSales,
            double commissionRate, double baseSalary, BirthDate birthDate) {
        super(FirstName, LastName, SocialSecurityNumber, grossSales, commissionRate, birthDate);
        this.baseSalary = baseSalary;
    }

    public double getBaseSalary() {
        return baseSalary;
    }

    public void setBaseSalary(double baseSalary) {
        this.baseSalary = baseSalary;
    }

    @Override
    public double earnings() {
        return getBaseSalary() + super.earnings();
    }

    @Override
    public String toString() {
        return String.format(
                "Base Plus Commision Employee:\n Name: %s %s\n Social Number: %d\n Gross Sales: %.2f\n Commission Rate: %.2f\n Base Salary: %.2f\n BirthDate %s",
                getFirstName(), getLastName(),
                getSocialSecurityNumber(),
                getGrossSales(), getCommissionRate(), getBaseSalary(), getBirthDate());
    }
}
