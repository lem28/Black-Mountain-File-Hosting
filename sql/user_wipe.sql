drop table if exists users;
create table users
(
	user_id INT(12) primary key auto_increment,
	user_login varchar(64),
	user_pw varchar(64),
	user_first_name varchar(32),
	user_last_name varchar(32),
	user_email varchar(32),
	activeSession varchar(128),
    firstLogin datetime,
    lastLogin  datetime
);
