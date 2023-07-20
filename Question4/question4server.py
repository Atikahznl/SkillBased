import socket
import threading
import random

# List of quotes
quotes = ["There's always light after dark.",
          "Don't ruin a good day by thinking about a bad yesterday.",
          "Always remember that self-care is important.",
          "When it feels life it hard, don't give up.",
          "Be proud of yourself for how hard you're trying",
          "Be strong because things will get better",
          "Trust your journey"]

def handleClient(clientSocket):
    randomQuote = random.choice(quotes)
    clientSocket.send(randomQuote.encode())
    clientSocket.close()

def main():
    host = "0.0.0.0"
    port = 8888
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.bind((host, port))
    serverSocket.listen(5)

    print("Quote of the Day Server is listening on {}:{}".format(host,port))

    while True:
        clientSocket, client_addr = serverSocket.accept()
        print(f"Connection accepted from client")
        clientThread = threading.Thread(target=handleClient, args=(clientSocket,))
        clientThread.start()

if __name__ == "__main__":
    main()
