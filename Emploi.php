<html>
    <head>
	<meta charset = "UTF-8">
	<title> Ma page d'accueil </title>
</head>
   <body>
        <h1>BONJOUR </h1>
        <?php
        //Initialisation des variables
        $travail= "L'informatique, la robotique ou l'électronique";
        $salaire=2000;
        $etude=false;
        $bac=11.5 ;
		
        //affichage
        echo  "Le salaire auquel j'aspire pour bien vivre : <b> $salaire </b> € <br>" ;
        echo  "La branche dans laquelle je travaille ou souhaiterais travailler : <b> $travail </b> <br>" ;
        echo "Pour préciser : <b> $travail </b>";
        if ($etude==false)
		{
            echo "<b> sont une des branches dans laquelle je souhaiterais travailler. </b> <br>";
       		}
        		else
			{
            		Echo "<b> est la branche dans laquelle je travaille. </b> <br>";
      			}
        	echo "La note moyenne que j'ai obtenue au bac : <b> $bac </b>" ;
         

        ?>   
    </body>
</html>
