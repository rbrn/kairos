/*
 * Copyright 2013 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.springframework.social.showcase.account;

import org.springframework.dao.DuplicateKeyException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

import javax.inject.Inject;
import java.sql.ResultSet;
import java.sql.SQLException;

@Repository
public class JdbcUserRepository implements UserRepository {

	private final JdbcTemplate jdbcTemplate;

	private final PasswordEncoder passwordEncoder;

	@Inject
	public JdbcUserRepository(JdbcTemplate jdbcTemplate, PasswordEncoder passwordEncoder) {
		this.jdbcTemplate = jdbcTemplate;
		this.passwordEncoder = passwordEncoder;
	}

	@Transactional
	public void createAccount(Account user) throws UsernameAlreadyInUseException {
		try {
			jdbcTemplate.update(
					"insert into utenti (id_utente, pwd_utente, nome, cognome, email, sesso, stato) values (?, ?, ?, ?, ?, ?, ?)",
					user.getUsername(), passwordEncoder.encode(user.getPassword()), user.getFirstName(), user.getLastName(), user.getEmail(), user.getSex(), 1);
		} catch (DuplicateKeyException e) {
			throw new KairosUserInUseException(user.getUsername());
		}
	}

	public Account findAccountByUsername(String username) {
		return null;
	}

}
