
/**
 * A class to represent a singular light, it's colour and its state (On or Off).
 *
 * @author Matt B
 * @version 1.0.0
 */
public class Light
{
    private String colour;
    private boolean is_on;
    
    /**
     * Constructor for objects of class Light
     * @param colour The colour that the light should be.
     */
    public Light(String colour)
    {
        this.colour = colour;
        this.is_on = false;
    }

    /**
     *  Accessor method for the light colour
     *  @return The current colour of the light
     */
    public String getColour()
    {
        return this.colour;
    }
    
    /**
     *  Mutator methods used to set the light's colour
     *  @param new_colour The new colour that the light should be set to
     */
    public void setColour(String new_colour)
    {
        this.colour = new_colour;
    }
    
    /**
     *  Function to turn on the light ie. set its on status to true
     */ 
    public void turnOn()
    {
        this.is_on = true;
    }
    
    /**
     *  Function to turn off the light ie. set its on status to false
     */ 
    public void turnOff()
    {
        this.is_on = false;
    }
    
    /** 
     *  Function to print the state of the light directly to the console.
     *  Prints the colour of the light if the light is on.
     *  Prints "=OFF=" if the light is turned off.
    */
    public void printState()
    {
        if(this.is_on)
            System.out.println(this.colour);
        else
            System.out.println("=OFF=");
    }
}
