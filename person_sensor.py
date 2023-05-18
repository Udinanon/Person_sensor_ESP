#Python Code
import serial
import time

serialcomm = serial.Serial('/dev/ttyUSB0', 9600)
serialcomm.timeout = 1

def main():
    while True:

        print(serialcomm.readline().decode('ascii'))

    serialcomm.close()
    
# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()