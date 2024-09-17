
/**
 * A class that represents a street traffic light.
 *
 * @author Matt B
 * @version 1.0.0
 */
public class TrafficLights
{
    private Light red_light;
    private Light amber_light;
    private Light green_light;

    /**
     * Constructor for objects of class TraficLights
     * Instantiates the three lights, red, amber and green.
     */
    public TrafficLights()
    {
        this.red_light = new Light("Red");
        this.amber_light = new Light("Amber");
        this.green_light = new Light("Green");
    }
    
    /**
     *  Turns only the green light on
     */
    public void go()
    {
        this.red_light.turnOff();
        this.amber_light.turnOff();
        this.green_light.turnOn();
    }
    
    /**
     *  Turns only the amber light on
     */
    public void prepareToStop()
    {
        this.red_light.turnOff();
        this.amber_light.turnOn();
        this.green_light.turnOff();
    }
    
    /**
     *  Turns only the red light on
     */
    public void stop()
    {
        this.red_light.turnOn();
        this.amber_light.turnOff();
        this.green_light.turnOff();
    }
    
    /**
     *  Calls the "printState" method of all the lights.
     *  This prints the state of all the lights to the console.
     */
    public void printState()
    {
        this.red_light.printState();
        this.amber_light.printState();
        this.green_light.printState();
    }
}
