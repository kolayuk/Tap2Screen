<?php
/*
=====================================================
 DataLife Engine Nulled by M.I.D-Team
-----------------------------------------------------
 http://www.mid-team.ws/
-----------------------------------------------------
 Copyright (c) 2004,2010 SoftNews Media Group
=====================================================
 Данный код защищен авторскими правами
=====================================================
 Файл: addcomments.php
-----------------------------------------------------
 Назначение: Добавление комментариев в базу данных
=====================================================
*/
if( ! defined( 'DATALIFEENGINE' ) or $config['allow_comments'] != "yes" ) {
	die( "Hacking attempt!" );
}
require_once ENGINE_DIR . '/classes/parse.class.php';

$parse = new ParseFilter( );
$parse->safe_mode = true;
$parse->allow_url = $user_group[$member_id['user_group']]['allow_url'];
$parse->allow_image = $user_group[$member_id['user_group']]['allow_image'];

$_TIME = time() + ($config['date_adjust'] * 60);
$_IP = $db->safesql( $_SERVER['REMOTE_ADDR'] );

$name = $db->safesql( $parse->process( trim( $_POST['name'] ) ) );
$mail = $db->safesql( $parse->process( trim( $_POST['mail'] ) ) );
$post_id = intval( $_POST['post_id'] );
$stop = array ();

if( $is_logged ) {
	$name = $member_id['name'];
	$mail = $member_id['email'];
}


if( intval($config['comments_minlen']) AND strlen( $_POST['comments'] ) < $config['comments_minlen'] ) {

	$stop[] = $lang['news_err_40'];
	$CN_HALT = TRUE;

}

if( $config['allow_comments_wysiwyg'] != "yes" ) $comments = $db->safesql( $parse->BB_Parse( $parse->process( $_POST['comments'] ), false ) );
else {
	
	$parse->wysiwyg = true;
	
	$parse->ParseFilter( Array ('div', 'span', 'p', 'br', 'strong', 'em', 'ul', 'li', 'ol' ), Array (), 0, 1 );
	
	if( $user_group[$member_id['user_group']]['allow_url'] ) $parse->tagsArray[] = 'a';
	if( $user_group[$member_id['user_group']]['allow_image'] ) $parse->tagsArray[] = 'img';
	
	$comments = $db->safesql( $parse->BB_Parse( $parse->process( $_POST['comments'] ) ) );
}

if( ! $user_group[$member_id['user_group']]['captcha'] ) {
	$_SESSION['sec_code_session'] = 1;
	$_REQUEST['sec_code'] = 1;
}

if( $is_logged and ($member_id['restricted'] == 2 or $member_id['restricted'] == 3) ) {
	
	$stop[] = $lang['news_info_3'];
	$CN_HALT = TRUE;

}

if( strlen( $name ) > 50 ) {
	$stop[] = $lang['news_err_1'];
	$CN_HALT = TRUE;
}

if( strlen( $mail ) > 50 and ! $is_logged ) {
	$stop[] = $lang['news_err_2'];
	$CN_HALT = TRUE;
}
if( ! $post_id ) {
	$stop[] = $lang['news_err_id'];
	$CN_HALT = TRUE;
}
if( strlen( $comments ) > $config['comments_maxlen'] ) {
	$stop[] = $lang['news_err_3'];
	$CN_HALT = TRUE;
}
if( $_REQUEST['sec_code'] != $_SESSION['sec_code_session'] or ! $_SESSION['sec_code_session'] ) {
	$stop[] = $lang['news_err_30'];
	$CN_HALT = TRUE;
}

if( $comments == '' ) {
	$stop[] = $lang['news_err_11'];
	$CN_HALT = TRUE;
}

if( $parse->not_allowed_tags ) {
	$stop[] = $lang['news_err_33'];
	$CN_HALT = TRUE;
}

if( $parse->not_allowed_text ) {
	$stop[] = $lang['news_err_37'];
	$CN_HALT = TRUE;
}

// Проверка защиты от флуда
if( $member_id['user_group'] > 2 and intval( $config['flood_time'] ) and ! $CN_HALT ) {
	if( flooder( $_IP ) == TRUE ) {
		$stop[] = $lang['news_err_4'] . " " . $lang['news_err_5'] . " {$config['flood_time']} " . $lang['news_err_6'];
		$CN_HALT = TRUE;
	}
}

// Проверка на правильность новости
$row = $db->super_query( "SELECT id, date, allow_comm, approve, access from " . PREFIX . "_post WHERE id='$post_id'" );
$options = news_permission( $row['access'] );

if( (! $user_group[$member_id['user_group']]['allow_addc'] and $options[$member_id['user_group']] != 2) or $options[$member_id['user_group']] == 1 ) die( "Hacking attempt!" );

