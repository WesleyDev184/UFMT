public class Account{

    private String name;
    private double balance;

    public Account(String name, double balance) {
        this.name = name;
        if (balance > 0.0) {
            this.balance = balance;
        }
    }

    public void deposit(double depositAmount) {
        if(depositAmount > 0.0) {
            this.balance = this.balance + depositAmount;
        }
    }

    public double getBalance() {
        return this.balance;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void withdraw(double withdrawAmount) {
        if (withdrawAmount > this.balance) {
            System.out.println("Withdrawal amount exceeded account balance.");
        } else {
            this.balance = this.balance - withdrawAmount;
        }
    }

}