# CS1B_ZooAnimals
For CS 1B at Foothill College Project 4 Zoo Animals

```
public interface iAnimal {
    public String getAnimalType();
    public int getIdTag();
    public void setIdTag(int anIdTag);
    public int getMinTemperature();
    public int getMaxTemperature();
}
```


Create a class that implements the interface listed above for an animal type that begins with the same letter as your last name. For example, my last name begins with M, so I might create a Mongoose class. Your class must implement the interface and it must compile. If you cannot find an animal that begins with the same letter as your last name, you can choose an animal type that begins with the same letter as your first name. 

Post your class to this discussion as an attachment or provide a link to the github repository for your code.  As soon as you post your code, you will unlock all of the other posts to see the classes created by your fellow students.  You will then choose one or more classes posted to the discussion by your classmates and download the code to use for Project 4.

Project 4 will require that you use at least one class from a fellow student in your solution, so start work early on your discussion post!   

**Implementation Requirements For Your Class:

getAnimalType: This should return the type of animal.  For example, for my Mongoose class, the animal type will be directly set to "Mongoose" in the code, which would be returned by this method. You must not get this information from the user, so you should not include a mutator method to set the animal type value.

getIdTag and setIdTag: These can be standard mutator and accessor methods without any validation to get and set the animal's id number.

getMinTemperature and getMaxTemperature: These methods should return the minimum and maximum temperatures for the animal's enclosure, but you must not get this information from the user, so you should not include a mutator method to set these values.  Instead, set these values directly in your code according to the appropriate temperature range for your animal's environment. You can find this information online, such as from wikipedia (Links to an external site.) or from an Animal Care Manual. (Links to an external site.)

# Project Instructions

For this project, you will create an application for a zoo.  You can earn up to 5 points extra credit if you create a  JavaFX or Swing application for this project.

You will need to create a class that implements the `iAnimal` interface and download at least one class by a fellow classmate for a different animal than your own from that discussion.  Modify the animal classes that you will use for this project so they implement Java's comparable or comparator interface. 

You will also need a `Foothill (Main) Class` that will provide a user interface for this application.  This can be a console-based interface or a JavaFX or Swing interface (you choose).  If you use JavaFX or Swing, you will need input boxes, at least one button with a click event to get the extra credit.  Based on user interaction, you will need to perform the tasks listed below.  These tasks can be performed in one or more methods as needed.

The `Foothill (Main) class` should have one or more methods that handle these tasks:

- Create a new instance (object) of each of the animal classes and pass the user input as arguments to the object's mutator methods to set the private instance data for the appropriate animal class.

- Create an ArrayList of type iAnimal and add the new instance created in task 1 to the ArrayList.  Before adding the instance to the ArrayList you must:

- Call the compareTo method for the new animal's instance to compare that new instance to each of the instances already in the ArrayList (use a loop or recursion for this).

   - If the ArrayList is empty, or if none of the instances are identical to the new instance, insert the new instance into the ArrayList.
  - If the new instance is identical to any of the instances already in the ArrayList, display an error message and do not insert the new instance.
  
When testing, add multiple instances of your animal's class and multiple instances of the class you borrowed from the discussion to the ArrayList as described above.  Because you are working with more than one class, you can decide how to determine which class to use based on user input, but the goal is to create an instance of the class that matches the type of animal entered by the user.

Use a loop to iterate through the ArrayList and display all of the data for each instance in the ArrayList using accessor or ToString methods.


Feel free to add whatever you need for testing purposes.  You can also make changes to your classmate's class as needed.  You do not need to include the output with your submission, but please add a comment to let me know which type of application you selected (console, Swing or JavaFX).
