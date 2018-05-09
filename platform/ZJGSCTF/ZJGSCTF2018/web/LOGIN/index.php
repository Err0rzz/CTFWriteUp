<html>
<head>
    <meta http-equiv="content-type" content="text/html;charset=utf8">
    <title>intersting </title>
</head>
<body>
<form action="index2.php" method="post">
    username:  <input name="username" type="text" /><br/>
    password:  <input name="password" type="password"><br/>
                <input name="submit" type="submit">
</form>
</body>
</html>
<?php
  $dbhost = "localhost";
  $dbuser = "root";
  $dbpass = "12ytsdsg";
  $db = "ctf";
  $conn = mysql_connect($dbhost,$dbuser,$dbpass);
  if($conn)
	   echo "connect is success";
   else
	   echo "connect is fail ";
  $vo=mysql_select_db($db,$conn);
function   filter($str){
      $filterlist = "/\(|\)|username|password|where|case|when|like|regexp|into|limit|=|for|;/";
      if(preg_match($filterlist,strtolower($str))){
        die(" stupid hacker .illegal input!");
      }
      return $str;
  }
$username = isset($_POST['username'])?filter($_POST['username']):die("please input username!");
$paaword = isset($_POST['password'])?filter($_POST['password']):die("please input password!");
echo $username;
echo $paaword;
$sql = "select * from admin where username='$username' and password='$paaword'";
$res =mysql_query($sql,$conn);
if($result=mysql_fetch_array($res)){
     echo $result['username'];
}else{
   echo "the flag == password";
}
?>
