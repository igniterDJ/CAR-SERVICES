#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define numcust 10
#define repno 10
int ind_cost[10],required[10],slno=0,recp=2354;
float cartax=0.5;
//Database of customer
struct customer{
    char cust_name[30];
    char cust_carno[10];
    int cust_time;
    int cust_cday;
    int cust_cmonth;
    int cust_dday;
    int cust_dmonth;
    int cust_cost;
    int cust_required[10];
    int cust_indcost[10];
};
struct customer cust[10];
//Database of types of repairs available
struct repair{
    int repair_id;
    char repair_name[100];
    int repair_time;
    int repair_cost[3];
};
struct repair repser[10];
void printreh(int n)
{
    int i;
    if(n==0)
        for(i=0;i<103;i++)
        {
            printf("_");
        }
    else
        for(i=0;i<103;i++)
        {
            printf("-");
        }
    printf("\n");
}
//To print bill
void print_bill(char name[30],char no[10],int ccost,int exescount,int extracost,int bill)
{
    float service_tax,rcost;
    int i,lenght,j;
    service_tax=cartax*ccost/100;
    rcost=ccost+service_tax;

    printreh(0);
    if(bill==1)
        printf("                                     ESTIMATED CAR BILL\n");
    else
        printf("                                         CAR BILL\n");
    printreh(1);
    printf("   HSD car services\n");
    printf("   HSD street\n");
    printf("   Vellore 632001\n");
    printf("                                                                              Receipt no :  %d\n",recp);
    printf("                                                                            Customer Name:  %s\n",name);
    printf("                                                                               Vehicle No:  %s\n",no);
    printreh(0);
    printf("   SERVICE DESCRIPTION                                                                      RS AMOUNT\n");
    printreh(1);
    for(i=0;i<numcust;i++)
    {
        if(repser[required[i]].repair_cost[0]!=-1 && ind_cost[required[i]]!=0)
        {
            lenght=strlen(repser[required[i]].repair_name);
            for(j=0;j<44-lenght;j++)
            {
                strcat(repser[required[i]].repair_name," ");
            }
            printf("   %s                                              %d\n",repser[required[i]].repair_name,ind_cost[required[i]]);
        }
    }
    if(exescount==1)
    {
        printf("   Extra repairs cost                                                                        %d",extracost);
    }
    printf("\n\n\n");
    printreh(1);
    printf("                                                                      AMOUNT                 %d\n",ccost);
    printf("                                                                SERVICE TAX                  %.2f\n",service_tax);
    printreh(1);
    printf("                                                                TOTAL AMOUNT              RS %.2f\n",rcost);
    printreh(1);
    printf("                                         Please come again\n");
    printreh(0);
}

void recprint(int p)
{
    if(p<9)
    {
        printf("id - %d  | service - %s\n",repser[p].repair_id,repser[p].repair_name);
        p++;
        recprint(p);
    }
    else
    {
        printf("id - %d | service - %s\n",repser[p].repair_id,repser[p].repair_name);
    }

}

