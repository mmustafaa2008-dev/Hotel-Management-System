#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* making the limit as a macro */
#define limit 20




/* Function prototypes - menu and features  */
void menu();            /* function for printing menu                       */
void book();            /* for booking room                                 */
void price();           /* for checking price                               */
void view();            /* for view customer detail                         */
void checkroom();       /* for checking room availability                   */
void del();             /* for removing old customer // for staff only      */
void bill();            /* for generating bill                              */
void all();             /* only for staff who can see all the customer details*/
void services();        /* for showing the services provided by the hotel   */
void terms();           /* for showing terms and condition of HOTEL         */
void cont();            /* for all emergency and contact number             */
void foodmenu();        /* for buffee                                       */


/* making pass as a global variable */
int pass = 2008; /* staff access password */



/* structure for questioning (booking information) */
struct hotel
{
    char name[100];
    int member;
    int stay_day;
    char room[50];
    int cnic;
    char meal[50];
};




/* array to hold bookings in memory (max 'limit') */
struct hotel books[limit];



/* counter for current bookings */
int count = 0;




/* structure for bill details (per booking index) */
struct bills
{
    int rate;    /* multiplying the constant price with total staying days */
    int buff;    /* this for storing the buffee price * total member * staying days */
    int tax;     /* implementing the 15% tax on the total price */
    int total;   /* for total price */
};




/* array to hold temporary bill calculations */
struct bills totals[limit];




/* ------------------------------
   File helper declarations
   ------------------------------ */

void saveData();                       /* write current 'books' to records.dat */
void loadData();                       /* read records.dat into 'books' & set count */
void saveBillToFile(struct hotel h, struct bills b); /* append bill to bills.txt */

/* ------------------------------
   Implementation of file helpers
   ------------------------------ */


/* loadData: load saved bookings from "records.dat" (binary) */
void loadData()
{
    FILE *fp = fopen("records.dat", "rb");
    if (fp != NULL)
    {
        /* read up to 'limit' records into books[] */
        size_t n = fread(books, sizeof(struct hotel), limit, fp);
        /* set count based on how many entries read */
        count = (int) n;
        fclose(fp);
    }
    else
    {
        /* If file doesn't exist yet, start with zero bookings */
        count = 0;
    }
}




/* saveData: write current in-memory bookings to "records.dat" (binary) */
void saveData()
{
    FILE *fp = fopen("records.dat", "wb");
    if (fp != NULL)
    {
        if (count > 0)
        {
            fwrite(books, sizeof(struct hotel), count, fp);
        }
        fclose(fp);
    }
    else
    {
        /* If saving fails, print a message (non-fatal) */
        printf("Warning: Failed to save records to file.\n");
    }
}




/* saveBillToFile: append a single human-readable bill to "bills.txt" */
void saveBillToFile(struct hotel h, struct bills b)
{
    FILE *fp = fopen("bills.txt", "a");
    if (fp != NULL)
    {
        fprintf(fp, "**************INVOICE**************\n");
        fprintf(fp, "NAME         : %s \n", h.name);
        fprintf(fp, "CNIC NO      : %d\n", h.cnic);
        fprintf(fp, "STAYING DAYS : %d\n", h.stay_day);
        fprintf(fp, "ROOM TYPE    : %s \n", h.room);
        fprintf(fp, "BUFFEE PRICE : %d PKR\n", b.buff);
        fprintf(fp, "AMOUNT       : %d PKR\n", b.rate);
        fprintf(fp, "TAX(15)      : %d PKR\n", b.tax);
        fprintf(fp, "TOTAL AMOUNT : %d PKR\n", b.total);
        fprintf(fp, "***********************************\n\n");
        fclose(fp);
    }
    else
    {
        printf("Warning: Could not open bills.txt to write bill.\n");
    }
}




/* ------------------------------
   MAIN
   ------------------------------ */

