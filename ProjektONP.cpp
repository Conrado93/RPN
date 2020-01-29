#include <iostream>
#include <math.h>
using namespace std;
 
 
  typedef float typ;
  
  const int roznica=static_cast<int>('0'); //48
  
 
 struct element
 {
 	typ wartosc;
 	element  *next;
 };
 
 typedef element * position;


 
 class stos
 {
 	
	protected:
 	position l; //szczyt stosu
 	public:
 	 stos()
 	{
 		l=new element();
 		l->next=NULL;
 	}
 	
 	position end() //ostatni element stosu=dno stosu!
 	{
 		position temp=l->next;
 		if(temp==NULL){return temp;}
 		else
 		{
 			
 		while(temp->next !=NULL)
		 {
		 	temp=temp->next;
		 }
 		return temp;
		 	
 		}
 	}
 	
 	 void put(typ x)
 	{
 		position temp;
 		temp=l->next;
 		l->next=new element();
 		(l->next)->wartosc=x;
 		(l->next)->next=temp;
 	}
 	typ check()
 	{
 		if(l->next == NULL){ //cout<<"Stos jest pusty";
		  return 0;}else
 		{return (l->next)->wartosc;}
 	}
 	void pop()
 	{
 		position temp=l->next;
 		if(l->next == NULL){cout<<"Stos jest pusty"<<endl;}
 		else
 		{
 			temp=temp->next;
 			delete l->next;
 			l->next=temp;
 		}
	 	
 	}
 		
 	bool empty() 
 	{
 		if(l->next == NULL) return true;
 		else
 		{
 			return false;
 		}
 	}
 	
 	void wyswietl()
 	{
 		position temp=l->next;
 		if(l->next == NULL)
		 {cout<<"Stos jest pusty"<<endl;}
 		else
 		{
 		while(temp !=NULL)
 		{
 			cout<<temp->wartosc<<endl;
 			temp=temp->next;
 		}
 		}

 	}
 	
 };
 
 
 
 class queue
 {
 	position l;
 	position last;
 	public:
 	queue()
 	{
 		l=new element();
 		l->next=NULL;
 		last=l;
 	}
 	void put(typ x)
 	{
 		position temp;
 		temp=new element();
 		temp->wartosc=x;
 		if(l->next == NULL)
 		{
 			l->next=temp;
 			last=temp;
 		}else
 		{
 		last->next=temp;
 		last=last->next;
 		last->next=NULL;
 		
 		}
 
 	}
 	void pop()
 	{
 		position temp=l->next;
 		if(last==l){cout<<"Kolejka jest pusta"<<endl;}else if((l->next) == last)
 		{
 			delete l->next;
 			last=l;
 			l->next=NULL;
 		}else 
 		{
 			temp=temp->next;
 			//delete l->next;
 			l->next=temp;
 		
 		}
 	}
 	typ check()
 	{
 		
 		if(l==last)
 		{
 			cout<<"Kolejka jest pusta"<<endl;
 			return 0;
		}else
		{
			return (l->next)->wartosc;
		}
 	}
 	void wyswietl()
 	{
 		position temp=l->next;
 		if(temp == NULL){cout<<"Kolejka jest pusta"<<endl;}
 		else{
 		while(temp != NULL)
 		{
 			cout<<temp->wartosc<<endl;
 			temp=temp->next;
 		}
 		
 		
 		}
 		
 	}
 	bool empty()
 	{
 		if(l==last){return true;}
 		else{return false;}
 	}
 	
 	
 	
 };
 
 
 
 
 int kod(char a)
 {
 	return static_cast<int>(a);
 }
 char znak(int a)
 {
 	return static_cast<char>(a);
 }
 bool porownaj(char a, char b) //true oznacza øe priorytet a jest mniejszy lub rÛwny b
 {
 	if(a==b ||
	 ((a=='+' ||a=='-')&&(b=='+' ||b=='-'))||
	 ((a=='*' || a=='/')&&(b=='*' || b=='/'))||
	 ((a=='+' || a=='-') && (b=='*' || b=='/' || b=='^' || b=='~'))||
	 (((a=='*')||a=='/')&&(b=='^' || b=='~')) ||
	 ((b=='~')&&(a=='^' )))
 	{return true;}else
 	return false;
 	
 }
 const char* nawias(const char* p, queue &q, stos &st);
 float potega(float podst, int wyk)
 {
 	float wynik=1;
 	if(wyk==0){return 1;}
 	else if(wyk>0)
 	{
 		for(int i=0;i<wyk;i++)
 		{
 			wynik*=podst;
 		}
 	}else
 	{
 		for(int i=0;i>wyk;i--)
 		{
 			wynik/=podst;
 		}
 	}
 	return wynik;
 }
 
 const char* uzysk(const char *t, float &wynik)
 {
 	stos st;
 	wynik=0;
 	float pom=0, pom1=0; //pom1 dla czÍúci u≥amkowej
 	while(kod(*t)==kod(' '))t++;
 	while((kod(*t)>=roznica)&&(kod(*t)<=(roznica+9)))
 	{
 		pom*=10;
 		pom+=(kod(*t)-roznica);
 		t++;
 	}
 	if((*t)=='.')
 	{ 
 		t++;
 		while((kod(*t)>=roznica)&&(kod(*t)<=(roznica+9)))
 		{
 			
 			st.put((kod(*t)-roznica));
 			t++;
 		}
 	}
 	while(!(st.empty())){
 	pom1/=10;
 	pom1+=(st.check())*(0.1);
 	st.pop();}
 	
 	pom=pom+pom1;
 	wynik=pom;
 	return t;
 	
 }
 
 string tonp(string a)
 {
 	string wy;
 	const char *wsk= a.c_str();
 	stos stack, stacktemp;
 	queue temp, out;
 	int pom, prev;
 	bool pom1=false; //do sprawdzenia czy poprzedni znak teø by≥ cyfrπ
 	int liczba=-1;
 
 	
 	while(static_cast<int>(*wsk) != 0)
 	{
 		pom=static_cast<int>(*wsk);
 		if((pom>=roznica && pom<=(roznica+9)) /*|| pom==kod('-')&&(stack.empty() || prev<roznica || prev>(roznica+9) || (prev==kod('('))) */|| pom==kod(',') )
 		{
 			out.put(pom);
 		}else 
 			
  		{
		  //wsk pokazuje na operator
 			if(pom!=kod('.')){out.put(kod(' '));}
 			if(*wsk=='(')
 			{
 				stack.put(kod('('));
 				wsk++;
 				wsk=nawias(wsk, out, stack);
 				wsk--;
 			}else if(*wsk=='.'){out.put(pom);}
			 else if(stack.empty() ||  !(porownaj(*wsk, znak(stack.check())  )))
 			{
 				stack.put(kod(*wsk));
 				
 			}
 			else
 			{
 				while(porownaj(*wsk, znak(stack.check())))
 				{
 					
 					out.put(stack.check());
 					
 					stack.pop();
 				}
 				stack.put(kod(*wsk));

 	
 			}
 			
 			
 		}
 		
 		 prev=pom;
 		wsk++;
 	}
 	
 	while(!(stack.empty()))
 	{
 		out.put(stack.check());
		stack.pop();
	
	}
 	
 	
 	while(!(out.empty()))
 	{
 		if(!((znak(out.check()))=='(' || (znak(out.check()))==')'))wy+=(znak(out.check()));
 		
		 out.pop();
 	}
 	
 	
 return wy;	
 }

