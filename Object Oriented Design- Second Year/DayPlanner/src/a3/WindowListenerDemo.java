/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 *
 * @author Reem
 */
public class WindowListenerDemo extends JFrame
{
    public static final int WIDTH = 300;
    public static final int HEIGHT = 200;
    public static final int SMALL_WIDTH = 200;
    public static final int SMALL_HEIGHT = 100;
    
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
    
    private class ConfirmWindow extends JFrame implements ActionListener
    {
        public ConfirmWindow()
        {
            setSize(SMALL_WIDTH, SMALL_HEIGHT);
            getContentPane().setBackground(Color.YELLOW);
            setLayout(new BorderLayout());
             JLabel confirmLabel = new JLabel("Are you sure you want to exit?");
             add(confirmLabel, BorderLayout.CENTER);
             JPanel buttonPanel = new JPanel();
             buttonPanel.setBackground(Color.ORANGE);
             buttonPanel.setLayout(new FlowLayout());
             JButton exitButton = new JButton("Yes");
             exitButton.addActionListener(this);
             buttonPanel.add(exitButton);
             JButton cancelButton = new JButton("No");
             cancelButton.addActionListener(this);
             buttonPanel.add(cancelButton);
             add(buttonPanel, BorderLayout.SOUTH);
            
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
