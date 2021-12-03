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
package org.springframework.social.showcase;

import org.springframework.social.connect.ConnectionRepository;
import org.springframework.social.showcase.account.AccountRepository;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.inject.Inject;
import javax.inject.Provider;
import java.security.Principal;

@Controller
public class HomeController {

    public static final String URL_APP = "http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com";
    //public static final String URL_APP = "http://localhost";
    private final Provider<ConnectionRepository> connectionRepositoryProvider;
    private final AccountRepository accountRepository;

    @Inject
    public HomeController(Provider<ConnectionRepository> connectionRepositoryProvider, AccountRepository accountRepository) {
        this.connectionRepositoryProvider = connectionRepositoryProvider;
        this.accountRepository = accountRepository;
    }

    @RequestMapping("/")
    public String home(Principal currentUser, Model model) {
        model.addAttribute("connectionsToProviders", getConnectionRepository().findAllConnections());
        if (accountRepository.findAccountByUsername(currentUser.getName()) == null) {
            return "/signup";
        }
        model.addAttribute(accountRepository.findAccountByUsername(currentUser.getName()));
        return "redirect:" + URL_APP + "/kairos/logingateway.php?id=" + currentUser.getName();
    }

    private ConnectionRepository getConnectionRepository() {
        return connectionRepositoryProvider.get();
    }
}