//For giving car to service
int Car_service()
{
    int i,j,z,x=10,dist,total_time=0,total_cost=0,grade,receipt,jcount,date;
    for(i=0;i<repno;i++)
    {
        if(cust[i].cust_cmonth!=0)
            slno++;
    }


    for(i=0;i<repno;i++)
    {
        required[i]=-1;
    }
    slno+=2;


    do
    {
        printf("Enter date in the format of MMDD or MDD: ");
        scanf("%d",&date);
        cust[slno].cust_cmonth=date/100;
        cust[slno].cust_cday=date-(100*cust[slno].cust_cmonth);
    }while(cust[slno].cust_cmonth>12 || cust[slno].cust_cmonth<=0 || cust[slno].cust_cday>31 || cust[slno].cust_cday<1);
    printf("Enter your name:");
    scanf(" %[^\n]%*c",cust[slno].cust_name);
    printf("Enter your car number:");
    scanf(" %s",cust[slno].cust_carno);

    printf("Total distance covered by the car (else '0')\n");
    scanf("%d",&z);
    if(z>=0)
    {
        dist=z;
        printf("As your car has traveled an approximate distance of %d KM ",dist);

        if(z>3000)
        {
            printf("we recommend you to take this services\n");
            printf("%s\n",repser[6].repair_name);
            if(5000<=dist)
            {
                printf("%s\n",repser[3].repair_name);
                printf("%s\n",repser[7].repair_name);
                if(10000<=dist)
                {
                    printf("%s\n",repser[1].repair_name);
                    (20000<=dist)?(printf("%s\n",repser[5].repair_name)):(printf("\n"));
                }
            }
        }
        else
        {
            printf("There are no recommended repairs\n");
        }

    }
    printf("\nThese are the services available at our showroom\n\n");

    recprint(0);

    printf("According to the given ID's for each type of service select what services does your car required\n");
    printf("After all required services are given please enter -1\n");

    for(i=0;i<repno;i++)
    {
        jcount=0;
        printf("Enter required repair id\n");
        scanf("%d",&z);
        for(j=0;j<x;j++)
        {
            if(required[j]==z-1)
            {
                jcount=1;
            }
	    }
	    if(jcount==0)
	    {
	        if(z!=-1)
	        {
	            required[i]=z-1;
		    }
		    if(z==-1)
		    {
		        break;
		    }
	    }
	    if(jcount==1)
	    {
	        printf("this is already taken\n");
	        i--;
	    }

    }

    for(i=0;i<repno;i++)
    {
        if(required[i]!=-1)
        {
            if(repser[required[i]].repair_cost[1]!=0)
            {
                do
                {
                    printf("enter which grade quality do you want for %s\n",repser[required[i]].repair_name);
                    printf("There are three grades 1,2,3 select one , 1 is the best grade,0 if you want to cancel\n");
                    scanf("%d",&grade);
                    if(grade==1 || grade==2 || grade ==3)
                    {
                        grade=grade-1;
                        total_cost+=repser[required[i]].repair_cost[grade];
                        ind_cost[required[i]]=repser[required[i]].repair_cost[grade];
                    }
                }while(grade!=0 && grade!=1 && grade!=2);
            }
            else
            {
                total_cost+=repser[required[i]].repair_cost[0];
                ind_cost[required[i]]=repser[required[i]].repair_cost[0];
            }
        }
    }

    for(i=0;i<repno;i++)
    {
        if(required[i]!=-1)
        {
            total_time+=repser[required[i]].repair_time;
        }

    }

    if(total_time%24==0)
    {
        total_time=(total_time/24);
    }
    else
    {
        total_time=(total_time/24)+1;
    }

    if(total_time==1)
    {
        printf("your repairs will be completed in %d day\n",total_time);
    }
    else
    {
        printf("your repairs will be completed by %d days\n",total_time);
    }
    cust[slno].cust_time=total_time;
    cust[slno].cust_cost=total_cost;
    printf("you can pay the bill when you come to take your car\n");
    printf("If you want to print estimated receipt enter 1 else enter 0\n");
    scanf("%d",&receipt);

    if(receipt==1)
    {
        print_bill(cust[slno].cust_name,cust[slno].cust_carno,total_cost,0,0,1);

    }
    if(receipt==0)
    {
        printf("total estimated cost for repair is %d\n",total_cost);
    }

    printf("If there are any extra repairs we will inform you when you come again\n\n\n");

    for(i=0;i<numcust;i++)
    {
        cust[slno].cust_required[i]=required[i];
        cust[slno].cust_indcost[i]=ind_cost[i];
    }

    return(0);
}
//for taking car after service
int Car_return()
{
    int rcar_time,extra,extrarep,i,tcount=0,j;
    printf("Welcome back\nPlease enter your car no\n");
    char rcar_no[10];
    scanf("%s",rcar_no);
    for(i=0;i<numcust;i++)
    {
        if(strcmp(cust[i].cust_carno,rcar_no)==0 && cust[i].cust_dday==0)
        {
            int date;
            printf("Hi Mr/Ms %s\n",cust[i].cust_name);
            do
            {
                printf("Enter date in the format MMDD or MDD:\n");
                scanf("%d",&date);
                cust[i].cust_dmonth=date/100;
                cust[i].cust_dday=date-(100*cust[i].cust_dmonth);
            }while(cust[i].cust_dmonth<1 || cust[i].cust_dmonth>12 || cust[i].cust_dday<0 || cust[i].cust_dday>31);

            if(cust[i].cust_dmonth-cust[i].cust_cmonth==0)
            {
                rcar_time=cust[i].cust_dday-cust[i].cust_cday;
            }
            else
            {
                rcar_time=30-(cust[i].cust_cday-cust[i].cust_dday);
            }
            if(rcar_time>=cust[i].cust_time)
            {
                for(j=0;j<10;j++)
                {
                    required[j]=cust[i].cust_required[j];
                    ind_cost[j]=cust[i].cust_indcost[j];
                }
                printf("Your work has been completed\n");
                printf("Give 1 if any extra repairs has been done else enter 0\n");
                scanf("%d",&extra);
                if(extra == 1)
                {
                    printf("What is the total cost if extra repairs\n");
                    scanf("%d",&extrarep);
                    cust[i].cust_cost+=extrarep;
                    print_bill(cust[i].cust_name,cust[i].cust_carno,cust[i].cust_cost,extra,extrarep,0);
                }
                if(extra == 0)
                {
                    printf("This is the bill\n");
                    print_bill(cust[i].cust_name,cust[i].cust_carno,cust[i].cust_cost,0,0,0);
                }

            }
            else
            {
                cust[i].cust_dday=0;cust[i].cust_dmonth=0;
                printf("All your work has not completed\nPlease come after %d day\n\n\n",(cust[i].cust_time - rcar_time));
            }
            tcount=1;
            break;
        }
    }

    if(tcount==0)
    {
        printf("A car with car number %s is not with us\n\n\n",rcar_no);
    }

    return 0;

}

