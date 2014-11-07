#ifndef THEHTTP_HPP
#define THEHTTP_HPP

/**
    C++ client example using sockets
*/
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent
#include <iterator>
 
/**
    TCP Client class
*/
class tcp_client
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;
     
public:
    tcp_client();
    bool conn(std::string, int);
    bool send_data(std::string data);
	void receiveall();
    std::string receive(int);
};
 
tcp_client::tcp_client()
{
    sock = -1;
    port = 0;
    address = "";
}
 
/**
    Connect to a host on a certain port number
*/
bool tcp_client::conn(std::string address , int port)
{
    //create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
			return false;
            //perror("Could not create socket");
        }
         
        //cout<<"Socket created\n";
    }
    else    {   /* OK , nothing */  }
     
    //setup address structure
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;
         
        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            //herror("gethostbyname");
            //cout<<"Failed to resolve hostname\n";
             
            return false;
        }
         
        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;
 
        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];
             
            //cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<endl;
             
            break;
        }
    }
     
    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }
     
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
     
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //perror("connect failed. Error");
        return false;
    }
     
    //cout<<"Connected\n";
    return true;
}
 
/**
    Send data to the connected host
*/
bool tcp_client::send_data(std::string data)
{
    //Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        //perror("Send failed : ");
        return false;
    }
   // cout<<"Data send\n";
     
    return true;
}
 
/**
    Receive data from the connected host
*/
bool rec_error = false;
std::string tcp_client::receive(int size=512)
{
    char buffer[size];
    std::string reply;
     
    //Receive a reply from the server
    if( recv(sock , buffer , sizeof(buffer) , 0) < 1)
    {
		rec_error = true;
		return "";
       // puts("recv failed");
    }
     
    reply = buffer;
	rec_error = false;
    return reply;
}

std::vector <char> recv_data;
void tcp_client::receiveall()
{
	recv_data.clear();
    char buffer[512];
     
	bool docopy = false;
	
	int iResult;
	do {
        iResult = recv(sock, buffer, 512, 0);
        if ( iResult > 0 )
		{
            //printf("Bytes received: %d\n", iResult);
			for (int i = 0; i < iResult; i++)
			{
				recv_data.push_back(buffer[i]);
			}
		}
		//if ( iResult < 512)
		//	break;

    } while( iResult > 0 );
     
    return;
}

int FindStartPos()
{
	for (int i = 0; i < recv_data.size(); i++)
	{
		if (recv_data[i]=='\r')
			if (recv_data[i+1]=='\n')
				if (recv_data[i+2]=='\r')
					if (recv_data[i+3]=='\n')
						return i+4;
	}
	return 0;
}

// host - update.juxta.cf
// file - version.txt

int GetHTTPResultInt(std::string parse,int len)
{
	std::string::size_type    start_position = 0;
	start_position = parse.find("\r\n\r\n");
	if (start_position != std::string::npos)
	{
		start_position+=4;
		std::string temp = parse.substr(start_position, len);
		return std::stoi( temp );
	}
	else
		return -1;
}

std::string GetHTTPResultString(std::string parse,int len)
{
	std::string::size_type    start_position = 0;
	start_position = parse.find("\r\n\r\n");
	if (start_position != std::string::npos)
	{
		start_position+=4;
		return parse.substr(start_position, len);
	}
	else
		return "";
}

int GetHTTPResultLenght(std::string parse)
{
	std::string::size_type    start_position = 0;
	std::string::size_type    end_position = 0;
	start_position = parse.find("Content-Length: ");
	if (start_position != std::string::npos)
	{
		start_position+=16;
		std::string temp = parse.substr(start_position, parse.length() - start_position);
		end_position = temp.find("\r\n");
		if (end_position != std::string::npos)
		{
			std::string found = temp.substr(0, end_position);
			return std::stoi( found );
		}
		else
			return -1;
	}
	else
		return -1;
}

bool GetHTTPResultType(std::string parse)
{
	std::size_t found = parse.find("HTTP/1.1 200 OK");
	return (found!=std::string::npos);
}

int DownloadText(std::string host, std::string file)
{
		tcp_client c;
     
		if ( !c.conn(host , 80) )
		{
			return -1;
		}
     
		c.send_data("GET /"+file+" HTTP/1.1\nHost: "+host+"\n\n\n\n");
     
		std::string temp = c.receive(1024);
		
		bool ok = GetHTTPResultType(temp);
		if (!ok)
		{
			return -1;
		}
		
		int count = GetHTTPResultLenght(temp);
		
		return GetHTTPResultInt(temp,count);
		
}

bool DownloadBinary(std::string host, std::string file, std::string saveto)
{
		tcp_client c;
     
		if ( !c.conn(host , 80) )
		{
			return false;
		}
     
		c.send_data("GET /"+file+" HTTP/1.1\nHost: "+host+"\n\n\n\n");
		
		c.receiveall();
		
		std::ofstream write;
		
		if (recv_data.size() < 300)
			return false;
		
		write.open(saveto.c_str(), std::ios::out);
		
		int where = FindStartPos();
		
		std::vector<char>::iterator starte = recv_data.begin() + where;
		copy(starte, recv_data.end(), std::ostream_iterator<char>(write)); 
		
		write.close();
		return true;
}

#endif