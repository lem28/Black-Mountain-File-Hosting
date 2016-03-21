<?php
$servername = "localhost";
$username = "root";
$password = "herecomesthesnow45";
$dbname = "black_mountain";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

// sql to create table
$sql = "create table files
(
	file_id int(128) primary key auto_increment,
	file_name text,
	file_url text,
    upload_date datetime,
    expiration_date datetime
)";

if (mysqli_query($conn, $sql)) {
    echo "Table created successfully";
} else {
    echo "Error creating table: " . mysqli_error($conn);
}
