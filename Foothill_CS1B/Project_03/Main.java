public class Main {

    public static void main(String[] args) {

        // Browser History Test
        System.out.println("\nString BoundedStack");
        BoundedStack<String> browserHistory = new BoundedStack<String>();
        for (int i = 1; i <= 51; i++) {
            browserHistory.push("100.10.100." + i);
        }
        for (int i = 0; i < 50; i++) {
            System.out.println(browserHistory.pop());
        }

        // Maji Game Test
        System.out.println("\nDouble BoundedStack");
        BoundedStack<Double> majiGame = new BoundedStack<Double>();
        for (double i = 1.0; i <= 51.0; i++) {
            majiGame.push(i);
        }
        for (double i = 0.0; i < 50.0; i++) {
            System.out.println(majiGame.pop());
        }
    }
}
