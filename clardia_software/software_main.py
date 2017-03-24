#Clardia Data Entering Programe (c) olivescipt
#by Chirath Hettiarachchi

import wx
import serial
import connector_GUI
import time
import MySQLdb
import serial

class MainFrame(wx.Frame):
   
   def __init__(self, parent, title):
      wx.Frame.__init__(self, parent, title=title)
      self.count = 0 
      
      panel = wx.Panel(self)
      #self.SetBackgroundColour((108, 176, 131))

      #Clardia logo
      png = wx.Image('clardia_logo.png', wx.BITMAP_TYPE_ANY).ConvertToBitmap()
      self.imageCtrl = wx.StaticBitmap(panel, -1, png, (1200, 0), (png.GetWidth(), png.GetHeight()))

      #background box
      wx.StaticBox(panel, label='Patient Information ', pos = (20,40), size = (500,700))
      wx.StaticBox(panel, label='Real Time Graphs ', pos = (550,40), size = (850,700))

      wx.StaticText (panel, -1 , "Patient ID: " , (40,70))
      self.name = wx.TextCtrl(panel,pos = (40, 90), size = (450,20),style = wx.TE_MULTILINE)
      
      wx.StaticText (panel, -1 , "Age: " , (40,130))
      self.age = wx.TextCtrl(panel,pos = (100, 130), size = (50,20),style = wx.TE_MULTILINE)

      wx.StaticText (panel, -1 , "Height (cm) : " , (200,130))
      self.height = wx.TextCtrl(panel,pos = (300, 130), size = (50,20),style = wx.TE_MULTILINE)


      wx.StaticText (panel, -1 , "Gender: " , (40,165))
      #self.gender = wx.TextCtrl(panel,pos = (100, 160), size = (50,20),style = wx.TE_MULTILINE)
      genders = ['M', 'F', 'Other'] 
      self.combo = wx.ComboBox(panel,choices = genders, pos = (100,160)) 

      wx.StaticText (panel, -1 , "Blood Group: " , (200,165))
      #self.bloodGroup = wx.TextCtrl(panel,pos = (280, 160), size = (50,20),style = wx.TE_MULTILINE)
      types = ['None', 'A+', 'A-', 'B+', 'B-', 'AB+', 'AB-', 'O+', 'O-'] 
      self.combo = wx.ComboBox(panel,choices = types, pos = (300,160)) 

      wx.StaticText (panel, -1 , "Medical History: " , (40,200))

      #check boxes
      self.diabetis = wx.CheckBox(panel, -1, "Diabetics", (40, 230) , (160,-1))
      self.kidney = wx.CheckBox(panel, -1, "Kidney Disease", (40, 260) , (160,-1))
      self.hbp = wx.CheckBox(panel, -1, "High Blood Pressure", (40, 290) , (160,-1))
      self.cholestrol = wx.CheckBox(panel, -1, "Cholestrol", (40, 320) , (160,-1))

      wx.StaticText (panel, -1 , "Other: " , (40,370))
      self.other = wx.TextCtrl(panel,pos = (40, 400), size = (450,100),style = wx.TE_MULTILINE)

      #olivescript logo footer
      png = wx.Image('olivescript.png', wx.BITMAP_TYPE_ANY).ConvertToBitmap()
      self.imageCtrl = wx.StaticBitmap(panel, -1, png, (640, 750), (png.GetWidth(), png.GetHeight()))



      #the buttons
      start_button = wx.Button(panel,label="Start",pos=(75,675),size=(80,60))
      #self.Bind(wx.EVT_BUTTON, self.onStartClick, start_button)

      stop_button = wx.Button(panel,label="Stop",pos=(175,675),size=(80,60))
      #self.Bind(wx.EVT_BUTTON, self.onTerminateClick, terminate_button)

      save_button = wx.Button(panel,label="Save",pos=(275,675),size=(80,60))
      #self.Bind(wx.EVT_BUTTON, self.onTerminateClick, terminate_button)

      new_button = wx.Button(panel,label="New",pos=(375,675),size=(80,60))
      #self.Bind(wx.EVT_BUTTON, self.onTerminateClick, terminate_button)


      self.Centre()
      self.Show(True)
      self.Maximize(True)

   #def onStartClick(self,event):

# Main program
if __name__ == '__main__':
    try:
        arduino = serial.Serial('/dev/tty.usbmodem1421', 9600)
    except:
        print "Failed to connect"
        exit()

    app = wx.App()
    MainFrame(None, 'Clardia Data Entry Program')
    app.MainLoop()
    arduino.close()




