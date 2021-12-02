package org.springframework.social.showcase.account;

import org.junit.Before;
import org.junit.Test;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.social.showcase.account.Account;
import org.springframework.social.showcase.account.JdbcAccountRepository;
import org.springframework.util.ReflectionUtils;

import java.sql.ResultSet;
import java.sql.SQLException;

import static org.hamcrest.CoreMatchers.instanceOf;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.mockito.Matchers.anyString;
import static org.mockito.Mockito.*;
import static org.hamcrest.CoreMatchers.notNullValue;


public class JdbcAccountRepositoryTest {

    private JdbcAccountRepository accountRepository;
    private JdbcTemplate templateMock;

    @Before
    public void setUp() {
        templateMock = mock(JdbcTemplate.class);
        PasswordEncoder encoder = mock(PasswordEncoder.class);
        accountRepository = new JdbcAccountRepository(templateMock, encoder);
    }

    @Test
    public void testGetAccountRepository() {
        when(templateMock.queryForInt(anyString(), anyString())).thenReturn(0);
        Account result = accountRepository.findAccountByUsername("costin");
        verify(templateMock, times(1)).queryForInt(anyString(), anyString());
        assertThat("Should be null", result == null);
    }

    @Test
    public void testGetAccountReal() throws SQLException {
        when(templateMock.queryForInt(anyString(), any())).thenReturn(1);
        RowMapper<Account> mapper = mock(RowMapper.class);
        ReflectionUtils.setField(ReflectionUtils.findField(JdbcAccountRepository.class, "rowMapper"), accountRepository, mapper);

        Account mockAccount = mock(Account.class);
        when(templateMock.queryForObject(anyString(), any(RowMapper.class), anyString())) .thenReturn(mockAccount);
        Account result = accountRepository.findAccountByUsername("costin");
        verify(templateMock, times(1)).queryForObject(anyString(), any(RowMapper.class), anyString());
        assertThat(result, notNullValue());
        assertThat(result, instanceOf(Account.class));
    }


}
