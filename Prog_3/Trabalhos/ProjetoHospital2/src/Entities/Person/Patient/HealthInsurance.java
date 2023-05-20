package Entities.Person.Patient;

public class HealthInsurance {
  private int id;
  private String healthInsuranceName;
  private double healthInsuranceMonthlyPayment;

  public HealthInsurance(int id, String healthInsuranceName, double healthInsuranceMonthlyPayment) {
    this.id = id;
    this.healthInsuranceName = healthInsuranceName;
    this.healthInsuranceMonthlyPayment = healthInsuranceMonthlyPayment;
  }

  public void setId(int id) {
    this.id = id;
  }

  public int getId() {
    return id;
  }

  public String getHealthInsuranceName() {
    return healthInsuranceName;
  }

  public void setHealthInsuranceName(String healthInsuranceName) {
    this.healthInsuranceName = healthInsuranceName;
  }

  public double getHealthInsuranceMonthlyPayment() {
    return healthInsuranceMonthlyPayment;
  }

  public void setHealthInsuranceMonthlyPayment(double healthInsuranceMonthlyPayment) {
    this.healthInsuranceMonthlyPayment = healthInsuranceMonthlyPayment;
  }
}
