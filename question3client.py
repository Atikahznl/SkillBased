import socket

SERVER_PORT = 8888

def main():
    pressureBar = input("Enter the pressure value in bar: ")

    try:
        pressureBar = float(pressureBar)
    except ValueError:
        print("Invalid input.")
        return

    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket.connect(('192.168.80.128', SERVER_PORT))

    # Send the pressure in bar to the server
    clientSocket.sendall(str(pressureBar).encode())

    # Receive the converted value from the server
    data = clientSocket.recv(1024)
    atmosphereStandard = float(data.decode())
    print(f"Received atmosphere-standard value from server: {atmosphereStandard:.2f} atm")
    clientSocket.close()

if __name__ == "__main__":
    main()
