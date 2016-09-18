/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.util.ArrayList;
import java.util.InputMismatchException;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

/**
 *
 * @author Reem
 */
/*This class extends the JFrame and implements the GUI*/
public class MainMenu extends JFrame{
        private JPanel buttonBoard;
        private JPanel entryBoard;
        private JLabel comment;
        private GridBagConstraints gbc;
        private JComboBox<String> activityList;
        private JComboBox<String> searchActivityList;
        private JLabel location;
        private JTextField commentEntry;
        private JTextField locationEntry;
        private JTextField titleEntry;
        private JTextField startEntry;
        private JTextField endEntry;
        private JLabel addingActivity;
        private JLabel searchingActivity;
        private JLabel type;
        private JPanel messageBoard;
        private JLabel title;
        private JLabel start;
        private JLabel end;
        private JLabel messages;
        private JLabel results;
        private JTextArea messageDisplay;
        private JScrollPane messagePane;
        private JButton reset;
        private JButton enter;
        private JPanel board;
        private JPanel addBoard;
        private JPanel searchBoard;
        private JMenuBar bar;
        private JMenu commands;
        private JMenu preferences;
        private JMenuItem add;
        private JMenuItem search;
        private JMenuItem edit;
        private DayPlanner planner;
        private JMenuItem exit;
        private CheckOnExit exitCheck;
        private JPanel centreBoard;



