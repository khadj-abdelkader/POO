<html>
<head>
 <meta charset = "UTF-8">
	 <body>
</head>
  <title> Ma page d'accueil </title>
        <h1> Bienvenue sur le site de Big Hallouf </h1>
        <h2> Commencez-donc par vous inscrire :</h2>
        <form name="inscription" method="post" action="IMC.php">
          Entrez votre prénom : <input type="text" name="pseudo"> <br>
             Entrez votre taille : <input type="text" name="taille"> <br>
             Entrez votre poids : <input type="text" name="poids"> <br>
            <input type="submit" name="valider" value="OK">
        </form> 
        <? php
        if (iset($_POST)("Submit"))
        {

        $prénom=$_POST ("pseudo");
        $taille=$_POST ("taille");
        $taille=$_POST ("poids");
        $IMC=$_POST ("IMC");
        echo "Salut pseudo votre IMC est $IMC";
		}

        
	</body>
