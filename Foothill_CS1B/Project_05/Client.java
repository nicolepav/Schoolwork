import java.io.File;

public class Client
{
    public static void main(String[] args) throws Exception {
        Reverser<String> poem = new Reverser<String>();
        poem.FileToStack("reversePoem.txt");
        poem.StackToFile("newPoem.txt");

        Reverser<Float> maji = new Reverser<Float>();
        maji.FileToStack("reverseSpells.txt");
        maji.StackToFile("newSpells.txt");

    }
} 