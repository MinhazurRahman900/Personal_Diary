#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

// sets appropriate macro to clear screen
#ifdef __linux__
    #define _clear_scrn system("clear")
#else
    #define _clear_scrn system("cls")
#endif



int safeInput();

int password();

void addrecord();

void viewrecord();

void editrecord();

void editPassword();

void deleterecord();

struct record

{

    char time[6];

    char name[30];

    char place[25];

    char duration[10];

    char note[500];

} ;

int main()

{

    int ch;

    printf("\n\n\t***********************************\n");

    printf("\t*PASSWORD PROTECTED PERSONAL DIARY*\n");

    printf("\t***********************************");

    while(1)

    {

        printf("\n\n\t\tMAIN MENU:");

        printf("\n\n\tADD RECORD\t[1]");

        printf("\n\tVIEW RECORD\t[2]");

        printf("\n\tEDIT RECORD\t[3]");

        printf("\n\tDELETE RECORD\t[4]");

        printf("\n\tEDIT PASSWORD\t[5]");

        printf("\n\tEXIT\t\t[6]");

        printf("\n\n\tENTER YOUR CHOICE:");


        ch = safeInput();

        switch(ch)

        {

        case 1:

            addrecord();

            break;

        case 2:

            viewrecord();

            break;

        case 3:

            editrecord();

            break;

        case 4:

            deleterecord();

            break;

        case 5:

            editPassword();

            break;

        case 6:

            printf("\n\n\t\tTHANK YOU FOR USING THE SOFTWARE ");

            getch();

            exit(0);

        default:

            printf("\nYOU ENTERED WRONG CHOICE..");

            printf("\nPRESS ANY KEY TO TRY AGAIN");

            getch();

            break;

        }

        _clear_scrn;

    }

    return 0;

}

// safely take inputs in the program
int safeInput()    {
    
    char str[4];

    int ret = scanf("%1[(0-9)]", str);
    str[1] = '\0';

    if(ret)    {

        fflush(stdin);
        int ch = atoi(str);
        return ch;
    }

    fflush(stdin);

    return -1;

}

void addrecord( )

{

    _clear_scrn;

    FILE *fp ;

    char another = 'Y' ,time[10];

    struct record e ;

    char filename[15];

    int choice;

    // chaecking for authentication
    int pas = password();

    if(pas != 0)    return ;

    _clear_scrn;


    printf("\n\n\t\t***************************\n");

    printf("\t\t* WELCOME TO THE ADD MENU *");

    printf("\n\t\t***************************\n\n");



    printf("\n\n\tENTER DATE OF YOUR RECORD:[yyyy-mm-dd]:");

    fflush(stdin);

    //updated
    fgets(filename, sizeof(filename), stdin);
    
    filename[strlen(filename)-1] = '\0';

    fp = fopen (filename, "ab+" ) ;

    if ( fp == NULL )

    {

        fp=fopen(filename,"wb+");

        if(fp==NULL)

        {

            printf("\nSYSTEM ERROR...");

            printf("\nPRESS ANY KEY TO EXIT");

            getch();

            return ;

        }

    }

    while ( another == 'Y'|| another=='y' )

    {

        choice=0;

        fflush(stdin);

        printf ( "\n\tENTER TIME:[hh:mm]:");

        //potential threat
        scanf("%s",time);

        rewind(fp);

        while(fread(&e,sizeof(e),1,fp)==1)

        {
            
            if(strcmp(e.time,time)==0)

            {

                printf("\n\tTHE RECORD ALREADY EXISTS.\n");

                choice=1;

            }

        }

        if(choice==0)

        {

            strcpy(e.time,time);

            printf("\tENTER NAME:");

            fflush(stdin);

            fgets(e.name, sizeof(e.name), stdin);

            e.name[strlen(e.name)-1] = '\0';

            fflush(stdin);

            printf("\tENTER PLACE:");

            fgets(e.place, sizeof(e.place), stdin);

            e.place[strlen(e.place)-1] = '\0';

            fflush(stdin);

            printf("\tENTER DURATION:");
            
            //updated
            fgets(e.duration,sizeof(e.duration), stdin);

             e.duration[strlen(e.duration)-1] = '\0';

            fflush(stdin);

            printf("\tNOTE:");
            
            //update
            fgets(e.note, sizeof(e.note), stdin);

            e.note[strlen(e.note)-1] = '\0';

            fwrite ( &e, sizeof ( e ), 1, fp ) ;

            printf("\nYOUR RECORD IS ADDED...\n");

        }

        printf ( "\n\tADD ANOTHER RECORD...(Y/N) " ) ;

        fflush ( stdin ) ;

        another = getchar( ) ;

        fflush ( stdin ) ;

    }

    fclose ( fp ) ;

    printf("\n\n\tPRESS ANY KEY TO EXIT...");

    getch();

}

void viewrecord( )

