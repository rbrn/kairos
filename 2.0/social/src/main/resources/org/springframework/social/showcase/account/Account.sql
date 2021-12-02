create table Account (id int not null,
						username varchar(50) not null,
						password varchar(50) not null,
						firstName varchar(50) not null, 
						lastName varchar(50) not null,
						primary key (id));
						ALTER TABLE `account` CHANGE `id` `id` INT( 11 ) NOT NULL AUTO_INCREMENT ;