#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <winbgim.h>

#define Y 11
#define X 11


#define N 10

typedef struct{
        int x;
        int y;
        int color;
}Icono;

typedef struct nodo{
        int x,y;
        struct nodo *sig, *ant, *arriba, *abajo;
        char id;
}TNodo;

TNodo *creaNodo(int x, int y);
void creaMalla(TNodo **Lista);
void pantalla();
void cargarIconos(void *imagen, void *arregloIconos[50]);
void Archivo(char archivo[],int *malla);
void moverJugador(TNodo *malla,void *arregloIconos[50]);
void escenario(TNodo *malla, void *arregloIconos[50]);
TNodo *enemigo(TNodo *malla, void *arregloIconos[50]);
void gameOver();


void portada(void *arregloIconos[50]);

int main()
{

    initwindow(1024,600,"Cygnus X - 1");
    TNodo *Lista;
    void *imagen;
    void *arreglodeIconos[50];


    creaMalla(&Lista);

    cargarIconos(imagen,arreglodeIconos);
    portada(arreglodeIconos);
    pantalla();
    //escenario(Lista,arreglodeIconos);
    enemigo(Lista,arreglodeIconos);

    moverJugador(Lista,arreglodeIconos);



    system("PAUSE");



}

TNodo *creaNodo(int x, int y)
{
     TNodo* aux=(TNodo*)malloc(sizeof(TNodo));
          aux->x=x*5;

          aux->y=y*5;

          aux->sig=NULL;
          aux->ant=NULL;
          aux->arriba=NULL;
          aux->abajo=NULL;


      return (aux);
}


void creaMalla(TNodo **Lista)
{
     TNodo *aux = NULL;
     TNodo *nuevo = NULL;
     TNodo *atras = NULL;
     TNodo *arriba = NULL;


     int renglon,columna;

     for(renglon=0; renglon<X; renglon++)
     {
       atras = NULL;
       arriba = aux;

       for(columna=0; columna<Y; columna++)
       {

           nuevo=creaNodo(renglon*N,columna*N);
           if(nuevo != NULL)
           {
                if(columna==0)
                {
                     aux=nuevo;
                     if(renglon==0)
                     {
                        *Lista=nuevo;
                     }
                }
                if(atras!=NULL)
                {
                     nuevo->ant=atras;
                     atras->sig=nuevo;

                }
                if(arriba!=NULL)
                {
                     nuevo->arriba=arriba;
                     arriba->abajo=nuevo;
                     arriba = arriba->sig;
                }

                atras=nuevo;
           }
       }
     }
}

void pantalla()
{



    setcolor(YELLOW);
    rectangle(601,11,1001,551);
    rectangle(591,1,1011,561);

    setcolor(WHITE);
    settextstyle(2,0,17);
    outtextxy(630,31,"Cygnus X-1");

    rectangle(630,300,680,350);
    settextstyle(10,0,3);
    outtextxy(655,320,"z");
    settextstyle(2,0,14);
    outtextxy(690,325,"Dispara");






}