{

    FILE *fpte ;

    _clear_scrn;

    struct record customer ;

    char time[6],choice,filename[14];

    int ch, pass;

    // checking authentication
    pass = password();

    if(pass != 0)    return ;

    _clear_scrn;

    printf("\n\n\t\t*******************************\n");

    printf("\t\t* HERE IS THE VIEWING MENU *");

    printf("\n\t\t*******************************\n\n");


    do

    {

        printf("\n\tENTER THE DATE OF RECORD TO BE VIEWED:[yyyy-mm-dd]:");

        fflush(stdin);

        fgets(filename, sizeof(filename), stdin);

        filename[strlen(filename)-1] = '\0';

        fpte = fopen ( filename, "rb" ) ;

        if ( fpte == NULL )

        {

            puts ( "\nTHE RECORD DOES NOT EXIST...\n" ) ;

            printf("PRESS ANY KEY TO EXIT...");

            getch();

            return ;

        }

        _clear_scrn;

        printf("\n\tHOW WOULD YOU LIKE TO VIEW:\n");

        printf("\n\t1.WHOLE RECORD OF THE DAY.");

        printf("\n\t2.RECORD OF FIX TIME.");

        printf("\n\t\tENTER YOUR CHOICE:");

        ch = safeInput();

        switch(ch)

        {

        case 1:

            printf("\nTHE WHOLE RECORD FOR %s IS:",filename);

            while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )

            {

                printf("\n");

                printf("\nTIME: %s",customer.time);

                printf("\nNAME: %s",customer.name);

                printf("\nPLACE: %s",customer.place);

                printf("\nDURATION: %s",customer.duration);

                printf("\nNOTE: %s",customer.note);

                printf("\n");

            }

            break;

        case 2:

            fflush(stdin);

            printf("\nENTER TIME:[hh:mm]:");

            fgets(time, sizeof(time), stdin);

            time[strlen(time)-1] = '\0';

            while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )

            {

                if(strcmp(customer.time,time)==0)

                {

                    printf("\nYOUR RECORD IS:");

                    printf("\nTIME: %s",customer.time);

                    printf("\nNAME: %s",customer.name);

                    printf("\nPLACE: %s",customer.place);

                    printf("\nDUARATION: %s",customer.duration);

                    printf("\nNOTE: %s",customer.note);

                }

            }

            break;

        default:
            printf("\nYOU TYPED SOMETHING ELSE...\n");

            break;

        }

        printf("\n\nWOULD YOU LIKE TO CONTINUE VIEWING...(Y/N):");

        fflush(stdin);

        scanf("%c",&choice);

        fflush(stdin);

    }
    while(choice=='Y'||choice=='y');

    fclose ( fpte ) ;

    return ;

}

void editrecord()

