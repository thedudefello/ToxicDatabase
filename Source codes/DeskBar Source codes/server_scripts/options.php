<?
	/*=-= Start session =-=*/
	if (isset ($HTTP_COOKIE_VARS['SID'])) session_id ($HTTP_COOKIE_VARS['SID']);
	session_start ();

	if (session_is_registered('Advanced_uid') && session_is_registered('Advanced_id') &&
	 session_is_registered('Advanced_email') && session_is_registered('Advanced_name') &&
	 session_is_registered('Advanced_company') && session_is_registered('SID')) $is_login = true;
	else $is_login = false;

	if (isset ($HTTP_POST_VARS ['p'])) $page = $HTTP_POST_VARS ['p'];
	else if (isset ($HTTP_GET_VARS ['p'])) $page = $HTTP_GET_VARS ['p'];
	else $page = "general";

	/*=-=[ Set cookies configuration ]=-=*/
	if ($is_login && $page == 'autologin' && isset ($HTTP_POST_VARS ['a']) &&
	 $HTTP_POST_VARS ['a'] == 'set' && isset ($HTTP_POST_VARS ['sess_save']) ) {
		/*=-=[ Set session lifetime ]=-=*/
		switch ($HTTP_POST_VARS ['sess_save']) {
			case 'day':
				setcookie ("SID", $HTTP_SESSION_VARS ['SID'], time () + 86400);
				setcookie ("sess_save", "day", time () + 86400);
				break;
			case 'week':
				setcookie ("SID", $HTTP_SESSION_VARS ['SID'], time () + 604800);
				setcookie ("sess_save", "week", time () + 604800);
				break;
			case 'month':
				setcookie ("SID", $HTTP_SESSION_VARS ['SID'], time () + 2592000);
				setcookie ("sess_save", "month", time () + 2592000);
				break;
			case 'forever':
				setcookie ("SID", $HTTP_SESSION_VARS ['SID'], time () + 315360000);
				setcookie ("sess_save", "forever", time () + 315360000);
				break;
			default:
				setcookie ("SID", $HTTP_SESSION_VARS ['SID'], time ());
				break;
		}
		/*=-=[ Redirect to this page ]=-=*/
		header ("Location: options.php?p=autologin");
	}
	/*=-=[ Set local settings ]=-=*/
	else if ($page == 'locale' && isset ($HTTP_POST_VARS ['a']) && $HTTP_POST_VARS ['a'] == 'set' ) {
		/*=-=[ Store settings, you can change it ]=-=*/
		if (isset ($HTTP_POST_VARS ['language']) && $HTTP_POST_VARS ['language'] != "") 
			setcookie ("language", $HTTP_POST_VARS ['language'], time () + 315360000);
		if (isset ($HTTP_POST_VARS ['location']) && $HTTP_POST_VARS ['location'] != "") 
			setcookie ("location", $HTTP_POST_VARS ['location'], time () + 315360000);
		/*=-=[ Redirect to this page ]=-=*/
		header ("Location: options.php?p=locale");
	}
	
	$to_print = '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Advanced Dynamic Toolbar</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<style>
form {
    margin: 0 0 0 0;
  }
body{
  background-color: #ffffff;
} 
p,table,tr,ul{
  font: 11px verdana, arial,helvetica,sans-serif,geneva;
  color: #333333;
  text-align: justify;
}
b{
  font: bold 11px verdana, arial,helvetica,sans-serif,geneva;
  color: #555555;
  font-weight: 700;
}
center{
  font: 11px verdana, arial,helvetica,sans-serif,geneva;
  color: #333333;
}
.bold{
  font: 11px verdana, arial,helvetica,sans-serif,geneva;
  color: #333333;
  font-weight: 700;
}
.title{
  font: 13px verdana, arial,helvetica,sans-serif,geneva;
  color: #333333;
  font-weight: 700;
}
a{
  color: #000000;
  text-decoration: none;
}
a:hover{
  color: #FF0000;
  text-decoration: none;
}

