#Clardia Data Entering Programe (c) olivescipt
#by Chirath Hettiarachchi

import wx
import serial
import connector_GUI
import MySQLdb

class MainFrame(wx.Frame):
   
   def __init__(self, parent, title):
      wx.Frame.__init__(self, parent, title=title, size=(1250,800))
      
      panel = wx.Panel(self)
      self.Bind(wx.EVT_PAINT, self.OnPaint)


      #pnl = wx.Panel(self)
      wx.StaticBox(panel, label='Patient Information ', pos = (5,5), size = (500,750))


      #clardia_logo
     
      #self.png = wx.StaticBitmap(self, -1, wx.Bitmap("clardia_logo.png", wx.BITMAP_TYPE_ANY))
      

      #static texts
      #wx.StaticText (panel, -1 , "Patient Information " , (10,20))
      wx.StaticText (panel, -1 , "Patient ID: " , (10,50))
      self.name = wx.TextCtrl(panel,pos = (10, 70), size = (450,20),style = wx.TE_MULTILINE)
      


      wx.StaticText (panel, -1 , "Age: " , (10,100))
      self.age = wx.TextCtrl(panel,pos = (10, 120), size = (450,20),style = wx.TE_MULTILINE)

      wx.StaticText (panel, -1 , "Height (m) : " , (10,150))
      self.height = wx.TextCtrl(panel,pos = (10, 170), size = (450,20),style = wx.TE_MULTILINE)

      wx.StaticText (panel, -1 , "Medical History: " , (10,200))

      #check boxes
      self.diabetis = wx.CheckBox(panel, -1, "Diabetis", (20, 230) , (160,-1))
      self.kidney = wx.CheckBox(panel, -1, "Kidney", (20, 260) , (160,-1))
      self.hbp = wx.CheckBox(panel, -1, "High Blood Pressure", (20, 290) , (160,-1))
      self.cholestrol = wx.CheckBox(panel, -1, "Cholestrol", (20, 320) , (160,-1))

      wx.StaticText (panel, -1 , "Other: " , (10,370))
      self.other = wx.TextCtrl(panel,pos = (10, 400), size = (450,100),style = wx.TE_MULTILINE)

      #the buttons
      start_button = wx.Button(panel,label="Start",pos=(20,650),size=(80,60))
      self.Bind(wx.EVT_BUTTON, self.onStartClick, start_button)

      terminate_button = wx.Button(panel,label="Terminate",pos=(140,650),size=(80,60))
      self.Bind(wx.EVT_BUTTON, self.onTerminateClick, terminate_button)

      #self.clearButton = wx.Button(panel,ID_CLEARBUTTON,label="Retry",pos=(260,650),size=(80,60))
      #self.Bind(wx.EVT_BUTTON, ID_CLEARBUTTON, self.OnClear)

      new_button = wx.Button(panel,label="New",pos=(380,650),size=(80,60))
      self.Bind(wx.EVT_BUTTON, self.onNewClick, new_button)

      self.Centre()
      self.Show(True)
      self.Maximize(True)


   def onStartClick(self,event):
      #start reading from serial
      #value = arduino.readline()
      #print "reading from serial"
      var1 = self.name.GetValue()
      #print type(self.age.GetValue())
      db = MySQLdb.connect("127.0.0.1","chiru","chiru","clardia_test" )
      cursor = db.cursor()
      sql = ("""INSERT INTO patient_info(ID)
         VALUES (%s)""",(var1)) 
      try:
   # Execute the SQL command
        cursor.execute(sql)
   # Commit your changes in the database
        db.commit()
      except:
   # Rollback in case there is any error
        db.rollback()

      data = cursor.fetchone()

      db.close()

   def onTerminateClick(self,event):
      connector_GUI.connector()

   def OnClear(self,event):
      self.clearButton.Clear()

   def onNewClick(self,event):
      self.Close(True)

   #painting the straight verticle line
   def OnPaint(self, event=None):
        dc = wx.PaintDC(self)
        dc.Clear()
        dc.SetPen(wx.Pen(wx.BLACK, 2))
        dc.DrawLine(500, 0, 500, 800)

        png = wx.Image('clardia_logo.png', wx.BITMAP_TYPE_ANY).ConvertToBitmap()
        self.imageCtrl = wx.StaticBitmap(self, -1, png, (950, 0), (png.GetWidth(), png.GetHeight()))


# Main program
if __name__ == '__main__':
    # Connect to serial port first
    #try:
        #arduino = serial.Serial('/dev/cu.usbmodem1411', 9600)
    #except:
        #print "Failed to connect"
        #exit()

    # Create and launch the wx interface
    app = wx.App()
    MainFrame(None, 'Clardia Data Entry Program')
    app.MainLoop()

    # Close the serial connection
    #arduino.close()