{

    _clear_scrn;

    FILE *fpte ;

    struct record customer ;

    char time[6],choice,filename[14];

    int num,count=0;

    //checking for authentication
    int pass = password();
    
    if(pass != 0)    return ;

    _clear_scrn;

    printf("\n\n\t\t*******************************\n");

    printf("\t\t* WELCOME TO THE EDITING MENU *");

    printf("\n\t\t*******************************\n\n");

    

    do

    {

        printf("\n\tENTER THE DATE OF RECORD TO BE EDITED:[yyyy-mm-dd]:");

        fflush(stdin);

        fgets(filename, sizeof(filename), stdin);

        filename[strlen(filename)-1] = '\0';

        fflush(stdin);

        printf("\n\tENTER TIME:[hh:mm]:");

        fgets(time, sizeof(time), stdin);

        time[strlen(time)-1] = '\0';

        fflush(stdin);

        fpte = fopen ( filename, "rb+" ) ;

        if ( fpte == NULL )

        {

            printf( "\nRECORD DOES NOT EXISTS:" ) ;

            printf("\nPRESS ANY KEY TO GO BACK");

            getch();

            return;

        }

        while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )

        {

            if(strcmp(customer.time,time)==0)

            {

                printf("\nYOUR OLD RECORD WAS AS:");

                printf("\nTIME: %s",customer.time);

                printf("\nNAME: %s",customer.name);

                printf("\nPLACE: %s",customer.place);

                printf("\nDURATION: %s",customer.duration);

                printf("\nNOTE: %s",customer.note);

                printf("\n\n\t\tWHAT WOULD YOU LIKE TO EDIT..");

                printf("\n1.TIME.");

                printf("\n2.NAME.");

                printf("\n3.PLACE.");

                printf("\n4.DURATION.");

                printf("\n5.NOTE.");

                printf("\n6.WHOLE RECORD.");

                printf("\n7.GO BACK TO MAIN MENU.");

                do

                {

                    printf("\n\tENTER YOUR CHOICE:");

                    fflush(stdin);

                    num = safeInput();

                    fflush(stdin);

                    switch(num)

                    {

                    case 1:
                        printf("\nENTER THE NEW DATA:");

                        printf("\nNEW TIME:[hh:mm]:");

                        fgets(customer.time, sizeof(customer.time), stdin);

                        customer.time[strlen(customer.time)-1] = '\0';

                        break;

                    case 2:
                        printf("\nENTER THE NEW DATA:");

                        printf("\nNEW NAME:");

                        fgets(customer.name, sizeof(customer.name), stdin);

                        customer.name[strlen(customer.name)-1] = '\0';


                        break;

                    case 3:
                        printf("\nENTER THE NEW DATA:");

                        printf("\nNEW PLACE:");

                        fgets(customer.place, sizeof(customer.place), stdin);

                        customer.place[strlen(customer.place)-1] = '\0';


                        break;

                    case 4:
                        printf("\nENTER THE NEW DATA:");

                        printf("\nDURATION:");

                        fgets(customer.duration, sizeof(customer.duration), stdin);

                        customer.duration[strlen(customer.duration)-1] = '\0';


                        break;

                    case 5:
                        printf("ENTER THE NEW DATA:");

                        printf("\nNOTE:");

                        fgets(customer.note, sizeof(customer.note), stdin);

                        customer.note[strlen(customer.note)-1] = '\0';


                        break;

                    case 6:
                        printf("\nENTER THE NEW DATA:");

                        printf("\nNEW TIME:[hh:mm]:");

                        fgets(customer.time, sizeof(customer.time), stdin);

                        customer.time[strlen(customer.time)-1] = '\0';


                        printf("\nNEW NAME:");

                        fgets(customer.name, sizeof(customer.name), stdin);

                        customer.name[strlen(customer.name)-1] = '\0';


                        printf("\nNEW PLACE:");

                        fgets(customer.place, sizeof(customer.place), stdin);

                        customer.place[strlen(customer.place)-1] = '\0';


                        printf("\nDURATION:");

                        fgets(customer.duration, sizeof(customer.duration), stdin);

                        customer.duration[strlen(customer.duration)-1] = '\0';

                        printf("\nNOTE:");

                        fgets(customer.note, sizeof(customer.note), stdin);

                        customer.note[strlen(customer.note)-1] = '\0';


                        break;

                    case 7:
                        printf("\nPRESS ANY KEY TO GO BACK...\n");

                        getch();

                        return ;

                        break;

                    default:
                        printf("\nYOU TYPED SOMETHING ELSE...TRY AGAIN\n");

                        break;

                    }

                }
                while(num<1||num>8);

                fseek(fpte,-sizeof(customer),SEEK_CUR);

                fwrite(&customer,sizeof(customer),1,fpte);

                fseek(fpte,-sizeof(customer),SEEK_CUR);

                fread(&customer,sizeof(customer),1,fpte);

                choice=5;

                break;

            }

        }

        if(choice==5)

        {

            _clear_scrn;

            printf("\n\t\tEDITING COMPLETED...\n");

            printf("--------------------\n");

            printf("THE NEW RECORD IS:\n");

            printf("--------------------\n");

            printf("\nTIME: %s",customer.time);

            printf("\nNAME: %s",customer.name);

            printf("\nPLACE: %s",customer.place);

            printf("\nDURATION: %s",customer.duration);

            printf("\nNOTE: %s",customer.note);

            fclose(fpte);

            printf("\n\n\tWOULD YOU LIKE TO EDIT ANOTHER RECORD.(Y/N)");

            fflush(stdin);

            scanf("%c",&choice);

            fflush(stdin);

            count++;

        }

        else

        {

            printf("\nTHE RECORD DOES NOT EXIST::\n");

            printf("\nWOULD YOU LIKE TO TRY AGAIN...(Y/N)");

            fflush(stdin);

            scanf("%c",&choice);

            fflush(stdin);

        }

    }
    while(choice=='Y'||choice=='y');

    fclose ( fpte ) ;

    if(count==1)

        printf("\n%d FILE IS EDITED...\n",count);

    else if(count>1)

        printf("\n%d FILES ARE EDITED..\n",count);

    else

        printf("\nNO FILES EDITED...\n");

    printf("\tPRESS ENTER TO EXIT EDITING MENU.");

    getch();

}


// Recieves password entry from the user
// MAX PASS len is 12
// Takes input untill user press ENTER
// Has the functionality of "Backspace" and Password hiding with "*"
void passEntry(char* pass)    {

    int i = 0;
    pass[0]=getch();

    while(pass[i]!='\r')    {
            
        if(pass[i]=='\b')    {
            if(i == 0 )    pass[i] = getch();
            i--;
            printf("\b");
            printf(" ");
            printf("\b");
            pass[i]=getch();

        }
        else if(i >= 12)    {
            pass[i] = getch();
        }
        else    {
            printf("*");
            i++;
            pass[i]=getch();
        }
    }

    pass[i]='\0';
}

// function to check authentication
// returns 0 if matches other wise false
// Max Length of the password is 12
int password()    {

    char pass[15] = {0}, check[15]= {0},ch;

    FILE *fpp;
    int i = 0, j;

    printf("::FOR SECURITY PURPOSE::");
    printf("::ONLY THREE TRIALS ARE ALLOWED::");

    for(j = 0; j < 3; j++)

    {
        //read the password from user
        printf("\n\n\tENTER THE PASSWORD:");
        passEntry(pass);
        
        fpp = fopen("SE","r");
        if (fpp == NULL)    {

            printf("\nERROR WITH THE SYSTEM FILE...[FILE MISSING]\n");
            getch();

            return 1;
        }

        // reads the password from the file
        // decript it and puts it int the check string
        while( 1 )    {

            ch = fgetc(fpp);
            if(ch == EOF)    {

                check[i] = '\0';
                break;
            }

            check[i] = ch - 5;
            i++;

        }

        if(strcmp(pass,check)==0)    {

            printf("\n\n\tACCESS GRANTED...\n");
            return 0;
        }

        else
            printf("\n\n\tWRONG PASSWORD..\n\n\tACCESS DENIED...\n");
    }

    printf("\n\n\t::YOU ENTERED WRONG PASSWORD::YOU ARE NOT ALLOWED TO ACCESS ANY FILE::\n\n\tPRESS ANY KEY TO GO BACK...");
    getch();

    return 1;
}