int main()
{
    int choice;     /* initializing choice for choicing the option below */

    /* Load existing saved bookings on start */
    loadData();

    do
    {   
        menu();
        if (scanf("%d",&choice) != 1)
        {
            /* if bad input, clear stdin and continue (safe guard) */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            choice = 12; /* treat invalid input as exit */
        }

        switch (choice)
        {        
            case 1:
                book();  /* book function calling */
                break;
        
            case 2:
                price();  /* price function calling */
                break;

            case 3:
                view();  /* view function calling */
                break;

            case 4:
                checkroom();  /* check room availability function calling */
                break;
            
            case 5:
                del();  /* delete function calling */
                break;

            case 6:
                bill();  /* billing function calling */
                break;


            case 7:
                all();  /* all customer showing function calling */
                break;

            case 8:
                services();  /* all services function calling */
                break;

            case 9:
                terms();  /* showing terms and conditon of the hotel */
                break;

            case 10:
                cont();  /* showing the contact number of the hotel management */
                break;

            case 11:
                foodmenu();  /* showing the menu of the buffee */
                break;

            default:
                /* Before exiting, save current records */
                saveData();
                return 0;  /* for exit */
        }
    } while (choice <= 11);

    /* Save again on graceful exit (redundant, but safe) */
    saveData();
    return 0;
}




/* ------------------------------
   FUNCTION DEFINITIONS
   ------------------------------ */


/* function definition for booking room using structure for storing different datatype of variable; */
void book ()
{
    if (count >= limit)
    {
        printf("No Vacant Room is avalaible\n");
        return ;
    }

    /* show price list to user before booking */
    price();

    printf("\nPlease Fill the Form Below to Book Your Room\n");

    printf("Enter Your Name : ");
    scanf(" %[^\n]", books[count].name);

    printf("Family Member   : ");
    scanf("%d",&books[count].member);

    printf("Staying Days    : ");
    scanf("%d",&books[count].stay_day);

    printf("Room Catogaries : ");
    scanf(" %[^\n]", books[count].room);

    printf("Enter CNIC NO   : ");
    scanf("%d",&books[count].cnic);

    printf("Do Want Buffee  : ");
    /* corrected scanf use for meal string (no & for array) */
    scanf(" %[^\n]", books[count].meal);

    int found=0;

    for (int i=0;i<count;i++)
    {
        if (books[i].cnic == books[count].cnic)
        {
            found=1;
            break;
        }
    }

    if (found == 1)
    {
        printf("User Exist at this credentials Unfortunately....!!\n");
    }
    else
    {
        printf("%s your Room %d have been booked for %d days in DAYS_INN HOTEL.. Enjoy your vacations\n", books[count].name, count+1 ,books[count].stay_day);
        count++;

        /* save data to persistent storage immediately after booking */
        saveData();
    }
    
}
/* ending the function definition of function booking */




/* function definition for staff to check all the rooms */

void all()
{
    int pas;
    printf("Enter Your Code : ");
    scanf("%d",&pas);

    if (pas == pass)
    {
        /* reload data to ensure latest snapshot */
        loadData();

        if (count > 0)
        {

            for(int i=0;i<count;i++)
            {
                printf("NAME          : %s\n", books[i].name);
                printf("CNIC NUMBER   : %d\n",books[i].cnic);
                printf("FAMILY MEMBER : %d\n",books[i].member);
                printf("STAYING DAYS  : %d\n",books[i].stay_day);
                printf("ROOM TYPE     : %s\n", books[i].room);
                printf("\n");
            }
        }
        else
        {
            printf("Since No Room is booked\n");
        }
    }

    else
    {
        printf("Wrong Password , Only Staff Can Access This\n");
    }
}

/* function definition ending here */




/* function definition for viewing the customer details */

void view ()
{
    if (count == 0)
    {
        printf("No Visitor Available\n");
        return ;
    }
    int id;
    printf("Enter Your CNIC NUMBER : ");
    scanf("%d",&id);
    for( int i=0;i< count;i++)
    {
        if (id == books[i].cnic)
        {
            printf("\nVisitor Name : %s\n", books[i].name);
            printf("Total Member : %d\n",books[i].member);
            printf("Staying Days : %d\n",books[i].stay_day);
            printf("Room Category: %s\n", books[i].room);
            printf("CNIC Number  : %d\n",books[i].cnic);
            printf("Buffee       : %s\n",books[i].meal);
            return ;
        }

    }
            printf("Sorry!. No User Found With this ID.\n");
}
/* ENDING THE VIEW FUNCTION */




