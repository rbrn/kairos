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
package org.springframework.social.showcase.signup;

import org.hibernate.validator.constraints.NotEmpty;
import org.hibernate.validator.constraints.impl.EmailValidator;
import org.springframework.social.connect.UserProfile;

import javax.validation.constraints.Size;

public class SignupForm {

    @NotEmpty
    private String username;
    @Size(min = 6, message = "must be at least 6 characters")
    private String password;
    @NotEmpty
    private String firstName;
    @NotEmpty
    private String lastName;
    @NotEmpty()
    @Size(max = 1, message = "the sex is max 1 char")
    private String sex;
    @NotEmpty
    private String email;

    public static SignupForm fromProviderUser(UserProfile providerUser) {
        SignupForm form = new SignupForm();
        form.setFirstName(providerUser.getFirstName());
        form.setLastName(providerUser.getLastName());
        form.setUsername(providerUser.getUsername());
        form.setEmail(providerUser.getEmail());
        form.setSex("M");
        return form;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getSex() {
        return sex;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }
}