// Changes password
void editPassword()    {

    _clear_scrn;

    printf("\n");

    char pass[15]= {0}, conform[15] = {0}, ch;
    int choice, i, check;

    // checks if the file already exits or not,if not creates the file 
    // upon creating the file default pass is empty
    FILE* fp = fopen("SE","rb");
    if(fp == NULL)    {
        
        fp = fopen("SE","wb");
        if(fp == NULL)    {
            printf("SYSTEM ERROR...");
            getch();
            return ;
        }

        //fclose(fp);

        printf("\nSYSTEM RESTORED...\nYOUR PASSWORD IS 'ENTER'\n PRESS ENTER TO CHANGE PASSWORD\n\n");
        getch();
    }

    fclose(fp);

    // checks current password
    check = password();
    if(check == 1)    return ;

    // Takes new pass and conforms it . Iterates untill the passwords are matched
    do    {
        if(check == 0)    {

            choice = 0;

            // Take New Password input from user
            printf("\n\n\tENTER THE NEW PASSWORD:");
            fflush(stdin);
            passEntry(pass);

            // Take New Password conformation from the user
            printf("\n\tCONFORM PASSWORD:");
            fflush(stdin);
            passEntry(conform);

            if(strcmp(pass,conform) == 0)    {

                fp = fopen("SE","wb");

                if(fp==NULL)    {

                    printf("\n\t\tSYSTEM ERROR");
                    getch();
                    return ;
                }

                // Updates the file with the new Encrypted password
                i = 0;
                while(pass[i] != '\0')    {

                    ch = pass[i];
                    putc(ch + 5, fp);
                    i++;
                }
                putc(EOF,fp);
                fclose(fp);
            }

            else    {
                printf("\n\tTHE NEW PASSWORD DOES NOT MATCH.");
                choice = 1;
            }

        }

    }
    while(choice == 1);

    printf("\n\n\tPASSWORD CHANGED...\n\n\tPRESS ANY KEY TO GO BACK...");
    getch();

}

void deleterecord( )

{

    _clear_scrn;

    FILE *fp,*fptr ;

    struct record file ;

    char filename[15],another = 'Y' ,time[10];;

    int choice,check;

    printf("\n\n\t\t*************************\n");

    printf("\t\t* WELCOME TO DELETE MENU*");

    printf("\n\t\t*************************\n\n");

    check = password();

    if(check==1)

    {

        return ;

    }

    while ( another == 'Y' )

    {

        printf("\n\n\tHOW WOULD YOU LIKE TO DELETE.");

        printf("\n\n\t#DELETE WHOLE RECORD\t\t\t[1]");

        printf("\n\t#DELETE A PARTICULAR RECORD BY TIME\t[2]");

        do

        {

            printf("\n\t\tENTER YOU CHOICE:");

            fflush(stdin);

            choice = safeInput();

            switch(choice)

            {

            case 1:

                printf("\n\tENTER THE DATE OF RECORD TO BE DELETED:[yyyy-mm-dd]:");

                fflush(stdin);

                fgets(filename, sizeof(filename), stdin);

                filename[strlen(filename) - 1 ] = '\0';

                fp = fopen (filename, "wb" ) ;

                if ( fp == NULL )

                {

                    printf("\nTHE FILE DOES NOT EXISTS");

                    printf("\nPRESS ANY KEY TO GO BACK.");

                    getch();

                    return ;

                }

                fclose(fp);

                remove(filename);

                printf("\nDELETED SUCCESFULLY...");

                break;

            case 2:

                printf("\n\tENTER THE DATE OF RECORD:[yyyy-mm-dd]:");

                fflush(stdin);

                fgets(filename, sizeof(filename), stdin);

                filename[strlen(filename) -1 ] = '\0';

                fp = fopen (filename, "rb" ) ;

                if ( fp == NULL )

                {

                    printf("\nTHE FILE DOES NOT EXISTS");

                    printf("\nPRESS ANY KEY TO GO BACK.");

                    getch();

                    return ;

                }

                fptr=fopen("temp","wb");

                if(fptr==NULL)

                {

                    printf("\nSYSTEM ERROR");

                    printf("\nPRESS ANY KEY TO GO BACK");

                    getch();

                    return ;

                }

                printf("\n\tENTER THE TIME OF RECORD TO BE DELETED:[hh:mm]:");

                fflush(stdin);

                fgets(time, sizeof(time), stdin);

                time[strlen(time) - 1] = '\0';

                while(fread(&file,sizeof(file),1,fp)==1)

                {

                    if(strcmp(file.time,time)!=0)

                        fwrite(&file,sizeof(file),1,fptr);

                }

                fclose(fp);

                fclose(fptr);

                remove(filename);

                rename("temp",filename);

                printf("\nDELETED SUCCESFULLY...");

                break;

            default:

                printf("\n\tYOU ENTERED WRONG CHOICE");

                break;

            }

        }
        while(choice<1||choice>2);

        printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD.(Y/N):");

        fflush(stdin);

        scanf("%c",&another);

        fflush(stdin);

    }

    printf("\n\n\tPRESS ANY KEY TO EXIT...");

    getch();

}
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

