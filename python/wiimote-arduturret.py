

import cwiid
import time
import serial

def main():

        
        ser = serial.Serial('/dev/ttyACM0',9600)
        ser.write ('/nhi there')
        print 'Press button 1 + 2 on your Wii Remote...'
        

        wm=cwiid.Wiimote()
        print 'Wii Remote connected...'
        print '\nPress the PLUS button to disconnect the Wii and end the application'
        
        
        wm.led = 1
       
        Rumble = False
        wm.rpt_mode = cwiid.RPT_BTN| cwiid.RPT_ACC| cwiid.RPT_IR
        print wm.state


        while True:

                if wm.state['ir_src'] == [1]:
                        print 'irsourcedetected'
                        time.sleep(.1)
                
                if wm.state['buttons'] == 8:
                        acc = str(wm.state['acc'])
                
                        ser.write(acc)
                        print acc
                        time.sleep(.05)

                if wm.state['buttons'] == 4:
                        ser.write('\nF')
                        print 'FIRE!'
                        time.sleep(.05)

                if wm.state['buttons'] == 12:
                        acc = str(wm.state['acc'])
                
                        ser.write(acc + '\nF')
                        print acc + 'FIRE!'
                        time.sleep(.05)
                        

                if wm.state['buttons'] == 16:
                        if Rumble == False:
                                wm.rumble = True
                                Rumble = True
                                time.sleep(.5)
                        elif Rumble == True:
                                wm.rumble = False
                                Rumble = False
                                time.sleep(.5)
                if wm.state['buttons'] == 4096:
                        print 'closing Bluetooth connection. Good Bye!'
                        exit(wm)
                

    
if __name__ == '__main__':
    main()