if( ! $row['id'] or ! $row['allow_comm'] or ! $row['approve'] ) {
	$stop[] = $lang['news_err_29'];
	$CN_HALT = TRUE;
}

if ( $config['max_comments_days'] ) {
	$row['date'] = strtotime( $row['date'] );

	if ($row['date'] < ($_TIME - ($config['max_comments_days'] * 3600 * 24)) ) {
		$stop[] = $lang['news_err_29'];
		$CN_HALT = TRUE;
	}
}

// Проверка является ли имя зарегистрированным
if( ! $is_logged and $CN_HALT != TRUE ) {
	$db->query( "SELECT name from " . USERPREFIX . "_users where LOWER(name) = '" . strtolower( $name ) . "'" );
	
	if( $db->num_rows() > 0 ) {
		$stop[] = $lang['news_err_7'];
		$CN_HALT = TRUE;
	}
	$db->free();
}

if( empty( $name ) and $CN_HALT != TRUE ) {
	$stop[] = $lang['news_err_9'];
	$CN_HALT = TRUE;
}

if( $mail != "" ) {
	if( !preg_match( "/^[\.A-z0-9_\-]+[@][A-z0-9_\-]+([.][A-z0-9_\-]+)+[A-z]{1,4}$/", $mail ) ) {
		$stop[] = $lang['news_err_10'];
		$CN_HALT = TRUE;
	}
}

//* Автоперенос длинных слов
if( intval( $config['auto_wrap'] ) ) {
	
	$comments = preg_split( '((>)|(<))', $comments, - 1, PREG_SPLIT_DELIM_CAPTURE );
	$n = count( $comments );
	
	for($i = 0; $i < $n; $i ++) {
		if( $comments[$i] == "<" ) {
			$i ++;
			continue;
		}
		
		$comments[$i] = preg_replace( "#([^\s\n\r]{" . intval( $config['auto_wrap'] ) . "})#i", "\\1<br />", $comments[$i] );
	}
	
	$comments = join( "", $comments );
	
//		$comments = preg_replace("#([^\s<>'\"/\.\\-\?&\n\r\%]{".intval($config['auto_wrap'])."})#i", "\\1<br />" ,$comments);


}

$time = date( "Y-m-d H:i:s", $_TIME );
$where_approve = 1;

$_SESSION['sec_code_session'] = 0;