void cargarIconos(void *imagen,void *arregloIconos[50])
{
    int i = 0;
    int tam = 20;
    while(i < 50)
    {
        switch(i)
        {
            case 0:
                    Archivo("personaje.txt",&tam);
                    imagen = malloc(imagesize(10,0,60,60));
                    getimage(10,0,60,60,imagen);
                    arregloIconos[0] = imagen;
                    cleardevice();


            break;

            case 1:
                    Archivo("mira.txt",&tam);
                    imagen = malloc(imagesize(10,0,60,60));
                    getimage(10,0,60,60,imagen);
                    arregloIconos[1] = imagen;
                    cleardevice();


            break;

            case 2:
                    Archivo("bala.txt",&tam);
                    imagen = malloc(imagesize(10,5,60,40));
                    getimage(10,5,60,40,imagen);
                    arregloIconos[2] = imagen;
                    cleardevice();

            break;

            case 3:
                    Archivo("bloque.txt",&tam);
                    imagen = malloc(imagesize(10,0,60,60));
                    getimage(10,0,60,60,imagen);
                    arregloIconos[3] = imagen;
                    cleardevice();
            break;

            case 4:
                    Archivo("enemigo.txt",&tam);
                    imagen = malloc(imagesize(0,0,80,80));
                    getimage(0,0,80,80,imagen);
                    arregloIconos[4] = imagen;
                    cleardevice();
            break;

            case 5:
                    Archivo("caido.txt",&tam);
                    imagen = malloc(imagesize(0,0,60,60));
                    getimage(0,0,60,60,imagen);
                    arregloIconos[5] = imagen;
                    cleardevice();

            break;

            case 6:
                    Archivo("enemigopierde.txt",&tam);
                    imagen = malloc(imagesize(0,0,80,80));
                    getimage(0,0,80,80,imagen);
                    arregloIconos[6] = imagen;
                    cleardevice();

            break;

            case 7:
                    Archivo("izquierda.txt", &tam);
                    imagen = malloc((imagesize(0,0,60,60)));
                    getimage(0,0,60,60,imagen);
                    arregloIconos[7] = imagen;
                    cleardevice();
            break;

            case 8:
                    Archivo("corazon.txt", &tam);
                    imagen = malloc((imagesize(0,0,80,80)));
                    getimage(0,0,80,80,imagen);
                    arregloIconos[8] = imagen;
                    cleardevice();
            break;

            case 9:
                    Archivo("portada.txt", &tam);
                    imagen = malloc(imagesize(0,0,60,60));
                    getimage(0,0,60,60,imagen);
                    arregloIconos[9] = imagen;
                    cleardevice();
            break;


        }
        i = i+1;
    }
}

void Archivo(char archivo[], int *malla)
{

    FILE *arch;
    Icono *abrir;
    int cont  = 0;
    int aux = 2;
    void *img;
    arch = fopen(archivo,"rb");
    if(arch != NULL)
    {
        fread(&aux,sizeof(int),1,arch);
        fread(malla,sizeof(int),1,arch);
        abrir = (Icono*)malloc(sizeof(Icono)*aux);
        while(cont < aux)
        {
            fread(&abrir[cont],sizeof(Icono),1,arch);
            putpixel(abrir[cont].x,abrir[cont].y,abrir[cont].color);






            cont++;
        }
            img = malloc(imagesize(650,450,730,520));
            getimage(650,450,730,520,img);
            rectangle(650,450,730,520);
            putimage(0,0,img,COPY_PUT);
    }
    else
    {
        outtextxy(500,200,"No se encontro el archivo");

    }
    free(abrir);
    fclose(arch);
}



void escenario(TNodo *malla, void *arregloIconos[50])
{
    setactivepage(3);
    setvisualpage(3);
    TNodo *aux = NULL;
     TNodo *aux2 = NULL;

     FILE *archivo;
     char caracter;
     archivo = fopen("nivel.txt","rb");
     if(archivo == NULL)
     {
        printf("ERROR");
        exit(1);
     }

     while(feof(archivo) == 0)
     {
         caracter = fgetc(archivo);
         printf("%c", caracter);



            for(aux=malla; aux!=NULL; aux=aux->abajo)
            {
                aux2=aux;
                while(aux2!=NULL)
                {
                    switch(caracter)
                    {
                            case '1':
                                    putimage(aux2->x,aux2->y,arregloIconos[3],0);

                            break;


                            case '\n':
                                        aux2->x = malla->x;
                                        aux2->y = aux2->sig->y;

                            break;

                    }
                    aux2 = aux2->sig;







                }

            }
    }
    getch();
}

