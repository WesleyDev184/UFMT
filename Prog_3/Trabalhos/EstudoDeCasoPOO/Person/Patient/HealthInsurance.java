package Person.Patient;

public class HealthInsurance {

    private String HealthInsuranceName;
    private String HealthInsuranceMonthlyPayment;

    public HealthInsurance(String HealthInsuranceName, String HealthInsuranceMonthlyPayment) {
        this.HealthInsuranceName = HealthInsuranceName;
        this.HealthInsuranceMonthlyPayment = HealthInsuranceMonthlyPayment;
    }

    public String getHealthInsuranceName() {
        return HealthInsuranceName;
    }

    public void setHealthInsuranceName(String HealthInsuranceName) {
        this.HealthInsuranceName = HealthInsuranceName;
    }

    public String getHealthInsuranceMonthlyPayment() {
        return HealthInsuranceMonthlyPayment;
    }

    public void setHealthInsuranceMonthlyPayment(String HealthInsuranceMonthlyPayment) {
        this.HealthInsuranceMonthlyPayment = HealthInsuranceMonthlyPayment;
    }
}
