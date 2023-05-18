#Python Code
import serial
import json
import time

serialcomm = serial.Serial('/dev/ttyUSB0', 9600)
serialcomm.timeout = 1

def main():
    while True:
        recv_string = serialcomm.readline().decode('ascii')
        #print(recv_string)
        try:
            recv_data = json.loads(recv_string)
            print("OK")
            print(recv_data["n_faces"])
        except:
            
            pass
    serialcomm.close()
    
# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()