    /****Generates the main panels****/
    public MainMenu()
    {
        board = new JPanel(new BorderLayout());
        addBoard = new JPanel(new BorderLayout());
        searchBoard = new JPanel(new GridBagLayout());
        planner = new DayPlanner();
        gbc = new GridBagConstraints();
    }
    /*Creates the welcome panel*/
    public void createMenu()
    {
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        board.setBackground(new Color(13,54,100));
        exitCheck = new CheckOnExit();
        addWindowListener(exitCheck);

        /*setting background for main menu*/
        ImageIcon plane = new ImageIcon("plane.png"); 
        JLabel planeLabel = new JLabel("", plane, JLabel.CENTER);
        planeLabel.setPreferredSize(new Dimension(190,94));
        board.setBackground(new Color(13,54,100));
        centreBoard = new JPanel(new GridBagLayout());
        centreBoard.setBackground(new Color(13,54,100));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(15,15,15,15);

        board.setPreferredSize(new Dimension(650,375));
        
        bar = new JMenuBar();
        commands = new JMenu("Commands");
        preferences = new JMenu("Preferences");
        add = new JMenuItem("Add");
        edit = new JMenuItem("Edit");
        search = new JMenuItem("Search");
        exit = new JMenuItem("Exit");
        bar.setBackground(new Color(13,54,100));
        commands.setBackground(new Color(13,54,100));
        preferences.setBackground(new Color(13,54,100));
        edit.setBackground(new Color(255,210,159));
        add.setBackground(new Color(255,210,159));
        search.setBackground(new Color(255,210,159));
        exit.setBackground(new Color(255,210,159));
        
        /*Action listeners are added for each option in the toolbar**/
        add.addActionListener(new AddListener());
        search.addActionListener(new SearchListener());
        exit.addActionListener(new exitListener());
        edit.addActionListener(new preferencesListener());
         
        commands.add(add);
        commands.add(search);
        commands.add(exit);
        preferences.add(edit);
        bar.add(commands);
        bar.add(preferences);
        setJMenuBar(bar);
        
        JLabel welcome = new JLabel("Welcome to my Day Planner");
        JLabel message = new JLabel("<html>Choose a command from the \"Commands\" menu above for adding <br>an activity, searching activities, or quitting the program</html>");
        welcome.setForeground(Color.white);
        message.setForeground(Color.white);

        gbc.gridy = 0;
        centreBoard.add(welcome, gbc);
        gbc.gridy = 2;
        centreBoard.add(message, gbc);
        board.add(planeLabel, BorderLayout.EAST);
        board.add(centreBoard, BorderLayout.CENTER);
        add(board, BorderLayout.CENTER);
        pack();

        implementAddGUI();
        addBoard.setVisible(false);
    }
    /*Generates the components of each panel*/
    public void implementAddGUI()
    {
        buttonBoard  = new JPanel(new FlowLayout());
        addBoard.setBackground(new Color(76,65,65));
        JLabel background = new JLabel(new ImageIcon("image2.png"));
        addBoard.setPreferredSize(new Dimension(550,625));
        buttonBoard.setBackground(new Color(76,65,65));
        buttonBoard.setPreferredSize(new Dimension(150, 250));            
        buttonBoard.add(background, BorderLayout.NORTH);
        add(addBoard);
        addBoard.add(buttonBoard);
        addBoard.setVisible(false);

        entryBoard = new JPanel(new GridBagLayout());
        messageBoard = new JPanel(new BorderLayout(5,5));
        entryBoard.setBackground(new Color(13,54,100));
        entryBoard.setPreferredSize(new Dimension(400,250));
        messageBoard.setBackground(new Color(187, 29, 31));
        messageBoard.setBorder(BorderFactory.createLineBorder(Color.WHITE));
        messageBoard.setPreferredSize(new Dimension(550, 150));
        addBoard.add(entryBoard, BorderLayout.WEST);
        addBoard.add(messageBoard,BorderLayout.SOUTH);
        gbc.insets = new Insets(2,2,2,2);
        gbc.weightx = 0;
        gbc.weightx = 0;

        addingActivity = new JLabel("Adding an activity");
        searchingActivity = new JLabel("Searching activities");
        addingActivity.setForeground(Color.WHITE);
        searchingActivity.setForeground(Color.WHITE);
        entryBoard.add(addingActivity, gbc);
        entryBoard.add(searchingActivity, gbc);
        gbc.fill = GridBagConstraints.CENTER;

        type = new JLabel();    
        type.setForeground(Color.WHITE);
        activityList = new JComboBox<String>(new String[]{"Other", "School", "Home"});
        searchActivityList = new JComboBox<String>(new String[]{"", "Other", "School", "Home"});

        gbc.gridx = 0;
        gbc.gridy = 1;

        entryBoard.add(type, gbc);
        gbc.gridx = 1;
        entryBoard.add(activityList, gbc);
        entryBoard.add(searchActivityList, gbc);

        title = new JLabel();
        title.setForeground(Color.WHITE);
        titleEntry = new JTextField(15);
        gbc.gridx = 0;
        gbc.gridy = 2;
        entryBoard.add(title, gbc);
        gbc.gridx = 1;
        entryBoard.add(titleEntry, gbc);

        start = new JLabel();
        end = new JLabel();
        start.setForeground(Color.WHITE);
        end.setForeground(Color.WHITE);
        startEntry = new JTextField(25);
        endEntry = new JTextField(25);

        gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.WEST;
        gbc.gridx = 0;
        gbc.gridy = 3;
        entryBoard.add(start, gbc);
        gbc.gridy = 4;
        entryBoard.add(startEntry, gbc);
        entryBoard.add(startEntry, gbc);

        gbc.gridy = 5;

        entryBoard.add(end, gbc);
        gbc.gridy = 6;
        entryBoard.add(endEntry, gbc);

        location = new JLabel("Location");
        location.setForeground(Color.WHITE);
        locationEntry = new JTextField(15);
        comment = new JLabel("Comment");
        comment.setForeground(Color.WHITE);
        commentEntry = new JTextField(15);
        gbc.gridy = 7;
        gbc.gridx = 0;
        entryBoard.add(location,gbc);
        gbc.gridx = 1;
        entryBoard.add(locationEntry, gbc);
        location.setVisible(false);
        locationEntry.setVisible(false);
        gbc.gridx = 0;
        gbc.gridy = 9;
        entryBoard.add(comment, gbc);
        gbc.gridx = 1;
        entryBoard.add(commentEntry, gbc);

        messages = new JLabel("Messages:");
        results = new JLabel("Search results:");
        messages.setForeground(Color.WHITE);
        results.setForeground(Color.WHITE);
        messageDisplay = new JTextArea(4,35);
        messagePane = new JScrollPane(messageDisplay);
        messagePane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        messagePane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
//
        messageBoard.add(messagePane, BorderLayout.CENTER);
        messageBoard.add(new JLabel(" "), BorderLayout.SOUTH);
        messageBoard.add(new JLabel(" "), BorderLayout.EAST);
        messageBoard.add(new JLabel(" "), BorderLayout.WEST);

        reset = new JButton("Reset");
        enter = new JButton("Enter");
        reset.setPreferredSize(new Dimension(80, 40));
        enter.setPreferredSize(new Dimension(80, 40));
        ////
        reset.addActionListener(new ResetListener());
        buttonBoard.add(reset);
        buttonBoard.add(enter); 
    }
    /*This class creates a new Jframe where the user can edit their preferences for the theme of the DayPlanner*/
    private class preferencesListener extends JFrame implements ActionListener
    {
        JFrame prefFrame;
        JPanel prefPanel;
        JComboBox<Integer> mainRChoice;
        JComboBox<Integer> mainGChoice;
        JComboBox<Integer> mainBChoice;
        JComboBox<Integer> messageRChoice;
        JComboBox<Integer> messageGChoice;
        JComboBox<Integer> messageBChoice;
        JComboBox<Integer> buttonRChoice;
        JComboBox<Integer> buttonGChoice;
        JComboBox<Integer> buttonBChoice;