float onpwynik(string rownanie)
{

	const char* wsk, *wskp;
	wsk=rownanie.c_str();
	stos stack, oper;
	stack.put(0);
	bool minus=false, liczba=false;
	int pom, pom1;
	float temp=0, temp1=0;
	pom=kod(*wsk);
	while(pom!=0)
	{
		while(kod(*wsk)==kod(' '))wsk++;
		 if(kod(*wsk)>=roznica && kod(*wsk)<=(roznica+9))
		{

				wsk=uzysk(wsk, temp);
				while((kod(*wsk))==kod(' '))wsk++;
				stack.put(temp); 
				temp=0;
				wsk--;	
				
		}//else if(*wsk==' '){}
		else if(*wsk=='+')
		{
			temp=stack.check();
			stack.pop();
			temp1=stack.check();
			stack.pop();
			temp+=temp1;
			stack.put(temp);
			temp=0; temp1=0;
		}else if(*wsk=='-')
		{
			temp=stack.check();
			stack.pop();
			temp1=stack.check();
			stack.pop();
			temp1-=temp;
			stack.put(temp1);
			temp=0;temp1=0;
		}else if(*wsk=='*')
		{
			temp=stack.check();
			stack.pop();
			temp1=stack.check();
			stack.pop();
			temp*=temp1;
			stack.put(temp); temp=0;temp1=0;
		}else if(*wsk=='/')
		{
			temp=stack.check();
			stack.pop();
			temp1=stack.check();
			stack.pop();
			temp1/=temp;
			stack.put(temp1);
		}else if(*wsk=='^')
		{
			temp=stack.check();
			stack.pop();
			temp1=stack.check();
			stack.pop();
			temp=potega(temp, temp1);
			stack.put(temp);
		}else if(*wsk=='~')
		{
			temp=stack.check();
			stack.pop();
			temp*=(-1);
			stack.put(temp);
		}
		
		wsk++;
		while(kod(*wsk)==kod(' '))wsk++;
		pom=kod(*wsk);
	}
	return stack.check();
	
}

const char* nawias(const char* p, queue &q, stos &st)
{
	
	int pom, prev=kod('(');
	stos temp;
	while(*p != ')')
	{
		pom=static_cast<int>(*p);
		if(pom>=roznica && pom<=(roznica+9) ||  pom==kod('-')&&(prev<roznica || prev>(roznica+9)) ||pom==kod('.') )
		{q.put(pom);
		}else if(pom==kod('(')){
		 p++; 
		 st.put(kod('('));
		  p=nawias(p, q, st);
		  p--;
		 }
		else{ //wskaünik pokazuje na operator
				if(*p!='.')q.put(kod(' '));
 			if(st.empty() ||  !(porownaj(*p, znak(st.check())  )))
 			{
 				st.put(kod(*p));
 			}else
 			{
 				while(porownaj(*p, znak(st.check())) && (znak(st.check())!='('))
 				{
 					q.put(st.check());
 					
 					st.pop();
 				}
 				if((*p)!='('){st.put(kod(*p));} 
 				
 	
 			}
 			
 			
 		}

		
		prev=pom;
		p++;
	} 
	 	while(st.check() != kod('(')) 
 		{
 			q.put(st.check());
 			st.pop();
 		}
 		st.pop();
 		
 		p++;
 		
	return p;
}



int main()
{
	
	float x;
	
	string ww="2+3+5";
	const char* j=ww.c_str();
	string aa;
	cout<<"Napisz dzialanie w notacji tradycyjnej: "<<endl;
	cin>>aa;
	//string aa="222+3.3*(2+6.2*(53+6.6))+15";
	string gg;
	gg= tonp(aa);
	x=onpwynik(gg);
	
	

	cout<<"Oto ONP: "<<gg<<endl;
	


return 0;	
}
