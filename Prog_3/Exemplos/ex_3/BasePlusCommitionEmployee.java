public class BasePlusCommitionEmployee extends CommissionEmployee {
    private double baseSalary;

    public BasePlusCommitionEmployee(String FirstName, String LastName, int SocialSecurityNumber, double grossSales,
            double commissionRate, double baseSalary) {
        super(FirstName, LastName, SocialSecurityNumber, grossSales, commissionRate);
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
        return String.format("Base Plus Commision Employee: %s %s %d %.2f %.2f %.2f", getFirstName(), getLastName(),
                getSocialSecurityNumber(),
                getGrossSales(), getCommissionRate(), getBaseSalary());
    }
}
