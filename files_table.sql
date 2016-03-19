drop table if exists files;
create table files
(
	file_id int(24) primary key auto_increment,
	file_name shorttext,
	file_url text,
    upload_date datetime,
    expiration_date datetime
);
