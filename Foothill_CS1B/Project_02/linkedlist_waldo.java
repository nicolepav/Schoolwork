public class linkedlist_waldo {

    public class node {

        public String touristName;
        public int passport;
        public String destination;
        public node next;

        public node(String tn, int p, String d, node n) {
            touristName = tn;
            passport = p;
            destination = d;
            next = n;
        }

        public String toString() {
            String nodeInfo = touristName + " " + passport + " " + destination;
            return nodeInfo;
        }
    }

    private node first;
    private static int listSize;
    public linkedlist_waldo(){
        first = null;
        listSize = 0;
    }
    public linkedlist_waldo(String tn, int p, String d, node n) {
        first = new node(tn, p, d , null);
        listSize = 0;
    }

    public void addFront(String tn, int p, String d){
        first = new node(tn, p , d, first);
        listSize++;
    }


    public int size() {
        return listSize;
    }

    public String findNode(String find) {

        node p = first;
        String solution;
        while(p.next != null) {
            //Do work on each node of the list here
            if ( p.touristName == find) {
                solution = "The tourist " + p.touristName + " has been found";
                return solution;
            }
            p = p.next;
        }
        if ( p.touristName == find) {
            solution = "The tourist " + p.touristName + " has been found";
            return solution;
        }
        else {
            solution = "The tourist could not be found";
            return solution;
        }
    }

    public String toString() {

        node p = first;
        String thingy = "";
        while(p.next != null) {
            thingy = thingy + p.touristName + " " + p.passport + " " + p.destination + "\n";
            p = p.next;
        }
        thingy = thingy + p.touristName + " " + p.passport + " " + p.destination + "\n";
        return thingy;
    }

}
