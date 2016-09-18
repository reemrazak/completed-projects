
import java.util.Scanner;
import java.util.ArrayList;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.HashMap;


/**
 *
 * @author Reem
 */
public class DayPlanner {
    private String type;
    private String title;
    private String startingTime;
    private String endingTime;
    private String location;
    private String comment;
    private ArrayList<Activity> activityList;
    private HashMap<String, ArrayList<Integer>> activities;
    public DayPlanner()
    {
        type = " ";
        title = " ";
        startingTime = " ";
        endingTime = " ";
        location = " ";
        comment = " ";
        activityList = new ArrayList<Activity>();
        activities = new HashMap<String, ArrayList<Integer>>();
        
    }
    public ArrayList<Activity> getArrayList()
    {
        return activityList;
    }
    public HashMap<String, ArrayList<Integer>> getHashMap()
    {
        return activities;
    }

    public boolean addActivity(String type, String title, String startingTime, String endingTime, String location, String comment) {

        Scanner keyboard = new Scanner(System.in);
        boolean quit = false;
        String userInput;
        int i;
        int test;
        boolean searchSchool;
        boolean searchHome;
        boolean searchOther;
        boolean searchError = true;
        boolean checkTime;
        String inputFile = null;
        String outputFile = null;
        
        
        checkTime = timeCheck(startingTime);
        if(checkTime == false)
        {
            return false;
        }
        checkTime = timeCheck(endingTime);
        if(checkTime == false)
        {
            return false;
        }

        if(type.equalsIgnoreCase("school"))
        {
            SchoolActivity A = new SchoolActivity(title ,startingTime, endingTime, comment);
            activityList.add(A);
        }
        else if(type.equalsIgnoreCase("home"))
        {
            HomeActivity A = new HomeActivity(title, startingTime, endingTime, comment);
            activityList.add(A);
        }
        else if(type.equalsIgnoreCase("other"))
        {
            OtherActivity A = new OtherActivity(title, startingTime, endingTime, comment, location);
            activityList.add(A);
        }
        /*Processing Hash map*/
        StringTokenizer titleParse = new StringTokenizer(title, " ");
        String titleWord;
        while(titleParse.hasMoreTokens())
        {
            titleWord = titleParse.nextToken();
            titleWord = titleWord.toLowerCase();
            if(!activities.containsKey(titleWord))
            {
                ArrayList<Integer> list = new ArrayList<Integer>();
                list.add(activityList.size());
                activities.put(titleWord, list);
            }
            else
            {
                ArrayList<Integer> list = new ArrayList<Integer>();
                list = activities.get(titleWord);
                list.add(activityList.size());                        
            }
        }
        /*End of hashmap process.*/
        
        return true;
    }

        
       