void printrecphead(int flag)
{

    printreh(0);
    if(flag==0)
        printf("                                    DELEVERED CARS REPORT\n");
    if(flag==1)
        printf("                                  NOT-DELEVERED CARS REPORT\n");
    printreh(1);
    printf("   Date                Customer Name                    Car Number              Total Cost \n");
    printreh(1);
}

void printreport(int day,int month,char name[30],char carno[10],int cost)
{

    int index1,index2,index3;
    char carnoo[10];char namee[30];
    strcpy(carnoo,carno);strcpy(namee,name);
    index1= strlen(namee);
    index2= strlen(carnoo);
    index1=29-index1;
    index2=9-index2;
    for(index3=0;index3<index1;index3++)
    {
        strcat(namee," ");
    }
    for(index3=0;index3<index2;index3++)
    {
        strcat(carnoo," ");
    }

    printf("   %d-%d               %s    %s               %.2f  \n",day,month,namee,carnoo,cost*(1+cartax/100));
}

void rip1()
{
    int date,day,month,i,dnd,tcount=0;
    printf("Enter 0 for delivered 1 of not delivered list\n");
    scanf("%d",&dnd);
    if(dnd==1)
    {
        do
        {
            printf("Enter date in the format of MMDD or MDD: ");
            scanf("%d",&date);
            month=date/100;
            day=date-(100*month);
        }while(month<1 || month >12 || day<1 || day>31);

        for(i=0;i<numcust;i++)
        {
            if(day==cust[i].cust_cday && month==cust[i].cust_cmonth && cust[i].cust_dday==0)
            {
                if(tcount==0)
                {
                    tcount=1;
                    printrecphead(dnd);
                }
                printreport(cust[i].cust_cday,cust[i].cust_cmonth,cust[i].cust_name,cust[i].cust_carno,cust[i].cust_cost);
            }
        }

    }
    if(dnd==0)
    {
        do
        {
            printf("Enter date in the format of MMDD or MDD: ");
            scanf("%d",&date);
            month=date/100;
            day=date-(100*month);
        }while(month<1 || month >12 || day<1 || day>31);

        for(i=0;i<numcust;i++)
        {
            if(day==cust[i].cust_dday && month==cust[i].cust_dmonth)
            {
                if(tcount==0)
                {
                    tcount=1;
                    printrecphead(dnd);
                }
                printreport(cust[i].cust_cday,cust[i].cust_cmonth,cust[i].cust_name,cust[i].cust_carno,cust[i].cust_cost);
            }
        }
    }
    if(tcount==0)
    {
        printf("No data available\n\n");
    }
}

void rip2()
{
    int date,day1,day2,month1,month2,i,dnd,tcount=0;
    printf("Enter 0 for delivered 1 of not delivered list\n");
    scanf("%d",&dnd);
    do
    {
        printf("Enter first date in the format of MMDD or MDD: ");
        scanf("%d",&date);
        month1=date/100;
        day1=date-(100*month1);
    }while(month1>12 || month1 <1 || day1>31 || day1<1);
    do
    {
        printf("Enter last date in the format of MMDD or MDD: ");
        scanf("%d",&date);
        month2=date/100;
        day2=date-100*month2;
    }while(month2>12 || month2 <1 || day2>31 || day2<1);
    if(dnd==1)
    {
        for(i=0;i<numcust;i++)
        {
            if(day1<=cust[i].cust_cday && month1<=cust[i].cust_cmonth && day2>=cust[i].cust_cday && month2>=cust[i].cust_cmonth && cust[i].cust_dday==0)
            {
                if(tcount==0)
                {
                    tcount=1;
                    printrecphead(dnd);
                }
                printreport(cust[i].cust_cday,cust[i].cust_cmonth,cust[i].cust_name,cust[i].cust_carno,cust[i].cust_cost);
            }
        }
    }
    if(dnd==0)
    {
        for(i=0;i<numcust;i++)
        {
            if(day1<=cust[i].cust_dday && month1<=cust[i].cust_dmonth && day2>=cust[i].cust_dday && month2>=cust[i].cust_dmonth)
            {
                if(tcount==0)
                {
                    tcount=1;
                    printrecphead(dnd);
                }
                printreport(cust[i].cust_cday,cust[i].cust_cmonth,cust[i].cust_name,cust[i].cust_carno,cust[i].cust_cost);
            }
        }
    }
    if(tcount==0)
    {
        printf("No data available\n\n");
    }
}



