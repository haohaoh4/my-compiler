#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

enum
{
	EOS,		//end of setence
	TYPE,
	EXP,	//±Ì¥Ô Ω 
	NAME,
	OP,
	ERR
};
string types[]=
{
	"int",
	"char"
};

bool is_a_var(string);
int get();
void pass();
bool com_exp();

int point=0;
string source;
int get()
 {
	char *p = const_cast<char*>(source.c_str()); 
	p+=point;
	string s;
	int times=0;
	if(point>=source.length())
		return EOF;
	while(p[point+times]!=' ' && point+times<s.length())
	{
		s+=p[point+times];
		times++;
	}
	if(s=="")
		return EOF;
	if(s==";")
		return EOS;
	for(int i=0;i<sizeof(types)/sizeof(string);i++)
	{
		if(s==types[i])
			return TYPE;
	}
	if(is_a_var(s))
		return NAME;
	for(int i=0;i<10;i++)
	{
		if(s[0]==i+'0')
			return EXP;
	}
	return ERR;
}

string get_string()
 {
	char *p = const_cast<char*>(source.c_str()); 
	string s;
	int times=0;
	while(p[point+times]!=' ' && point+times<source.length())
	{
		s+=p[point+times];
		times++;
	}
	return s;
}

struct var
{
	string name;
	string type;
};
vector<var> vars;
bool is_a_var(string str)
{
	for(vector<var>::iterator i=vars.begin();i!=vars.end();i++)
	{
		if((*i).name==str)
			return true;
	}
	return false;
}
bool def_var()
{
	var n;
	n.type=get_string();
	pass();
	n.name=get_string();
	pass();
	vars.push_back(n);
	cout<<"Define a var:"<<n.type<<" "<<n.name<<endl;
	return true;
}

void pass()
{
	if(point>=source.length())
		return;
	while(source[point]!=' ' && source[point+1]!=';')
		point++;
	int times=0;
	while(source[point])
	{
		point++,times++;
	}
	return;
}
int main()
{
	char file[255];
	cout<<"enter the file name:[test.c]";
	cin.getline(file,254);
	cout<<endl;

	ifstream fin(file);
	if(!fin)
	{
		cout<<"failed";
		return -1;
	}
	istreambuf_iterator<char> beg(fin), end;
	string sour(beg, end);
	source=sour;
	
	while(get()!=EOF)
	{
		while(1)
		{
			int status=get();
			switch (status)
			{
				case EOS:
					pass();
					cout<<"EOS"<<endl;
					break;
				case TYPE:
					if(get()==OP)
						com_exp();
					else
						if(!def_var())goto error;
					break;
				case NAME:
					if(get()==OP)
						if(!com_exp())goto error;
					if(get()==EOS)
						pass();
					break;
				case ERR:
				  error:
					cout<<"ERROR "<<point<<endl;
					pass();
			}
		}
	}
	return 0;
}
bool com_exp()
{
	return true;
}