// Добавление комментария
if( $CN_HALT ) {
	
	msgbox( $lang['all_err_1'], implode( "<br />", $stop ) . "<br /><br /><a href=\"javascript:history.go(-1)\">" . $lang['all_prev'] . "</a>" );

} else {
	
	$update_comments = false;

	if ( $config['allow_combine'] ) {
	
		$row = $db->super_query( "SELECT id, post_id, user_id, DATE_FORMAT(date,'%Y-%m-%d') as date, text, ip, is_register, approve FROM " . PREFIX . "_comments WHERE post_id = '$post_id' ORDER BY id DESC LIMIT 0,1" );
		
		if( $row['id'] ) {
			
			if( $row['user_id'] == $member_id['user_id'] and $row['is_register'] ) $update_comments = true;
			elseif( $row['ip'] == $_IP and ! $row['is_register'] and ! $is_logged ) $update_comments = true;
			
			if( $row['date'] != date( "Y-m-d", $_TIME ) ) $update_comments = false;
			
			if( ((strlen( $row['text'] ) + strlen( $comments )) > $config['comments_maxlen']) and $update_comments ) {
				$update_comments = false;
				$stop[] = $lang['news_err_3'];
				$CN_HALT = TRUE;
				msgbox( $lang['all_err_1'], implode( "<br />", $stop ) . "<br /><br /><a href=\"javascript:history.go(-1)\">" . $lang['all_prev'] . "</a>" );
			
			}
		
		}

	}
	
	if( ! $CN_HALT ) {
		
		if( $config['allow_cmod'] and $user_group[$member_id['user_group']]['allow_modc'] ) {
			
			if( $update_comments ) {
				if( $row['approve'] ) $update_comments = false;
			}
			
			$where_approve = 0;
			$stop[] = $lang['news_err_31'];
			$CN_HALT = TRUE;
			msgbox( $lang['all_info'], implode( "<br />", $stop ) . "<br /><br /><a href=\"javascript:history.go(-1)\">" . $lang['all_prev'] . "</a>" );
		
		}
		
		if( $update_comments ) {
			
			$comments = $db->safesql( $row['text'] ) . "<br /><br />" . $comments;
			$db->query( "UPDATE " . PREFIX . "_comments set text='{$comments}', approve='{$where_approve}' WHERE id='{$row['id']}'" );
		
		} else {
			
			if( $is_logged ) $db->query( "INSERT INTO " . PREFIX . "_comments (post_id, user_id, date, autor, email, text, ip, is_register, approve) values ('$post_id', '$member_id[user_id]', '$time', '$name', '$mail', '$comments', '$_IP', '1', '$where_approve')" );
			else $db->query( "INSERT INTO " . PREFIX . "_comments (post_id, date, autor, email, text, ip, is_register, approve) values ('$post_id', '$time', '$name', '$mail', '$comments', '$_IP', '0', '$where_approve')" );
			
			// обновление количества комментариев в новостях 
			if( $where_approve ) $db->query( "UPDATE " . PREFIX . "_post set comm_num=comm_num+1 where id='$post_id'" );
			
			// обновление количества комментариев у юзера 
			if( $is_logged ) {
				$db->query( "UPDATE " . USERPREFIX . "_users set comm_num=comm_num+1 where user_id ='$member_id[user_id]'" );
			}
		}
		

		if ( $config['mail_comments'] OR $config['allow_subscribe'] ) {

			include_once ENGINE_DIR . '/classes/mail.class.php';
			$mail = new dle_mail( $config );
			
			$row = $db->super_query( "SELECT template FROM " . PREFIX . "_email WHERE name='comments' LIMIT 0,1" );

			$row['template'] = stripslashes( $row['template'] );
			$row['template'] = str_replace( "{%username%}", $name, $row['template'] );
			$row['template'] = str_replace( "{%date%}", langdate( "j F Y H:i", $_TIME ), $row['template'] );
			$row['template'] = str_replace( "{%link%}", $config['http_home_url'] . "index.php?newsid=" . $post_id, $row['template'] );

			$body = str_replace( '\n', "", $comments );
			$body = str_replace( '\r', "", $body );
			
			$body = stripslashes( stripslashes( $body ) );
			$body = str_replace( "<br />", "\n", $body );
			$body = strip_tags( $body );
			
			$row['template'] = str_replace( "{%text%}", $body, $row['template'] );

		}

		if( $config['mail_comments'] ) {
			
			$body = str_replace( "{%ip%}", $_IP, $row['template'] );
			$body = str_replace( "{%username_to%}", $lang['admin'], $body );
			$body = str_replace( "{%unsubscribe%}", "--", $body );			
			$mail->send( $config['admin_mail'], $lang['mail_comments'], $body );
		
		}


		if ( $config['allow_subscribe'] ) {

			$row['template'] = str_replace( "{%ip%}", "--", $row['template'] );
			$found_subscribe = false;

			$db->query( "SELECT user_id, name, email, hash FROM " . PREFIX . "_subscribe WHERE news_id='{$post_id}'" );

			while($rec = $db->get_row())
			{
				if ($rec['user_id'] != $member_id['user_id'] ) {

					$body = str_replace( "{%username_to%}", $rec['name'], $row['template'] );
					$body = str_replace( "{%unsubscribe%}", $config['http_home_url'] . "index.php?do=unsubscribe&post_id=" . $post_id . "&user_id=" . $rec['user_id'] . "&hash=" . $rec['hash'], $body );
					$mail->send( $rec['email'], $lang['mail_comments'], $body );

				} else {

					$found_subscribe = true;

				}

			}

			$db->free();

			if ($_POST['allow_subscribe'] AND $user_group[$member_id['user_group']]['allow_subscribe'] AND !$found_subscribe) {

				$salt = "abchefghjkmnpqrstuvwxyz0123456789";
				srand( ( double ) microtime() * 1000000 );
				$s_hash = "";
				
				for($i = 0; $i < 5; $i ++) {
					$s_hash .= $salt{rand( 0, 33 )};
				}

				$s_hash = md5($s_hash);

				$db->query( "INSERT INTO " . PREFIX . "_subscribe (user_id, name, email, news_id, hash) values ('{$member_id['user_id']}', '{$member_id['name']}', '{$member_id['email']}', '{$post_id}', '{$s_hash}')" );

			}

		}
		
		// Защита от флуда
		if( $config['flood_time'] != 0 and $config['flood_time'] != "" ) {
			$db->query( "INSERT INTO " . PREFIX . "_flood (id, ip) values ('$_TIME', '$_IP')" );
		}
		
		clear_cache( 'news_' );
		if( $config['rss_informer'] ) clear_cache( 'informer_' );
		
		if( ! $ajax_adds AND ! $CN_HALT ) {
			header( "Location: {$_SERVER['REQUEST_URI']}" );
			die();
		}
	
	} else
		msgbox( $lang['all_err_1'], implode( "<br />", $stop ) . "<br /><br /><a href=\"javascript:history.go(-1)\">" . $lang['all_prev'] . "</a>" );

}
?>