void reports()
{
    int rip;
    printf("1) Press 1 if you want day wise reports\n2) Press 2 if you want reports between two days\n");
    scanf("%d",&rip);
    switch(rip)
    {
        case 1:
            rip1();
            break;
        case 2:
            rip2();
            break;
    }

}
int Car_services()
{
    int choice,i,kn=0;
    FILE* rfile=fopen("repairlist.txt","r");
    if(rfile==NULL)
    {
        printf("not abel to open file");
        return 2;
    }
    char buffer[200];
    fgets(buffer,200,rfile);
    while(!feof(rfile))
    {
        struct repair *p = repser +kn;
        sscanf(buffer,"%d %d  %d  %d  %d  %s\n",&p->repair_id,&p->repair_time,&p->repair_cost[0],&p->repair_cost[1],&p->repair_cost[2],&p->repair_name);
        fgets(buffer,200,rfile);kn++;
    }





    FILE * custfile=fopen("customer_data.txt","r");
    if(custfile==NULL)
    {
        printf("cant open file\n");
        return (1);
    }
    char buff[200];
    fgets(buff,200,custfile);
    while(!feof(custfile))
    {
        struct customer *p=cust + i;
        sscanf(buff ,"%d %d %d %d %d %d %s %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",&p->cust_time,&p->cust_cday,&p->cust_cmonth,&p->cust_dday,&p->cust_dmonth,&p->cust_cost,&p->cust_carno,&p->cust_name,&p->cust_required[0],&p->cust_required[1],&p->cust_required[2],&p->cust_required[3],&p->cust_required[4],&p->cust_required[5],&p->cust_required[6],&p->cust_required[7],&p->cust_required[8],&p->cust_required[9],&p->cust_indcost[0],&p->cust_indcost[1],&p->cust_indcost[2],&p->cust_indcost[3],&p->cust_indcost[4],&p->cust_indcost[5],&p->cust_indcost[6],&p->cust_indcost[7],&p->cust_indcost[8],&p->cust_indcost[9]);
        fgets(buff,200,custfile);
        i++;
    }
    fclose(custfile);

    printf("1) Enter 1 for car service\n2) Enter 2 for car delivery\n3) Enter 3 for reports\n");
    scanf("%d",&choice);
    switch(choice)
        {
        case 1:
            Car_service();
            recp++;
            break;
        case 2:
            Car_return();
            break;recp++;
        case 3:
            reports();
            break;
        }



    FILE *write=fopen("customer_data.txt","w");
    if(write==NULL)
    {
        printf("error occurred");
        return (1);
    }
    for(i=0;i<numcust;i++)
    {
        if(cust[i].cust_time==1 || cust[i].cust_time==2 || cust[i].cust_time==3 || cust[i].cust_time==4)
            fprintf(write,"%d %d %d %d %d %d %s %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",cust[i].cust_time,cust[i].cust_cday,cust[i].cust_cmonth,cust[i].cust_dday,cust[i].cust_dmonth,cust[i].cust_cost,cust[i].cust_carno,cust[i].cust_name,cust[i].cust_required[0],cust[i].cust_required[1],cust[i].cust_required[2],cust[i].cust_required[3],cust[i].cust_required[4],cust[i].cust_required[5],cust[i].cust_required[6],cust[i].cust_required[7],cust[i].cust_required[8],cust[i].cust_required[9],cust[i].cust_indcost[0],cust[i].cust_indcost[1],cust[i].cust_indcost[2],cust[i].cust_indcost[3],cust[i].cust_indcost[4],cust[i].cust_indcost[5],cust[i].cust_indcost[6],cust[i].cust_indcost[7],cust[i].cust_indcost[8],cust[i].cust_indcost[9]);
    }
    fclose(write);

        return (0);
}


