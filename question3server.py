import socket

SERVER_PORT = 8888

def bar_to_atm(pressureBar):
    # Conversion formula from bar to atmosphere-standard
    return pressureBar / 1.01325

def main():
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.bind(('', SERVER_PORT))
    serverSocket.listen(1)

    print(f"Server listening on port {SERVER_PORT}...")

    while True:
        conn, addr = serverSocket.accept()
        print(f"Connected to {addr}")

        # Receive the pressure in bar from the client
        data = conn.recv(1024)
        pressureBar = float(data.decode())

        # Convert pressure to atmosphere-standard
        atmosphereStandard = bar_to_atm(pressureBar)

        # Send the converted value back to the client
        conn.sendall(str(atmosphereStandard).encode())
        conn.close()

if __name__ == "__main__":
    main()