/* NOW MAKING THE FUNCTION FOR CHECKING THE ROOM AVAILABILITY */
void checkroom()
{
    int select;
    if (count >= limit)
    {
        printf("All Rooms are booked, Sorry! for inconvenience\n");
        return;
    }

    printf("%d Rooms are Available, Do you want to Book(1/0) : ",limit - count);
    scanf("%d",&select);
    if(select == 1)
    {
        book();
    }
    else
    {
        return;
    }
    
}

/* Ending the function definition */




/* DELETE FUNCTION DEFINITION */
void del()
{
    int pas;
    printf("Enter Credential Pass key : ");
    scanf("%d",&pas);
    if (pas == pass)
    {
    int id;
    printf("Enter CNIC Number : ");
    scanf("%d",&id);
    int choice=0;
    for (int i=0;i<count;i++)
    {
        if (id == books[i].cnic)
        {
            for (int j= i ;j < (count-1) ;j++)
            {
                books[j] = books[j+1];
            }
            choice = 1;
            count--;
            /* save data after deletion */
            saveData();
            break;
        }
    }
    
    if (choice == 1)
    {
        printf("Customer has been Removed\n");
    }
    else
    {
        printf("Customer Not yet found\n");
    }
}
    else
    {
        printf("Only Staff can access\n");
    }
    
}

/* ENDING FUNCTION DEFINITION */







