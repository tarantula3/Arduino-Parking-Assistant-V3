<?PHP
  // VPS hosting
  $con = new mysqli("127.0.0.1", "USERID", "PASSWORD", "Arduino");
  if (mysqli_connect_errno()) die('Could not connect: ' . mysqli_error());
?>