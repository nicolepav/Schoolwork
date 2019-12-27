public class Main {

    public static void main(String[] args) {
        linkedlist_waldo L = new linkedlist_waldo();

        System.out.println("\n");
        System.out.println("The following toursits have been added: ");
        L.addFront("Waldo", 111, "America");
        L.addFront("Jimmy", 222, "France");
        L.addFront("Rorry", 333, "Estonia");
        System.out.println(L);

        System.out.println("Is Waldo in the list?");
        System.out.println(L.findNode("Waldo"));

        System.out.println("Is Rorry in the list?");
        System.out.println(L.findNode("Rorry"));

        System.out.println("Is Jimmy in the list?");
        System.out.println(L.findNode("Jimmy"));

        System.out.println("Is Isabel in the list?");
        System.out.println(L.findNode("Isabel"));
    }
}