/* Function definition for Bill

   Note: program will look up a booking by CNIC, compute totals[] for
   that index and then print invoice, save invoice to file and remove
   the booking from the records (as in original logic).
*/
void bill() /* add condition that generate option is not available until room is booked //  */
{
    int id;
    printf("Enter Your CNIC Number : ");
    scanf("%d",&id);

    /* make sure we have the latest data loaded */
    loadData();

    for(int i=0;i<count;i++)
    {
        if (id == books[i].cnic)
        {
            /* compute bills based on room type and meal choice */

            /* SINGLE ROOM with meal */
            if ((strcmp(books[i].room,"single")==0 || strcmp(books[i].room, "SINGLE")==0) &&
                (strcmp(books[i].meal,"yes")==0 || strcmp(books[i].meal,"YES")==0))
            {   /* both meal and single room charges */
                totals[i].rate = 2200 * books[i].stay_day;  /* room rate for total staying days */
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = (int)(totals[i].rate * 0.15);
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;

            }

            else  /* only for single room payment (no meal) */
            {
                if ((strcmp(books[i].meal,"no")==0 || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"SINGLE")==0 || strcmp(books[i].room,"single")==0))
                {
                    totals[i].rate = 2200 * books[i].stay_day;
                    totals[i].tax = (int)(totals[i].rate * 0.15);
                    totals[i].total = totals[i].rate + totals[i].tax;
                    totals[i].buff = 0;
                }
            }
        
            /* DOUBLE ROOM */
            if ((strcmp(books[i].room,"double")==0 || strcmp(books[i].room,"DOUBLE")==0) &&
                (strcmp(books[i].meal,"yes")==0 || strcmp(books[i].meal,"YES")==0))
            {
                /* for both meal and double room payment */
                totals[i].rate = 3500 * books[i].stay_day;
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = (int)(totals[i].rate * 0.15);
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;
                
            }

            else
            {    /* only for double room payment (no meal) */
                if ((strcmp(books[i].meal,"no")==0 || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"double")==0 || strcmp(books[i].room,"DOUBLE")==0))
                {
                    totals[i].rate = 3500 * books[i].stay_day;
                    totals[i].buff = 0;
                    totals[i].tax = (int)(totals[i].rate * 0.15);
                    totals[i].total = totals[i].rate + totals[i].tax;
                }
            }



            /* TRIPLE ROOM */
            if ((strcmp(books[i].room,"triple")==0 || strcmp(books[i].room,"TRIPLE")==0) &&
                (strcmp(books[i].meal,"yes")==0 || strcmp(books[i].meal,"YES")==0))
            {
                /* for triple room and meal charges */
                totals[i].rate = 4800 * books[i].stay_day;
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = (int)(totals[i].rate * 0.15);
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;

            }    
            else
            {   /* no meal for triple */
                if ((strcmp(books[i].meal,"no")==0 || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"triple")==0 || strcmp(books[i].room,"TRIPLE")==0))
                {
                    totals[i].rate = 4800 * books[i].stay_day;
                    totals[i].buff = 0;
                    totals[i].tax = (int)(totals[i].rate * 0.15);
                    totals[i].total = totals[i].rate + totals[i].tax;
                }
            }



            /* QUADRUPLE ROOM */
            if ((strcmp(books[i].room,"quadruple")==0|| strcmp(books[i].room,"QUADRUPLE")==0) &&
                (strcmp(books[i].meal,"yes")==0 || strcmp(books[i].meal,"YES")==0))
            {
                /* for quadruple room and meal only */
                totals[i].rate = 6500 * books[i].stay_day;
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = (int)(totals[i].rate * 0.15);
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;
                
            }
            else  /* no meal for quadruple */
            {
                if ((strcmp(books[i].meal,"no")==0 || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"quadruple")==0 || strcmp(books[i].room,"QUADRUPLE")==0))
                {
                  totals[i].rate = 6500 * books[i].stay_day;
                  totals[i].buff = 0;
                  totals[i].tax = (int)(totals[i].rate * 0.15);
                  totals[i].total = totals[i].rate + totals[i].tax;
                }
            }



            /* QUIN ROOM */
            if ((strcmp(books[i].room,"quin")==0|| strcmp(books[i].room,"QUIN")==0) &&
                (strcmp(books[i].meal,"yes")==0 || strcmp(books[i].meal,"YES")==0))
            {
                /* for quin room and meal charges */
                totals[i].rate = 8000 * books[i].stay_day;
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = (int)(totals[i].rate * 0.15);
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;

            }

            else          /* for quin no meal */
            {
                if ((strcmp(books[i].meal,"no")==0 || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"quin")==0 || strcmp(books[i].room,"QUIN")==0))
                {
                    totals[i].rate = 8000 * books[i].stay_day;
                    totals[i].buff = 0;
                    totals[i].tax = (int)(totals[i].rate * 0.15);
                    totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;

                }
            }
            
            
            /* QUEEN ROOM */
            if ((strcmp(books[i].room,"queen")==0 || strcmp(books[i].room,"QUEEN")==0) &&
                (strcmp(books[i].meal,"yes")==0  || strcmp(books[i].meal,"YES")==0))
            {
                /* for queen room and meal charges */
                totals[i].rate = 7800 * books[i].stay_day;
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = (int)(totals[i].rate * 0.15);
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;

            }
            else      /* queen no meal */
            {
                if  ((strcmp(books[i].meal,"no")==0  || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"queen")==0 || strcmp(books[i].room,"QUEEN")==0))
                {
                    totals[i].rate = 7800 * books[i].stay_day;
                    totals[i].buff = 0;
                    totals[i].tax = (int)(totals[i].rate * 0.15);
                    totals[i].total = totals[i].rate + totals[i].tax ;
                }
            }
            

                /* showing the final bill */

            printf("**************INVOICE**************\n");
            printf("NAME         : %s \n", books[i].name);  /* for name */
            printf("CNIC NO      : %d\n",books[i].cnic); /* for cnic */
            printf("STAYING DAYS : %d\n",books[i].stay_day);  /* for staying days */
            printf("ROOM TYPE    : %s \n", books[i].room);  /* for room type */
            printf("BUFFEE PRICE : %d PKR\n", totals[i].buff); /* for buffee */
            printf("AMOUNT       : %d PKR\n",totals[i].rate);  /* for without tax amount */
            printf("TAX(15)      : %d PKR\n",totals[i].tax);  /* implementing the tax 15% */
            printf("TOTAL AMOUNT : %d PKR\n",totals[i].total);  /* showing final total */
            
            
            /* before removing the record, save the bill details to file */
            saveBillToFile(books[i], totals[i]);

            /* after billing the customer should be remove from the list */

            /* remove the record at index i by shifting left */
            for(int j=i;j<(count-1);j++)
            {
                books[j] = books[j+1];
            }

            /* decrement the in-memory count */
            count--;

            /* save updated records to file */
            saveData();

            printf("Thanks, We Received your payment. Please Come Again!!\n");

            /* return after processing one bill */
            return;
        }

        /* if loop continues, keep looking */
    }

    /* if we reach here, no user found with provided CNIC */
    printf("USER NOT EXIST!!\n");
}
/* ending function of bill function */




