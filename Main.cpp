//21900084 Rabiu Amir Rabiu 351 Project
#include<iostream>	
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;


void firstCome(struct node* header);
void shj(struct node* header);
void pnp(struct node* header);
void sm(struct node* header);
void prem(struct node* header);
void nonPrem(struct node* header);
void sr(struct node* header);
void amir();

struct node {
	int an;
	int burst;
	int arriv;
	int prior;
	struct node *next;
};

int is_empty_node(struct node * header);
struct node * sortList(struct node * header);
struct node * insertBack(struct node * header, int an, int b, int a, int p);
struct node * checkCompletion(struct node * header, int count);
struct node * sortPriority(struct node * header);
struct node * createNode(int an, int b, int a, int p);
struct node * deleteFront(struct node * header);
int main()
{
	struct node *header = NULL;
	int an;
	int b;
	int a;
	int p;
	ifstream fin;
	bool loop = true;
	fin.open("input.txt");


	if (fin.is_open()) {

		while (fin >> an >> b >> a >> p) {
			header = insertBack(header, an, b, a, p);
		}
	}
	fin.close();
	while (loop) {
		int option;
		cout<<"..............CPU SCHEDULER SIMULATOR..............." << endl;
		cout<<"\n1)Scheduling Method";
		cout<<"\n2)Preemptive Method";
		cout<<"\n3)Non-preemptive Mode";
		cout<<"\n4)Show Result";
		cout<<"\n5)End Program";
		cout<<"\nOption>";
		cin>>option;

		if (option == 1) {
			sm(header);
		}
		else if (option == 2) {
			prem(header);
		}
		else if (option == 3) {
			nonPrem(header);
		}
		else if (option == 4) {
			sr(header);
		}
		else if (option == 5) {
			return 0;
		}
		else {
			cout << endl << "please Choose a Valid Option" << endl;
		}
	}
	cin.ignore();
	return 0;
}

void sm(struct node* header) {
	bool loop = true;
	int option = 12;
	char menu;
	while (loop) {
		cout<<"\n1)First Come, First Served Scheduling";
		cout<<"\n2)Shortest - Job - First Scheduling";
		cout<<"\n3)Priority Scheduling";
		cout<<"\n4)Round - Robin Scheduling" ;
		cout<<"\nChoose scheduling method";
		cout<<"\nOption > ";
		cin >> option;
		if (option == 1) {
			firstCome(header);
			cout <<"\nFCFS scheduling completed, check output.txt file for result";
			loop = false;
		}
		else if (option == 2) {
			int choice;
			cout << "\n1-Shortest job first preemptive method";
			cout << "\n2->Shortest job first non-preemptive method" << endl;
			cin >> choice;
			if (choice == 1) {

				cout<<"Wasnt possible";
				loop = false;
			}
			else if (choice == 2) {
				shj(header);
				loop = false;
			}

			else {
				cout << "invalid choice";
				continue;
			}
		}
		else if (option == 3) {
			int choice;
			cout <<"\n1-Priority scheling preemptive method";
			cout <<"\n2->Priority scheduling non-preemptive method" << endl;
			cin >> choice;
			if (choice == 1) {

				cout<<"Wasnt Possible";
				loop = false;
			}
			else if (choice == 2) {
				pnp(header);
				loop = false;
			}
			else {
				cout << "please enter from 1 - 2";
				continue;
			}
		}
		else if (option == 4) {
			cout<<"Wasnt Possible";
			loop = false;
		}
		else {
			cout << endl << "please enter from 1 - 4" << endl;
		}
	}
	cout <<"\nhit a key" << endl;
	cin >> menu;
}

void firstCome(struct node* header) {
	int waittime = 0;
	float average = 0;
	int pr;
	struct node *temp = header;
	ofstream fin("output.txt");
	fin <<"Scheuling Method: First Come First Served " << endl;
	fin <<"Process Waiting Times: " << endl;
	while (!(is_empty_node(temp))) {
		fin << "P" << pr << ": " << waittime << endl;
		average += waittime;
		waittime += (int)temp->burst - '0';

		temp = deleteFront(temp);

		pr++;
	}
	fin << "Average waiting time " << average / (pr - 1);
}
void shj(struct node* header) {

	struct node *temp = header;

	int wtm = 0, counter = 0;
	int pr = 1;
	float average = 0;
	temp = sortList(temp);

	ofstream fin("output.txt");

	fin << "Scheuling Method: Shortest Job First(Non-Preemptive)" << endl;
	fin << "Process Waiting Times: " << endl;

	while (!(is_empty_node(temp))) {
		temp = checkCompletion(temp, counter);

		if (counter < (int)temp->arriv - '0') {
			counter++;
			continue;
		}
		fin << "P" << temp->an << ": " << wtm << endl;
		average += wtm;
		wtm += (int)temp->burst - '0';

		counter += (int)temp->burst - '0';

		temp = deleteFront(temp);


		pr++;
	}
	fin << "Average waiting time " << average / (pr - 1);

	cout << "Schduling done, check file output.txt for details";

}



