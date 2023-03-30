public class CommissionEmployee extends Employee {
    private double grossSales;
    private double commissionRate;

    public CommissionEmployee(String FirstName, String LastName, int SocialSecurityNumber, double grossSales,
            double commissionRate, BirthDate birthDate) {
        super(FirstName, LastName, SocialSecurityNumber, birthDate);
        this.grossSales = grossSales;
        this.commissionRate = commissionRate;
    }

    public double getGrossSales() {
        return grossSales;
    }

    public void setGrossSales(double grossSales) {
        this.grossSales = grossSales;
    }

    public double getCommissionRate() {
        return commissionRate;
    }

    public void setCommissionRate(double commissionRate) {
        this.commissionRate = commissionRate;
    }

    @Override
    public double earnings() {
        return getCommissionRate() * getGrossSales();
    }

    @Override
    public String toString() {
        return String.format(
                "Commission Employee: \n Name: %s %s\n Social Number: %d\n Gross Sales: %.2f\n Commission Rate: %.2f\n BirthDate %s",
                getFirstName(), getLastName(),
                getSocialSecurityNumber(),
                getGrossSales(), getCommissionRate(), getBirthDate());
    }
}
