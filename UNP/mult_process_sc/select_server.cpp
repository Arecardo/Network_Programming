/*
 * I/O multiplexing select tcp server
 * date: 11/06/2020
*/

#include<iostream>
#include<sys/socket.h>      // for socket() and other
#include<netinet/in.h>      // for sockaddr_in
#include<arpa/inet.h>       // for inet_pton()
#include<unistd.h>          // for fork(), exec()
#include<string.h>          // for memset()
#include<sys/select.h>      // for select()
#include<sys/time.h>        // for timeval
#include<string>

int main(int argc, char** argv){
    // initial listening socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        std::cout<<"Can't create listening socket!"<<std::endl;
        return -1;
    }

    // initial server address
    sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    // bind the address to listening socket
    if(bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        std::cout<<"Can't bind servaddr to listenfd!"<<std::endl;
        return -2;
    }

    // start listening
    if(listen(listenfd, SOMAXCONN) == -1){
        std::cout<<"Can't make listenfd to listen!"<<std::endl;
        return -3;
    }

    // initial fd_set
    int maxfd = listenfd;                           // for reduce the traverse cost
    int maxi = -1;                                  // for traverse query the clientfd
    int i;                                          // just for loop
    int client[FD_SETSIZE];                         // record clientfd
    for(int j=0; j<FD_SETSIZE; j++){
        client[j] = -1;
    }
    fd_set allset;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);                        // add listenfd to the fd_set      
    
    // loop
    while(1){
        // copy the outside rser
        fd_set rset = allset;

        // select, any read ready, rset is modified
        int nready = select(maxfd+1, &rset, nullptr, nullptr, nullptr);

        // check the if there is new connection
        if(FD_ISSET(listenfd, &rset)){                          // new connection coming
            // initial client address
            sockaddr_in clientaddr;
            socklen_t clilen = 0;
            memset(&clientaddr, 0, sizeof(clientaddr));

            // accept connection
            int clifd = accept(listenfd, (sockaddr*)&clientaddr, &clilen);
            if(clifd == -1){
                std::cout<<"Problem with client connection!"<<std::endl;
                continue;
            }

            // record the clifd
            for(i=0; i<FD_SETSIZE; i++){
                if(client[i] < 0){
                    client[i] = clifd;                          // save clifd
                    break;
                }
            }
            if(i == FD_SETSIZE){                                // if the client vector is full
                std::cout<<"too many clients!"<<std::endl;
                return -4;
            }

            // set the clifd to the outside fd_set
            FD_SET(clifd, &allset);
            if(clifd > maxfd){
                maxfd = clifd;                                  // check the max fd value
            }
            if(i > maxi){                                       // check the max i value
                maxi = i;
            }

            if(--nready == 0){                                  // no more readable fd
                continue;
            }
        }

        // sitll have readable fd, check the current clients
        for(i=0; i<=maxi; i++){
            int sockfd = client[i];
            if(sockfd < 0){                                     // no fd in this position
                continue;
            }

            if(FD_ISSET(sockfd, &rset)){                        // this client fd is readable
                
                char buf[4096];                                 // initial buffer
                memset(&buf, 0, 4096);

                int n = recv(sockfd, &buf, 4096, 0);
                if(n == 0){                                     // connection closed by client
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else if(n == -1){
                    std::cout<<"There is a connection issue!"<<std::endl;
                    continue;
                }
                else{
                    // display the message
                    std::cout<<"Recieved: "<<buf<<std::endl;

                    // send the message back
                    send(sockfd, buf, n+1, 0);
                }
                
                if(--nready <= 0){                              // no more readable fd
                    break;
                }
            }
        }
    }

    return 0;
}