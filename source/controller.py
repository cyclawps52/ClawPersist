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

        # restart current script in case controller was updated in pull
        print("--------------------------------------------")
        input("Press ENTER to reload controller")
        os.execl(sys.executable, sys.executable, * sys.argv) 

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

        # testInt
        testInt = str(input("testInt: "))
        if(testInt == ""):
            testInt = str(52)

        # testArray
        testArray = str(input("testArray: "))
        if(testArray == ""):
            testArray = "{0}"
        
        # run the actual insmod command
        os.system("sudo insmod ../build/csc492.ko callbackIP={0} testInt={1} testArray={2}".format(callbackIP, str(testInt), testArray))

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