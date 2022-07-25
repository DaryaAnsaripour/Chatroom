#include"../headers/Client.hpp"


Client::Client()
{
    MAX_LEN = 520;
	logged_in = false;
	exited = false;
    username = new char[MAX_LEN];
	password = new char[MAX_LEN];
	name = new char[MAX_LEN];
	menu = "1. change my name to\n2. show my groups\n3. show my friends\n4. show blocked\n5. exit";
}

void Client::start_connecting()
{
	if ((client_socket=socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket: ");
		exit(-1);
	}

    struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(10001);
	client.sin_addr.s_addr=INADDR_ANY;
    if ((connect(client_socket, (struct sockaddr *)&client, sizeof(struct sockaddr_in))) == -1)
	{
		perror("connect: ");
		exit(-1);
	}
}

void Client::start_communicating()
{
	login();
    send_thread = new thread(send_handler, this);
    recv_thread = new thread(recv_handler, this);	
	if (send_thread->joinable())
		send_thread->join();
	if (recv_thread->joinable())
		recv_thread->join();
	
}

void Client::login()
{
	while(true)
	{
		cout<<"Enter l to login or s to sign up!\n";
		char* command = new char[MAX_LEN];
		cin.getline(command, MAX_LEN);
		send(client_socket, command, sizeof(command), 0);

		if(command[0]=='l')
		{
			cout<<"Enter your username : ";
			cin.getline(username, MAX_LEN);
			send(client_socket, username, sizeof(username), 0);

			cout<<"Enter your password : ";
			cin.getline(password, MAX_LEN);
			send(client_socket, password, sizeof(password), 0);

			multi_print("Your login request has been sent!", false);
			char answer[MAX_LEN];
			int bytes_received = recv(client_socket, answer, sizeof(answer), 0);
			if(bytes_received <= 0)
				continue;
			multi_print(answer, false);
			if (string(answer) == "Server | welcome " + string(username))
			{
				multi_print(menu);
				break;
			}
		}
		else if(command[0]=='s')
		{
			cout<<"Choose a username : \n";
			cin.getline(username, MAX_LEN);
			send(client_socket, username, sizeof(username), 0);

			cout<<"Choose a name : \n";
			cin.getline(name, MAX_LEN);
			send(client_socket, name, sizeof(name), 0);

			cout<<"Choose a password : \n";
			cin.getline(password, MAX_LEN);
			send(client_socket, password, sizeof(password), 0);

			cout<<"Confirm password : \n";
			cin.getline(password, MAX_LEN);
			send(client_socket, password, sizeof(password), 0);

			multi_print("Your sign up request has been sent!", false);
			char answer[MAX_LEN];
			int bytes_received = recv(client_socket, answer, sizeof(answer), 0);
			if(bytes_received <= 0)
				continue;
			multi_print(answer, false);
			if (string(answer) == "Server | welcome " + string(username))
			{
				multi_print(menu);
				break;
			}
		}
	}
}


void Client::send_handler(Client* client)
{
	while(true)
	{
		client->multi_print("");
		char str[client->MAX_LEN];
		cin.getline(str,client->MAX_LEN);

		if (string(str) == "#exit")
		{
			client->exited = true;
			client->recv_thread->detach();
			close(client->client_socket);
			return;
		}
		send(client->client_socket, str, sizeof(str),0);
	}
}

void Client::recv_handler(Client* client)
{
	while(!client->exited)
	{
		char message[client->MAX_LEN];
		int bytes_received = recv(client->client_socket, message, sizeof(message), 0);
		if(bytes_received <= 0)
			continue;
		client->multi_print(message);
		fflush(stdout);
	}
}


void Client::multi_print(string message, bool you)
{
	lock_guard<mutex> guard(print_mtx);
	if (message.length())
		cout<<"\33[2K \r"<<message<<endl;
	if (you)
		cout<<"\33[2K \r"<<"You : ";
}

void Client::close_connection()
{
	if (send_thread)
	{
		if (send_thread->joinable())
		{
			send_thread->detach();
			delete send_thread;
		}
		send_thread = 0;
	}
	if (recv_thread)
	{
		if (recv_thread->joinable())
		{
			recv_thread->detach();
			delete recv_thread;
		}
		recv_thread = 0;
	}
    close(client_socket);
	multi_print("=== The socket turned off ===", false);
}

Client::~Client()
{
	close_connection();
	delete [] name;
	delete [] password;
}