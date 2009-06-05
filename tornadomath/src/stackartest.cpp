#include "stackar.h"
#include "my_string.h"
#include "my_string.cpp"
int  main()
{
	StackAr<String, const char*> ar;
	//StackAr<int, int>ar;
	char i[100];
	//int i;
	for(;;)
	{
		//String s;
		//char ch=cin.get();
		char ch;
		cin>>ch;
		//cin.getline(buf, 100);
		if(ch=='a'){
			//int i;
			cin>>i;
			ar.add(i);
		}
		else if(ch=='r')
			cout<<ar.remove()<<endl;
		else if(ch=='q')
			return 0;
		cout<<"oper complete...\n";
		ar.debug_dump("test");
	}
	return 1;
}

		
