#include<stdio.h>
//Student information For LMS
typedef struct students{
unsigned int student_id;
char student_name[15];
char student_mob_num[12];
char student_course[8];
char student_add[20];
int status;
struct student *sptr;
}student;
student *shome=NULL;
static int login_student_id;
//Issue Structure for student and librarian 

typedef struct issue_books{
	int issue_id;
	int book_id;
	int student_id;
	int book_qty;
	int issue_date;
	int return_date;
	int issue_status;
	int librarian_id;
	struct issue_book *iptr; 
}issue_book;

// Books Structure for student and librarian both
typedef struct books{
	int book_id;
	char book_name[20];
	char book_author[20];
	char book_language[20];
	int book_qty;
	int book_status;
	struct book *bptr;
}book;

// Librarian structure

typedef struct librarians{
	int librarian_id;
	char librarian_name[20];
	char librarian_uname[20];
	char librarian_password[10];
	char librarian_mob[12];
	int librarian_status;
	struct librarian *lptr;
}librarian;

void login_menu();
void logout();
student * search_student_by_student_id(int student_id);
void librarian_menu();
//create memory  for student
student* create_memory_student()
{
	student *stemp;
	stemp=(student *)malloc(sizeof(student));
	stemp->sptr=NULL;
	return stemp;
}

int add_student_data(student *stemp)
{
	printf("\nEnter Student Id:");
	scanf("%d",&stemp->student_id);
	printf("\nEnter Student Name:");
	fflush(stdin);
	gets(stemp->student_name);
	printf("\nEnter Student Mobile Nu:");
	gets(stemp->student_mob_num);
	printf("\nEnter Student Course:");
	gets(stemp->student_course);
	printf("\nEnter Student Address:");
	gets(stemp->student_add);
	stemp->status=1;
	return 1;
}

int link_student_memory(student *stemp){
	if(shome==NULL)
	shome=stemp;
	else{
	student *vsptr=shome;
	while(vsptr->sptr!=NULL)
	vsptr=vsptr->sptr;
	vsptr->sptr=stemp;
	}
	return 1;
}
void print_student_data()
{
	student *stemp=shome;
	printf("\n%-5s%-10s%-10s%-7s%-15s","id","name","mobile","course" ,"Address" );
	while(stemp!=NULL)
	{
	printf("\n%-05d%-10s%-10s%-5s%-15s",stemp->student_id,stemp->student_name,stemp->student_mob_num,stemp->student_course,stemp->student_add);
	stemp=stemp->sptr;
	}
}
void print_student_single_data(student *stemp)
{
	//student *stemp=shome;
	printf("\n%-5s%-10s%-10s%-7s%-15s","id","name","mobile","course" ,"Address" );
	printf("\n%-05d%-10s%-10s%-5s%-15s",stemp->student_id,stemp->student_name,stemp->student_mob_num,stemp->student_course,stemp->student_add);
}

void lb_student_menu(){
	int lb_choice,student_id;
	student *temp;
	clrscr();
	while(1){
	puts("*********Librarian student Dashboard*********");
	puts("\n1.Add Student\n2.Search Student\n3.Delete Student\n4.Home\nEnter Your Choice:-");
	scanf("%d",&lb_choice);
	switch(lb_choice)
	{
	case 1:
			temp=create_memory_student();
			if(temp!=NULL&&add_student_data(temp))
			link_student_memory(temp);
			else
				printf("!Memory Allocation Failed!");
		break;
	case 2:
		printf("Enter Student Id");
		scanf("%d",&student_id);
		temp=search_student_by_student_id(student_id);
		if(temp==NULL){
			printf("No Record Found or Student Blocked ");
		}else{
			print_student_single_data(temp);
		}
		break;
	case 3:
		printf("Enter Student Id");
		scanf("%d",&student_id);
		if (delete_student_by_student_id(student_id))
		{
			printf("\nDelete Success");
		}
		else{
			printf("\nNo Record Found Or already Blocked");
		}
		break;
	case 4:
		librarian_menu();
		break;
	default :puts("!Invalid Choice");
	}
	getch();
	}
}

void librarian_menu(){
	int lb_choice;
	clrscr();
	while(1){
	puts("*********Librarian Dashboard*********");
	puts("\n1.Student\n2.Book\n3.Logout\nEnter Your Choice:-");
	scanf("%d",&lb_choice);
	switch(lb_choice)
	{
	case 1:
		lb_student_menu();
		break;
	case 2:
	       //	lb_book_menu();
		break;
	case 3:	logout();
		break;
	default :puts("!Invalid Choice");
	}

	}
}

int student_login(){
	char suname[20];
	char spassword[10];
	clrscr();
	puts("\nEnter User Name:");
	fflush(stdin);
	gets(suname);
	puts("\nEnter Password:");
	fflush(stdin);
	gets(spassword);
	return 1;
}

int librarian_login(){
	librarian_menu();
return 1;
}

void current_issue_books(int student_id){

}
void student_menu(){
	int student_choice;
	clrscr();
	while(1){
	puts("*********Login*********");
	puts("\n1.Current Issue Books\n2.Books History\n3.Change Password\n4.Logout\nEnter Your Choice:-");
	scanf("%d",&student_choice);
	switch(student_choice)
	{
	case 1:
		current_issue_books(login_student_id);
		break;
	case 2:
		//student_book_history(login_student_id);
		break;
	case 3:
		//change_password(login_student_id);
		break;
	case 4:
	logout();
		break;
	default:puts("!Invalid Choice");
	}

	}

}

void logout(){
login_menu();
}

void login_menu(){
	int login_choice;
	clrscr();
	while(1){
	puts("*********Login*********");
	puts("\n1.Student\n2.Librarian\n3.Exit\nEnter Your Choice:-");
	scanf("%d",&login_choice);
	switch(login_choice)
	{
	case 1:	if(student_login())
		student_menu();
		else
		student_login();

		break;
	case 2: librarian_login();
		break;
	case 3:exit(0);
	default:puts("!Invalid Choice");
	}

	}
}

int  delete_student_by_student_id(int student_id){
	student *temp;
	int d_choice;
	temp=shome;
	while(temp!=NULL)
	{
		if (temp->student_id==student_id&&temp->status==1)
		{
			print_student_single_data(temp);
			printf("\n1 For Delete else 0");
			scanf("%d",&d_choice);
			if (d_choice==1)
			{
				temp->status=0;
				return 1;
			}
			else
				return 0;
		}
		temp=temp->sptr;
	}
	return 0;
}

student * search_student_by_student_id(int student_id){
	student *temp;
	temp=shome;
	while(temp!=NULL)
	{
		if (temp->student_id==student_id&&temp->status==1)
		{
			return temp;
		}
		temp=temp->sptr;
	}
	return temp;
}
void main(){
student *temp,*temp2;
//librarian_menu();
login_menu();
getch();
}