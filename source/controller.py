import os
import sys

while True:
    os.system("clear")
    print("0. git pull")
    print("1. make")
    print("2. make install - default options")
    print("3. make install - specify options")
    print("4. make checkLog")
    print("5. make uninstall")
    print("6. make clean")
    print("-1. Exit controller")
    selection = int(input("Select an option: "))

    print("--------------------------------------------")

    if(selection == 0):
        # git pull
        os.system("git pull")
        os.execl(sys.executable, sys.executable, * sys.argv) # restart current script in case controller was updated in pull

    elif(selection == 1):
        # make module
        os.system("make")

    elif(selection == 2):
        # install w/ default
        os.system("sudo insmod ../build/csc492.ko")

    elif(selection == 3):
        # install w/ specifications

        # callbackIP
        callbackIP = str(input("callbackIP: "))
        if(callbackIP == ""):
            # content not entered, set to default
            callbackIP = "127.0.0.1"
        
        # run the actual insmod command
        os.system("sudo insmod ../build/csc492.ko callbackIP={0}".format(callbackIP))

    elif(selection == 4):
        # check module log
        os.system("sudo less +G /var/log/kern.log")

    elif(selection == 5):
        # uninstall module
        os.system("sudo rmmod csc492")
        
    elif(selection == 6):
        # clean
        os.system("make clean")

    elif(selection == -1):
        exit(0)

    else:
        continue

    print("--------------------------------------------")
    input("Press ENTER to continue")