struct BRV{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct WRV{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct Creta{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct Venue{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct Compass{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct Seltos{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct Sonet{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct X2{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct Boleno{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct C220{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct panemera{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct A6{
    int a;
    char car[20];
  	char com[10];
	char t[20];
	int c;
};
struct vento{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct glanza{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct continental{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct evoque{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
struct ff{
    int a;
    char car[20];
    char com[10];
	char t[20];
	int c;
};
New_car(){
  	FILE *fp;
    char lines;
    fp = fopen("car.txt", "w+");
    if(fp==NULL){
        printf("\\Error cannot open file");
        exit(1);
    }
    struct BRV b;
    strcpy(b.car,"BRV");
    strcpy(b.com,"Honda");
    strcpy(b.t,"SUV");
    b.c = 1000000;
    b.a = 1;
    printf("%d\n", b.a);
    printf("%s\n", b.car);
    printf("%s\n", b.com);
    printf("%s\n", b.t);
    printf("%d\n", b.c);
    printf("\n");

    struct WRV w;
    strcpy(w.car,"WRV");
    strcpy(w.com,"Honda");
    strcpy(w.t,"SUV");
    w.c = 1400000;
    w.a = 2;
    printf("%d\n", w.a);
    printf("%s\n", w.car);
    printf("%s\n", w.com);
    printf("%s\n", w.t);
    printf("%d\n", w.c);
    printf("\n");

    struct Creta c1;
    strcpy(c1.car,"Creta");
    strcpy(c1.com,"Hyundai");
    strcpy(c1.t,"SUV");
    c1.c = 1100000;
    c1.a = 3;
    printf("%d\n", c1.a);
    printf("%s\n", c1.car);
    printf("%s\n", c1.com);
    printf("%s\n", c1.t);
    printf("%d\n", c1.c);
    printf("\n");

    struct Venue v;
    strcpy(v.car,"Venue");
    strcpy(v.com,"Hyundai");
    strcpy(v.t,"SUV");
    v.c = 800000;
    v.a = 4;
    printf("%d\n", v.a);
    printf("%s\n", v.car);
    printf("%s\n", v.com);
    printf("%s\n", v.t);
    printf("%d\n", v.c);
    printf("\n");

    struct Compass s;
    strcpy(s.car,"Compass");
    strcpy(s.com,"Jeep");
    strcpy(s.t,"SUV");
    s.c = 1700000;
    s.a = 5;
    printf("%d\n", s.a);
    printf("%s\n", s.car);
    printf("%s\n", s.com);
    printf("%s\n", s.t);
    printf("%d\n", s.c);
    printf("\n");

    struct Seltos o;
    strcpy(o.car,"Seltos");
    strcpy(o.com,"Kia");
    strcpy(o.t,"SUV");
    o.c = 1000000;
    o.a = 6;
    printf("%d\n", o.a);
    printf("%s\n", o.car);
    printf("%s\n", o.com);
    printf("%s\n", o.t);
    printf("%d\n", o.c);
    printf("\n");

    struct X2 x;
    strcpy(x.car,"X2");
    strcpy(x.com,"BMW");
    strcpy(x.t,"SUV");
    x.c = 4500000;
    x.a = 7;
    printf("%d\n", x.a);
    printf("%s\n", x.car);
    printf("%s\n", x.com);
    printf("%s\n", x.t);
    printf("%d\n", x.c);
    printf("\n");

    struct Boleno n;
    strcpy(n.car,"Boleno");
    strcpy(n.com,"Suzuki");
    strcpy(n.t,"Hatchback");
    n.c = 700000;
    n.a = 8;
    printf("%d\n", n.a);
    printf("%s\n", n.car);
    printf("%s\n", n.com);
    printf("%s\n", n.t);
    printf("%d\n", n.c);
    printf("\n");

    struct C220 me;
    strcpy(me.car,"C220");
    strcpy(me.com,"Mercedes");
    strcpy(me.t,"Sedan");
    me.c = 4500000;
    me.a = 9;
    printf("%d\n", me.a);
    printf("%s\n", me.car);
    printf("%s\n", me.com);
    printf("%s\n", me.t);
    printf("%d\n", me.c);
    printf("\n");

    struct panemera d;
    strcpy(d.car,"Panemera");
    strcpy(d.com,"Porsche");
    strcpy(d.t,"hatchback");
    d.c = 23000000;
    d.a = 10;
    printf("%d\n", d.a);
    printf("%s\n", d.car);
    printf("%s\n", d.com);
    printf("%s\n", d.t);
    printf("%d\n", d.c);
    printf("\n");

    struct A6 z1;
    strcpy(z1.car,"A6");
    strcpy(z1.com,"Audi");
    strcpy(z1.t,"Sedan");
    z1.c = 5600000;
    z1.a = 11;
    printf("%d\n", z1.a);
    printf("%s\n", z1.car);
    printf("%s\n", z1.com);
    printf("%s\n", z1.t);
    printf("%d\n", z1.c);
    printf("\n");

    struct vento f;
    strcpy(f.car,"Vento");
    strcpy(f.com,"Volkswagen");
    strcpy(f.t,"Sedan");
    f.c = 1500000;
    f.a = 12;
    printf("%d\n", f.a);
    printf("%s\n", f.car);
    printf("%s\n", f.com);
    printf("%s\n", f.t);
    printf("%d\n", f.c);
    printf("\n");

    struct glanza m;
    strcpy(m.car,"Glanza");
    strcpy(m.com,"Toyota");
    strcpy(m.t,"hatchback");
    m.c = 1100000;
    m.a = 13;
    printf("%d\n", m.a);
    printf("%s\n", m.car);
    printf("%s\n", m.com);
    printf("%s\n", m.t);
    printf("%d\n", m.c);
    printf("\n");

    struct continental aa;
    strcpy(aa.car,"Continental");
    strcpy(aa.com,"Bentley");
    strcpy(aa.t,"Sedan");
    aa.c = 4000000;
    aa.a = 14;
    printf("%d\n", aa.a);
    printf("%s\n", aa.car);
    printf("%s\n", aa.com);
    printf("%s\n", aa.t);
    printf("%d\n", aa.c);
    printf("\n");

    struct evoque q;
    strcpy(q.car,"Evoque");
    strcpy(q.com,"Land Rover");
    strcpy(q.t,"SUV");
    q.c = 5600000;
    q.a = 15;
    printf("%d\n", q.a);
    printf("%s\n", q.car);
    printf("%s\n", q.com);
    printf("%s\n", q.t);
    printf("%d\n", q.c);
    printf("\n");

    struct ff gg;
    strcpy(gg.car,"FF");
    strcpy(gg.com,"Ferrari");
    strcpy(gg.t,"Hatchback");
    gg.c = 25000000;
    gg.a = 16;
    printf("%d\n", gg.a);
    printf("%s\n", gg.car);
    printf("%s\n", gg.com);
    printf("%s\n", gg.t);
    printf("%d\n", gg.c);
 	printf("\n");

 	int z;
 	printf("Select a car number: ");
 	scanf("%d", &z);
 	switch(z){
        case 1:
            printf("Congratulations, You have ordered a Honda BRV");
            break;
        case 2:
            printf("Congratulations, You have ordered a Honda WRV");
            break;
        case 3:
            printf("Congratulations, You have ordered a Hyundai Creta");
            break;
        case 4:
            printf("Congratulations, You have ordered a Hyundai Venue");
            break;
        case 5:
            printf("Congratulations, You have ordered a Jeep Compass");
            break;
        case 6:
            printf("Congratulations, You have ordered a Kia Seltos");
            break;
        case 7:
            printf("Congratulations, You have ordered a BMW X2");
            break;
        case 8:
            printf("Congratulations, You have ordered a Suzuki Boleno");
            break;
        case 9:
            printf("Congratulations, You have ordered a Mercedes C220");
            break;
        case 10:
            printf("Congratulations, You have ordered a Porsche Panemera");
            break;
        case 11:
            printf("Congratulations, You have ordered an Audi A6");
            break;
        case 12:
            printf("Congratulations, You have ordered a Volkswagen Vento");
            break;
        case 13:
            printf("Congratulations, You have ordered a Toyota Glanza");
            break;
        case 14:
            printf("Congratulations, You have ordered a Bentley Continental");
            break;
        case 15:
            printf("Congratulations, You have ordered a Land Rover Evoque");
            break;
        case 16:
            printf("Congratulations, You have ordered a Ferrari FF");
            break;
        default:
            printf("Sorry, you have entered the wrong car number");
            break;
 	}
 	return 0;
}
int Job()
{
    FILE* filepointer;
    filepointer=fopen("write.txt","a");
    start1:
    printf("Enter name\n");
    char name[100];
    scanf("%s",&name);
    printf("Enter phone number\n");
    char phone[100];
    scanf("%s",&phone);
    if(strlen(phone)!=10){
    printf("Phone number should have 10 digits\n");
    goto start1;
    }
    fprintf(filepointer,"Name:%s\n",name);
    fprintf(filepointer,"Phone:%s",phone);
    char* ar1[6]={"Mechanic","Salesman","Safety Inspector","Manager","Designer","Supervisor"};
    char dataToBeWritten[150];
    printf("Applying for position :\n");
    start:
    printf("1.%s\n",ar1[0]);
    printf("2.%s\n",ar1[1]);
    printf("3.%s\n",ar1[2]);
    printf("4.%s\n",ar1[3]);
    printf("5.%s\n",ar1[4]);
    printf("6.%s\n",ar1[5]);
    printf("Enter position here: ");
    int op;
    scanf("%d",&op);
    if(op<0||op>6){
        printf("wrong information entered \n");
        goto start;
    }
    printf("The following are qualifications required: \n");
    printf("1.Education till class 10 \n2.Class 12 education\n3.Btech Degree\n");
    printf("Enter the Class 10 percentage here: ");
    float marks[3];
    scanf("%f",&marks[0]);
    if(marks[0]>100||marks[0]<0){
        printf("wrong information entered \n");
        goto start;
    }
    printf("Enter the Class 12 percentage here: ");
    scanf("%f",&marks[1]);
    if(marks[1]>100||marks[1]<0){
         printf("wrong information entered \n");
        goto start;
    }
    printf("Enter the CGPA between 0 to 10: ");
    scanf("%f",&marks[2]);
    if(marks[2]>10||marks[2]<0){
        printf("wrong information entered \n");
        goto start;
    }
    bool flag=false;
    if(marks[1]>=87&&marks[2]>=8.6){
        if(op==6){
            strcat(dataToBeWritten,"\nJob: Supervisor\n");
            flag=true;
        }
    }
    if(marks[1]>=80&&marks[2]>=8.0&&flag==false){
        if(op==4||op==5){
            if(op==4){
            strcat(dataToBeWritten,"\nJob: Manager\n");}
            if(op==5){
            strcat(dataToBeWritten,"\nJob: Designer\n");}
            flag=true;
        }
    }
    if(marks[1]>=70&&marks[2]>=8.0&&flag==false){
        if(op==3||op==1||op==5){
            if(op==1){
            strcat(dataToBeWritten,"\nJob: Mechanic\n");}
            if(op==3){
            strcat(dataToBeWritten,"\nJob: Safety Inspector\n");}
            if(op==5){
            strcat(dataToBeWritten,"\nJob: Designer\n");}
            flag=true;
        }
    }
    if(marks[1]>=65&&marks[2]>=6.5&&flag==false){
        if(op==1||op==2||op==3||op==4||op==5){
            if(op==1){
            strcat(dataToBeWritten,"\nJob: Mechanic\n");}
            if(op==2){
            strcat(dataToBeWritten,"\nJob: Salesman\n");}
            if(op==3){char dataToBeWritten[150];
            strcat(dataToBeWritten,"\nJob: Safety Inspector\n");}
            if(op==4){
            strcat(dataToBeWritten,"\nJob: Manager\n");}
            if(op==5){
            strcat(dataToBeWritten,"\nJob: Designer\n");}
            flag=true;
        }
    }
    if(flag==false){
        printf("Sorry the minimum requirements are not meeting\n");
        printf("Do you want to try again?\nPress yes to try again\n");
        char option[5];
        scanf("%s",option);
        if(!strcmp(option,"yes")){
        goto start;
        }
        if(!strcmp(option,"yes")){
        goto start;
        }
        }
    else{
        if(op==6){
           if(marks[1]>=87&&marks[1]<=100&&marks[2]>=8.6){
                printf("The salary will be Rs 90000 per month\n");
                strcat(dataToBeWritten,"Salary:90000");
            }
        }
        else if(op==4||op==6){
            if(marks[1]>=80&&marks[2]>=8){
                printf("The salary will be Rs 85000 per month\n");
                strcat(dataToBeWritten,"Salary:85000");
            }
        }
        else if(op==1||op==3||op==5||op==4||op==6){
            if(marks[1]>=70&&marks[2]>=8.0){
                printf("The salary will be Rs 50000 per month\n");
                strcat(dataToBeWritten,"Salary:50000");
            }
            else if(marks[1]>85&&marks[2]>=9){
                printf("The salary will be Rs 80000 per month\n");
                strcat(dataToBeWritten,"Salary:80000");
            }
        }
        else if(op==2){
            if(marks[1]>=65&&marks[2]>=6.5){
                printf("The salary will be Rs 40000 per month\n");
                strcat(dataToBeWritten,"Salary:40000");
            }
            else if(marks[1]>85&&marks[2]>=9){
                printf("The salary will be Rs 60000 per month\n");
                strcat(dataToBeWritten,"Salary:60000");
            }
        }
    }
    if (strlen (dataToBeWritten)>0)
        {
            fputs(dataToBeWritten, filepointer) ;
            fputs("\n", filepointer) ;
        }
    printf("\n");
    fclose(filepointer) ;
    char s[100];
    int i=0;
    int r=1;
    printf("Do you want to delete a record?\n");
    int option;
    scanf("%d",&option);
    if(option==1){
    FILE* file;
    FILE* file1;
    file=fopen("write.txt","r");
    file1=fopen("w.txt","w");
    printf("Enter record to be deleted\n");
    scanf("%d",&r);
    while(fgets(s,100,file)){
    if(i!=r-1&&i!=r&&i!=r+1&&i!=r+2){
            fprintf(file1,"%s",s);
    }
    i++;
    }
    printf("File has been updated");
    fclose(file);
    fclose(file1);
    remove("write.txt");
    rename("w.txt","write.txt");
    }
    return 0;
}
int main()
{
    int choice,i;
    /*
    strcpy((repser+0)->repair_name,"Battery replacement------------------------- ");
    strcpy((repser+1)->repair_name,"Brake replacement--------------------------- ");//
    strcpy((repser+2)->repair_name,"Ignition coil and spark plug---------------- ");
    strcpy((repser+3)->repair_name,"Oil filter---------------------------------- ");//
    strcpy((repser+4)->repair_name,"Wiper blade replacement--------------------- ");
    strcpy((repser+5)->repair_name,"New tires ---------------------------------- ");//
    strcpy((repser+6)->repair_name,"Wheel alignment----------------------------- ");//
    strcpy((repser+7)->repair_name,"Wheel balancing----------------------------- ");//
    strcpy((repser+8)->repair_name,"Engine lubrication system replacement------- ");
    strcpy((repser+9)->repair_name,"Scheduled maintenance----------------------- ");

    (repser+0)->repair_time=3;
    (repser+1)->repair_time=6;
    (repser+2)->repair_time=12;
    (repser+3)->repair_time=12;
    (repser+4)->repair_time=3;
    (repser+5)->repair_time=12;
    (repser+6)->repair_time=6;
    (repser+7)->repair_time=3;
    (repser+8)->repair_time=12;
    (repser+9)->repair_time=24;


    (repser+0)->repair_cost[0]=3000;  (repser+0)->repair_cost[1]=2500;  (repser+0)->repair_cost[2]=2000;
    (repser+1)->repair_cost[0]=10000; (repser+1)->repair_cost[1]=9050;  (repser+1)->repair_cost[2]=8000;
    (repser+2)->repair_cost[0]=2200;  (repser+2)->repair_cost[1]=2000;  (repser+2)->repair_cost[2]=1800;
    (repser+3)->repair_cost[0]=836;   (repser+3)->repair_cost[1]=760;   (repser+3)->repair_cost[2]=500;
    (repser+4)->repair_cost[0]=1050;  (repser+4)->repair_cost[1]=950;   (repser+4)->repair_cost[2]=780;
    (repser+5)->repair_cost[0]=26000; (repser+5)->repair_cost[1]=21000; (repser+5)->repair_cost[2]=14000;
    (repser+6)->repair_cost[0]=200;   (repser+6)->repair_cost[1]=0;     (repser+6)->repair_cost[2]=0;
    (repser+7)->repair_cost[0]=250;   (repser+7)->repair_cost[1]=0;     (repser+7)->repair_cost[2]=0;
    (repser+8)->repair_cost[0]=25000; (repser+8)->repair_cost[1]=19000; (repser+8)->repair_cost[2]=15000;
    (repser+9)->repair_cost[0]=2000;  (repser+9)->repair_cost[1]=0;     (repser+9)->repair_cost[2]=0;



    FILE *wfile = fopen("repairlist.txt","w");
    if(wfile==NULL)
    {
        printf("not abel to open file");
        return(1);
    }
    for(i=0;i<repno;i++)
    {
        fprintf(wfile,"%d\t%s\t%d\t%d\t%d\t%d\n",(repser+i)->repair_id,(repser+i)->repair_name,(repser+i)->repair_time,(repser+i)->repair_cost[0],(repser+i)->repair_cost[1],(repser+i)->repair_cost[2]);
    }
    fclose(wfile);

    */
    printf("1) Press 1 to buy a new car\n2) Press 2 for car services \n3) Press 3 for job opportunity\n");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        New_car();
        break;
    case 2:
        Car_services();
        break;
    case 3:
        Job();
        break;
    }
}

