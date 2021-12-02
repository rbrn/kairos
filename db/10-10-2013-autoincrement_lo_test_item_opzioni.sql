truncate lo_test_item_opzioni;
alter table lo_test_item_opzioni modify column id_item_opzione int(8) not null auto_increment;
truncate lo_test_item;
alter table lo_test_item modify column id_item int(15) not null auto_increment;
--prod
