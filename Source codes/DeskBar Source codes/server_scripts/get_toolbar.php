<?
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	Settings section
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
	/*=-=[ Guest XML-file, containing login-button ]=-=*/
	$guest_xml = '
<TOOLBAR>
	<BUTTON caption="Login" id="tb_btn_login" img="53" command="dologin"/>
	<SEPARATOR/>
<COMMANDS>
	<WEBJUMP name="dologin" href="http://localhost/dbscripts/login.html" newbrowserwindow="minibrowser"/>
</COMMANDS>
</TOOLBAR>';

	/*=-=[ Member XML-file, containing all after-login elements ]=-=*/
	$member_xml = '
<TOOLBAR>
	<BANNER name="MessageRollingArea" url="http://localhost/dbscripts/usermessage.php" width="150" id="tb_bnr_message"/>
	<SEPARATOR/>
	<BUTTON caption="Logout" id="tb_btn_logout" img="53" href="http://localhost/dbscripts/login.php?a=logout" command="redirect"/>
	<SEPARATOR/>
</TOOLBAR>';

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	Send XML to the toolbar
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
	header("Cache-control: private");
	/*header("Content-type: text/plain");*/
	header("Content-Disposition: ; filename=tb_member.xml");

	/*=-=[ Try to read cookies for SID and start session ]=-=*/
	if (isset ($HTTP_COOKIE_VARS['SID'])) session_id ($HTTP_COOKIE_VARS['SID']);
	session_start();

	/*=-=[ Is it member? ]=-=*/
	if (session_is_registered('Advanced_uid') && session_is_registered('Advanced_id') &&
	 session_is_registered('Advanced_email') && session_is_registered('Advanced_name') &&
	 session_is_registered('Advanced_company') && session_is_registered('SID')) print ($member_xml);
	/*=-=[ Or it guest? ]=-=*/
	else print ($guest_xml);
?>