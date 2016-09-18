
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Reem
 */
import java.util.StringTokenizer;

/**
 *
 * @author Reem
 */
public class Time {
    private int year;
    private int month;
    private int day;
    private int hour;
    private int minute;
    String timeInput;
    
    Time()
    {
        year = 00;
        month = 00;
        day = 00;
        hour = 00;
        minute = 00;
    }
    Time(String timeInput)
    {
        year = 00;
        month = 00;
        day = 00;
        hour = 00;
        minute = 00;
        StringTokenizer wordFactory = new StringTokenizer(timeInput, " :/");   

        year = Integer.parseInt(wordFactory.nextToken());
        month = Integer.parseInt(wordFactory.nextToken());
        day = Integer.parseInt(wordFactory.nextToken());
        hour = Integer.parseInt(wordFactory.nextToken());
        minute = Integer.parseInt(wordFactory.nextToken());

    }
    public Time(Time aTime)
    {
        year = aTime.year;
        month = aTime.month;
        day = aTime.day;
        hour = aTime.hour;
        minute = aTime.minute;
    }
    /*CompareTo method.
    returns true if this.time is greater than the Activity.time
    returns false otherwise
    */
    public boolean compareTo(Time Activity)
    {
        boolean check = true;
        if(this.year < Activity.year)
        {
            check = false;
        }
        if(this.month < Activity.month)
        {
            check = false;
        }
        if(this.day < Activity.day)
        {
            check = false;
        }
        if(this.hour < Activity.hour)
        {
            check = false;
        }
        if(this.minute < Activity.minute)
        {
            check = false;
        }
    
        return  check;
                        
    }
    /*equals method*/
    public boolean equalsTo(Time Activity)
    {
        boolean check = false;
        if((this.year == Activity.year)&&(this.month == Activity.month)&&(this.day == Activity.day)&&(this.hour == Activity.hour)&&(this.minute == Activity.minute))
        {
            check = true;
        }

        return check;
    }
    /*Accessor method*/
    public int getYear()
    {
        return(year);
    }
    /*Accessor method*/
    public int getMonth()
    {
        return month;
    }
    /*Accessor method*/
    public int getDay()
    {
        return day;
    }
    /*Accessor method*/
    public int getHour()
    {
        return hour;
    }
    /*Accessor method*/
    public int getMinute()
    {
        return minute;
    }
    /*toString method*/
    @Override
    public String toString()
    {
        String time;
        time = (year + "/" + month + "/" + day + " " + hour + ":" + minute);
        return time;
    }
    /*Mutator method*/
    public void setTime(int year, int month, int day, int hour, int minute)
    {
        this.year = year;
        this.month = month;
        this.day = day;
        this.hour = hour;
        this.minute = minute;
    }
}