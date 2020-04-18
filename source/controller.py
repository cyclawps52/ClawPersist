import os
import sys

while True:
    os.system("clear")
    print("0. git pull")
    print("1. make")
    print("2. make install")
    print("3. make checkLog")
    print("4. make uninstall")
    print("5. make clean")
    print("6. cat /dev/noll")
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
        # install
        os.system("sudo insmod ../build/csc492.ko")
        os.system("sudo mknod /dev/noll c $(cat /sys/module/csc492/parameters/majorNum) 0")

    elif(selection == 3):
        # check module log
        os.system("sudo less +G /var/log/kern.log")

    elif(selection == 4):
        # uninstall module
        os.system("sudo rmmod csc492")
        os.system("sudo rm /dev/noll")
        
    elif(selection == 5):
        # clean
        os.system("make clean")

    elif(selection == 6):
        # cat /dev/noll
        os.system("sudo cat /dev/noll")

    elif(selection == -1):
        exit(0)

    else:
        continue

    print("--------------------------------------------")
    input("Press ENTER to continue")