
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Reem
 */
public class HomeActivity extends Activity {

    
    /*Default constructor for HomeActivity Class*/
    public HomeActivity(){
        super();
    }
    /*Secondary constructor for HomeActivity Class*/
    public HomeActivity(String title, String startTime, String endTime, String comment){
        super(title, startTime, endTime, comment);
    }
    public HomeActivity(HomeActivity originalObject)
    {
        super(originalObject);
    }


    
}