// sets appropriate macro to clear screen
#ifdef __linux__
    #define _clear_scrn system("clear")
#else
    #define _clear_scrn system("cls")
#endif



int safeInput();

int password();

void addrecord();

void viewrecord();

void editrecord();

void editPassword();

void deleterecord();

struct record

{

    char time[6];

    char name[30];

    char place[25];

    char duration[10];

    char note[500];

} ;

int main()

{

    int ch;

    printf("\n\n\t***********************************\n");

    printf("\t*PASSWORD PROTECTED PERSONAL DIARY*\n");

    printf("\t***********************************");

    while(1)

    {

        printf("\n\n\t\tMAIN MENU:");

        printf("\n\n\tADD RECORD\t[1]");

        printf("\n\tVIEW RECORD\t[2]");

        printf("\n\tEDIT RECORD\t[3]");

        printf("\n\tDELETE RECORD\t[4]");

        printf("\n\tEDIT PASSWORD\t[5]");

        printf("\n\tEXIT\t\t[6]");

        printf("\n\n\tENTER YOUR CHOICE:");


        ch = safeInput();

        switch(ch)

        {

        case 1:

            addrecord();

            break;

        case 2:

            viewrecord();

            break;

        case 3:

            editrecord();

            break;

        case 4:

            deleterecord();

            break;

        case 5:

            editPassword();

            break;

        case 6:

            printf("\n\n\t\tTHANK YOU FOR USING THE SOFTWARE ");

            getch();

            exit(0);

        default:

            printf("\nYOU ENTERED WRONG CHOICE..");

            printf("\nPRESS ANY KEY TO TRY AGAIN");

            getch();

            break;

        }

        _clear_scrn;

    }

    return 0;

}

// safely take inputs in the program
int safeInput()    {
    
    char str[4];

    int ret = scanf("%1[(0-9)]", str);
    str[1] = '\0';

    if(ret)    {

        fflush(stdin);
        int ch = atoi(str);
        return ch;
    }

    fflush(stdin);

    return -1;

}

void addrecord( )

{

    _clear_scrn;

    FILE *fp ;

    char another = 'Y' ,time[10];

    struct record e ;

    char filename[15];

    int choice;

    // chaecking for authentication
    int pas = password();

    if(pas != 0)    return ;

    _clear_scrn;


    printf("\n\n\t\t***************************\n");

    printf("\t\t* WELCOME TO THE ADD MENU *");

    printf("\n\t\t***************************\n\n");



    printf("\n\n\tENTER DATE OF YOUR RECORD:[yyyy-mm-dd]:");

    fflush(stdin);

    //updated
    fgets(filename, sizeof(filename), stdin);
    
    filename[strlen(filename)-1] = '\0';

    fp = fopen (filename, "ab+" ) ;

    if ( fp == NULL )

    {

        fp=fopen(filename,"wb+");

        if(fp==NULL)

        {

            printf("\nSYSTEM ERROR...");

            printf("\nPRESS ANY KEY TO EXIT");

            getch();

            return ;

        }

    }

    while ( another == 'Y'|| another=='y' )

    {

        choice=0;

        fflush(stdin);

        printf ( "\n\tENTER TIME:[hh:mm]:");

        //potential threat
        scanf("%s",time);

        rewind(fp);

        while(fread(&e,sizeof(e),1,fp)==1)

        {
            
            if(strcmp(e.time,time)==0)

            {

                printf("\n\tTHE RECORD ALREADY EXISTS.\n");

                choice=1;

            }

        }

        if(choice==0)

        {

            strcpy(e.time,time);

            printf("\tENTER NAME:");

            fflush(stdin);

            fgets(e.name, sizeof(e.name), stdin);

            e.name[strlen(e.name)-1] = '\0';

            fflush(stdin);

            printf("\tENTER PLACE:");

            fgets(e.place, sizeof(e.place), stdin);

            e.place[strlen(e.place)-1] = '\0';

            fflush(stdin);

            printf("\tENTER DURATION:");
            
            //updated
            fgets(e.duration,sizeof(e.duration), stdin);

             e.duration[strlen(e.duration)-1] = '\0';

            fflush(stdin);

            printf("\tNOTE:");
            
            //update
            fgets(e.note, sizeof(e.note), stdin);

            e.note[strlen(e.note)-1] = '\0';

            fwrite ( &e, sizeof ( e ), 1, fp ) ;

            printf("\nYOUR RECORD IS ADDED...\n");

        }

        printf ( "\n\tADD ANOTHER RECORD...(Y/N) " ) ;

        fflush ( stdin ) ;

        another = getchar( ) ;

        fflush ( stdin ) ;

    }

    fclose ( fp ) ;

    printf("\n\n\tPRESS ANY KEY TO EXIT...");

    getch();

}

void viewrecord( )

