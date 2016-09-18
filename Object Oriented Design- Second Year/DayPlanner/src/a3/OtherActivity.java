

/**
 *
 * @author Reem
 */
public class OtherActivity extends Activity
{

    private String location;
        /*Default constructor for HomeActivity Class*/
    public OtherActivity(){
        super();
        location = " ";
    }
    /*Secondary constructor for HomeActivity Class*/
    public OtherActivity(String title, String startTime, String endTime, String comment, String location){
        super(title, startTime, endTime, comment);
        this.location = location;
    }
    public OtherActivity(OtherActivity originalObject)
    {
        super(originalObject);
    }

    /*Accessor method returns the title, location, and comment info on the class*/
    @Override
    public String getActivity()
    {
        String theString;
        theString = (getTitle() + "," + getStartTime().toString() + "," + getEndTime().toString() + "," + getComment() + "," + location);
        return(theString);
    }
    public String getLocation()
    {
        return location;
    }
    /*mutator method for future use in changing OtherActivity*/
    public void setOther(String location)
    {
        this.location = location;
    }
    /*toString method converts information in this class into a string*/
    @Override
    public String toString()
    {
        String theString;
        theString = ("\n*** " + getTitle() + " ***" + "\nlocation: " + location + "\n" + getStartTime().toString() + " to " + getEndTime().toString() + "\n" + getComment());
        return theString;
    }
  

    
}
