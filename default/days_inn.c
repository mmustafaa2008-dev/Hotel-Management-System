#include<stdio.h>
#include<string.h>
#include<math.h>
// making the limit as a macro
#define limit 20
void menu(); // function for printing menu
void book(); // for booking room
void price();  // for checking price
void view();  // for view customer detail
void checkroom();  // for checking room availability
void del();  // for removing old customer // for staff only 
void bill();  // for generating bill
void all(); // only for staff who can see all the customer details // for staff only pass required
void services(); // for showing the services provided by the hotel
void terms();  // for showing terms and condition of HOTEL
void cont();  // for all emergency and contact number
void foodmenu();  // for buffee

// making pass as a global variable
int pass = 2008;

// structure for questioning
struct hotel
{
    char name[100];
    int member;
    int stay_day;
    char room[50];
    int cnic;
    char meal[50];
};

struct hotel books[limit];
int count=0;

// structure for bill
struct bills
{

int rate; // multiplying the constant price with total staying days
int buff; // this for storing the buffee price * total member * staying days
int tax;  // implementing the 15% tax on the total price
int total; // for total price

};

struct bills totals[limit];


// making function for file handling

void savedata();
void bill_txt(struct bills b,struct hotel h);

// file function handling ending here


int main()
{
    int choice;     // initializing choice for choicing the option below
    do
    {   
        menu();
        scanf("%d",&choice);
        switch (choice)
        {        
            case 1:
            book();  // book function calling
            break;
        
            case 2:
            price();  // price function calling
            break;

            case 3:
            view();  // view function calling
            break;

            case 4:
            checkroom();  // check room availability function calling
            break;
            
            case 5:
            del();  // delete function calling
            break;

            case 6:
            bill();  // billing function calling
            break;


            case 7:
            all();  // all customer showing function calling
            break;

            case 8:
            services();  // all services function calling
            break;

            case 9:
            terms();  // showing terms and conditon of the hotel
            break;

            case 10:
            cont();  // showing the contact number of the hotel management
            break;

            case 11:
            foodmenu();  // showing the menu of the buffee
            break;

            default:
            return 0;  // for exit

        }
    }while(choice<= 11);
}



// function definition for booking room using structure for storing different datatype of variable;
void book ()
{
    if (count >= limit)
    {
        printf("No Vacant Room is avalaible\n");
        return ;
    }

    // for unique cnic 
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
        return ;
    }
    else
    {
        printf("%s your Room %d have been booked for %d days in DAYS_INN HOTEL.. Enjoy your vacations\n", books[count].name, count+1 ,books[count].stay_day);
        count++;
        savedata();
    }
    
    
}
// ending the function definition of function booking




// function definition for staff to check all the rooms

