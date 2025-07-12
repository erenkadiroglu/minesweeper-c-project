#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h> // Kullanicidan input almak icin

int main()
{
	int boyut,mayinSayisi,satir,sutun,i,j,m,n,sayac;
	char izlenenYol[500][500]; // Kullanicinin hareket ettigi yolu hafizada tutan matris
	while(1)
	{
		// Hafizadaki Bilgileri Sifirlama
		sayac=0;
		satir=0;
		sutun=0;
        for (i=0 ; i<500 ; i++) 
		{
            for (j=0 ; j<500 ; j++)
			{
                izlenenYol[i][j] ='.';
            }
        }
        printf("=======================================\n");
		printf("  <<< MAYIN TARLASINA HOSGELDINIZ >>>  ");
		printf("\n=======================================\n");
		printf("-KURALLAR-\n");
		printf("1-) Oyundaki amaciniz, basladiginiz noktadan cikis noktasina(sag en alt) guvenli sekilde ulasmak.\n");
		printf("2-) Oyuna baslamadan once oynamak istediginiz alan boyutunu sececeksiniz.\n");
		printf("3-) Oyun alaninin rastgele yerlerinde , sizin sectiginiz boyuta oranla mayinlar dosenmistir.\n");
		printf("4-) Eger cikisa ulasmadan once mayina basarsaniz oyunu kaybedersiniz ancak mayinin etki alanlarina basarsaniz baslangic noktasina geri donersiniz.(oyunu kaybetmeden))\n");
		printf("5-) Bulundugunuz konum 'O' ile isaretlenmektedir.\n");
		printf("Bol sans ^^\n");
		printf("\nOynamak Istediginiz Alan Boyutunu Giriniz : ");
		scanf("%d",&boyut);
		mayinSayisi=boyut*boyut/20;
		printf("\nIstediginiz Alan Boyutu : %dx%d\n",boyut,boyut);
		printf("Oyun Alaninda Bulunan Mayin Sayisi : %d\n",mayinSayisi); 
		char oyunAlani[boyut][boyut];
		
		for(i=0 ; i<boyut ; i++)
		{
			for(j=0 ; j<boyut ; j++)
			{
				oyunAlani[i][j]='.'; // Oyun alaninda gorunen matris elemanlari
			}
		}
	
		srand(time(NULL)); 
		// Oyun alaninda rastgele yerlere mayin ve etrafina etki alanini yerlestirme
		for (i=0; i<mayinSayisi ; i++)
		{
		    do{
		        m = rand() % boyut; 				
		        n = rand() % boyut; 
		    }while ((m==0 && n==0) || (m==boyut-1 && n==boyut-1) || (m==0 && n==1) || (m==1 && n==0) || (m==boyut-2 && n==boyut-1) || (m==boyut-1 && n==boyut-2) || oyunAlani[m][n] == '#'); // Baslangic veya bitis noktalarina mayin veya etki alani gelirse ya da mayinlar ayni yere denk gelirse yeniden rastgele secmesi icin 
		
		    oyunAlani[m][n] ='#'; // MAYIN
		    if(m>0 && oyunAlani[m-1][n] !='#')
		    {
		        oyunAlani[m-1][n] ='x'; // Mayinin ustundeki etki alani
		    }
		    if(m<boyut-1 && oyunAlani[m+1][n] !='#')
		    {
		        oyunAlani[m+1][n] ='x'; // Mayinin altindaki etki alani
		    }
		    if(n>0 && oyunAlani[m][n-1] !='#')
		    {
		        oyunAlani[m][n-1] ='x'; // Mayinin solundaki etki alani
		    }
		    if(n<boyut-1 && oyunAlani[m][n+1] !='#')
		    {
		        oyunAlani[m][n+1] ='x'; // Mayinin sagindaki etki alani
		    }
		}
		
	    while (1)
		{
			printf("\n");
			// matrisi ekrana yazdirma
		    for (i=0 ; i<boyut ; i++)
		    {
		        for (j=0 ; j<boyut ; j++)
		        {
		        	if (i==satir && j==sutun)
				{
					oyunAlani[i][j]='O';
                    printf(" %c",oyunAlani[i][j]); // Kullanicinin konumu
					izlenenYol[i][j] ='@'; // Kullanicinin hareket ettigi yolu '@' ile isaretleme
				}
                else
                    printf(" .");
		        }
		        printf("\n");
		    }
		    printf("\n========================================================================\n");
		    printf("Lutfen Hareket Yonunuzu Seciniz. (W=Yukari , A=Sol , S=Asagi , D=Sag)\nPes Etmek ve Mayinlarin Konumunu Ogrenmek Istiyorsaniz [ P ] Tuslayiniz.");
		    printf("\n========================================================================\n");
		    if (satir==boyut-1 && sutun==boyut-1) // Oyunu kazanma durumu
	        {
	        	printf("\n\nTEBRIKLER!! Oyunu Kazandiniz. (^_^)\n");
	        	printf("Oyun Boyunca %d Kez Etki Alanina Bastiniz.\n",sayac);
	        	printf("(# = Mayin,  x = Etki Alani,  @ = Izlediginiz Yol)\n\n");
	        	// Oyunu kazandiktan sonra oyun alanini ekrana yazdirma
		    for (i=0 ; i<boyut ; i++)
		    {
		        for (j=0 ; j<boyut ; j++)
		        {
		            if(oyunAlani[i][j] =='#')
		                printf(" #");
		            else if(oyunAlani[i][j] =='x')
		                printf(" x");
		            else if(izlenenYol[i][j] =='@')
		                printf(" @");
		            else
		                printf(" .");
		        }
		        printf("\n");
		    }
		    break;
	    	}
	        else if(oyunAlani[satir][sutun]=='#') // Mayina basma durumu
			{
				printf("Mayina bastiginiz icin oyunu kaybettiniz. (-_-)");
				break;
			}
		    
		    hataliTuslama:;
	        // Kullanicinin tus secimi
	        char hareket = getch();
	        switch (hareket)
			{
	            case 'w':
	            case 'W':
	                if (satir > 0) 
					satir--; // Yukari
					if(oyunAlani[satir][sutun]=='x') // Etki alanina basma durumu
		        {
		        				sayac+=1;
		            satir=0;
		            sutun=0;
		            for(i=0 ; i<boyut ; i++)
		            {
		            	for(j=0 ; j<boyut ; j++)
		            	{
		            		izlenenYol[i][j]='.';
						}
					}
					printf("\nBILGILENDIRME: Mayinin etki alanina bastiginiz icin basa dondunuz. (O_O)\n");
		        }
	                break;
	            case 'a':
	            case 'A':
	                if (sutun > 0) 
					sutun--; // Sol
					if(oyunAlani[satir][sutun]=='x') // Etki alanina basma durumu
		        {
		        				sayac+=1;
		            satir=0;
		            sutun=0;
		            for(i=0 ; i<boyut ; i++)
		            {
		            	for(j=0 ; j<boyut ; j++)
		            	{
		            		izlenenYol[i][j]='.';
						}
					}
					printf("\nBILGILENDIRME: Mayinin etki alanina bastiginiz icin basa dondunuz. (O_O)\n");
		        }
	                break;
	            case 's':
	            case 'S':
	                if (satir < boyut-1) 
					satir++; // Asagi
					if(oyunAlani[satir][sutun]=='x') // Etki alanina basma durumu
		        {
		        				sayac+=1;
		            satir=0;
		            sutun=0;
		            for(i=0 ; i<boyut ; i++)
		            {
		            	for(j=0 ; j<boyut ; j++)
		            	{
		            		izlenenYol[i][j]='.';
						}
					}
					printf("\nBILGILENDIRME: Mayinin etki alanina bastiginiz icin basa dondunuz. (O_O)\n");
		        }
	                break;
	            case 'd':
	            case 'D':
	                if (sutun < boyut-1) 
					sutun++; // Sag
					if(oyunAlani[satir][sutun]=='x') // Etki alanina basma durumu
		        {
		        				sayac+=1;
		            satir=0;
		            sutun=0;
		            for(i=0 ; i<boyut ; i++)
		            {
		            	for(j=0 ; j<boyut ; j++)
		            	{
		            		izlenenYol[i][j]='.';
						}
					}
					printf("\nBILGILENDIRME: Mayinin etki alanina bastiginiz icin basa dondunuz. (O_O)\n");
		        }
	                break;
	            case 'p':
	            case 'P':
	            	printf("\n <<< Mayinlarin Yerleri >>>\n(# = Mayin , x = Etki Alani)\n\n");
	            	for (i=0 ; i<boyut ; i++)
			    {
			        for (j=0 ; j<boyut ; j++)
			        {
			            if(oyunAlani[i][j] =='#')
			                printf(" #");
			            else if(oyunAlani[i][j] =='x')
			                printf(" x");
			            else
			                printf(" .");
			        }
			        printf("\n");
			    }
	        	goto pes;
	            	break;
	            default:
	            	goto hataliTuslama;
	                break;
	        }
	    }
	    pes:;
        printf("\n>> Yeni Oyuna Baslamak Icin [ Y ] , Oyundan Cikmak Icin [ Q ] Tuslayiniz. <<\n");
        sectirme:;
        char secim = getch();
        switch(secim)
        {
        	case 'y':
        	case 'Y':
        		break;
        	case 'q':
        	case 'Q':
        		system("cls");
        		printf("<< HAZIRLAYAN >>\n\n Eren KADIROGLU\n\n");
        		return 0;
        		break;
        	default:
        		goto sectirme;
        		break;
		}
        system("cls");
	}
	return 0;	
}
