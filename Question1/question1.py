import socket

def send_and_receive_data(host, port, data):
    try:
        # Create a TCP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as clientSocket:
            # Connect to the server
            clientSocket.connect((host, port))

            # Send data
            studentId = '2021886126'
            clientSocket.sendall(studentId.encode())

            # Receive and read server response
            response = clientSocket.recv(1024)
            print("Server response:", response.decode())

    except ConnectionRefusedError:
        print("Connection refused.")
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    host = "izani.synology.me"
    port = 8443

    send_and_receive_data(host, port, '2021886126')
