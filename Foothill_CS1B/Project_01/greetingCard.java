public class greetingCard {

    private String sender;
    private String recipient;
    private String message;
    private String occasion;

    public greetingCard(String s, String r, String m, String o) {
        sender = s;
        recipient = r;
        message = m;
        occasion = o;

    }

    public String toString() {
        String cardData  = "From: " + recipient + " To: " + sender + '\n' + " For: " + occasion + " Contents: " + message;
        return cardData;
    }

    public String getSender() { return sender; }
    public String getRecipient() { return recipient; }
    public String getMessage() { return message; }
    public String getOccasion() { return occasion; }


}