TNodo *enemigo(TNodo *malla, void *arregloIconos[50])
{
    TNodo *enemi = NULL;
    enemi=malla;

    //putimage(enemi->x,enemi->y,arregloIconos[4],0);


            int pos;
            pos = 1+(rand()%4);

            switch(pos)
            {
                case 1: if(enemi->abajo != NULL)
                        {
                            enemi = enemi->abajo;
                            delay(1000);
                            cleardevice();
                        }


                break;
                case 2:  if(enemi->arriba != NULL)
                        {
                            enemi = enemi->arriba;
                            //delay(1000);
                            cleardevice();
                        }

                break;
                case 3:
                            if(enemi->sig != NULL)
                            {
                                enemi = enemi->sig;
                                //delay(1000);
                                cleardevice();
                            }


                break;
                case 4:
                            if(enemi->ant != NULL)
                            {
                                enemi = enemi->ant;
                                //delay(1000);
                                cleardevice();
                            }

                break;


            }

        //putimage(enemi->x,enemi->y,arregloIconos[4],0);

        return enemi;







}
void moverJugador(TNodo *malla,void *arregloIconos[50])
{

    setactivepage(0);
    setvisualpage(0);




    TNodo *Soldier = NULL;
    Soldier = malla->sig->sig->sig->abajo->abajo->abajo->abajo;

    char tecla;
    void *imagen;
    //imagen = malloc(imagesize(10,0,60,60));
    //getimage(10,0,60,60,imagen);
    imagen = arregloIconos[0];
    cleardevice();
    pantalla();
    putimage(Soldier->x,Soldier->y,imagen,COPY_PUT);
    TNodo *robot = NULL;
    TNodo *enemi = NULL;
            enemi=malla;
    int pierdes = 0;


    do{



    //putimage(enemi->x,enemi->y,arregloIconos[4],0);


            int pos;
            pos = 1+(rand()%4);

            switch(pos)
            {
                case 1: if(enemi->abajo != NULL)
                        {

                            enemi = enemi->abajo;
                            putimage(enemi->x,enemi->y,arregloIconos[4],0);
                            delay(200);
                             setactivepage(1);
                                cleardevice();
                                putimage(enemi->x,enemi->y,arregloIconos[4],0);
                                putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);
                                pantalla();
                                setactivepage(0);
                                setvisualpage(1);
                                cleardevice();
                                pantalla();
                                setvisualpage(0);
                        }


                break;
                case 2:  if(enemi->arriba != NULL)
                        {
                            enemi = enemi->arriba;
                            putimage(enemi->x,enemi->y,arregloIconos[4],0);
                            delay(200);

                            setactivepage(1);
                                cleardevice();
                                putimage(enemi->x,enemi->y,arregloIconos[4],0);
                                putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);
                                pantalla();
                                setactivepage(0);
                                setvisualpage(1);
                                cleardevice();
                                pantalla();
                                setvisualpage(0);
                        }

                break;
                case 3:
                            if(enemi->sig != NULL)
                            {
                                enemi = enemi->sig;
                                putimage(enemi->x,enemi->y,arregloIconos[4],0);
                                delay(200);

                                setactivepage(1);
                                cleardevice();
                                putimage(enemi->x,enemi->y,arregloIconos[4],0);
                                putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);
                                pantalla();
                                setactivepage(0);
                                setvisualpage(1);
                                cleardevice();
                                pantalla();
                                setvisualpage(0);
                            }


                break;
                case 4:
                            if(enemi->ant != NULL)
                            {
                                enemi = enemi->ant;
                                putimage(enemi->x,enemi->y,arregloIconos[4],0);
                                delay(200);

                                setactivepage(1);
                                cleardevice();
                                putimage(enemi->x,enemi->y,arregloIconos[4],0);
                                putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);
                                pantalla();
                                setactivepage(0);
                                setvisualpage(1);
                                cleardevice();
                                pantalla();
                                setvisualpage(0);
                            }

                break;


            }




            if(enemi == Soldier)
            {
                pierdes = pierdes +1;
                if(pierdes == 3)
                    gameOver();
                putimage(Soldier->x,Soldier->y,arregloIconos[5],0);
                delay(500);
            }



            //putimage(enemi->x,enemi->y,arregloIconos[4],0);


            //enemigo(robot,arregloIconos);

            if(kbhit() == 0)
            {
                tecla = NULL;
            }
            if(kbhit() ==1)
            {

                tecla = getch();

            }





    switch(tecla)
    {

        case KEY_DOWN:

                        if(Soldier->sig != NULL)
                            Soldier = Soldier->sig;

                        setactivepage(1);
                        cleardevice();
                        putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);
                        pantalla();
                        setactivepage(0);
                        setvisualpage(1);
                        cleardevice();
                        pantalla();
                        setvisualpage(0);
                        putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);

        break;

        case KEY_UP:

                    if(Soldier->ant != NULL)
                           Soldier = Soldier->ant;

                    setactivepage(1);
                    cleardevice();
                    putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);
                    pantalla();
                    setactivepage(0);
                    setvisualpage(1);
                    cleardevice();
                    pantalla();
                    setvisualpage(0);
                    putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);

                    break;

        case KEY_RIGHT:
                        if(Soldier->abajo != NULL)
                            Soldier = Soldier->abajo;

                    setactivepage(1);
                    cleardevice();
                    putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);
                    pantalla();
                    setactivepage(0);
                    setvisualpage(1);
                    cleardevice();
                    pantalla();
                    setvisualpage(0);
                    putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);

        break;

        case KEY_LEFT:
                      if(Soldier->arriba != NULL)
                            Soldier = Soldier->arriba;

                    setactivepage(1);
                    cleardevice();
                    putimage(Soldier->x, Soldier->y, arregloIconos[7],COPY_PUT);
                    pantalla();
                    setactivepage(0);
                    setvisualpage(1);
                    cleardevice();
                    pantalla();
                    setvisualpage(0);
                    putimage(Soldier->x, Soldier->y, arregloIconos[7],COPY_PUT);
        break;







        case  'z':
                 TNodo *disparo = NULL;

                 disparo = Soldier->abajo;

                 while(disparo != NULL)
                 {
                    putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);
                    putimage(disparo->x,disparo->y,arregloIconos[2],COPY_PUT);
                    putimage(enemi->x,enemi->y,arregloIconos[4],0);
                    setactivepage(1);
                    cleardevice();
                    putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);
                    putimage(disparo->x,disparo->y,arregloIconos[2],COPY_PUT);
                    putimage(enemi->x,enemi->y,arregloIconos[4],0);
                    pantalla();
                    setactivepage(0);
                    setvisualpage(1);
                    cleardevice();
                    pantalla();
                    setvisualpage(0);
                    disparo = disparo->abajo;

                    if(disparo == enemi)
                    {
                        putimage(enemi->x,enemi->y,arregloIconos[6],0);
                        delay(1000);
                        free(enemi);
                        enemi =NULL;
                        exit(1);
                    }
                 }
                 free(disparo);
        break;















    }



   /* if(Soldier->x >= 400 && Soldier->y >= 5 && Soldier->x <= 500 && Soldier->y <=105 )
    {

                Soldier->x = 320;
                Soldier->y = 320;

                setactivepage(0);
                moverJugador(Soldier,arregloIconos);

    }*/
    putimage(Soldier->x, Soldier->y, imagen,COPY_PUT);

    }while(kbhit() != 27);


}

void gameOver()
{
    cleardevice();
    outtextxy(400,getmaxy()/2,"G A M E O V E R");
    delay(3000);
    exit(1);

}


void portada(void *arregloIconos[50])
{

    putimage(0,0,arregloIconos[9],0);
    setcolor(3);
    settextstyle(2,0,52);
    outtextxy(300,250,"CYGNUS X-1");
    delay(500);
    do{
        settextstyle(0,0,13);
        setcolor(RED);
        outtextxy(280,350,"Presione una tecla para comenzar");

    }while(kbhit()!= 1);


}

