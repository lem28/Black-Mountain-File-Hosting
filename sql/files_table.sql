drop table if exists files;
create table files
(
	file_id INT(12) primary key auto_increment,
	file_name varchar(128),
	file_url varchar(128),
    upload_date datetime,
    expiration_date datetime
);
