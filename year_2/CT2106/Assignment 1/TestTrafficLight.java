
/**
 * Class used to test the TrafficLight class
 *
 * @author Matt B
 * @version 1.0.0
 */
public class TestTrafficLight
{
    public static void main(String[] args)
    {
        // We create a new instance of a TrafficLights object which we will then test.
        TrafficLights lights = new TrafficLights();
        
        // Create a for loop which will run 5 times.
        for(int i = 0; i < 5; i++)
        {
            // Print the following header to the console.
            System.out.println("-- Run " + (i + 1) + " --");
            
            // Call the lights "go" method to change the state of the lights and print the state to the console.
            lights.go();
            lights.printState();
            
            // Print an empty line to the console for spacing.
            System.out.println("");
            
            // Call the lights "preparetoStop" method to change the state of the lights and print the state to the console.
            lights.prepareToStop();
            lights.printState();
            
            // Print an empty line to the console for spacing.
            System.out.println("");
            
            // Call the lights "preparetoStop" method to change the state of the lights and print the state to the console.
            lights.stop();
            lights.printState();
            
            // Print the following footer to the console.
            // The additional "\n" at the end will add an additional empty line after the footer for more spacing.
            System.out.println("------------\n");
        }
    }
}
