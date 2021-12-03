package org.springframework.social.showcase.account;

/**
 * Created with IntelliJ IDEA.
 * User: Costin
 * Date: 10/31/13
 * Time: 9:43 PM
 * To change this template use File | Settings | File Templates.
 */
public class KairosUserInUseException extends UsernameAlreadyInUseException {
    public KairosUserInUseException(String username) {
        super("The username '" + username + "' is already in use in kairos.");
    }
}
