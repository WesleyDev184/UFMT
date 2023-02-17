import java.util.Scanner;

public class AccountTest {
    public static void main(String[] args) {
        Account account1 = new Account("Jane Green", 50.00);
        Account account2 = new Account("John Blue", -7.53);

        System.out.printf("%s balance: $%.2f %n",
        account1.getName(),account1.getBalance());

        System.out.printf("%s balance: $%.2f %n%n",
        account2.getName(),account2.getBalance());

        try (Scanner input = new Scanner(System.in)) {
            System.out.print("Enter deposit amount for account1: ");
            double depositAmount = input.nextDouble();

            System.out.printf("%n added %.2f to account1 balance%n%n", depositAmount);
            account1.deposit(depositAmount);

            System.out.printf("%s balance: $%.2f %n", account1.getName(), account1.getBalance());
            System.out.printf("%s balance: $%.2f %n%n", account2.getName(), account2.getBalance());

            System.out.print("Enter deposit amount for account2: ");
            depositAmount = input.nextDouble();

            System.out.printf("%n added %.2f to account2 balance%n%n", depositAmount);
            account2.deposit(depositAmount);
            
            System.out.printf("%s balance: $%.2f %n", account1.getName(), account1.getBalance());
            System.out.printf("%s balance: $%.2f %n%n", account2.getName(), account2.getBalance());

            System.out.print("from which account you want to transfer the amount \n 1. account1 \n 2. account2 \n\n ");
            int acc = input.nextInt();

            if (acc == 1) {
                System.out.print("Enter amount to transfer from account1 to account2:");
                double transferAmount = input.nextDouble();
                account1.withdraw(transferAmount);
                account2.deposit(transferAmount);
            } else if (acc == 2) {
                System.out.print("Enter amount to transfer from account2 to account1: ");
                double transferAmount = input.nextDouble();
                account2.withdraw(transferAmount);
                account1.deposit(transferAmount);
            } else {
                System.out.println("Invalid input");
            }
        }

        System.out.printf("%s balance: $%.2f %n", account1.getName(), account1.getBalance());
        System.out.printf("%s balance: $%.2f %n%n", account2.getName(), account2.getBalance());
    }
    
}
