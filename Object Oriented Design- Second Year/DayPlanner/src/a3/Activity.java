
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Reem
 */
abstract class Activity {
    private String title;
    private Time startTime;
    private Time endTime;
    private String comment; 
    
    public Activity(){
        title = " ";
        startTime = new Time();
        endTime = new Time();
        comment = " ";
        }
    public Activity(String title, String start, String end, String comment){
        this.title = title;
        startTime = new Time(start);
        endTime = new Time(end);
        this.comment = comment;
        }
    public Activity(Activity originalObject)
    {
        title = originalObject.title;
        comment = originalObject.comment;
        startTime = new Time(originalObject.startTime);
        endTime = new Time(originalObject.endTime);

    }
    public String getActivity()
    {
        String theString;
        theString = (title + "," + startTime.toString() + "," + endTime.toString() + "," + comment);
        return(theString);
    }
    public String getTitle()
    {
        return title;
    }
    public String getComment()
    {
        return comment;
    }
    public Time getStartTime()
    {
        return new Time(startTime);
    }
    public Time getEndTime()
    {
        return new Time(endTime);
    }
    public void setActivity(String title, String comment, Time startTime, Time endTime)
    {
        this.title = title;
        this.comment = comment;        
    }
    @Override
    public String toString()
    {
        String theString;
        theString = ("\n*** " + title + " ***" + "\n" + startTime.toString() + " to " + endTime.toString() + "\n" + comment);
        return theString;
    }
    public boolean equals(Object otherObject)
    {
        /*if(title.equals(NewActivity.title))
        {
            return true;
        }*/
        if(otherObject == null)
        {
            return false;
        }
        else if(getClass() != otherObject.getClass())
        {
            return false;
        }
        else
        {
            Activity otherActivity = (Activity)otherObject;
            return (title.equals(otherActivity.title) && 
            comment.equals(otherActivity.comment));
        }
    }
    
}