{

    FILE *fpte ;

    _clear_scrn;

    struct record customer ;

    char time[6],choice,filename[14];

    int ch, pass;

    // checking authentication
    pass = password();

    if(pass != 0)    return ;

    _clear_scrn;

    printf("\n\n\t\t*******************************\n");

    printf("\t\t* HERE IS THE VIEWING MENU *");

    printf("\n\t\t*******************************\n\n");


    do

    {

        printf("\n\tENTER THE DATE OF RECORD TO BE VIEWED:[yyyy-mm-dd]:");

        fflush(stdin);

        fgets(filename, sizeof(filename), stdin);

        filename[strlen(filename)-1] = '\0';

        fpte = fopen ( filename, "rb" ) ;

        if ( fpte == NULL )

        {

            puts ( "\nTHE RECORD DOES NOT EXIST...\n" ) ;

            printf("PRESS ANY KEY TO EXIT...");

            getch();

            return ;

        }

        _clear_scrn;

        printf("\n\tHOW WOULD YOU LIKE TO VIEW:\n");

        printf("\n\t1.WHOLE RECORD OF THE DAY.");

        printf("\n\t2.RECORD OF FIX TIME.");

        printf("\n\t\tENTER YOUR CHOICE:");

        ch = safeInput();

        switch(ch)

        {

        case 1:

            printf("\nTHE WHOLE RECORD FOR %s IS:",filename);

            while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )

            {

                printf("\n");

                printf("\nTIME: %s",customer.time);

                printf("\nNAME: %s",customer.name);

                printf("\nPLACE: %s",customer.place);

                printf("\nDURATION: %s",customer.duration);

                printf("\nNOTE: %s",customer.note);

                printf("\n");

            }

            break;

        case 2:

            fflush(stdin);

            printf("\nENTER TIME:[hh:mm]:");

            fgets(time, sizeof(time), stdin);

            time[strlen(time)-1] = '\0';

            while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )

            {

                if(strcmp(customer.time,time)==0)

                {

                    printf("\nYOUR RECORD IS:");

                    printf("\nTIME: %s",customer.time);

                    printf("\nNAME: %s",customer.name);

                    printf("\nPLACE: %s",customer.place);

                    printf("\nDUARATION: %s",customer.duration);

                    printf("\nNOTE: %s",customer.note);

                }

            }

            break;

        default:
            printf("\nYOU TYPED SOMETHING ELSE...\n");

            break;

        }

        printf("\n\nWOULD YOU LIKE TO CONTINUE VIEWING...(Y/N):");

        fflush(stdin);

        scanf("%c",&choice);

        fflush(stdin);

    }
    while(choice=='Y'||choice=='y');

    fclose ( fpte ) ;

    return ;

}

void editrecord()

