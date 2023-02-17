import java.util.Scanner;

public class main {
    public static void main(String[] args) {

        HeartRates heartRates = new HeartRates(null, null, 0, 0, 0);

        try (Scanner input = new Scanner(System.in)) {
            String firstName;
            String lastName;
            int birthMonth;
            int birthDay;
            int birthYear;


            System.out.println("Enter your first name: ");
            firstName = input.nextLine();
            heartRates.setFirstName(firstName);

            System.out.println("Enter your last name: ");
            lastName = input.nextLine();
            heartRates.setLastName(lastName);
            
            System.out.println("Enter your birth day: ");
            birthDay = input.nextInt();
            heartRates.setBirthDay(birthDay);
            
            System.out.println("Enter your birth month: ");
            birthMonth = input.nextInt();
            heartRates.setBirthMonth(birthMonth);


            System.out.println("Enter your birth year: ");
            birthYear = input.nextInt();
            heartRates.setBirthYear(birthYear);
        }

        infoDisplay(heartRates);

    }
    public static String infoDisplay(HeartRates heartRates) {
        System.out.println("\nYour name is " + heartRates.getFirstName() + " " + heartRates.getLastName()
         + " you were born on " + heartRates.getBirthDate() + "\n"
         + "and you are " + heartRates.calculateAge() + " years old.\n" 
         + "Your maximum heart rate is " + heartRates.calculateMaximumHeartRate() + " and your target heart rate is " + heartRates.calculateTargetHeartRate() + ".\n");
        return null;
    }
}
