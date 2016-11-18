// This application is design to simulate an MP3 player,
// using a singly linked list.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

// The songs are nodes.  Let's set that up first.
class Song
{
	char artistName[50], songName[50];
	node *next;

public:
	node(int x);
	Song();
	void playlistSong(char an[], char sn[]);
	void displaySong();
	friend class linkedList;
	friend class SongList;
};

node::node(int x)
{
	data = x;
	next = NULL;
}

Song::Song()
{
	strcpy_s(artistName, "");
	strcpy_s(songName, "");
}

void Song::playlistSong(char an[], char sn[])
{
	strcpy_s(artistName, an);
	strcpy_s(songName, sn);
}

void Song::displaySong()
{
	printf("-------------------------\n");
	printf("Currently Playing");
	printf("Song Title:\t%s\n", songName);
	printf("By Artist:\t%s\n", artistName);
	printf("-------------------------\n");
}

class SongList
{
	char fileName[1000];
	int songCount;
	Song **myplayList;

public:
	SongList();
	~SongList();
	void setFileName(char f[]);
	int getSongCount();
	void showSongList();
	int saveSongList();
	void readSongList();
};

SongList::SongList()
{
	myplayList = new Song*[songCount];
}

SongList::~SongList()
{
	delete myplayList;
}

void SongList::setFileName(char f[])
{
	strcpy_s(fileName, f);
}

int SongList::getSongCount()
{
	return songCount;
}

void SongList::showSongList()
{
	for (int i = 0; i < songCount; i++)
	{
		cout << "Song Number: " << i + 1 << endl;
		myplayList[i]->displaySong();
		char answer;
		cout << "Type any character and press Enter to continue" << endl;
		cin >> answer;
		cin.ignore();
		cin.clear();
	}
}

int SongList::saveSongList()
{
	ofstream output(fileName);
	if (!output)
	{
		cout << "You definitely did something wrong." << endl;
		return -1;
	}

	for (int i = 0; i < songCount; i++)
	{
		output << myplayList[i]->artistName << ",";
		output << myplayList[i]->songName << endl;
	}

	output.close();
	return 0;
}

void SongList::readSongList()
{
	ifstream infile(fileName);

	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		Song *ptr;
		char aName[50];
		char sName[50];

		infile.getline(aName, 50, ',');
		if (strlen(aName))
		{
			infile.getline(sName, 50);
			ptr = new Song();
			ptr->playlistSong(aName, sName);
		}
	}

	infile.close();
}

// Linked List Class
class LinkedList
{
	node *head;
	node *tail;
public:
	LinkedList();
	void addNodeToEnd(node *nptr);
	void addNodeToHead(node *nptr);
	int insertAfter(node *ptr, int i);
	int removeNode(int i);
	void showList();
	node * findItem(int i);
};

LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
}

// This is where the magic is going to happen...
void LinkedList::showList()
{
	char answer;
	node *ptr;
	ptr = head;
	
	cout << "****  List Contents *****" << endl;
	
	if (ptr == NULL)
	{
		cout << "list is empty " << endl;
		return;
	}
	
	cout << "The current song is" << head->data << " tail is " << tail->data << ")" << endl;
	cout << "Press any key and Enter to move to the next song." << endl;
	cin >> answer;
	cin.clear;
	cin.ignore;

	while (ptr != NULL)
	{
		cout << "data is " << ptr->data << endl;
		ptr = ptr->next;
	}
}

void LinkedList::addNodeToEnd(node *ptr)
{
	// if list is empty
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

void LinkedList::addNodeToHead(node *ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		ptr->next = head;
		head = ptr;
	}
}

int LinkedList::insertAfter(node *newnode, int i)
{
	node *ptr = head;
	while (ptr != NULL)
	{
		if (ptr->data == i) // we found the node to insert after
		{
			newnode->next = ptr->next;
			ptr->next = newnode;
			if (tail == ptr) // repoint tail if we added to end
				tail = newnode;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

node * LinkedList::findItem(int i)
{
	node *ptr;
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->data == i)
		{
			cout << "found it!" << endl;
			return ptr;
		}
		ptr = ptr->next;
	}

	cout << "Not found" << endl;
	return NULL;
}


int LinkedList::removeNode(int i)
{
	node *ptr = head;
	if (ptr == NULL)  // empty list
		return -1;

	// if node is at the head
	if (head->data == i)
	{
		//if only 1 node in the list
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
		delete ptr;
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (ptr->next)->data == i)
		{
			if (tail == ptr->next)
				tail = ptr;
			node *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

int main()
{
	char answer = 'y';
	char artistName[30];
	char songName[30];
	char fileName[50];
	Song *songCount;

	//ptr for the Song List
	Song *slist = new SongList();
	
	// Get the filename with the song list
	cout << "Please enter the full path filname for your playlist." << endl;
	gets_s(fileName);
	sList->setFileName(fileName);

	LinkedList *mylist = new linkedList();
	// test if list is empty
	if (mylist->removeNode(42))
		cout << "failed to remove" << endl;
	node *newnode = new node(4);
	mylist->addNodeToEnd(newnode);
	mylist->showList();
	mylist->addNodeToEnd(new node(3));
	mylist->showList();
	mylist->addNodeToEnd(new node(20));
	mylist->showList();
	mylist->addNodeToHead(new node(42));
	mylist->showList();
	mylist->insertAfter(new node(11), 3);
	mylist->showList();
	if (mylist->removeNode(42))
		cout << "failed to remove" << endl;
	if (mylist->removeNode(11))
		cout << "failed to remove" << endl;
	if (mylist->removeNode(33))
		cout << "failed to remove" << endl;
	if (mylist->removeNode(20))
		cout << "failed to remove" << endl;
	mylist->showList();
	if (mylist->findItem(2))
		cout << "found it";
	if (mylist->findItem(3))
		cout << "found it";


	return 0;
}