{

    _clear_scrn;

    FILE *fpte ;

    struct record customer ;

    char time[6],choice,filename[14];

    int num,count=0;

    //checking for authentication
    int pass = password();
    
    if(pass != 0)    return ;

    _clear_scrn;

    printf("\n\n\t\t*******************************\n");

    printf("\t\t* WELCOME TO THE EDITING MENU *");

    printf("\n\t\t*******************************\n\n");

    

    do

    {

        printf("\n\tENTER THE DATE OF RECORD TO BE EDITED:[yyyy-mm-dd]:");

        fflush(stdin);

        fgets(filename, sizeof(filename), stdin);

        filename[strlen(filename)-1] = '\0';

        fflush(stdin);

        printf("\n\tENTER TIME:[hh:mm]:");

        fgets(time, sizeof(time), stdin);

        time[strlen(time)-1] = '\0';

        fflush(stdin);

        fpte = fopen ( filename, "rb+" ) ;

        if ( fpte == NULL )

        {

            printf( "\nRECORD DOES NOT EXISTS:" ) ;

            printf("\nPRESS ANY KEY TO GO BACK");

            getch();

            return;

        }

        while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )

        {

            if(strcmp(customer.time,time)==0)

            {

                printf("\nYOUR OLD RECORD WAS AS:");

                printf("\nTIME: %s",customer.time);

                printf("\nNAME: %s",customer.name);

                printf("\nPLACE: %s",customer.place);

                printf("\nDURATION: %s",customer.duration);

                printf("\nNOTE: %s",customer.note);

                printf("\n\n\t\tWHAT WOULD YOU LIKE TO EDIT..");

                printf("\n1.TIME.");

                printf("\n2.NAME.");

                printf("\n3.PLACE.");

                printf("\n4.DURATION.");

                printf("\n5.NOTE.");

                printf("\n6.WHOLE RECORD.");

                printf("\n7.GO BACK TO MAIN MENU.");

                do

                {

                    printf("\n\tENTER YOUR CHOICE:");

                    fflush(stdin);

                    num = safeInput();

                    fflush(stdin);

                    switch(num)

                    {

                    case 1:
                        printf("\nENTER THE NEW DATA:");

                        printf("\nNEW TIME:[hh:mm]:");

                        fgets(customer.time, sizeof(customer.time), stdin);

                        customer.time[strlen(customer.time)-1] = '\0';

                        break;

                    case 2:
                        printf("\nENTER THE NEW DATA:");

                        printf("\nNEW NAME:");

                        fgets(customer.name, sizeof(customer.name), stdin);

                        customer.name[strlen(customer.name)-1] = '\0';


                        break;

                    case 3:
                        printf("\nENTER THE NEW DATA:");

                        printf("\nNEW PLACE:");

                        fgets(customer.place, sizeof(customer.place), stdin);

                        customer.place[strlen(customer.place)-1] = '\0';


                        break;

                    case 4:
                        printf("\nENTER THE NEW DATA:");

                        printf("\nDURATION:");

                        fgets(customer.duration, sizeof(customer.duration), stdin);

                        customer.duration[strlen(customer.duration)-1] = '\0';


                        break;

                    case 5:
                        printf("ENTER THE NEW DATA:");

                        printf("\nNOTE:");

                        fgets(customer.note, sizeof(customer.note), stdin);

                        customer.note[strlen(customer.note)-1] = '\0';


                        break;

                    case 6:
                        printf("\nENTER THE NEW DATA:");

                        printf("\nNEW TIME:[hh:mm]:");

                        fgets(customer.time, sizeof(customer.time), stdin);

                        customer.time[strlen(customer.time)-1] = '\0';


                        printf("\nNEW NAME:");

                        fgets(customer.name, sizeof(customer.name), stdin);

                        customer.name[strlen(customer.name)-1] = '\0';


                        printf("\nNEW PLACE:");

                        fgets(customer.place, sizeof(customer.place), stdin);

                        customer.place[strlen(customer.place)-1] = '\0';


                        printf("\nDURATION:");

                        fgets(customer.duration, sizeof(customer.duration), stdin);

                        customer.duration[strlen(customer.duration)-1] = '\0';

                        printf("\nNOTE:");

                        fgets(customer.note, sizeof(customer.note), stdin);

                        customer.note[strlen(customer.note)-1] = '\0';


                        break;

                    case 7:
                        printf("\nPRESS ANY KEY TO GO BACK...\n");

                        getch();

                        return ;

                        break;

                    default:
                        printf("\nYOU TYPED SOMETHING ELSE...TRY AGAIN\n");

                        break;

                    }

                }
                while(num<1||num>8);

                fseek(fpte,-sizeof(customer),SEEK_CUR);

                fwrite(&customer,sizeof(customer),1,fpte);

                fseek(fpte,-sizeof(customer),SEEK_CUR);

                fread(&customer,sizeof(customer),1,fpte);

                choice=5;

                break;

            }

        }

        if(choice==5)

        {

            _clear_scrn;

            printf("\n\t\tEDITING COMPLETED...\n");

            printf("--------------------\n");

            printf("THE NEW RECORD IS:\n");

            printf("--------------------\n");

            printf("\nTIME: %s",customer.time);

            printf("\nNAME: %s",customer.name);

            printf("\nPLACE: %s",customer.place);

            printf("\nDURATION: %s",customer.duration);

            printf("\nNOTE: %s",customer.note);

            fclose(fpte);

            printf("\n\n\tWOULD YOU LIKE TO EDIT ANOTHER RECORD.(Y/N)");

            fflush(stdin);

            scanf("%c",&choice);

            fflush(stdin);

            count++;

        }

        else

        {

            printf("\nTHE RECORD DOES NOT EXIST::\n");

            printf("\nWOULD YOU LIKE TO TRY AGAIN...(Y/N)");

            fflush(stdin);

            scanf("%c",&choice);

            fflush(stdin);

        }

    }
    while(choice=='Y'||choice=='y');

    fclose ( fpte ) ;

    if(count==1)

        printf("\n%d FILE IS EDITED...\n",count);

    else if(count>1)

        printf("\n%d FILES ARE EDITED..\n",count);

    else

        printf("\nNO FILES EDITED...\n");

    printf("\tPRESS ENTER TO EXIT EDITING MENU.");

    getch();

}


// Recieves password entry from the user
// MAX PASS len is 12
// Takes input untill user press ENTER
// Has the functionality of "Backspace" and Password hiding with "*"
void passEntry(char* pass)    {

    int i = 0;
    pass[0]=getch();

    while(pass[i]!='\r')    {
            
        if(pass[i]=='\b')    {
            if(i == 0 )    pass[i] = getch();
            i--;
            printf("\b");
            printf(" ");
            printf("\b");
            pass[i]=getch();

        }
        else if(i >= 12)    {
            pass[i] = getch();
        }
        else    {
            printf("*");
            i++;
            pass[i]=getch();
        }
    }

    pass[i]='\0';
}

// function to check authentication
// returns 0 if matches other wise false
// Max Length of the password is 12
int password()    {

    char pass[15] = {0}, check[15]= {0},ch;

    FILE *fpp;
    int i = 0, j;

    printf("::FOR SECURITY PURPOSE::");
    printf("::ONLY THREE TRIALS ARE ALLOWED::");

    for(j = 0; j < 3; j++)

    {
        //read the password from user
        printf("\n\n\tENTER THE PASSWORD:");
        passEntry(pass);
        
        fpp = fopen("SE","r");
        if (fpp == NULL)    {

            printf("\nERROR WITH THE SYSTEM FILE...[FILE MISSING]\n");
            getch();

            return 1;
        }

        // reads the password from the file
        // decript it and puts it int the check string
        while( 1 )    {

            ch = fgetc(fpp);
            if(ch == EOF)    {

                check[i] = '\0';
                break;
            }

            check[i] = ch - 5;
            i++;

        }

        if(strcmp(pass,check)==0)    {

            printf("\n\n\tACCESS GRANTED...\n");
            return 0;
        }

        else
            printf("\n\n\tWRONG PASSWORD..\n\n\tACCESS DENIED...\n");
    }

    printf("\n\n\t::YOU ENTERED WRONG PASSWORD::YOU ARE NOT ALLOWED TO ACCESS ANY FILE::\n\n\tPRESS ANY KEY TO GO BACK...");
    getch();

    return 1;
}

