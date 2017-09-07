import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO.setup(18,GPIO.OUT)
GPIO.setup(23,GPIO.OUT)

print 
#str= raw_input();
print "Press the button"

try:
    GPIO.output(18,False)
    GPIO.output(23,False)

    val = input("input1 :")
    print(val)
    if val==1 :
        print "correct"  
        GPIO.OUTPUT(18,HIGH)
        
#    val2= raw_input("input2 : ")
#    print(val2)

#    if GPIO.input(1)==1:
#       print "Buttonpressed"
#      time.sleep(100)

except KeyboardInterrupt:
    GPIO.cleanup()
