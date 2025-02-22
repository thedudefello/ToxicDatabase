<?php

	
  /*=-=[ Logout ]=-=*/
  if (isset ($HTTP_GET_VARS ['a']) && $HTTP_GET_VARS ['a']=='logout') {
  	setcookie ("SID", "");
	setcookie ("save_sess", "");
	session_start ();
	session_unset ();
	session_destroy ();
	header ("Location: login.html"); // <- After-logout page
	exit ();
  }

	if (isset ($HTTP_COOKIE_VARS['SID']) && $HTTP_COOKIE_VARS['SID'] != "") session_id ($HTTP_COOKIE_VARS['SID']);
	session_start();

	session_register('Advanced_uid');
	session_register('Advanced_id');
	session_register('Advanced_email');
	session_register('Advanced_name');
	session_register('Advanced_company');
	session_register('SID');

	$SID = session_id();
	$Advanced_uid = "1";
	$Advanced_id = "2";
	$Advanced_name = "3";
	$Advanced_email = "4";
	$Advanced_company = "5";

	setcookie ("SID", $SID, time ());
	header("Location: options.php?p=autologin"); // <- After-login page. It's DEMO. In really you must change link at the end of file!!!
	exit ();
?>

