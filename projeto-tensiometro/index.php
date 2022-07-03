<?php
    include('conexao.php');

    if(isset($_POST['email_usuario']) || isset($_POST['senha_usuario'])) {

        if(strlen($_POST['email_usuario']) == 0) {
            echo "<p class=\"text-center mt-5\">Preencha seu e-mail</p>";
        } else if(strlen($_POST['senha_usuario']) == 0) {
            echo "<p class=\"text-center mt-5\">Preencha sua senha</p>";
        } else {

            $email = $mysqli->real_escape_string($_POST['email_usuario']);
            $senha = $mysqli->real_escape_string($_POST['senha_usuario']);

            $sql_code = "SELECT * FROM tbl_usuario WHERE email_usuario = '$email' AND senha_usuario = '$senha'";
            $sql_query = $mysqli->query($sql_code) or die("Falha na execução do código SQL: " . $mysqli->error);

            $quantidade = $sql_query->num_rows;

            if($quantidade == 1) {
                
                $usuario = $sql_query->fetch_assoc();

                if(!isset($_SESSION)) {
                    session_start();
                }

                $_SESSION['id_usuario'] = $usuario['id_usuario'];
                $_SESSION['nome_usuario'] = $usuario['nome_usuario'];

                header("Location: painel.php");

            } else {
                echo "<p class=\"text-center mt-5\">Falha ao logar! E-mail ou senha incorretos</p>";
            }
        }
    }
?>
<!DOCTYPE html>

<html lang="pt-br">

    <head>
        <title> Projeto Tensiômetro - Login</title>

        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <!-- REFERÊNCIA BOOTSTRAP -->
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
    </head>

    <body>
        <h1 class="text-center mt-5"> Projeto Tensiômetro </h1>

        <div class="text-center mt-5">
            <form action="" method="POST">
                <p>
                    <label>E-mail</label>
                    <input type="text" name="email_usuario">
                <p>
                    <label>Senha</label>
                    <input type="password" name="senha_usuario">
                </p>
                <p>
                    <button type="submit">Entrar</button>
                </p>
            </form>
        </div>
    </body>

</html>