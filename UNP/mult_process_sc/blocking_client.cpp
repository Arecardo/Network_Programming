/*
 * multi-process tcp client
 * date: 11/08/2020
*/

#include<iostream>
#include<sys/socket.h> // socket
#include<netinet/in.h> //sockaddr
#include<arpa/inet.h> // inet_pton
#include<unistd.h> // fork, exec, close
#include<string.h> // memset
#include<netdb.h> // getnameinfo
#include<string>


int main(int argc, char** argv){
    
    // create client socket
    int clifd = socket(AF_INET, SOCK_STREAM, 0);
    if(clifd == -1){ // if fail to create client socket
        std::cout<<"Can't create client socket"<<std::endl;
        return -1;
    }

    // set server address
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    // connect to the server
    int ifcon = connect(clifd, (sockaddr*)&servaddr, sizeof(servaddr));
    if(ifcon == -1){
        std::cout<<"Connection failed!"<<std::endl;
        return -2;
    }

    // send and recv mesg loop
    char buf[4096];
    std::string userInput;
    while(true){
        // enter the mesg
        std::cout<<"> ";
        std::getline(std::cin, userInput);

        // send the mesg
        int ifsend = send(clifd, userInput.c_str(), userInput.size()+1, 0);
        if(ifsend == -1){
            std::cout<<"Can't send the message to the server!"<<std::endl;
            continue;
        }

        // get the mesg back
        memset(&buf, 0, sizeof(buf));
        int byteReceived = recv(clifd, buf, 4096, 0);

        // output the mesg
        std::cout<<"SERVER> "<<std::string(buf, byteReceived)<<std::endl;
    }

    // close the client socket
    close(clifd);

    return 0;
}