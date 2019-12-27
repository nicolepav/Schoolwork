public class cardOrganizer {

    private greetingCard[] cards = new greetingCard[20];
    private int numcards = 0;

    public boolean addCard(String sender, String recipient, String message, String occasion) {
        if ( numcards ==  19) {
            System.out.println("Card Organizer is full");
            return false;
        }
        else {
            cards[numcards] = new greetingCard(sender, recipient, message, occasion);
            numcards++;
            System.out.println("Your card has been added");
            return true;
        }
    }

    public String findRecipients(String recipient) {
        for (int i = 0; i < numcards; i++) {
            if (cards[i].getRecipient().equals(recipient)) {
                return cards[i].toString();
            }
        }

        return "No Match Found";
    }

    public void displayCards(String occasion) {

        for (int i = 0; i < numcards; i++) {
            if(cards[i].getOccasion().equals(occasion)) {
                System.out.println(cards[i].toString());
            }
        }
    }

    public String toString() {

        String print = "";
        for (int i = 0; i < numcards; i ++) {
            print = print + "Recipient: " + cards[i].getRecipient() + '\t' + "Occasion: " + cards[i].getOccasion() + '\n';
        }
        return print;
    }
}
