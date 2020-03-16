<html>
    <head>
    <meta charset = "UTF-8">
    <title> Ma page d'accueil </title>
    </head>
    <body>
        <h1> Bienvenue sur le site de Big Hallouf </h1>
        <h2> Commencez-donc par vous inscrire :</h2>
        <form name="inscription" method="post" action="Formulaire.php">
            Entrez votre pseudo : <input type="text" name="pseudo"> <br>
            Entrez votre ville : <input type="text" name="ville"> <br>
            <input type="submit" name="valider" value="OK">
        </form> 

<?php 
  $age=$_POST["age"]; 
?>

<?php
if ($age<5)
{
    $verdict="Ok gamingo ! ";
}
elseif ($age<13)
{
    $verdict="Vous êtes un mioche ! ";
}
elseif ($age<18)
{
    $verdict="Vous êtes un(e) ado attardé ! ";
}
else
{
    $verdict="Ah ! enfin un(e) adulte (à priori) responsable ! ";
}
echo $verdict;
?>

        <?php
        if(isset($_POST["valider"]))
            {
                $pseudo=$_POST["pseudo"];
                $ville=$_POST["ville"];
                echo "Salut $pseudo de $ville <br> Bienvenue sur mon site ! ";
            }
        ?>
    </body>
</html>
