public class CommissionEmployee extends Employee {
    private double grossSales;
    private double commissionRate;

    public CommissionEmployee(String FirstName, String LastName, int SocialSecurityNumber, double grossSales,
            double commissionRate) {
        super(FirstName, LastName, SocialSecurityNumber);
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
        return String.format("Commission Employee: %s %s %d %.2f %.2f", getFirstName(), getLastName(),
                getSocialSecurityNumber(),
                getGrossSales(), getCommissionRate());
    }
}