        public void actionPerformed(ActionEvent e)
        {
            prefFrame = new JFrame();
            prefPanel = new JPanel(new GridBagLayout());
            GridBagConstraints gbc = new GridBagConstraints();
            prefFrame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
            gbc.insets = new Insets(15,15,15,15);
            JLabel mainMessage = new JLabel("Please enter three RGB values to change the colour scheme:");
            JLabel r = new JLabel("Main Board:");
            JLabel g = new JLabel("Reset/Enter Board:");
            JLabel b = new JLabel("Messages Board:");
            JLabel redLabel = new JLabel("R");
            JLabel blueLabel = new JLabel("G");
            JLabel greenLabel = new JLabel("B");
            mainRChoice = new JComboBox<Integer>();
            mainBChoice = new JComboBox<Integer>();
            mainGChoice = new JComboBox<Integer>();
            messageRChoice = new JComboBox<Integer>();
            messageGChoice = new JComboBox<Integer>();
            messageBChoice = new JComboBox<Integer>();
            buttonRChoice = new JComboBox<Integer>();
            buttonGChoice = new JComboBox<Integer>();
            buttonBChoice  = new JComboBox<Integer>();
            JButton enter = new JButton("Save");
            JButton cancel = new JButton("Cancel");
            cancel.addActionListener(new cancelPrefListener());

            for (int i = 0; i <= 256; i++)
            {
                mainRChoice.addItem(new Integer(i));
                mainBChoice.addItem(new Integer(i));
                mainGChoice.addItem(new Integer(i));
                //
                messageRChoice.addItem(new Integer(i));
                messageGChoice.addItem(new Integer(i));
                messageBChoice.addItem(new Integer(i));
                //
                buttonRChoice.addItem(new Integer(i));
                buttonGChoice.addItem(new Integer(i));
                buttonBChoice.addItem(new Integer(i));

            }
            //This is a cool colour 155,211, 156
            prefFrame.setSize(600, 400);
            prefFrame.setLayout(new BorderLayout());
            prefPanel.setBackground(new Color(155, 211, 156));
            prefFrame.add(prefPanel);
            
            gbc.gridx = 1;
            gbc.gridy = 0;
            prefPanel.add(redLabel, gbc);
            gbc.gridx = 2;
            prefPanel.add(greenLabel, gbc);
            gbc.gridx = 3;
            prefPanel.add(blueLabel, gbc);
            prefFrame.add(mainMessage, BorderLayout.NORTH);
            gbc.gridx = 0;
            gbc.gridy = 1;
            prefPanel.add(r, gbc);
            gbc.gridx = 1;
            prefPanel.add(mainRChoice, gbc);
            gbc.gridx = 2;
            prefPanel.add(mainGChoice, gbc);
            gbc.gridx = 3;
            prefPanel.add(mainBChoice, gbc);
            
            gbc.gridy = 2;
            gbc.gridx = 0;
            prefPanel.add(b, gbc);
            gbc.gridx = 1;
            prefPanel.add(messageRChoice, gbc);
            gbc.gridx = 2;
            prefPanel.add(messageGChoice, gbc);
            gbc.gridx = 3;
            prefPanel.add(messageBChoice, gbc);
            
            gbc.gridy = 3;
            gbc.gridx = 0;
            prefPanel.add(g, gbc);
            gbc.gridx = 1;
            prefPanel.add(buttonRChoice, gbc);
            gbc.gridx = 2;
            prefPanel.add(buttonGChoice, gbc);
            gbc.gridx = 3;
            prefPanel.add(buttonBChoice, gbc);
            
            gbc.gridy = 4;            
            prefPanel.add(enter, gbc); 
            gbc.gridx = 2;
            prefPanel.add(cancel, gbc);
            enter.addActionListener(new savePreferences());
            prefFrame.setVisible(true);            
        }
        /*actionlistener to cancel editing preferences*/
        private class cancelPrefListener implements ActionListener
        {
            public void actionPerformed(ActionEvent e)
            {
                prefFrame.dispose();
            }
        }
        /*actionlistener to save preferences*/
        private class savePreferences implements ActionListener
        {
            public void actionPerformed(ActionEvent e)
            {            
                int red;
                int green;
                int blue; 
                red = (int)mainRChoice.getSelectedItem();
                green = (int)mainGChoice.getSelectedItem();
                blue = (int)mainBChoice.getSelectedItem();
                entryBoard.setBackground(new Color( red, green, blue));
                board.setBackground(new Color( red, green, blue));
                centreBoard.setBackground(new Color( red, green, blue));
                centreBoard.repaint();
                entryBoard.repaint(); 
                board.repaint();
                red = (int)messageRChoice.getSelectedItem();
                green = (int)messageGChoice.getSelectedItem();
                blue = (int)messageBChoice.getSelectedItem();
                messageBoard.setBackground(new Color(red, green, blue));
                messageBoard.repaint();
                red = (int)buttonRChoice.getSelectedItem();
                green = (int)buttonGChoice.getSelectedItem();
                blue = (int)buttonBChoice.getSelectedItem();
                buttonBoard.setBackground(new Color(red, green, blue));
                buttonBoard.repaint();
                prefFrame.dispose();
            }
        }
    }
    /*actionlistener to create confirm window*/
    private class exitListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            exitCheck.windowClosing(null);
        }
    }
    /*actionlistener to implement searching activities*/
    private class enterSearchListener implements ActionListener
    {
        private String type;
        private String title;
        private String startTime;
        private String endTime;
        private boolean checkStart;
        private boolean checkEnd;
        private ArrayList<Activity> results;
        private int i;
        @Override
        public void actionPerformed(ActionEvent e)
        {
            type = (String)searchActivityList.getSelectedItem();
            try
            {
                title = titleEntry.getText();
                startTime = startEntry.getText();
                endTime = endEntry.getText();
                checkStart = planner.timeCheck(startTime);
                checkEnd = planner.timeCheck(endTime);
                if((checkStart == false)||(checkEnd == false)||(startTime.compareTo(endTime) > 0))
                {
                    throw new InputMismatchException();
                }
                messageDisplay.setText("Now printing search results:");
                results = planner.searchFunction(startTime, endTime, title, type, planner.getArrayList(), planner.getHashMap());
                for (i = 0; i < results.size(); i++)
                {
                    messageDisplay.append(results.get(i).toString());
                }
            }
            catch(InputMismatchException error)
            {
                messageDisplay.setText("Invalid Entry: Please ensure all required fields are filled in, and the starting time is before the ending time");
            }                
        }                     
    }
    /*Actionlistener which executed adding an acivity*/
    private class enterAddListener implements ActionListener
    {
        private String type;
        private String title;
        private String startTime;
        private String endTime;
        private String location;
        private String comment;
        boolean activityAdded;

        public void actionPerformed(ActionEvent e)
        {
            type = (String)activityList.getSelectedItem();
            if((type.equals("School"))||(type.equals("Home")))
            {
                try
                {
                    title = titleEntry.getText();
                    startTime = startEntry.getText();
                    endTime = endEntry.getText();
                    location = locationEntry.getText();
                    comment = commentEntry.getText();
                    if((title.equals(""))||(startTime.equals(""))||(endTime.equals(""))||(startTime.compareTo(endTime) > 0))
                    {
                        throw new InputMismatchException();
                    }
                    messageDisplay.setText("Successfully added " + title + " to DayPlanner");
                    activityAdded = planner.addActivity(type, title, startTime, endTime, null, comment);
                    if(activityAdded == false)
                    {
                        throw new InputMismatchException();
                    }
                }
                catch(InputMismatchException error)
                {
                    messageDisplay.setText("Invalid Entry: Please ensure all required fields are filled in. The time input should match the format specified, and the start time should be before the end time");
                }                
            }
            else if (type.equals("Other"))
            {
                try
                {
                    title = titleEntry.getText();
                    startTime = startEntry.getText();
                    endTime = endEntry.getText();
                    location = locationEntry.getText();
                    comment = commentEntry.getText();
                    if((title.equals(""))||(startTime.equals(""))||(endTime.equals(""))||(startTime.compareTo(endTime) > 0))
                    {
                        throw new InputMismatchException();
                    }
                    messageDisplay.setText("Successfully added " + title + " to DayPlanner");
                    activityAdded = planner.addActivity(type, title, startTime, endTime, location, comment);
                    if(activityAdded == false)
                    {
                        throw new InputMismatchException();
                    }
                }
                catch(InputMismatchException error)
                {
                    messageDisplay.setText("Invalid Entry: Please ensure all fields are filled in, and time input matches the format specified");
                }
            }
            else
            {
                messageDisplay.setText("Unexpected error. Please ensure a type is selected");
            }
        }
    }
    /*actionlistener which switches to the search activity pane*/
    private class SearchListener implements ActionListener              
    {
        public void actionPerformed(ActionEvent e)
        {
            setSize(550,625);
            board.setVisible(false);
            addBoard.setVisible(true);
            comment.setVisible(false);
            commentEntry.setVisible(false);
            searchingActivity.setVisible(true);
            addingActivity.setVisible(false);
            location.setVisible(false);
            locationEntry.setVisible(false);
            messages.setVisible(false);
            messageBoard.add(results, BorderLayout.NORTH);
            results.setVisible(true);
            title.setText("Title");
            type.setText("Type");
            start.setText("Starting time yy/mm/dd hh:mm");
            end.setText("Ending time yy/mm/dd hh:mm");
            activityList.setVisible(false);
            searchActivityList.setVisible(true);
            for(ActionListener act : searchActivityList.getActionListeners()) {
                searchActivityList.removeActionListener(act);
            }
            for(ActionListener act : enter.getActionListeners()) {
                enter.removeActionListener(act);
            }
            for(ActionListener act : reset.getActionListeners()) {
                reset.removeActionListener(act);
            }
            reset.addActionListener(new SearchResetListener());
            enter.addActionListener(new enterSearchListener());
            searchActivityList.setSelectedIndex(0);


        }
    }
    /*actionlistener which switches to the add activity pane*/
    private class AddListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            setSize(550,625);
            board.setVisible(false);
            searchingActivity.setVisible(false);
            addingActivity.setVisible(true);
            addBoard.setVisible(true);
            comment.setVisible(true);
            commentEntry.setVisible(true);
            messages.setVisible(true);
            results.setVisible(false);
            messageBoard.add(messages, BorderLayout.NORTH);
            messages.setVisible(true);
            activityList.setVisible(true);
            searchActivityList.setVisible(false);
            activityList.setSelectedIndex(1);
            activityList.addActionListener(new FieldListener());
            for(ActionListener act : enter.getActionListeners()) {
                enter.removeActionListener(act);
            }
            enter.addActionListener(new enterAddListener());
            for(ActionListener act : reset.getActionListeners()) {
                reset.removeActionListener(act);
            }
            reset.addActionListener(new ResetListener());
            
            //changing combo box shit so there's  a blank option for search

            title.setText("*Title");
            type.setText("*Type");
            start.setText("*Starting time yy/mm/dd hh:mm");
            end.setText("*Ending time yy/mm/dd hh:mm");
        }
    }
    /*action listener which resets the form*/
    private class ResetListener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e)
        {
            commentEntry.setText("");
            locationEntry.setText("");
            titleEntry.setText("");
            startEntry.setText("");
            endEntry.setText("");
            messageDisplay.setText("");
            activityList.setSelectedIndex(1);
        }            
    }
        /*action listener which resets the form*/
    private class SearchResetListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            commentEntry.setText("");
            locationEntry.setText("");
            titleEntry.setText("");
            startEntry.setText("");
            endEntry.setText("");
            messageDisplay.setText("");
            searchActivityList.setSelectedIndex(0);
        }
                
    }
    private class FieldListener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e)
        {
            String field = (String)activityList.getSelectedItem();
            if((field.equals("School"))||(field.equals("Home")))
            {
                location.setVisible(false);
                locationEntry.setVisible(false);
                pack();
            }
            else if(field.equals("Other"))
            {
                location.setVisible(true);
                locationEntry.setVisible(true);
                pack();
            }                
        }
    }
    /*Windowlistener*/
    public class CheckOnExit extends JFrame implements WindowListener
    {
        @Override
        public void windowOpened(WindowEvent e)
        {}        
        @Override
        public void windowClosing(WindowEvent e)
        {
            ConfirmWindow checkers = new ConfirmWindow();
            checkers.setVisible(true);
        }
        @Override
        public void windowClosed(WindowEvent e)
        {}
        
        @Override
        public void windowIconified(WindowEvent e)
        {}
        
        @Override
        public void windowDeiconified(WindowEvent e)
        {}
        
        
        @Override
        public void windowActivated(WindowEvent e)
        {}
                
        @Override
        public void windowDeactivated(WindowEvent e)
        {}
    }
    /*creates a confirm window listneer*/
    private class ConfirmWindow extends JFrame implements ActionListener
    {
        public ConfirmWindow()
        {
            setSize(200, 150);
            getContentPane().setBackground(new Color(255,210,159));
            setLayout(new BorderLayout());
             JLabel daConfirm = new JLabel("Are you sure you want to exit?");
             add(daConfirm, BorderLayout.CENTER);
             JPanel daButton = new JPanel();
             daButton.setBackground(new Color(255,210,159));
             daButton.setLayout(new FlowLayout());
             JButton daExit = new JButton("Yes");
             daExit.addActionListener(this);
             daButton.add(daExit);
             JButton daCancel = new JButton("No");
             daCancel.addActionListener(this);
             daButton.add(daCancel);
             add(daButton, BorderLayout.SOUTH);
            
        }
        public void actionPerformed(ActionEvent e)
        {
            String actionCommand = e.getActionCommand();
            if (actionCommand.equals("Yes"))
                System.exit(0);
            else if (actionCommand.equals("No"))
            dispose(); //Destroys only the ConfirmWindow.
            else
            System.out.println(
             "Unexpected Error in Confirm Window.");
        }
    }
}
    