// Changes password
void editPassword()    {

    _clear_scrn;

    printf("\n");

    char pass[15]= {0}, conform[15] = {0}, ch;
    int choice, i, check;

    // checks if the file already exits or not,if not creates the file 
    // upon creating the file default pass is empty
    FILE* fp = fopen("SE","rb");
    if(fp == NULL)    {
        
        fp = fopen("SE","wb");
        if(fp == NULL)    {
            printf("SYSTEM ERROR...");
            getch();
            return ;
        }

        //fclose(fp);

        printf("\nSYSTEM RESTORED...\nYOUR PASSWORD IS 'ENTER'\n PRESS ENTER TO CHANGE PASSWORD\n\n");
        getch();
    }

    fclose(fp);

    // checks current password
    check = password();
    if(check == 1)    return ;

    // Takes new pass and conforms it . Iterates untill the passwords are matched
    do    {
        if(check == 0)    {

            choice = 0;

            // Take New Password input from user
            printf("\n\n\tENTER THE NEW PASSWORD:");
            fflush(stdin);
            passEntry(pass);

            // Take New Password conformation from the user
            printf("\n\tCONFORM PASSWORD:");
            fflush(stdin);
            passEntry(conform);

            if(strcmp(pass,conform) == 0)    {

                fp = fopen("SE","wb");

                if(fp==NULL)    {

                    printf("\n\t\tSYSTEM ERROR");
                    getch();
                    return ;
                }

                // Updates the file with the new Encrypted password
                i = 0;
                while(pass[i] != '\0')    {

                    ch = pass[i];
                    putc(ch + 5, fp);
                    i++;
                }
                putc(EOF,fp);
                fclose(fp);
            }

            else    {
                printf("\n\tTHE NEW PASSWORD DOES NOT MATCH.");
                choice = 1;
            }

        }

    }
    while(choice == 1);

    printf("\n\n\tPASSWORD CHANGED...\n\n\tPRESS ANY KEY TO GO BACK...");
    getch();

}

void deleterecord( )

{

    _clear_scrn;

    FILE *fp,*fptr ;

    struct record file ;

    char filename[15],another = 'Y' ,time[10];;

    int choice,check;

    printf("\n\n\t\t*************************\n");

    printf("\t\t* WELCOME TO DELETE MENU*");

    printf("\n\t\t*************************\n\n");

    check = password();

    if(check==1)

    {

        return ;

    }

    while ( another == 'Y' )

    {

        printf("\n\n\tHOW WOULD YOU LIKE TO DELETE.");

        printf("\n\n\t#DELETE WHOLE RECORD\t\t\t[1]");

        printf("\n\t#DELETE A PARTICULAR RECORD BY TIME\t[2]");

        do

        {

            printf("\n\t\tENTER YOU CHOICE:");

            fflush(stdin);

            choice = safeInput();

            switch(choice)

            {

            case 1:

                printf("\n\tENTER THE DATE OF RECORD TO BE DELETED:[yyyy-mm-dd]:");

                fflush(stdin);

                fgets(filename, sizeof(filename), stdin);

                filename[strlen(filename) - 1 ] = '\0';

                fp = fopen (filename, "wb" ) ;

                if ( fp == NULL )

                {

                    printf("\nTHE FILE DOES NOT EXISTS");

                    printf("\nPRESS ANY KEY TO GO BACK.");

                    getch();

                    return ;

                }

                fclose(fp);

                remove(filename);

                printf("\nDELETED SUCCESFULLY...");

                break;

            case 2:

                printf("\n\tENTER THE DATE OF RECORD:[yyyy-mm-dd]:");

                fflush(stdin);

                fgets(filename, sizeof(filename), stdin);

                filename[strlen(filename) -1 ] = '\0';

                fp = fopen (filename, "rb" ) ;

                if ( fp == NULL )

                {

                    printf("\nTHE FILE DOES NOT EXISTS");

                    printf("\nPRESS ANY KEY TO GO BACK.");

                    getch();

                    return ;

                }

                fptr=fopen("temp","wb");

                if(fptr==NULL)

                {

                    printf("\nSYSTEM ERROR");

                    printf("\nPRESS ANY KEY TO GO BACK");

                    getch();

                    return ;

                }

                printf("\n\tENTER THE TIME OF RECORD TO BE DELETED:[hh:mm]:");

                fflush(stdin);

                fgets(time, sizeof(time), stdin);

                time[strlen(time) - 1] = '\0';

                while(fread(&file,sizeof(file),1,fp)==1)

                {

                    if(strcmp(file.time,time)!=0)

                        fwrite(&file,sizeof(file),1,fptr);

                }

                fclose(fp);

                fclose(fptr);

                remove(filename);

                rename("temp",filename);

                printf("\nDELETED SUCCESFULLY...");

                break;

            default:

                printf("\n\tYOU ENTERED WRONG CHOICE");

                break;

            }

        }
        while(choice<1||choice>2);

        printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD.(Y/N):");

        fflush(stdin);

        scanf("%c",&another);

        fflush(stdin);

    }

    printf("\n\n\tPRESS ANY KEY TO EXIT...");

    getch();

}
