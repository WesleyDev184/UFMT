import java.util.Scanner;

public class AccountTest {
    public static void main(String[] args) {
        Account account1 = new Account("Jane Green", 50.00);
        Account account2 = new Account("John Blue", -7.53);

        displayAccount(account1);
        displayAccount(account2);
        
        try (Scanner input = new Scanner(System.in)) {
            double depositAmount;
            int acc;

            System.out.print("\nEnter deposit amount for account1: ");
            depositAmount = input.nextDouble();

            System.out.printf("%n added %.2f to account1 balance%n%n", depositAmount);
            account1.deposit(depositAmount);

            displayAccount(account1);
            displayAccount(account2);

            System.out.print("\nEnter deposit amount for account2: ");
            depositAmount = input.nextDouble();

            System.out.printf("%n added %.2f to account2 balance%n%n", depositAmount);
            account2.deposit(depositAmount);

            displayAccount(account1);
            displayAccount(account2);

            System.out.print("\nfrom which account you want to transfer the amount \n 1. account1 \n 2. account2 \n\n ");
            acc = input.nextInt();

            if (acc == 1) {
                System.out.print("Enter amount to transfer from account1 to account2:\n");
                double transferAmount = input.nextDouble();
                account1.withdraw(transferAmount);
                account2.deposit(transferAmount);
            } else if (acc == 2) {
                System.out.print("Enter amount to transfer from account2 to account1:\n ");
                double transferAmount = input.nextDouble();
                account2.withdraw(transferAmount);
                account1.deposit(transferAmount);
            } else {
                System.out.println("Invalid input");
            }
        }

        displayAccount(account1);
        displayAccount(account2);
    }

    public static void displayAccount(Account  accountToDisplay) {
        System.out.printf("%s balance: $%.2f %n",  accountToDisplay.getName(),  accountToDisplay.getBalance());
    }
}