void pnp(struct node* header) {

	struct node *temp = header;

	int wtm = 0, counter = 0;
	int pr = 1;
	float average = 0;
	temp = sortPriority(temp);
	ofstream fin("output.txt");

	fin << "Scheuling Method: Priority Scheduling(Non-Preemptive)" << endl;
	fin << "Process Waiting Times: " << endl;

	while (!(is_empty_node(temp))) {


		if (counter < (int)temp->arriv - '0') {
			counter++;
			continue;
		}


		fin << "P" << temp->an << ": " << wtm << endl;
		average += wtm;
		wtm += (int)temp->burst - '0';

		counter += (int)temp->burst - '0';

		temp = deleteFront(temp);


		pr++;
	}
	fin << "Average waiting time " << average / (pr - 1);

	cout << "Schduling done, check file output.txt for details";

}


int is_empty_node(struct node* header) {
	if (header == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
struct node* sortList(struct node* header) {
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = temp->next;

	for (i = temp; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if ((int)(i->arriv) - '0' > (int)(j->arriv) - '0') {
				struct node* tempp = createNode(i->an, i->burst, i->arriv, i->prior);

				i->an = j->an;
				i->burst = j->burst;
				i->arriv = j->arriv;
				i->prior = j->prior;

				j->an = tempp->an;
				j->burst = tempp->burst;
				j->arriv = tempp->arriv;
				j->prior= tempp->prior;
			}

		}
	}
	struct node* tempp = temp;

	return temp;
}
struct node* insertBack(struct node* header, int an, int b, int a, int p) {
	struct node* temp = createNode(an, b, a, p);
	struct node* headerTemp;
	if (header == NULL) {
		header = temp;
		return header;
	}
	headerTemp = header;
	while (headerTemp->next != NULL)
		headerTemp = headerTemp->next;
	headerTemp->next = temp;
	return header;
}

struct node* deleteFront(struct node* header) {
	struct node* temp;
	if (header == NULL)
		return header;

	temp = header;
	header = header->next;
	free(temp);

	return header;
}


struct node* checkCompletion(struct node* header, int counter) {
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = i->next;

	for (i = temp; i != NULL; i = i->next) {

		for (j = i->next; j != NULL; j = j->next) {

			if ((((int)(i->burst) - '0') > ((int)(j->burst) - '0')) &&
				(((int)(j->arriv) - '0') <= counter)) {
				struct node* tempp = createNode(i->an, i->burst, i->arriv, i->prior);

				i->an = j->an;
				i->burst = j->burst;
				i->arriv = j->arriv;
				i->prior = j->prior;

				j->an = tempp->an;
				j->burst = tempp->burst;
				j->arriv = tempp->arriv;
				j->prior = tempp->prior;
			}
		}
	}
	struct node* tempp = temp;
	return temp;
}

struct node* sortPriority(struct node* header) {
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = temp->next;
	for (i = temp; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if ((int)(i->prior) - '0' > (int)(j->prior) - '0') {
				struct node* tempp = createNode(i->an, i->burst, i->arriv, i->prior);
				i->an = j->an;
				i->burst = j->burst;
				i->arriv = j->arriv;
				i->prior = j->prior;

				j->an = tempp->an;
				j->burst = tempp->burst;
				j->arriv = tempp->arriv;
				j->prior = tempp->prior;

			}
		}
	}
	struct node* tempp = temp;
	return temp;
}



struct node* createNode(int an, int b, int a, int p) {
	struct node *header = NULL;
	header = (struct node *) malloc(sizeof(node));
	header->an = an;
	header->burst = b;
	header->arriv = a;
	header->prior = p;
	header->next = NULL;

	return header;
}
void prem(struct node* header) {

}

void nonPrem(struct node* header) {

}

void sr(struct node* header) {

}

void amir() {

}
void pp(struct node* header) {

}

 

