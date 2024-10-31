#include <stdio.h>//libreria principal
#include <stdlib.h>
#include <string.h>//libreria para arrays y string
#include <time.h>//libreria para usar "srand(time(NULL));" del random
#include <limits.h>//libreria para usar MAX_INT 

void leerFichero(int *m,int *n,float matriz[500][500],char direc[100]);
void solucionAleatoria(int m,int n,int solucion[50]);
void EvaluacionSol(int m,int n,int solucion[50],float matriz[500][500]);
void solucionVoraz(int m,int n,float matriz[500][500]);
void SolucionGrasp(int m,int n,float matriz[500][500]);

void main()
{
   float matriz[500][500];//matrizque indica las distancias entre los puntos en decimales 
   int m,n,i; //m es el numero disponible de posciones para elegir// n es el numero de cuantos se deben elegir
   int solucion[50];
   
   
   for(i=1;i<21;i++){//bucle for para las 20 instancias de la practica obligatoria
   char dir [30]={0}; //cadena de caracteres en las que guardara el nombre de la instancia
   sprintf(dir,"GKD-Ic_%d_n500_m50.txt",i); //mediante esta funcion se guardara de acuerdo al for los nombres en el char dir
   leerFichero(&m,&n,matriz,dir); //funcion leer fichero
   SolucionGrasp(m,n,matriz); //funcion solucion grasp!!!
   
   }
   
   //solucionAleatoria(m,n,solucion);
   //EvaluacionSol(m,n,solucion,matriz);
   //solucionVoraz(m,n,matriz);
}
    //*********************************************************************************************//
   //********************************LEER FICHERO**************************************************//
   
   void leerFichero(int *m,int *n, float matriz[500][500], char direc[100])
{
   FILE *fp;
   char linea[100000];
   int p1,p2,i;
   int cont=0;
   int aux[2];
   float dist[1];

   //se lee el fichero 
	fp = fopen("GKD-Ic_2_n500_m50.txt","r");
    printf("\nInstancia: ");
	printf("%s\n",direc);
    if(fp==NULL)//si no se encuentra el fichero
        printf("ERROR");//se imprime error
 	
	 while(fgets(linea, 100000, (FILE*) fp)) {//se lee linea por linea con el cmdo FGETS
        
      
	if(cont==0){//si estamos en la primera fila o contador a 0
	    rewind(fp);//se regresa al inicio despues de haberse leido con el while anterior
		fscanf(fp, "%d", &aux[0]);//y se va leyendo numero por numero hasta el primer espacio
		*m=aux[0];//se toma m
   		fscanf(fp, "%d", &aux[1]);//luego del primer espacio viene el n
		*n=aux[1];//se toma el n

	}
	else//si el contador no es 0 nos encontramos en la segunda linea
	{
		fscanf(fp,"%d",&aux[0]);//se toma el primer punto
		p1=aux[0];
		
   		fscanf(fp, "%d", &aux[1]);//luego el segundo punto
		p2=aux[1];
		
		fscanf(fp, "%f", &dist[0]);//y la distancia de separacion
		matriz[p1][p2]=dist[0];//con esto se da a entender al computador 
		matriz[p2][p1]=dist[0];//que es igual las distancias entre los ptos 3 y 5 que entre 5 y 3
	}
	  cont++;//y se pasa a la siguiente linea
	  }
   fclose(fp);//se cierra el fichero

}
   
   void SolucionGrasp(int m,int n,float matriz[500][500])
{
	///*********************************CONTRUCTIVO GRASP*******************************************/////////
	
	int Candidatelist [m],CandidatelistAC[m-n],RCL[m],solucion [n];//array de lista de candidatos, lista actualizada(no se 
	int i,j,r,k,h,x,num;											//consideran los que estan lista de restringidos,lista de res
	float Dist[m];													//restringifos y solucion.
	float Mindist=INT_MAX;
	float Maxdist=0.0;
 	float DistMenores[500];
 	float SolMenorDist=INT_MAX;
 	float SolMenorDist2=INT_MAX;
 	float SolMenorDist3=INT_MAX;
 	float OPMLOCAL=0;
 	float Umbral;
 	float alfa=0.1;//se usa para la formula de umbral, si es 1 es totalmente aleatorio y si es 0 el totalmente voraz
	
	for(x=0;x<2;x++){  //se hace para encontrar el optimo local
	
	
	for (i=0;i<m;i++){
		Candidatelist[i]=i;//lista de candidatos, que son todas los disponibles
	}	
    for (i=0; i<n; i++)
   {
	if (i==0)//si i es 0
	{	
    srand(time(NULL));//con esto los numero aletorios no empiezan siempre igual.
    solucion[0] = rand()%m;//la primera solucion es aleatoria
    for(j=0; j<m; j++) { 
		if(solucion[i]!=j){ //para que no se compare con el mismo
	  		Dist[j]=matriz[solucion[i]][j]; //se halla la distancia de los comparados en un array
			if(Dist[j]>Maxdist)
			Maxdist=Dist[j];//se halla la maxima distancia
			if(Dist[j]<Mindist)
			Mindist=Dist[j];//se halla la minima distancia
		}
	}
	Umbral= Maxdist-alfa*(Maxdist-Mindist);//max y min para calcular el umbral que 
	for(j=0;j<m;j++){						//los que esten arriba o igual que le umbral
		if(Dist[j]>=Umbral){				//formaran la RCL
		for(k=0;k<m;k++){
		RCL[k]=j;
	    }
      }
    }
	num=0;
	num=rand()%m;		
	if(num=RCL[num]){	//se elige un numero al azar de la lista de restringidos
	solucion[i+1]=RCL[num];//y forma parte de a segunda solucion
	}
	i++;
	}
	else 
	{
	for(r=0;r<i;r++) //0 1 para compararlos con todos los Zs luego es 0 1 2 //i=2 y luego i=3 asi sucesivamente
    {
	  for(j=0; j<m; j++) //0 a 9
	    {
		if (solucion[r]!=j)//para que no se compare con el mismo munero 
	    {
	    	if (DistMenores[j]==0)
	    	{
	    		DistMenores[j]=matriz[solucion[r]][j];//se coloca primera comparacion en un array 
				                                        //con todas las distancias menores
			}
			else{
			Maxdist=0.0;
			Mindist=INT_MAX;
			if(matriz[solucion[r]][j]<DistMenores[j]){ //se comparan las distancias y se halla la menor
			   DistMenores[j]=matriz[solucion[r]][j];
			       }  
				}
		    }
	    }
	}
	                
	for(j=0;j<i;j++){ 
        DistMenores[solucion[j]]=0;//para que no se eliga las que se eligieron (repetidos)
					}
	for(j=0; j<m; j++) 
	{			
	    if(DistMenores[j]>Maxdist)//se recorre las distancias y se escoge la max
        Maxdist=DistMenores[j];
	    if(DistMenores[j]<Mindist&&DistMenores[j]!=0.000)//se recorre las distancias y se escoge la min
     	Mindist=DistMenores[j];		        
    }
	
	Umbral=0;    //se obtiene el umbral para la lista de candidatos restringidos
	Umbral= Maxdist-alfa*(Maxdist-Mindist);
	for(j=0;j<m;j++){
		if(DistMenores[j]>=Umbral){
		   for(k=0;k<m;k++){
		   RCL[k]=j;
	       }
	    }
    }
	num=0;
	num=rand()%m;
	if(num=RCL[num]){
		solucion[i]=RCL[num];}//se escoge uno al azar de la lista de restringidos
	
    }
	}
	
	 for (i = 0; i < n; i++) {
         for (j = i + 1; j < n; j++) {
            if (matriz[solucion[i]][solucion[j]] < SolMenorDist){
                SolMenorDist = matriz[solucion[i]][solucion[j]];//y se obtiene la menor distancia (funcion objetivo
				}   											//hasta el momento
            }
        }     
   
	///****************************************BUSQUEDA LOCAL*********************************************//
	
	  for(k=0;k<m;k++){
      	CandidatelistAC[k]=k;  //se halla la lista de caandidatos restingidos actualizados (sin lo que forman parte de la solucion)
        }
	 for(i=0;i<n;i++){
	 CandidatelistAC[solucion[i]]=-1;//los que forman parte de la solucion se igualan a -1 
     }   


	
     for(h=0;h<n;h++){
        for(i=0;i<n;i++){
	        CandidatelistAC[solucion[i]]=-1;
            }  
	num=0;
	srand(time(NULL));
	num=rand()%n;
		solucion[num];//se escoge uno al azar de la solucion
		
        for(k=0;k<m;k++){
		  if (CandidatelistAC[k]!=-1){//y se compara si no es -1
		  	solucion[num]=CandidatelistAC[k]; //se realiza el moviemnto con uno de la lista de candidatos
		  	for (i = 0; i < n; i++) {
                for (j = i + 1; j < n; j++) {
                    if (matriz[solucion[i]][solucion[j]] < SolMenorDist2){//se obtiene la menor distancia 
                      SolMenorDist2 = matriz[solucion[i]][solucion[j]];
					}   
                }
            }     
		  	if(SolMenorDist<SolMenorDist2){//si esa menor distancia con el valor del movimiento es mayor 
		  	OPMLOCAL=SolMenorDist2;
		  	solucion[num]=k;//nos la quedamos
		  	
		    }
		  	else{
		  		SolMenorDist3=SolMenorDist; //y si no la anterior distancia sigue siendo la funcion objetivo
			  }
           }
        }
    }
	
	if(SolMenorDist3>OPMLOCAL) //esto es para el bucle for x>200, 200 iteraciones 
	OPMLOCAL=SolMenorDist3;     //si es mayor se toma como optimo local
    }
    
     printf("\nPuntos: ");
     for(i=0;i<n;i++) {
     printf("%d ", solucion[i]);
        }
     printf("\n");   
     printf("\nFuncion Objetivo:  %f \n",OPMLOCAL);
}

   

   //***********************************************************************************************//
   //********************************SOLUCION VORAZ*************************************************//
   
   void solucionVoraz(int m,int n,float matriz[500][500])
{
   int i,j,r,Voraz,longSolVoraz,SolVoraz[n];
   float MayorDist=0;
   float DistMenores[m];//m es el numero de puntos disponibles
   float MayorMenorDist=0;
   float SolMenorDist=INT_MAX;//int_max es el maximo numero entero en c
   
   for (i=0; i<n; i++)
   {
	if (i==0)
	{	
   srand(time(NULL));//con esto los numero aletorios no empiezan siempre igual.
   SolVoraz[i] = rand()%m;//la primera solucion es aleatoria

    for(j=0; j<m; j++) {
		if(matriz[SolVoraz[i]][j]>MayorDist&&SolVoraz[i]!=j){
	  		MayorDist=matriz[SolVoraz[0]][j];//la segunda solucion(j) es la mas lejana del aleatorio.
			SolVoraz[ i+1 ] =j;
			}}
			i++;//se aumenta uno para que pase a la siguiente solucion
    }
    else 
	{
	for(r=0;r<i;r++) //0 1 para compararlos con todos los Zs luego es 0 1 2 //i=2 y luego i=3 asi sucesivamente
    {
	    for(j=0; j<m; j++) //0 a 9
	    {
		if (SolVoraz[r]!=j)//para que no se compare con el mismo munero 
	    {
	    	if (DistMenores[j]==0)
	    	{
	    		DistMenores[j]=matriz[SolVoraz[r]][j];//se coloca primera comparacion en un array 
				                                        //con todas las distancias menores
			}
			else{
				if(matriz[SolVoraz[r]][j]<DistMenores[j]){//si no es la primera distancia se compara con la anterior
					DistMenores[j]=matriz[SolVoraz[r]][j];}//y si es menor toma su posicion en distmenores
			    }
		    }
	    }
    }

			for(j=0;j<i;j++){ 
        DistMenores[SolVoraz[j]]=0;}	//en esta parte se igualan todas las distancias de las soluciones ya 
        								//tomadas a cero para que no se vuelvan a considerar
        
		MayorMenorDist=0;//se iguala a cero para que en la sgte iteracion no se repita el numero!!!(un dia y medio en darme cuenta)
		for(j=0; j<m; j++){
		if(DistMenores[j]>MayorMenorDist){//se coge la mayor de las distancias menores entre los puntos
			MayorMenorDist=DistMenores[j];
					    Voraz=j;}} //ese es elegido como el siguiente voraz.
					    
		SolVoraz[i]=Voraz;	
    }
    }
         for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                if (matriz[SolVoraz[i]][SolVoraz[j]] < SolMenorDist){//se obtiene la menor distancia de los
                    SolMenorDist = matriz[SolVoraz[i]][SolVoraz[j]];}   //ptos selecionados, esta menor distancia
                         										         //seria la solucion.
            }
        }     

    longSolVoraz=sizeof(SolVoraz)/sizeof(SolVoraz[0]);//se obtiene la longitud del array SolVoraz
    
    printf("\nSolucion Voraz");
    printf("\n--------------");
    printf(" \nPuntos: ");
    for(i=0;i<longSolVoraz;i++) {
    printf(" %d ", SolVoraz[i]);
	}
    printf("\n\nSolucion (Menor distancia): %f\n",SolMenorDist);
}


 //***********************************************************************************************//
   //********************************SOLUCION ALEATORIA*******************************************//

   void solucionAleatoria(int m,int n,int solucion[50])
{
   int i,j,num;
   srand(time(NULL));//para que no se repita el orden aletorio
    for(i=0;i<n;i++) 
	{ 
        int num = rand()%m; //numero aleatorio o random
    if(i>0) 
    {   
      for(j=0; j < i; j++)     
          if(num==solucion[j]) //se compara para que no se repita
          { 
             num =rand()%m; 
             j=-1;                          
          } 
    } 
    solucion[ i ] =num; 
    }
    
}
   
   //***********************************************************************************************//
   //********************************EVALUACION DE LA SOLUCION ALEATORIA***************************//
   
   
   void EvaluacionSol(int m,int n,int solucion[50],float matriz[500][500]) 
{
   	int i,j;
   	float minDis= INT_MAX;
   	   printf("Solucion aleatoria: ");
	   for (i=0;i<n;i++) {
	        printf("%d ",solucion[i]); 
            }
	   for(i=0; i<n;i++){//con los dos bucles for se comparan los dos soluciones obtenidas
	   	   for (j=i+1; j<n;j++){
	   	   	printf("\n\nPuntos %d ",solucion[i]);
	   	   	printf("- %d",solucion[j]);
	   	   	printf(" distancia = %f",matriz[solucion[i]][solucion[j]]);
	   	   	if(matriz[solucion[i]][solucion[j]]<minDis){//Se van comparando tomando el menor de todos
	   	   		minDis=matriz[solucion[i]][solucion[j]];
				  }
			  }
	   }
		printf("\n\nMinima distancia= %.5f",minDis);
}

// * written by  Jorge G. Moreno López.  * jorgustav@gmail.com*// 
   
 
