import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        cardOrganizer cards = new cardOrganizer();

        String sender;
        String recipient;
        String occasion;
        String message;
        String find;

        System.out.println("\n\nCS1B: Greeting Card Organizer \nNicole Pavlovich, 20411749");
        System.out.println("-----------------------------\n");

        while (true) {
            System.out.println("\nPress A to add a new card \nPress F to find a card by recipient \n" +
                    "Press D to display all cards: \n");
            String choice;
            choice = in.nextLine();

            if( choice.equals("A")) {
                System.out.print("Sender: ");
                sender = in.nextLine();

                System.out.print("Recipient: ");
                recipient = in.nextLine();

                System.out.print("Occasion: ");
                occasion = in.nextLine();

                System.out.print("Message: ");
                message = in.nextLine();

                cards.addCard(sender, recipient, message, occasion);
            }
            else if (choice.equals("F")) {
                System.out.print("Enter the recipient to search for: ");
                find = in.nextLine();
                System.out.println(cards.findRecipients(find));
            }
            else if (choice.equals("D")) {
                System.out.println(cards.toString());
            }
            else {
                System.out.println("Not a valid entry");
            }
        }
    }
}
