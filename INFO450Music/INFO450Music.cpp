// This application is design to simulate an MP3 player,
// using a singly linked list.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

// The songs are nodes.  Let's set that up first.
class SongList
{
	Song **myplayList;

public:
	SongList();
	~SongList();
	void showSongList();
	int saveSongList();
	void readSongList();
	friend class LinkedList;
	friend class Node;
	friend class song;
};

SongList::SongList()
{
	myplayList = new Song*[songCount];
}

SongList::~SongList()
{
	delete myplayList;
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
		Song *songPtr;
		char aName[50];
		char sName[50];

		infile.getline(aName, 50, ',');
		if (strlen(aName))
		{
			infile.getline(sName, 50);
			songPtr = new Song();
			songPtr->playlistSong(aName, sName);
		}
	}

	infile.close();
}

// Node Class for Linked List

class Node
{
	char artistName[50];
	char songName[50];
	Node *next;

public:
	Node();
	void playlistSong(char aN[], char sN[]);
	void displaySong();
	friend class LinkedList;
	friend class SongList;
};

void Node::playlistSong(char aN[], char sN[])
{
	strcpy_s(artistName, aN);
	strcpy_s(songName, sN);
}

void Node::displaySong()
{
	printf("-------------------------\n");
	printf("Currently Playing");
	printf("Song Title:\t%s\n", songName);
	printf("By Artist:\t%s\n", artistName);
	printf("-------------------------\n");
}

Node::Node()
{
	strcpy_s(artistName, "");
	strcpy_s(songName, "");
}

// Linked List Class
class LinkedList
{
	char fileName[100];
	int songCount;
	Node *head;
	Node *tail;
public:
	LinkedList();
	void setFileName(char f[]);
	int getSongCount();
	void addNodeToEnd(Node *nptr);
	void addNodeToHead(Node *nptr);
	int insertAfter(Node *ptr, int i);
	int removeNode(int i);
	void showList();
	Node * findItem(int i);
	friend class Node;
	friend class SongList;
};

LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
}

void LinkedList::setFileName(char f[])
{
	strcpy_s(fileName, f);
}

int LinkedList::getSongCount()
{
	return songCount;
}

// This is where the magic is going to happen...
void LinkedList::showList()
{
	char answer;
	Node *ptr;
	ptr = head;
	
	cout << "****  Play Song *****" << endl;
	
	if (ptr == NULL)
	{
		cout << "list is empty " << endl;
		return;
	}
	
	cout << "The current song is" << head->data << " tail is " << tail->data << ")" << endl;
	cout << "Press any key and Enter to move to the next song." << endl;
	cin >> answer;
	cin.ignore();
	cin.clear();

	while (ptr != NULL)
	{
		cout << "data is " << ptr->data << endl;
		ptr = ptr->next;
	}
}

void LinkedList::addNodeToEnd(Node *ptr)
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

void LinkedList::addNodeToHead(Node *ptr)
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

int LinkedList::insertAfter(Node *newnode, int i)
{
	Node *ptr = head;
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

Node * LinkedList::findItem(int i)
{
	Node *ptr;
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
	Node *ptr = head;
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
			Node *tbd = ptr->next;
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
	SongList *songCount;

	//ptr for the Song List
	SongList *sList = new SongList();
	
	// Get the filename with the song list
	cout << "Please enter the full path filname for your playlist." << endl;
	gets_s(fileName);
	sList->setFileName(fileName);

	sList->readSongList;

	LinkedList *mylist = new LinkedList();
	// test if list is empty
	for (int i = 0; i < songCount; i++)
	{
		Node *newnode = new Node(sList->showSongList);
		mylist->addNodeToEnd();
		mylist->showList();
		mylist->addNodeToEnd(new Node(3));
		mylist->showList();
		mylist->addNodeToEnd(new Node(20));
		mylist->showList();
		mylist->addNodeToHead(new Node(42));
		mylist->showList();
		mylist->insertAfter(new Node(11), 3);
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
	}

	return 0;
}