/* ------------------------------
   BUFFEE MENU FUNCTION
   ------------------------------ */

/* starting function of buffee items */
void foodmenu()
{
    printf("DAYS_INN BUFFEE MENU\n");
    printf("BREAK FAST\n");
    printf("1- Egg\n");
    printf("2- Bread\n");
    printf("3- Fresh Juice\n");
    printf("LUNCH\n");
    printf("1- Noodles\n");
    printf("2- Sandwithes\n");
    printf("3- Zinger\n");
    printf("4- Chicken Handi\n");
    printf("5- Flat Bread\n");
    printf("6- Coldrink\n");
    printf("DINNER\n");
    printf("1- Biryani\n");
    printf("2- Korma\n");
    printf("3- Pasta\n");
    printf("4- Icecream\n");
    printf("5- Mango Shake\n");
    printf("6- Flat Bread\n");

}
/* ending of buffee function items */






/* ------------------------------
   CONTACT / EMERGENCY FUNCTION
   ------------------------------ */


/* starting the function of function contact phone number */
void cont()
{
    printf("DAYS_INN HOTEL\n");
    printf("Emergency and Contact Number\n");
    printf("Phone Number 1  : 923322604529\n");
    printf("Phone Number 2  : 923212420701\n");
    printf("Phone Number 3  : 923313362880\n");
    printf("Landline Number : 021-34655614\n");
}

/* ending the function of contact number */





/* ------------------------------
   SERVICES / TIMINGS FUNCTION
   ------------------------------ */


/* function definition of services timing */
void services()
{
    printf("Swimming Timing : 9 am - 5 pm\n");
    printf("Gym Timing      : 24Hrs\n");
    printf("Buffet Timing   : 7am - 12pm\n");
    printf("Laundry Timing  : 9am - 5pm\n");
}

/* ending the function definition of function services timing */






/* ------------------------------
   TERMS / POLICY FUNCTION
   ------------------------------ */


/* starting the function the function for terms and policy */
void terms()
{
    printf("TERMS AND POLICY OF DAYS_INN HOTEL\n");
    printf("No Return Policy is allowed Once the Room is Booked\n");
    printf("Anything Broken or Misplaced then customer faced penalty\n");
    printf("Any Misbehavoir with Staff and Genetorial Management has right to cancel reservation\n");
}

/* ending the function of terms and policy. */





/* ------------------------------
   PRICE FUNCTION
   ------------------------------ */


/* function definition for price checking */
void price()
{
    printf("\nROOM CATOGARIES:\n");
    printf("1- SINGLE        : 2200 PKR\n");
    printf("2- DOUBLE        : 3500 PKR\n");
    printf("3- TRIPLE        : 4800 PKR\n");
    printf("4- QUADRUPLE     : 6500 PKR\n");
    printf("5- QUIN          : 8000 PKR\n");
    printf("6- QUEEN         : 7800 PKR\n");
}
/* ending the function definition of price viewing */





/* ------------------------------
   MENU PRINTING FUNCTION
   ------------------------------ */


/* function definition for printing menu */
void menu()
{
    printf("\nHello Dear, From DAYS_INN HOTEL\n");
    printf("1- Book a Room\n");
    printf("2- Price Of Rooms\n");
    printf("3- View Customer Details\n");
    printf("4- Check Room Availability\n");
    printf("5- Remove Customer\n");
    printf("6- Generate Bill\n");
    printf("7- All Customer Details\n");
    printf("8- Services Timing\n");
    printf("9- Terms and Policy\n");
    printf("10- Contact Information\n");
    printf("11- Buffee Items\n");
    printf("12- Exit\n");
    printf("Please Select From The Above Options.. : ");
}



/* ENDING THE FUNCTION DEFINITION OF MAIN FUNCTION */

