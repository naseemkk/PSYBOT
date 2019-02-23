import cv2
import numpy as np
import winsound
count1 = 0;
count2 = 0;
count = 0;
frequency = 2500  ​# Set Frequency To 2500 Hertz
duration = 100  ​# Set Duration To 1000 ms == 1 second
 
recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read('trainer/trainer.yml')
cascadePath = "haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascadePath)
 
 
cam = cv2.VideoCapture("http://192.168.43.17:8081/")
while True:
    ret, im =cam.read()
    gray=cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
    faces=faceCascade.detectMultiScale(gray, 1.2,5)
    for(x,y,w,h) in faces:
        cv2.rectangle(im,(x,y),(x+w,y+h),(225,0,0),2)
        Id, conf = recognizer.predict(gray[y:y+h,x:x+w])
        print(conf)
        if(conf<80):
            if(Id==1):count1=count1+1;
            elif (Id ==2):
                count2=count2+1;
        else:
            Id="Unknown"
        #cv2.putText(im,str(Id),(x,y+h),cv2.FONT_HERSHEY_PLAIN,1.5, 255)
 
        #cv2.rectangle(im, (x - 22, y - 90), (x + w + 22, y - 22), (0, 255, 0), -1)
        #cv2.putText(im, str(Id), (x, y - 10),cv2.FONT_HERSHEY_PLAIN, 2, (255, 255, 255), 2)
        if(count1)==3:
            #cv2.PutText(cv2.cv.fromarray(img),"ARAVIND"+str(conf),(x,y+h),font,255);
            cv2.putText(im, "NASEEM", (x, y - 10),cv2.FONT_HERSHEY_PLAIN, 2, (255, 255, 255), 2)
            winsound.Beep(frequency, duration)
            count1 = 0
            count2 = 0
            coutnt =0
        elif count2 == 3:
            #cv2.PutText(cv2.cv.fromarray(img),"NASEEM"+str(conf),(x,y+h),font,255);
            cv2.putText(im, "APPU", (x, y - 10),cv2.FONT_HERSHEY_PLAIN, 2, (255, 255, 255), 2)
            winsound.Beep(frequency, duration)
            count1 = 0
            count2 = 0
            count = 0
        count = count + 1;
        print ("\ncount=")
        print (count);
        if count > 30:
            count1 = 0
            count2 = 0
            count = 0
 
    cv2.imshow('im',im)
    if cv2.waitKey(10) & 0xFF==ord('q'):
        break
cam.release()
cv2.destroyAllWindows()
