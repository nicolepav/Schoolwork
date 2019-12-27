import java.io.*;

public class Reverser<E> {

    private Stack<E> s;

    public Reverser () {
        Stack<E> s = new Stack<E>();
    }


    public void FileToStack(String infilename) throws Exception {
        try {
            BufferedReader fin = new BufferedReader(new FileReader(infilename));
            for(int i = 0; fin.ready(); i++) {
                s.push((E)fin.readLine());
            }
            fin.close();
            System.out.println("Input file has been added to the stack");
        }
        catch (FileNotFoundException e) {
            System.out.println("Error: Input file not found");
        }
        catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: You exceeded the array bounds");
        }
        catch (Exception e) {
            System.out.println("Error: An unspecified error has occurred");
        }

    }


    public void StackToFile(String outfilename) throws Exception {
        try {
            PrintWriter fout = new PrintWriter(outfilename);
            while(!s.isEmpty()) {
                fout.println((E)s.pop());
            }
            fout.close();
            System.out.println("File has been successfully reversed");

        }
        catch (FileNotFoundException e ){
            System.out.println("Error: Output file not found");
        }
        catch (Exception e) {
            System.out.println("Error: An unspecified error has occurred");
        }

    }

}
