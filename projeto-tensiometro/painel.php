<?php
    include('protect.php');
    include('conexao.php');
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <title>Painel de Controle</title>

        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">

        <!-- REFERÊNCIA BOOTSTRAP -->
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

        <style>

            table, th, td {
                border: 1px solid black;
            }
            td, th{
                padding: 5px 10px;
            }

        </style>
    </head>
    <body>
        <p class="text-center mt-5">Bem vindo ao Painel de Controle, <?php echo $_SESSION['nome_usuario']; ?>.</p>
        
        <div class="d-flex align-items-center justify-content-center h-100 text-center mt-5">
            <?php
            
                $sql = "SELECT id_leitura, data_leitura, hora_leitura, pressao_leitura FROM tbl_leitura";

                $result = $mysqli->query($sql);

                if ($result->num_rows > 0) {
                    echo "
                    <table>
                    <tr>
                        <th>Id</th>
                        <th>Data</th>
                        <th>Hora</th>
                        <th>Pressão</th>
                    </tr>";
                    // output data of each row
                    while($row = $result->fetch_assoc()) {
                    echo 
                        "<tr>
                            <td>".$row["id_leitura"]."</td>
                            <td>".$row["data_leitura"]."</td>
                            <td>".$row["hora_leitura"]."</td>
                            <td>".$row["pressao_leitura"]."</td>
                        </tr>";
                    }
                    echo "</table>";
                } else {
                    echo "<p class=\"text-center mt-5\">0 results</p>";
                }

                $mysqli->close();
            ?>
        </div>

        <p class="text-center mt-5">
            <a href="logout.php">Sair</a>
        </p>
    </body>
</html>