void all()
{
    int pas;
    printf("Enter Your Code : ");
    scanf("%d",&pas);

    if (pas == pass)
    {
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

// function definition ending here




// function definition for viewing the customer details

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
// ENDING THE VIEW FUNCTION




// NOW MAKING THE FUNCTION FOR CHECKING THE ROOM AVAILABILITY
void checkroom()
{
    int select;
    if (count >= limit)
    {
        printf("All Rooms are booked, Sorry! for inconvenience\n");
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

// Ending the function definition




// DELETE FUNCTION DEFINITION
void del()
{
    int pas;
    printf("Enter Credential Pass key : ");
    scanf("%d",&pas);
    if (pas == pass)
    {
        if (count == 0)
        {
            printf("No Customer to Remove\n");
            return ;
        }
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
            savedata();
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

// ENDING FUNCTION DEFINITION





// Function definition for Bill

void bill() // add condition that generate option is not available untill room is booked // 
{
    int id;
    printf("Enter Your CNIC Number : ");
    scanf("%d",&id);
    for(int i=0;i<count;i++)
    {
        if (id == books[i].cnic)
        {
            if ((strcmp(books[i].room,"single")==0 || strcmp(books[i].room, "SINGLE")==0) && (strcmp(books[i].meal,"yes")==0 || strcmp(books[i].meal,"YES")==0))
            {   //both meal and single room charges
                totals[i].rate = 2200 * books[i].stay_day;  // room rate for total staying days
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = totals[i].rate * 0.15;
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;

            }

                else  // only for single room payment
                {
                if ((strcmp(books[i].meal,"no")==0 || strcmp(books[i].meal,"NO")==0) && strcmp(books[i].room,"SINGLE")==0 || strcmp(books[i].room,"single")==0)
                {
                    totals[i].rate = 2200 * books[i].stay_day;
                    totals[i].tax = totals[i].rate * 0.15;
                    totals[i].total = totals[i].rate + totals[i].tax;
                    totals[i].buff = 0;
                }
                }
        

            if ((strcmp(books[i].room,"double")==0 || strcmp(books[i].room,"DOUBLE")==0) && (strcmp(books[i].meal,"yes")==0 || strcmp(books[i].meal,"YES")==0))

            // for both meal and double room payment
            {
                totals[i].rate = 3500 * books[i].stay_day;
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = totals[i].rate * 0.15;
                totals[i].total = totals[i].rate + totals[i].tax; + totals[i].buff;
                
            }

                else
                {    // only for double room payment
                if ((strcmp(books[i].meal,"no")==0 || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"double")==0 || strcmp(books[i].room,"DOUBLE")==0))
                {
                    totals[i].rate = 3500 * books[i].stay_day;
                    totals[i].buff = 0;
                    totals[i].tax = totals[i].rate * 0.15;
                    totals[i].total = totals[i].rate + totals[i].tax;
                }
                }



             if ((strcmp(books[i].room,"triple")==0 || strcmp(books[i].room,"TRIPLE")==0) && (strcmp(books[i].meal,"yes")==0 || strcmp(books[i].meal,"YES")==0))

              // for triple room and meal charges
            {
                totals[i].rate = 4800 * books[i].stay_day;
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = totals[i].rate * 0.15;
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;

            }    
                else
                {   // for meal only
                if ((strcmp(books[i].meal,"no")==0 || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"triple")==0 || strcmp(books[i].room,"TRIPLE")==0))
                {
                    totals[i].rate = 4800 * books[i].stay_day;
                    totals[i].buff = 0;
                    totals[i].tax = totals[i].rate * 0.15;
                    totals[i].total = totals[i].rate + totals[i].tax;
                }
                }

            

            if ((strcmp(books[i].room,"quadruple")==0|| strcmp(books[i].room,"QUADRUPLE")==0) && (strcmp(books[i].meal,"yes")==0 || strcmp(books[i].meal,"YES")==0))

            // for quadruple room and meal only
            {
                totals[i].rate = 6500 * books[i].stay_day;
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = totals[i].rate * 0.15;
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;
                
            }
                else  // for meal only
                {
                if ((strcmp(books[i].meal,"no")==0 || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"quadruple")==0 || strcmp(books[i].room,"QUADRUPLE")==0))
                {
                  totals[i].rate = 6500 * books[i].stay_day;
                  totals[i].buff = 0;
                  totals[i].tax = totals[i].rate * 0.15;
                  totals[i].total = totals[i].rate + totals[i].tax;
                }
                }

            if ((strcmp(books[i].room,"quin")==0|| strcmp(books[i].room,"QUIN")==0) && (strcmp(books[i].meal,"yes")==0 || strcmp(books[i].meal,"YES")==0))

             // for quin room and meal charges
            {
                totals[i].rate = 8000 * books[i].stay_day;
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = totals[i].rate * 0.15;
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;

            }

                else          // for meal only
                {
                if ((strcmp(books[i].meal,"no")==0 || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"quin")==0 || strcmp(books[i].room,"QUIN")==0))
                {
                    totals[i].rate = 8000 * books[i].stay_day;
                    totals[i].buff = 0;
                    totals[i].tax = totals[i].rate * 0.15;
                    totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;

                }
                }
            
            
            if ((strcmp(books[i].room,"queen")==0 || strcmp(books[i].room,"QUEEN")==0) && (strcmp(books[i].meal,"yes")==0  || strcmp(books[i].meal,"YES")==0))

              // for queen room and meal charges
            {
                totals[i].rate = 7800 * books[i].stay_day;
                totals[i].buff = 3000 * books[i].member * books[i].stay_day;
                totals[i].tax = totals[i].rate * 0.15;
                totals[i].total = totals[i].rate + totals[i].tax + totals[i].buff;

            }
                else      // for meal only
                {
                if  ((strcmp(books[i].meal,"no")==0  || strcmp(books[i].meal,"NO")==0) && (strcmp(books[i].room,"queen")==0 || strcmp(books[i].room,"QUEEN")==0))
                {
                    totals[i].rate = 7800 * books[i].stay_day;
                    totals[i].buff = 0;
                    totals[i].tax = totals[i].rate * 0.15;
                    totals[i].total = totals[i].rate + totals[i].tax ;
                }
                }
            

                // showing the final bill 

            printf("**************INVOICE**************\n");
            printf("NAME         : %s \n", books[i].name);  // for name
            printf("CNIC NO      : %d\n",books[i].cnic); // for cnic
            printf("STAYING DAYS : %d\n",books[i].stay_day);  // for staying days
            printf("ROOM TYPE    : %s \n", books[i].room);  // for room type
            printf("BUFFEE PRICE : %d PKR\n", totals[i].buff); // for buffee
            printf("AMOUNT       : %d PKR\n",totals[i].rate);  // for without tax amount
            printf("TAX(15)      : %d PKR\n",totals[i].tax);  // implementing the tax 15%
            printf("TOTAL AMOUNT : %d PKR\n",totals[i].total);  // showing final total
            
            // saving the bill to the text file
            bill_txt(totals[i], books[i]);

            
            // after billing the customer should be remove from the list
            
            printf("Thanks %s We Recieved your payment, Please Come Again!!\n", books[i].name);
            for(int j=i;j<(count-1);j++)
            {
                books[i] = books[i+1];
            }
            count--;
            savedata();
        }

        else // if user cnic id doesnot match........
        {
            printf("USER NOT EXIST!!\n");
        }

    }
}
// ending function of bill function




// starting function of buffee items
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
// ending of buffee function items




// starting the function of function contact phone number
void cont()
{
    printf("DAYS_INN HOTEL\n");
    printf("Emergency and Contact Number\n");
    printf("Phone Number 1  : 923322604529\n");
    printf("Phone Number 2  : 923212420701\n");
    printf("Phone Number 3  : 923313362880\n");
    printf("Landline Number : 021-34655614\n");
}

// ending the function of contact number




// function definition of services timing
void services()
{
    printf("Swimming Timing : 9 am - 5 pm\n");
    printf("Gym Timing      : 24Hrs\n");
    printf("Buffet Timing   : 7am - 12pm\n");
    printf("Laundry Timing  : 9am - 5pm\n");
}

// ending the function definition of function services timing





// starting the function the function for terms and policy
void terms()
{
    printf("TERMS AND POLICY OF DAYS_INN HOTEL\n");
    printf("No Return Policy is allowed Once the Room is Booked\n");
    printf("Anything Broken or Misplaced then customer faced penalty\n");
    printf("Any Misbehavoir with Staff and Genetorial Management has right to cancel reservation\n");
}

// ending the function of terms and policy.




// function definition for price checking
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
// ending the function definition of price viewing




// function definition for printing menu
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


// ENDING THE FUNCTION DEFINITION OF MAIN FUNCTION


void savedata()
{
    FILE *file = fopen("data.txt", "w");
    if(file != NULL)
        {
            for(int i=0;i<count;i++)
            {
                fprintf(file, "Room Number   : %d\n", i+1);
                fprintf(file, "Name          : %s\n",books[i].name);
                fprintf(file, "Member        : %d\n",books[i].member);
                fprintf(file, "Staying days  : %d\n",books[i].stay_day);
                fprintf(file, "Cnic          : %d\n",books[i].cnic);
                fprintf(file, "Room Type     : %s\n",books[i].room);
                fprintf(file, "Buffee        : %s\n",books[i].meal);
                fprintf(file, "\n");
            }
            fclose(file);
        }
}


void bill_txt(struct bills b, struct hotel h)
{
    FILE *file = fopen("bill.txt", "a");
    if(file != NULL)
    {
        fprintf(file, "***********INVOICE***********\n");
        fprintf(file, "NAME         : %s \n", h.name);  // for name
        fprintf(file, "CNIC NO      : %d\n",h.cnic); // for cnic
        fprintf(file, "STAYING DAYS : %d\n",h.stay_day);  // for staying days
        fprintf(file, "ROOM TYPE    : %s \n", h.room);  // for room type
        fprintf(file, "BUFFEE PRICE : %d PKR\n", b.buff); // for buffee
        fprintf(file, "AMOUNT       : %d PKR\n",b.rate);  // for without tax amount
        fprintf(file, "TAX(15)      : %d PKR\n",b.tax);  // implementing the tax 15%
        fprintf(file, "TOTAL AMOUNT : %d PKR\n",b.total);

        fclose(file);
    }
}