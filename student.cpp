#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
#include<fstream>
using namespace std;
template<typename T>
class Student {
	struct node {
		T rollno;
		string name;
		node* left;
		node* right;
		node(const T& ele, node* l, node* r, string n) :rollno(ele), left(l), right(r), name(n) {
			
		
		}
		node() {
			rollno = -1;
			name = "";
			left = right = NULL;
		}
	};
	node* root;
	node* nullnode;
	void Insert(const T& x, string n, node*& t);
	void single_rotate_with_right(node*& t);
	void single_rotate_with_left(node*& t);
	void splay(const T& x, node*& t);
	void Delete(const T& x, node*& t);
	void Print(node*& t)const;
	T findmax(const T& x, node*& t);
	void find(T& x);
	void findname(node*& k, string x);
public:
	Student() {
		nullnode = new node;
		nullnode->left = nullnode->right = NULL;
		root = nullnode;
	}
	void Insert(const T& x, string n) {
		Insert(x, n, root);
	}
	void Delete(const T& x) {
		Delete(x, root);
	}
	void splay(const T& x) {
		splay(x, root);
	}
	void Print() {
		Print(root);
	}
	void Find(T& x) {
		find(x);
	}
	void findn(string x) {
		findname(root, x);
	}

};

template<typename T>
void Student<T>::splay(const T& x, node*& t) {
	node* ltmax, * rtmin;
	node header;
	ltmax = &header;
	rtmin = &header;
	nullnode->rollno = x;
	while (x != t->rollno) {
		if (x < t->rollno) {
			if (x < t->left->rollno)
				single_rotate_with_left(t);
			if (t->left == nullnode)
				break;
			rtmin->left = t;
			rtmin = t;
			t = t->left;
		}
		else if (x > t->rollno) {

			if (x > t->right->rollno)
				single_rotate_with_right(t);
			if (t->right == nullnode)
				break;
			ltmax->right = t;
			ltmax = t;
			t = t->right;
		}
	}
	ltmax->right = t->left;
	rtmin->left = t->right;
	t->left = header.right;
	t->right = header.left;
}
template<typename T>
void Student<T>::Print(node*& t)const {
	if (t != nullnode) {
		cout << t->rollno << " ";
		Print(t->left);
		Print(t->right);
	}
}
template<typename T>
void Student<T>::single_rotate_with_left(node*& t) {
	node* k2 = t->left;
	t->left = k2->right;
	k2->right = t;
	t = k2;
}
template<typename T>
void Student<T>::single_rotate_with_right(node*& t) {
	node* k2 = t->right;
	t->right = k2->left;
	k2->left = t;
	t = k2;
}
template<typename T>
void Student<T>::Insert(const T& x, string n, node*& t) {
	static node* newnode = NULL;
	if (newnode == NULL) {
		newnode = new node;
		newnode->rollno = x;
		newnode->name = n;
		newnode->left = newnode->right = nullnode;
	}
	if (root == nullnode) {
		root = newnode;
		newnode->left = newnode->right = nullnode;
	}
	else {

		splay(x, root);

		if (x > root->rollno) {
			newnode->right = root->right;
			newnode->left = root;
			root->right = nullnode;
			root = newnode;
		}
		else if (x < root->rollno) {
			newnode->left = root->left;
			newnode->right = root;
			root->left = nullnode;
			root = newnode;
		}


	}
	newnode = NULL;

}
template<typename T>
void Student<T>::Delete(const T& x, node*& t) {
	node* newtree;
	splay(x, root);
	if (root->rollno != x)
		return;
	if (root->right == nullnode) {
		newtree = root->left;
		delete root;
	}
	else {
		newtree = root->right;
		splay(x, newtree);
		newtree->left = root->left;
		delete root;
	}
	root = newtree;
}
template<typename T>
void Student<T>::find(T& x) {
	node* k;
	k = root;
	while (k != NULL) {
		if (x > k->rollno) {
			k = k->right;
		}
		else if (x < k->rollno) {
			k = k->left;
		}
		if (k->rollno == x) {
			cout << "Rollno:" << k->rollno << "\n";
			cout << "Name: " << k->name << endl;
			splay(x, root);
			break;


		}

	}
	if (k == NULL) {
		cout << "splay does not exist\n";
	}

}
template<typename T>
void Student<T>::findname(node*&k, string x) {
	if (k != NULL) {

		const char* cx = x.c_str();
		const char* cname = k->name.c_str();
		findname(k->left, x);
		findname(k->right, x);
		if (!strcmp(cx, cname)) {
			cout << k->rollno << "\t" << k->name << endl;
		}
		
	}
	

}

int main() {
	Student<int> obj;
	int n = 1, a, x;
	string k1;
	fstream db("db.txt");
	string c3,c4,c5;
	int j;
	while (getline(db, c3, ';'))
	{	
		if (c3 == "I") {
			getline(db, c4, ';');
			getline(db, c5, ';');
			j = stoi(c5);
			obj.Insert(j, c4);
		}
		else if (c3 == "D") {
			getline(db, c4, ';');
			j = stoi(c4);
			obj.Delete(j);

		}
		else if (c3 == "F") {
			getline(db, c4, ';');
			j = stoi(c4);
			obj.Find(j);

		}
	}
	

	while (n) {
		cout << "\nEnter 1 to Insert\n2 to Delete\n3 to Display :\n4 to find a student\n5 to find by name";
		cin >> a;
		switch (a) {
		case 1:
		{
			cout << "Enter the rollno of the student : \n";
			cin >> x;
			cout << "Enter the name of the student\n";
			cin >> k1;
			obj.Insert(x, k1);
			ofstream db("db.txt", ios_base::app);
			db << "I;"<<k1<<";"<<x<<";";
			db.close();
			cout << "record inserted\n" << endl;
			break;
		}
		case 2:
		{
			cout << "Enter the rollno to be Delete : \n";
			cin >> x;
			obj.Delete(x);
			ofstream db("db.txt", ios_base::app);
			db << "D;" << x << ";";
			db.close();
			cout << "The rollno " << x << " is deleted\n" << endl;
			break;
		}
		case 3:
			obj.Print();
			break;
		case 4: {
			cout << "Enter the rollno of student to find : \n";
			cin >> x;
			obj.Find(x);
			ofstream db("db.txt", ios_base::app);
			db << "F;" << x << ";";
			db.close();
			break;
		}
		case 5:
			cout << "Enter name to find\n";
			cin >> k1;
			obj.findn(k1);
			break;
		}
		cout << "\nEnter 1 to continue 0 to exit \n";
		cin >> n;
	}
	return 0;
}