    /*The timeCheck method ensures that the user inputs in the form yy/mm/dd hh:mm*/
    public boolean timeCheck(String input)
    {
        int year  = 0;
        int month = 0;
        int day = 0;
        int hour = 0;
        int minute = 0;
        StringTokenizer wordFactory = new StringTokenizer(input, " :/");   

        boolean check;
        check = input.matches("^\\d{2}/\\d{2}/\\d{2} \\d{2}:\\d{2}");
        if(check == true)
        {
            year = Integer.parseInt(wordFactory.nextToken());
            month = Integer.parseInt(wordFactory.nextToken());
            day = Integer.parseInt(wordFactory.nextToken());
            hour = Integer.parseInt(wordFactory.nextToken());
            minute = Integer.parseInt(wordFactory.nextToken());
        }
        if((month > 12)||(month < 0)||(day > 31) ||(day < 0)||((hour  == 24)&&(minute>00))||(hour>24)||(hour < 0)||(minute >59)||(minute <0))
        {
            check = false;
        }
        if(input.equals(""))
        {
            check = true;
        }

        return check;
    }
    /*The search function first asks the user which activities they would like to search. Then, for each
    element in the activity list (home, school, other), the timeSearch function is called, which returns a value of true or false
    dependant on whether the activity element occurs within a user selected time. If true, that activity is
    sent to the keywoard search function, which returns true or false dependant on whether the keyword is contained
    withing the activity element. If all the criteria is met, the element from the activity list is printed
    */
    public ArrayList<Activity> searchFunction(String inputStart, String inputEnd, String inputWords, String type, ArrayList<Activity> activityList, HashMap<String, ArrayList<Integer>> activities)
    {
        boolean searchSchool = false;
        boolean searchHome = false;
        boolean searchOther = false;
        boolean searchError = true;
        boolean foundTime;
        boolean foundWord;
        String userInput;
        int i;
        Scanner keyboard = new Scanner(System.in);
        ArrayList<Activity> results = new ArrayList<Activity>();
        
        if((type.equals(""))||(type.equals("School")))
        {
            searchSchool = true;
        }
        if((type.equals(""))||(type.equals("Home")))
        {
            searchHome = true;
        }
        if((type.equals(""))||(type.equals("Other")))
        {
            searchOther = true;
        }
        
        for (i = 0; i < activityList.size(); i++)
        {
            foundTime = timeSearch(activityList.get(i).getStartTime(), activityList.get(i).getEndTime(), inputStart, inputEnd);
            if(foundTime == true)
            {
                    foundWord = keywordSearch(activities, inputWords, i);
                    if((foundWord == true)&&(searchSchool == true)&&(activityList.get(i) instanceof SchoolActivity))
                    {
                        results.add(activityList.get(i));
                    }
                    if((foundWord == true)&&(searchHome == true)&&(activityList.get(i) instanceof HomeActivity))
                    {
                        results.add(activityList.get(i));
                    }
                    if((foundWord == true)&&(searchOther == true)&&(activityList.get(i) instanceof OtherActivity))
                    {
                        results.add(activityList.get(i));
                    }
            }               
        }
        
        return results;
    }
    /*The keywordSearch method tokenizes all words from the activity element, as well as the user input
    into two separate arrays. The arrays are then compared to see if the keywoard that the user inputted is
    contained within the activity element*/
    static boolean keywordSearch(HashMap<String, ArrayList<Integer>> activities, String inputWords, int currentWord)
    {
        Scanner keyboard = new Scanner(System.in);
        int i;
        int j;
        boolean found = false;
        boolean foundTemp = true;
        int inputTokens;
        int activityTokens;
        String inputWord;
        currentWord++;

        ArrayList<Integer> list = new ArrayList<Integer>();

        if(inputWords.equals(""))
        {
            return true;
        }

        inputWords = inputWords.toLowerCase();
        StringTokenizer inputParse = new StringTokenizer(inputWords, " ");
        while((inputParse.hasMoreTokens())&&(foundTemp == true))
        {
            inputWord = inputParse.nextToken();
            if(activities.containsKey(inputWord))
            {
                list = activities.get(inputWord);
                if(list.contains(currentWord))
                {
                    foundTemp = true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }

        }
        if(foundTemp = true)
        {
            found = true;
        }
        return found;
    }
    
    /*The timeSearch method takes in inputStart and inputEnd, which are chosen by the user, as well as
    the start and end times of the activity list element. It then compares these variables to ensure that the
    activity list element occurs during the time provided by inputStart and inputEnd. returns true if found
    */
    //static boolean timeSearch(ArrayList activityList, int i, String inputStart, String inputEnd)
    //{
      static boolean timeSearch(Time ActivityStart, Time ActivityEnd, String inputStart, String inputEnd)
      {

        boolean found = false;
        

        if((inputStart.equals(""))&&(inputEnd.equals("")))
        {
            found = true;
        }
        else if(inputStart.equals(""))
        {
            Time InputEnd = new Time(inputEnd);
            if(ActivityEnd.compareTo(InputEnd) == false)
            {
                found = true;
            }
            if(InputEnd.equalsTo(ActivityEnd) == true)
            {
                found = true;
              
            }

        }
        else if(inputEnd.equals(""))
        {
            Time InputStart = new Time(inputStart);
            if(ActivityStart.compareTo(InputStart) == true)
            {
                found = true;
            }

        }
        else
        {
            Time InputStart = new Time(inputStart);
            Time InputEnd = new Time(inputEnd);
            boolean start = false;
            boolean end = false;
            if((InputStart.equalsTo(ActivityStart) == true)&&(InputEnd.equalsTo(ActivityEnd) == true))
            {
                found = true;
              
            }
            start = InputStart.equalsTo(ActivityStart);
            end = InputEnd.equalsTo(ActivityEnd);
            if((ActivityStart.compareTo(InputStart) == true)&&(ActivityEnd.compareTo(InputEnd) == false))
            {
                found = true;
            }
            else if((ActivityStart.compareTo(InputStart) == true)&&(end == true))
            {
                found = true;
            }
            else if((ActivityEnd.compareTo(InputEnd) == false)&&(start == true))
            {
                found = true;
            }
        }
        return found;
    }
}



