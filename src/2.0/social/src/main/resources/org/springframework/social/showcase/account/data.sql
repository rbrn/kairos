update utenti set data_reg = current_timestamp where data_reg is null;
ALTER TABLE utenti MODIFY data_reg datetime DEFAULT CURRENT_TIMESTAMP;

ALTER TABLE Account ADD UNIQUE (username);