
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Reem
 */
public class SchoolActivity extends Activity{
    private String title;
    Time Start;
    Time End;
    private String comment;
    
      /*Default constructor for HomeActivity Class*/
    public SchoolActivity(){
        super();
    }
    /*Secondary constructor for HomeActivity Class*/
    public SchoolActivity(String title, String startTime, String endTime, String comment){
        super(title, startTime, endTime, comment);
    }
    public SchoolActivity(SchoolActivity originalObject)
    {
        super(originalObject);
    }

    
}