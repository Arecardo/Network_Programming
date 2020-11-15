/*
 * blocking tcp server
 * date: 11/06/2020
*/

#include<iostream>
#include<sys/socket.h> // socket
#include<netinet/in.h> //sockaddr
#include<arpa/inet.h> // inet_pton
#include<string.h> // memset
#include<unistd.h> // fork, exec, close
#include<netdb.h> // getnameinfo
#include<string>

int main(int argc, char** argv){
    std::cout<<"Start the server..."<<std::endl;
    
    // create listening socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){ // if fail to create listening socket
        std::cout<<"Can't create listening socket!"<<std::endl;
        return -1;
    }

    // set listening address
    struct sockaddr_in lisenaddr;
    memset(&lisenaddr, 0, sizeof(lisenaddr));                   // initial to all 0
    lisenaddr.sin_family = AF_INET;                             // family
    lisenaddr.sin_port = htons(9877);                           // port
    inet_pton(AF_INET, "127.0.0.1", &lisenaddr.sin_addr);       // ip address
    
    // bind listening address to listening
    if(bind(listenfd, (sockaddr *)& lisenaddr, sizeof(lisenaddr)) == -1){
        std::cout<<"Can't bind listening sockaddr to listenfd!"<<std::endl;
        return -2;
    }

    // indicate the server starts listen
    std::cout<<"Start listening..."<<std::endl;
    
    // active listenfd to listen
    if(listen(listenfd, SOMAXCONN) == -1){
        std::cout<<"Can't make listenfd to listen!"<<std::endl;
        return -3;
    }

    // accept connection
    struct sockaddr_in connaddr;
    socklen_t connlen;
    int connfd = accept(listenfd, (sockaddr*)& connaddr, &connlen);
    if(connfd == -1){
        std::cout<<"Problem with client connection!"<<std::endl;
        return -4;
    }

    // close listening
    close(listenfd);

    // get ip address and port number of the connection
    char host[NI_MAXHOST];
    char svrc[NI_MAXSERV];
    inet_ntop(AF_INET, &connaddr.sin_addr, host, NI_MAXHOST);
    std::cout<<host<<" connected on"<<ntohs(connaddr.sin_port)<<std::endl;

    // read message from connfd
    char buf[4096];
    while(true){
        // clear buf
        memset(&buf, 0, 4096);

        // wait for a message
        int byteRecv = recv(connfd, &buf, 4096, 0);
        if(byteRecv == -1){ // if recv failed
            std::cout<<"There is a connection issue!"<<std::endl;
            break;
        } 

        if(byteRecv == 0){ // if recv nothing
            std::cout<<"Client disconnected!"<<std::endl;
            break;
        }

        // display the message
        std::cout<<"Recieved: "<<buf<<std::endl;

        // send the message back
        send(connfd, buf, byteRecv+1, 0);
    }

    // close connfd
    close(connfd);
    
    return 0;
}