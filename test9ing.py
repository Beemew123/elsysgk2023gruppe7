import serial.tools.list_ports
import matplotlib.pyplot as plt

ports=serial.tools.list_ports.comports()
serialInst=serial.Serial()

portList=[]

for onePort in ports: #denne delen av koden etablerer kontakt med seriell overvåker
    portList.append(str(onePort))
    print(str(onePort))

    val=input("velg port: COM")

    for x in range(0,len(portList)):
        if portList[x].startswith("COM"+ str(val)):
            portVar = "COM" + str(val)
            print(portList[x])


serialInst.baudrate = 9600 #samme baudrate som i arduino programmet
serialInst.port=portVar
serialInst.open()
#serialInst.close()

x=[] #tomme lister for å lagre verdier
y0=[]
y1=[]
y2=[]
y3=[]

i=0

while i<200:
    data0=serialInst.readline() #leser av verdien gitt fra pHsensor 1
    data1=serialInst.readline() #leser av verdien gitt fra pHsensor 2
    data2=serialInst.readline() #leser av verdien gitt fra turbiditetsensor 1
    data3=serialInst.readline() #leser av verdien gitt fra turbiditetsensor 2
    print(data0.decode())
    print(data1.decode())
    print(data2.decode())
    print(data3.decode())
    x.append(i) #x verdien
    y0.append(data0.decode()) #y0 verdien er sensormålingene av pHsensor 1
    y1.append(data1.decode()) #y1 verdien er sensormålingene av pHsensor 2
    y2.append(data2.decode()) #y2 verdien er sensormålingene av turbiditetsensor 1
    y3.append(data3.decode()) #y3 verdien er sensormålingene av turbiditetsensor 2
    i+=1

    tur1=int(data2.decode()) #gjør om verdiene fra turbiditetsensor 1 til int 
    tur2=int(data3.decode()) #gjør om verdiene fra turbiditetsensor 2 til int 


    #varselsytem
    if tur1<= 250: #varsler brukeren dersom turbiditetsensoren måler under 250
        print(tur1, ": oversteget slamverdi ved turbiditetsensor 1")
        break
    elif tur2<=250:
        print(tur2, ": oversteget slamverdi ved turbiditetsensor 2")
        break


    ##gjør grafene pene


    plt.subplot(2,2,1) #lager 4 subpolts, en for hver sensor, plot nr 1
    plt.plot(x, y0) #plotte x og nåværende y verdi
    
    plt.subplot(2,2,2) #plot nr 2
    plt.plot(x,y1)
  
    plt.subplot(2,2,3) #plot nr 3
    plt.plot(x, y2)
   
    plt.subplot(2,2,4) #plot nr 4
    plt.plot(x, y3)

    plt.tight_layout()#kan legge til pad=et tall (feks pad=2) for å bestemme avstand
    plt.pause(0.001)
plt.show()


