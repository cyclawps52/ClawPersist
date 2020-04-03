import os

while True:
    print("0. Install module - default options")
    print("1. Install module - specify options")
    print("2. Check module log")
    print("3. Uninstall module")
    print("-1. Exit controller")
    selection = int(input("Select an option: "))

    if(selection == 0):
        # install w/ default
        os.system("sudo insmod ../build/csc492.ko")
    elif(selection == 1):
        # install w/ specifications

        # callbackIP
        callbackIP = str(input("callbackIP: "))
        if(callbackIP == ""):
            # content not entered, set to default
            callbackIP = "127.0.0.1"
        
        os.system("sudo insmod ../build/csc492.ko callbackIP={0}".format(callbackIP))

    elif(selection == 2):
        # check module log
        os.system("sudo less +G /var/log/kern.log")

    elif(selection == 3):
        # uninstall module
        os.system("sudo rmmod csc492")

    elif(selection == -1):
        exit(0)
    else:
        continue