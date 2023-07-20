import socket

def main():
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket.connect(('192.168.80.128', 8888))

    quote = clientSocket.recv(1024).decode()
    print("Received Quote of the Day:",quote)
    clientSocket.close()

if __name__ == "__main__":
    main()
