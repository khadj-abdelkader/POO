// version 2.0 du 31/07/2005 //
// maj : aucune //

#include <16F876a.h> //mettre #include <16F876.h> si PIC16F876-04 //
#device ICD=TRUE
#device *=16
#use delay(clock=2500000)
#fuses XT, NOPROTECT, BROWNOUT, NOWDT
#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#include "can.c"

#define led_on    output_high(PIN_B1)
#define led_off   output_low(PIN_B1)

int buf_ser[50];                       //buffer de reception serie
int is;                                //pointeur de reception serie
int16 mst;                             //compteur de temps en ms

/* declaration des fonctions */
void purge_srxbuf();                   //purge du tampon de reception serie
void send();                           //envoie d'une trame
void can_test();                       //test de reception
void init();

/* gestion du temps */
#int_timer2
void isr_timer2(void) {mst++;}         //timer qui est appele toutes les ms par une interruption du timer2

/* reception serie */
#int_RDA
RDA_isr()
{
   int c;

   c=getc();
   if (c!=0){
      buf_ser[is]=c;
      is++;
   }
   if (c==13)  {send();}
   if (is==49) {purge_srxbuf();}
}

void main() {
   init();
   while(TRUE)
   {
      can_test();
   }
}

void can_test(){
   if ( can_kbhit() )   //y a t il une reception ?
   {
      led_on;
      if(can_getd(crx_id,&crxbuf[0],crx_len,rxstat))        //...extraction des donnees et envoie
      {
         printf("%LU ",mst);                                //temps
         printf("     ID %LX   LEN %U   ",crx_id,crx_len);  //id et taille trame
         if (!rxstat.rtr)
         {
            for (ic=0;ic<crx_len;ic++)
               printf("%X",crxbuf[ic]);                     //data si c'est le cas
         }
         if (rxstat.rtr)      {printf("R");}                //indicateurs si c'est le cas
         if (rxstat.err_ovfl) {printf("O");}
         if (rxstat.inv)      {printf("I");}
         printf("\r\n");                                    //saut de ligne
      }
      led_off;
   }
}

void send(){
   int a,i,j,n;
   int txlen;
   int rflag;
   int txbuf[10];
   int32 tx_id;
   int32 var;

   rflag=0;
   txlen=0;
   tx_id=0;
   var=0;

   for (i=0;i<10;i++){txbuf[i]=0;}

   a=(buf_ser[1]-30);                                       //taille de l'identifiant
   n=a;
   for (i=0;i<a;i++){                                       //extraction de l'identifiant
      var=((buf_ser[i+2]-30));
      if (n==2) {var=var*10;}
      if (n==3) {var=var*100;}
      if (n==4) {var=var*1000;}
      if (n==5) {var=var*10000;}
      if (n==6) {var=var*100000;}
      if (n==7) {var=var*1000000;}
      if (n==8) {var=var*10000000;}
      tx_id= tx_id+var;
      n--;
   }
   txlen=buf_ser[a+2]-30;                                   //taille des donnees
   rflag=buf_ser[a+3]-30;                                   //indicateur
   j=a+4;
   for (i=0;i<txlen;i++){                                   //extraction des donnees
      a = buf_ser[j];
      if (a>=30 & a<=39){a=a-30;}
      if (a>=61 & a<=66){a=a-51;}
      txbuf[i]=a;
      a = buf_ser[j+1];
      if (a>=30 & a<=39){a=a-30;}
      if (a>=61 & a<=66){a=a-51;}
      txbuf[i+1]=a;
      a=txbuf[i+1]+16*txbuf[i];
      txbuf[i]=a;
      txbuf[i+1]=0;
      j++;
      j++;
   }
   can_putd(tx_id,&txbuf[0],txlen,3,0,rflag);               //envoie de la trame
   purge_srxbuf();                                          //nettoyage
}

void init(){
   can_init();
   purge_srxbuf();
   setup_timer_2(T2_DIV_BY_16,246,16);                      // parametrage du timer 2
   enable_interrupts(INT_TIMER2);                           // autorisation interruption timer2 100ms
   enable_interrupts(global);                               // autorisation de toutes les interruptions
   enable_interrupts(int_rda);                              // autorisation interruption liaison serie
}

void purge_srxbuf(){
   int i;
   for (i=0;i<50;i++){buf_ser[i]=0;}
   is=0;
}
