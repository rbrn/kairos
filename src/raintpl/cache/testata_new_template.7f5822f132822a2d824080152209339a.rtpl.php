<?php if(!class_exists('Rain\Tpl')){exit;}?><div id="wrap">
    <!-- Fixed navbar -->
    <div class="navbar navbar-default navbar-fixed-top">
        <div class="container">
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="<?php echo static::$conf['base_url']; ?>index.php?risorsa=index">Kairos 2.0</a>
            </div>

            <div class="collapse navbar-collapse">
                <ul class="nav navbar-nav">
                    <li class="active"><a href="<?php echo static::$conf['base_url']; ?>index.php?risorsa=index"><span class="glyphicon glyphicon-home"></span><?php echo htmlspecialchars( $stringa["home"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a>
                    </li>
                    <?php if( $ruolo == 'staff' or $ruolo == 'admin' ){ ?>

                    <li><a href="<?php echo static::$conf['base_url']; ?>index.php?risorsa=materiali"><span class="glyphicon glyphicon-th-large"></span><?php echo htmlspecialchars( $stringa["materiali"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a>
                    </li>
                    <li><a href="<?php echo static::$conf['base_url']; ?>index.php?risorsa=cerca"><span class="glyphicon glyphicon-search"></span><?php echo htmlspecialchars( $stringa["cerca"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a>
                    </li>
                    <li><a href="<?php echo static::$conf['base_url']; ?>index.php?risorsa=admin_index"><span class="glyphicon glyphicon-cog"></span><?php echo htmlspecialchars( $stringa["admin"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a>
                    </li>
                    <?php } ?>



                    <li class="dropdown">
                        <?php if( $id_utente ){ ?>

                        <a href="<?php echo static::$conf['base_url']; ?>#" class="dropdown-toggle" data-toggle="dropdown">
                            <span class="glyphicon glyphicon-user"></span><?php echo htmlspecialchars( $stringa["buon_lavoro"], ENT_COMPAT, 'UTF-8', FALSE ); ?>, <b><?php echo htmlspecialchars( $id_utente, ENT_COMPAT, 'UTF-8', FALSE ); ?></b>
                            <b class="caret"></b></a>
                        <?php } ?>

                        <?php if( !$id_utente ){ ?>

                        <a href="<?php echo static::$conf['base_url']; ?>#" class="dropdown-toggle" data-toggle="dropdown">
                            <span class="glyphicon glyphicon-user"></span><?php echo htmlspecialchars( $stringa["guest_welcome"], ENT_COMPAT, 'UTF-8', FALSE ); ?></b>
                            <b class="caret"></b></a>
                        <?php } ?>

                        <ul class="dropdown-menu">
                            <?php if( $id_utente ){ ?>

                            <li><a href="<?php echo static::$conf['base_url']; ?>index.php?risorsa=messaggi">
                                <span class="glyphicon glyphicon-envelope"></span>
                                <?php echo htmlspecialchars( $stringa["posta_interna"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a></li>

                            <li><a href="<?php echo static::$conf['base_url']; ?>index.php?risorsa=calendario">
                                <span class="glyphicon glyphicon-calendar"></span><?php echo htmlspecialchars( $stringa["eventi"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a></li>
                            <li><a href="javascript:;"
                                   onclick="javascript:apri_scheda(appunti.php, myRemoteUtente,
    'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0, menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0,myWindowUtente)"
                                    ><span class="glyphicon glyphicon-list-alt"></span><?php echo htmlspecialchars( $stringa["appunti"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a></li>
                            <?php } ?>


                            <?php if( !$id_utente ){ ?>

                            <li><a href="<?php echo static::$conf['base_url']; ?>index.php?risorsa=do_login">
                                <span class="glyphicon glyphicon-log-in"></span>
                                <?php echo htmlspecialchars( $stringa["login"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a></li>
                            <?php } ?>


                            <?php if( $ruolo == 'staff' or $ruolo == 'admin' ){ ?>

                            <li><a href="<?php echo static::$conf['base_url']; ?>index.php?risorsa=lo_repository">
                                <span class="glyphicon glyphicon-briefcase"></span><?php echo htmlspecialchars( $stringa["Repository"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a></li>
                            <?php } ?>


                            <li class="divider"></li>
                            <li class="dropdown-header"></li>


                            <?php if( !$id_utente ){ ?>

                            <a href="http://<?php echo htmlspecialchars( $server, ENT_COMPAT, 'UTF-8', FALSE ); ?>:<?php echo htmlspecialchars( $port, ENT_COMPAT, 'UTF-8', FALSE ); ?>/<?php echo htmlspecialchars( $context, ENT_COMPAT, 'UTF-8', FALSE ); ?>">
                                <span class="btn btn-mini btn-facebook"><i class="icon-facebook"></i> | Connect with
                                    Facebook
                                </span>
                            </a>
                            <?php } ?>


                            <?php if( $id_utente ){ ?>

                            <li>
                                <span class="btn btn-mini btn-info"><i class="icon-info"></i> <a href="<?php echo static::$conf['base_url']; ?>index.php?risorsa=modulo_utente"><?php echo htmlspecialchars( $stringa["modifica_profilo"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a></li>
                            <?php } ?>

                            <li class="divider"></li>
                            <li>
                                <a tabindex="-1" href="<?php echo htmlspecialchars( $script, ENT_COMPAT, 'UTF-8', FALSE ); ?>?<?php echo htmlspecialchars( $query_string, ENT_COMPAT, 'UTF-8', FALSE ); ?>&lingua=it<?php echo htmlspecialchars( $target, ENT_COMPAT, 'UTF-8', FALSE ); ?>">
                                    Italiano
                                    <img name="flag_it" border="0" src="http://<?php echo htmlspecialchars( $server, ENT_COMPAT, 'UTF-8', FALSE ); ?>/kairos/img/flags/it.png" width="16"
                                         height="11" align="absmiddle" hspace="5" alt="versione italiana"></a>
                            </li>

                            <li>
                                <a href="<?php echo htmlspecialchars( $script, ENT_COMPAT, 'UTF-8', FALSE ); ?>?<?php echo htmlspecialchars( $query_string, ENT_COMPAT, 'UTF-8', FALSE ); ?>&lingua=us<?php echo htmlspecialchars( $target, ENT_COMPAT, 'UTF-8', FALSE ); ?>">
                                    English US
                                    <img name="flag_en" border="0" src="http://<?php echo htmlspecialchars( $server, ENT_COMPAT, 'UTF-8', FALSE ); ?>/kairos/img/flags/us.png" width="16" height="11"
                                         align="absmiddle"
                                         hspace="5" alt="english/us version"></a>
                            </li>
                            <li>
                                <a href="<?php echo htmlspecialchars( $script, ENT_COMPAT, 'UTF-8', FALSE ); ?>?<?php echo htmlspecialchars( $query_string, ENT_COMPAT, 'UTF-8', FALSE ); ?>&lingua=ro<?php echo htmlspecialchars( $target, ENT_COMPAT, 'UTF-8', FALSE ); ?>">
                                    Romana
                                    <img name="flag_ro" border="0" src="http://<?php echo htmlspecialchars( $server, ENT_COMPAT, 'UTF-8', FALSE ); ?>/kairos/img/flags/ro.png" width="16" height="11"
                                         align="absmiddle"
                                         hspace="5" alt="romanian version"></a>
                            </li>
                            <li class="divider"></li>
                            <?php if( $id_utente ){ ?>

                            <li>
                                <a tabindex="-1" href="<?php echo static::$conf['base_url']; ?>logout.php" title="<?php echo htmlspecialchars( $stringa["logout_alt"], ENT_COMPAT, 'UTF-8', FALSE ); ?>"> <?php echo htmlspecialchars( $target, ENT_COMPAT, 'UTF-8', FALSE ); ?><span
                                        class="glyphicon glyphicon-off"></span> <?php echo htmlspecialchars( $stringa["logout_alt"], ENT_COMPAT, 'UTF-8', FALSE ); ?></a>
                            </li>
                            <?php } ?>

                        </ul>
                    </li>

                    <?php if( !$id_utente ){ ?>

                    <li>
                        <a href="http://<?php echo htmlspecialchars( $server, ENT_COMPAT, 'UTF-8', FALSE ); ?>:<?php echo htmlspecialchars( $port, ENT_COMPAT, 'UTF-8', FALSE ); ?>/<?php echo htmlspecialchars( $context, ENT_COMPAT, 'UTF-8', FALSE ); ?>">
                            <i class="icon-facebook"></i> | <i class="icon-twitter"></i>
                            <i class="icon-linkedin"></i> |
                            Connect using your favourite social identity

                        </a>
                    </li>

                    <?php } ?>

                </ul>
            </div>
            <!--/.nav-collapse -->
        </div>
    </div>