// This application is design to simulate an MP3 player,
// using a singly linked list.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

// The songs are nodes.  Let's set that up first.
// Node Class for Linked List

class Node
{
	char artistName[50];
	char songName[50];
	Node *next;

public:
	Node();
	void playlistSong(char aN[], char sN[]);
	friend class LinkedList;
};

void Node::playlistSong(char aN[], char sN[])
{
	strcpy_s(artistName, aN);
	strcpy_s(songName, sN);
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
	void showSongList();
	void readSongList();
	void addNodeToEnd(Node *nptr);
	void addNodeToHead(Node *nptr);
	int insertAfter(Node *ptr, char a[]);
	int removeNode(char a[]);
	void showList();
	Node * findItem(char i[]);
	friend class Node;
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

void LinkedList::showSongList()
{
	for (int i = 0; i < songCount; i++)
	{
		cout << "Song Number: " << i + 1 << endl;
		char answer;
		cout << "Type any character and press Enter to continue" << endl;
		cin >> answer;
		cin.ignore();
		cin.clear();
	}
}

void LinkedList::readSongList()
{
	//getFileName();
	ifstream infile(fileName);

	if (!infile)
	{
		cout << "Dude, you did something wrong with the file name.  Sorry." << endl;
		return;
	}

	while (!infile.eof())
	{
		char aName[50];
		char sName[50];

		infile.getline(aName, 50, ',');
		if (strlen(aName))
		{
			infile.getline(sName, 50);
			Node *songPtr = new Node();
			songPtr->playlistSong(aName, sName);
			this->addNodeToEnd(songPtr);
		}
	}

	infile.close();
}

// This is where the magic is going to happen...
void LinkedList::showList()
{
	char answer;
	Node *ptr;
	LinkedList *next;
	ptr = head;
	
	cout << "****  AwesomeSauce MyPod Version RnR.0 ****" << endl;

	if (ptr == NULL)
	{
		cout << "... Nevermind... The playlist is empty... " << endl;
		return;
	}
	
	while (ptr != NULL)
	{
		printf("*****  *****  *****  *****  *****\n");
		printf("Currently Playing\n");
		printf("Song Title:\t%s\n", ptr->songName);
		printf("By Artist:\t%s\n", ptr->artistName);
		printf("*****  *****  *****  *****  *****\n");
		printf("\n");
		printf("That's a pretty rocking song, lady!\n");
		printf("\n");
		printf("So, what should we do next?  There are oh so many possibilities!\n");
		printf("To (S)kip to the next rocking song, press 'S' and enter.\n");
		printf("To (D)elete this uber lame-o song, press 'D' and enter.\n");
		printf("To (Q)uit and switch to a podcast, press 'Q' and enter.\n");
		//printf("To (A)dd a new song to the list, press 'A' and enter.\n");

		cin >> answer;
		cin.ignore();
		cin.clear();

		if (answer == 'S' || answer == 's')
		{
				ptr = ptr->next;
		}

		else if (answer == 'D' || answer == 'd')
		{

			ptr = ptr->next;
			removeNode(ptr->artistName);
			showList();
		}

		else if (answer == 'Q' || answer == 'q')
		{
			printf("Have a nice day, lady.");
		}

		/*else if (answer == 'A' || answer == 'a')
		{
			LinkedList *addedSong = new LinkedList;
			cout << "Atrist Name? " << endl;
			addedSong->insertAfter(ptr->artistName, ptr->songName);
		}*/

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

int LinkedList::insertAfter(Node *newnode, char i[])
{
	Node *ptr = head;
	while (ptr != NULL)
	{
		if (ptr->artistName == i) // we found the node to insert after
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

Node * LinkedList::findItem(char i[])
{
	Node *ptr;
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->artistName == i)
		{
			cout << "found it!" << endl;
			return ptr;
		}
		ptr = ptr->next;
	}

	cout << "Not found" << endl;
	return NULL;
}


int LinkedList::removeNode(char a[])
{
	Node *ptr = head;
	if (ptr == NULL)  // empty list
		return -1;

	// if node is at the head
	if (strlen(head->artistName))
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
		printf("There you go.  No more lame song.");
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (strlen((ptr->next)->artistName)))
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
	char fileName[100];
	cout << "Please enter in the full path filename of your playlist please." << endl;
	gets_s(fileName);
	LinkedList *navigation = new LinkedList();
	navigation->setFileName(fileName);
	navigation->readSongList();	
	navigation->showList();
//	Node *songPtr;
	return 0;

}