.h_on  { color: #FFFFFF;}
A.h_on:hover { color: #FFFFFF;} 
A.h_on:vizited { color: #FFFFFF;} 
A.h_on:active { color: #FFFFFF;}

.h_off  { color: #000000;}
A.h_off:hover { color: #FF0000;} 
A.h_off:vizited { color: #000000;} 
A.h_off:active { color: #000000;}
</style>
<script language="JavaScript" type="text/JavaScript">
	dom = (document.getElementById)? true : false;
	nn4 = (document.layers)? true : false;
	ie4 = (document.all && !dom)? true : false;

	/*=-=[ Show content-block ]=-=*/
	function show_cnt(elemId) {
		if (dom) document.getElementById(elemId).style.display = "block";
		else if (ie4) document.all[elemId].style.display = "block";
		else alert ("Error: your browser doesn\'t support \'display\' property");
	}
	/*=-=[ Hide content-block ]=-=*/
	function hide_cnt(elemId) {
		if (dom) document.getElementById(elemId).style.display = "none";
		else if (ie4) document.all[elemId].style.display = "none";
		else alert ("Error: your browser doesn\'t support \'display\' property");
	}

	/*=-=[ Switch ON ]=-=*/
	function highlight_on (menu, lnk) {
		if (dom) {
			document.getElementById(menu).bgColor = "#586876";
			document.getElementById(lnk).className = "h_on";
		}
		
		else if (ie4) {
			document.all[menu].bgColor = "#586876";
			document.all[lnk].className = "h_on";
		}
	}
	/*=-=[ Switch OFF ]=-=*/
	function highlight_off (menu, lnk) {
		if (dom) {
			document.getElementById(menu).bgColor = "#FFFFFF";
			document.getElementById(lnk).className = "h_off";
		}
		else if (ie4) {
			document.all[menu].bgColor = "#FFFFFF";
			document.all[lnk].className = "h_off";
		}
	}

	function hide_all () {
		hide_cnt ("cnt_general");
		hide_cnt ("cnt_layout");
		hide_cnt ("cnt_autologin");
		hide_cnt ("cnt_locale");
		hide_cnt ("cnt_alert");
		
		highlight_off ("menu_general", "lnk_general");
		highlight_off ("menu_layout", "lnk_layout");
		highlight_off ("menu_autologin", "lnk_autologin");
		highlight_off ("menu_locale", "lnk_locale");
		highlight_off ("menu_alert", "lnk_alert");
	}

	/*=-=[ Navigate to the.. ]=-=*/
	function navigate (id) {
		hide_all ();

		show_cnt ("cnt_" + id);
		highlight_on ("menu_" + id, "lnk_" + id);
		
		return (false);
	}
		function SaveAndClose()
		{
			window.location = "setpg:save";
		}
		function ChangeButton()
		{
                	document.getElementById("tbs_button_020342").checked = !document.getElementById("tbs_button_020342").checked;
			window.location = "setpg:save";
		}
';

if($is_login=true) {
 $to_print .='window.location = "setpg:save";';

}
$to_print .='</script>
</head>

<body onLoad="hide_all (); ';
	
	switch ($page) {
		case 'layout':
			$to_print .= 'navigate (\'layout\');';
			break;
		case 'autologin':
			$to_print .= 'navigate (\'autologin\');';
			break;
		case 'locale':
			$to_print .= 'navigate (\'locale\');';
			break;
		default:
			$to_print .= 'navigate (\'general\');';
			break;
	}
	
	$to_print .= '">
<table width="100%"  border="0" cellspacing="1" cellpadding="0">
  <tr>
    <td align="center"><span class="title">Advanced Dynamic Toolbar Configuration </span></td>
  </tr>
  <tr>
    <td align="center" height="10"></td>
  </tr>
</table>
<table width="700" border="0" align="center" cellpadding="1" cellspacing="1" bgcolor="#586876">
       <tr>
         <td width="220" align="center" bgcolor="#586876" id="menu_general"><a href="#" class="h_on" onClick="return navigate (\'general\');" id="lnk_general">General Settings</a></td>
         <td width="250" align="center" bgcolor="#FFFFFF" id="menu_layout"><a href="#" class="h_off" onClick="return navigate (\'layout\');" id="lnk_layout">Add/remove Toolbar Buttons</a></td>
         <td width="230" align="center" bgcolor="#FFFFFF" id="menu_autologin"><a href="#" class="h_off" onClick="return navigate (\'autologin\');" id="lnk_autologin">Auto Login Configuration</a></td>
       </tr>
	   <tr>
         <td align="center" bgcolor="#FFFFFF" id="menu_locale"><a href="#" class="h_off" onClick="return navigate (\'locale\');" id="lnk_locale">Location and Language Settings</a></td>
	     <td align="center" bgcolor="#FFFFFF" id="menu_alert"><a href="#" class="h_off" onClick="return navigate (\'alert\');" id="lnk_alert">Alert Configuration</a></td>
         <td bgcolor="#FFFFFF"></td>
       </tr>
       <tr bgcolor="#DCE2E2">
         <td colspan="3">';

	/*=-=[ > Start General ]=-=*/	
	$to_print .= '<table width="100%" align="center" id="cnt_general">
           <tr>
             <td valign=top width=460>Not enough access rights</td>
             <td valign=top>';
		/*=-=[ Show after-login settings ]=-=*/
	if ($is_login) $to_print .= '';
	$to_print .= '
			 </td>
           </tr>
         </table>';
	/*=-=[ < End General ]=-=*/
	
	/*=-=[ > Start Layout ]=-=*/
	$to_print .= '<table width="100%" border="0" id="cnt_layout">
             <tr>
               <td width="250" valign="top"><table width="250"  border="0" cellspacing="1" cellpadding="0">
                   <tr>
                     <td width="20" valign=top><input type=checkbox id=DescriptiveText></td>
                     <td>Show text labels </td>
                   </tr>
                   <tr>
                     <td valign=top width=20><input type=checkbox id=tbs_button_020342 ></td>
                     <td width=100%> Show Bar Init</td>
                   </tr>
                  <tr><td colspan=2> <input type=button value="Save settings" onclick="javascript:SaveAndClose();"> <a href="javascript:SaveAndClose();">Save settings</a></td></tr>
               </table></td>';
		/*=-=[ Show after-login settings ]=-=*/
	if ($is_login) $to_print .= '<td valign="top"></td>';
	$to_print .= '</tr>
           </table>';
	/*=-=[ < End Layout ]=-=*/

	/*=-=[ > Start AutoLogin ]=-=*/
	$to_print .= '<form name="frmCookies" method="post" action="options.php">
			<input name="p" type="hidden" value="autologin">
			<input name="a" type="hidden" value="set">
           <table width="400"  border="0" cellpadding="1" cellspacing="2" id="cnt_autologin">
             <tr>
               <td><strong>How long should the password save in this computer?</strong></td>
             </tr>
             <tr>
               <td><input name="sess_save" type="radio" value="dontsave"';

	if (!isset ($HTTP_COOKIE_VARS['sess_save']) || $HTTP_COOKIE_VARS['sess_save'] == '')
		$sess_save = 'dontsave';
	else $sess_save = $HTTP_COOKIE_VARS['sess_save'];

	if ($sess_save == 'dontsave') $to_print .= ' checked';
	$to_print .= '>Do not save my password</td>
             </tr>
             <tr>
               <td><input name="sess_save" type="radio" value="day"';
	if ($sess_save == 'day') $to_print .= ' checked';
	$to_print .= '>One day</td>
             </tr>
             <tr>
               <td><input name="sess_save" type="radio" value="week"';
	if ($sess_save == 'week') $to_print .= ' checked';
	$to_print .= '>One week</td>
             </tr>
             <tr>
               <td><input name="sess_save" type="radio" value="month"';
	if ($sess_save == 'month') $to_print .= ' checked';
	$to_print .= '>One month</td>
             </tr>
             <tr>
               <td><input name="sess_save" type="radio" value="forever"';
	if ($sess_save == 'forever') $to_print .= ' checked';
	$to_print .= '>Forever</td>
             </tr>
             <tr>
               <td><input type="submit" name="Submit" value="Set options"></td>
             </tr>
           </table>
	       </form>';
	/*=-=[ < End AutoLogin ]=-=*/

	/*=-=[ > Start Locale ]=-=*/
	$to_print .= '		 <form name="frmLocale" method="post" action="options.php">
			<input name="p" type="hidden" value="locale">
			<input name="a" type="hidden" value="set">
           <table width="400"  border="0" cellpadding="1" cellspacing="2" id="cnt_locale">
             <tr>
               <td width="80">Language:</td>
               <td><select name="language">
<option selected value="us">English - United States
<option value="uk">English - United Kingdom 
<option value="cn">Chinese - China (Mainland)
<option value="hk">Chinese - Hong Kong
<option value="tw">Chinese - Taiwan
<option value="b5">Chinese - US &amp; other
<option value="dk">Danish - Denmark 
<option value="au">English - Australia 
<option value="ca">English - Canada
<option value="h1">English - Hong Kong
<option value="in">English - India
<option value="nz">English - New Zealand
<option value="sg">English - Singapore
<option value="aa">English - other Asia
<option value="cf">French - Canada
<option value="fr">French - France 
<option value="de">German - Germany
<option value="gr">Greek - Greece
<option value="it">Italian - Italy
<option value="kr">Korean - Korea 
<option value="no">Norwegian - Norway
<option value="br">Portuguese - Brazil 
<option value="ar">Spanish - Argentina
<option value="mx">Spanish - Mexico
<option value="es">Spanish - Spain
<option value="e1">Spanish - US &amp; other
<option value="se">Swedish - Sweden
</select></td>
             </tr><tr>
               <td>Location:</td>
               <td><SELECT NAME="location"><OPTION VALUE="af" SELECTED>Afghanistan<OPTION VALUE="al">Albania<OPTION VALUE="dz">Algeria<OPTION VALUE="as">American Samoa<OPTION VALUE="ad">Andorra<OPTION VALUE="ao">Angola<OPTION VALUE="ai">Anguilla<OPTION VALUE="aq">Antarctica<OPTION VALUE="ag">Antigua and Barbuda<OPTION VALUE="ar">Argentina<OPTION VALUE="am">Armenia<OPTION VALUE="aw">Aruba<OPTION VALUE="au">Australia<OPTION VALUE="at">Austria<OPTION VALUE="az">Azerbaijan<OPTION VALUE="bs">Bahamas<OPTION VALUE="bh">Bahrain<OPTION VALUE="bd">Bangladesh<OPTION VALUE="bb">Barbados<OPTION VALUE="by">Belarus<OPTION VALUE="be">Belgium<OPTION VALUE="bz">Belize<OPTION VALUE="bj">Benin<OPTION VALUE="bm">Bermuda<OPTION VALUE="bt">Bhutan<OPTION VALUE="bo">Bolivia<OPTION VALUE="ba">Bosnia and Herzegovina<OPTION VALUE="bw">Botswana<OPTION VALUE="bv">Bouvet Island<OPTION VALUE="br">Brazil<OPTION VALUE="io">British Indian Ocean Territory<OPTION VALUE="bn">Brunei Darussalam<OPTION VALUE="bg">Bulgaria<OPTION VALUE="bf">Burkina Faso<OPTION VALUE="bi">Burundi<OPTION VALUE="kh">Cambodia<OPTION VALUE="cm">Cameroon<OPTION VALUE="ca">Canada<OPTION VALUE="cv">Cape Verde<OPTION VALUE="ky">Cayman Islands<OPTION VALUE="cf">Central African Republic<OPTION VALUE="td">Chad<OPTION VALUE="cl">Chile<OPTION VALUE="cn">China<OPTION VALUE="cx">Christmas Island<OPTION VALUE="cc">Cocos (Keeling) Islands<OPTION VALUE="co">Colombia<OPTION VALUE="km">Comoros<OPTION VALUE="cg">Congo<OPTION VALUE="ck">Cook Islands<OPTION VALUE="cr">Costa Rica<OPTION VALUE="ci">Cote D\'Ivoire (Ivory Coast)<OPTION VALUE="hr">Croatia (Hrvatska)<OPTION VALUE="cu">Cuba<OPTION VALUE="cy">Cyprus<OPTION VALUE="cz">Czech Republic<OPTION VALUE="cs">Czechoslovakia (former)<OPTION VALUE="dk">Denmark<OPTION VALUE="dj">Djibouti<OPTION VALUE="dm">Dominica<OPTION VALUE="do">Dominican Republic<OPTION VALUE="tp">East Timor<OPTION VALUE="ec">Ecuador<OPTION VALUE="eg">Egypt<OPTION VALUE="sv">El Salvador<OPTION VALUE="gq">Equatorial Guinea<OPTION VALUE="er">Eritrea<OPTION VALUE="ee">Estonia<OPTION VALUE="et">Ethiopia<OPTION VALUE="fk">Falkland Islands (Malvinas)<OPTION VALUE="fo">Faroe Islands<OPTION VALUE="fj">Fiji<OPTION VALUE="fi">Finland<OPTION VALUE="fr">France<OPTION VALUE="fx">France<OPTION VALUE="gf">French Guiana<OPTION VALUE="pf">French Polynesia<OPTION VALUE="tf">French Southern Territories<OPTION VALUE="ga">Gabon<OPTION VALUE="gm">Gambia<OPTION VALUE="ge">Georgia<OPTION VALUE="de">Germany<OPTION VALUE="gh">Ghana<OPTION VALUE="gi">Gibraltar<OPTION VALUE="gb">Great Britain (UK)<OPTION VALUE="gr">Greece<OPTION VALUE="gl">Greenland<OPTION VALUE="gd">Grenada<OPTION VALUE="gp">Guadeloupe<OPTION VALUE="gu">Guam<OPTION VALUE="gt">Guatemala<OPTION VALUE="gn">Guinea<OPTION VALUE="gw">Guinea-Bissau<OPTION VALUE="gy">Guyana<OPTION VALUE="ht">Haiti<OPTION VALUE="hm">Heard and McDonald Islands<OPTION VALUE="hn">Honduras<OPTION VALUE="hk">Hong Kong<OPTION VALUE="hu">Hungary<OPTION VALUE="is">Iceland<OPTION VALUE="in">India<OPTION VALUE="id">Indonesia<OPTION VALUE="ir">Iran<OPTION VALUE="iq">Iraq<OPTION VALUE="ie">Ireland<OPTION VALUE="il">Israel<OPTION VALUE="it">Italy<OPTION VALUE="jm">Jamaica<OPTION VALUE="jp">Japan<OPTION VALUE="jo">Jordan<OPTION VALUE="kz">Kazakhstan<OPTION VALUE="ke">Kenya<OPTION VALUE="ki">Kiribati<OPTION VALUE="kp">Korea (North)<OPTION VALUE="kr">Korea (South)<OPTION VALUE="kw">Kuwait<OPTION VALUE="kg">Kyrgyzstan<OPTION VALUE="la">Laos<OPTION VALUE="lv">Latvia<OPTION VALUE="lb">Lebanon<OPTION VALUE="ls">Lesotho<OPTION VALUE="lr">Liberia<OPTION VALUE="ly">Libya<OPTION VALUE="li">Liechtenstein<OPTION VALUE="lt">Lithuania<OPTION VALUE="lu">Luxembourg<OPTION VALUE="mo">Macau<OPTION VALUE="mk">Macedonia<OPTION VALUE="mg">Madagascar<OPTION VALUE="mw">Malawi<OPTION VALUE="my">Malaysia<OPTION VALUE="mv">Maldives<OPTION VALUE="ml">Mali<OPTION VALUE="mt">Malta<OPTION VALUE="mh">Marshall Islands<OPTION VALUE="mq">Martinique<OPTION VALUE="mr">Mauritania<OPTION VALUE="mu">Mauritius<OPTION VALUE="yt">Mayotte<OPTION VALUE="mx">Mexico<OPTION VALUE="fm">Micronesia<OPTION VALUE="md">Moldova<OPTION VALUE="mc">Monaco<OPTION VALUE="mn">Mongolia<OPTION VALUE="ms">Montserrat<OPTION VALUE="ma">Morocco<OPTION VALUE="mz">Mozambique<OPTION VALUE="mm">Myanmar<OPTION VALUE="na">Namibia<OPTION VALUE="nr">Nauru<OPTION VALUE="np">Nepal<OPTION VALUE="nl">Netherlands<OPTION VALUE="an">Netherlands Antilles<OPTION VALUE="nt">Neutral Zone<OPTION VALUE="nc">New Caledonia<OPTION VALUE="nz">New Zealand (Aotearoa)<OPTION VALUE="ni">Nicaragua<OPTION VALUE="ne">Niger<OPTION VALUE="ng">Nigeria<OPTION VALUE="nu">Niue<OPTION VALUE="nf">Norfolk Island<OPTION VALUE="mp">Northern Mariana Islands<OPTION VALUE="no">Norway<OPTION VALUE="om">Oman<OPTION VALUE="pk">Pakistan<OPTION VALUE="pw">Palau<OPTION VALUE="pa">Panama<OPTION VALUE="pg">Papua New Guinea<OPTION VALUE="py">Paraguay<OPTION VALUE="pe">Peru<OPTION VALUE="ph">Philippines<OPTION VALUE="pn">Pitcairn<OPTION VALUE="pl">Poland<OPTION VALUE="pt">Portugal<OPTION VALUE="pr">Puerto Rico<OPTION VALUE="qa">Qatar<OPTION VALUE="re">Reunion<OPTION VALUE="ro">Romania<OPTION VALUE="ru">Russian Federation<OPTION VALUE="rw">Rwanda<OPTION VALUE="gs">S. Georgia and S. Sandwich Isls.<OPTION VALUE="kn">Saint Kitts and Nevis<OPTION VALUE="lc">Saint Lucia<OPTION VALUE="vc">Saint Vincent and the Grenadines<OPTION VALUE="ws">Samoa<OPTION VALUE="sm">San Marino<OPTION VALUE="st">Sao Tome and Principe<OPTION VALUE="sa">Saudi Arabia<OPTION VALUE="sn">Senegal<OPTION VALUE="sc">Seychelles<OPTION VALUE="sl">Sierra Leone<OPTION VALUE="sg">Singapore<OPTION VALUE="sk">Slovak Republic<OPTION VALUE="si">Slovenia<OPTION VALUE="sb">Solomon Islands<OPTION VALUE="so">Somalia<OPTION VALUE="za">South Africa<OPTION VALUE="es">Spain<OPTION VALUE="lk">Sri Lanka<OPTION VALUE="sh">St. Helena<OPTION VALUE="pm">St. Pierre and Miquelon<OPTION VALUE="sd">Sudan<OPTION VALUE="sr">Suriname<OPTION VALUE="sj">Svalbard and Jan Mayen Islands<OPTION VALUE="sz">Swaziland<OPTION VALUE="se">Sweden<OPTION VALUE="ch">Switzerland<OPTION VALUE="sy">Syria<OPTION VALUE="tw">Taiwan<OPTION VALUE="tj">Tajikistan<OPTION VALUE="tz">Tanzania<OPTION VALUE="th">Thailand<OPTION VALUE="tg">Togo<OPTION VALUE="tk">Tokelau<OPTION VALUE="to">Tonga<OPTION VALUE="tt">Trinidad and Tobago<OPTION VALUE="tn">Tunisia<OPTION VALUE="tr">Turkey<OPTION VALUE="tm">Turkmenistan<OPTION VALUE="tc">Turks and Caicos Islands<OPTION VALUE="tv">Tuvalu<OPTION VALUE="ug">Uganda<OPTION VALUE="ua">Ukraine<OPTION VALUE="ae">United Arab Emirates<OPTION VALUE="uk">United Kingdom<OPTION VALUE="us" selected>United States<OPTION VALUE="uy">Uruguay<OPTION VALUE="um">US Minor Outlying Islands<OPTION VALUE="su">USSR (former)<OPTION VALUE="uz">Uzbekistan<OPTION VALUE="vu">Vanuatu<OPTION VALUE="va">Vatican City State (Holy See)<OPTION VALUE="ve">Venezuela<OPTION VALUE="vn">Viet Nam<OPTION VALUE="vg">Virgin Islands (British)<OPTION VALUE="vi">Virgin Islands (U.S.)<OPTION VALUE="wf">Wallis and Futuna Islands<OPTION VALUE="eh">Western Sahara<OPTION VALUE="ye">Yemen<OPTION VALUE="yu">Yugoslavia<OPTION VALUE="zr">Zaire<OPTION VALUE="zm">Zambia<OPTION VALUE="zw">Zimbabwe</SELECT></td>
             </tr><script language="JavaScript" type="text/JavaScript">';
	/*=-=[ Select user options ]=-=*/
	if (isset ($HTTP_COOKIE_VARS['language']) && $HTTP_COOKIE_VARS['language'] != "") 
		$to_print .= "frmLocale.language.value = '".$HTTP_COOKIE_VARS['language']."'; ";
	if (isset ($HTTP_COOKIE_VARS['location']) && $HTTP_COOKIE_VARS['location'] != "") 
		$to_print .= "frmLocale.location.value = '".$HTTP_COOKIE_VARS['location']."'; ";

	$to_print .= '</script><tr>
               <td colspan="2"><input type="submit" name="Submit" value="Set options"></td>
             </tr>
           </table>
	     </form>
';
	/*=-=[ < End Locale ]=-=*/

	/*=-=[ < Start Alert Configuration ]=-=*/
	$to_print .= '<table width="250"  border="0" cellspacing="1" cellpadding="0" id="cnt_alert">
                   <tr>
                     <td width="20" valign=top></td>
                     <td>Not enough access rights</td>
                   </tr>
               </table>
';
	/*=-=[ < End Alert Configuration ]=-=*/
	$to_print .= '</td></tr>
</table>
</body>
</html>';
	
	/*=-=[ Print HTML ]=-=*/
	print ($to_print );
?>