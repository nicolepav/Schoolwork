package zooanimals;

import java.util.ArrayList;
import java.util.Scanner;

public class Foothill {

    public static void main(String[] args) {
        ArrayList<iAnimal> zooAnimals = new ArrayList<iAnimal>();
        Scanner in = new Scanner(System.in);

        System.out.println("Welcome to the Zoo");
        System.out.println("--------------------------------------");

        String user = " ";

        while(!(user.toUpperCase().equals("X"))) {
            new Foothill().createNewAnimal(zooAnimals);
            System.out.print("Enter X to exit or C to continue");
            user = in.nextLine();
        }

        for(int i =0; i < zooAnimals.size(); i++){
            System.out.println(zooAnimals.get(i).getIdTag() + " " + zooAnimals.get(i).getAnimalType());
        }
        System.out.println("Thank you for visiting the zoo");

    }


    public void createNewAnimal(ArrayList<iAnimal> zooAnimals) {

        String choice;
        int newid;
        Scanner in = new Scanner(System.in);

        System.out.print("Enter type of animal to add: ");
        System.out.print("Porcupine or Tiger\n");
        choice = in.nextLine();

        System.out.println("Enter the ID number for this animal: ");
        newid = in.nextInt();

        if (("PORCUPINE").equals(choice.toUpperCase())) {
            porcupine tempP = new porcupine();
            tempP.setIdTag(newid);
            checkPorcupines(zooAnimals, tempP);
        } else if (("TIGER").equals(choice.toUpperCase())) {
            Tiger tempT = new Tiger();
            tempT.setIdTag(newid);
            checkTigers(zooAnimals, tempT);
        } else {
            System.out.println("That is not a valid animal type");
        }

    }

    public void checkPorcupines(ArrayList<iAnimal> zooAnimals, porcupine tempAnimal) {
        boolean flag = true;
        for (int k = 0; k < zooAnimals.size(); k++) {
            if (tempAnimal.compareTo((zooAnimals.get(k))) == 1) {
                System.out.println("This animal already exists");
                flag = false;
            }
        }

        if (flag) {
            zooAnimals.add(tempAnimal);
            System.out.println("This animal has been added");
        }
    }

    public void checkTigers(ArrayList<iAnimal> zooAnimals, Tiger tempAnimal) {
        boolean flag = true;
        for (int k = 0; k < zooAnimals.size(); k++) {
            if (tempAnimal.compareTo((zooAnimals.get(k))) == 1) {
                System.out.println("This animal already exists");
                flag = false;
            }
        }

        if (flag) {
            zooAnimals.add(tempAnimal);
            System.out.println("This animal has been added");
        }
    }

}
